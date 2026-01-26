#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <algorithm>

// ===== 共有状態 =====
std::mutex g_mtx;
std::condition_variable g_cvLoaded;
std::condition_variable g_cvQuery;
std::condition_variable g_cvResult;

std::vector<std::vector<int>> g_rows;  // CSV全行（数値）
bool g_loaded = false;

std::queue<std::vector<int>> g_queries; // 検索したい行パターン
std::queue<std::string> g_results;      // 表示用結果

std::atomic<bool> g_exit{ false };

// ===== 文字列の前後空白を削除 =====
static inline void Trim(std::string& s) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
}

static bool ParseIntRow(const std::string& line, std::vector<int>& out) {
    out.clear();

    // 1) 前後の空白を除去
    std::string s = line;
    Trim(s);
    if (s.empty()) return false;

    // 2) 先頭が '{' なら末尾の '}' を期待して外す（無くても一応通す）
    if (!s.empty() && s.front() == '{') {
        s.erase(s.begin());
        Trim(s);
        if (!s.empty() && s.back() == '}') {
            s.pop_back();
        }
        Trim(s);
    }

    // 3) カンマ区切りで int に変換
    std::stringstream ss(s);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        Trim(cell);
        if (cell.empty()) continue; // "{ ... }" で余計な空白があってもOK

        try {
            int v = std::stoi(cell);
            out.push_back(v);
        }
        catch (...) {
            return false;
        }
    }

    return !out.empty();
}


// ===== Loaderスレッド：CSVを読み込む =====
void LoadCSVThread(const std::string& path) {
    std::vector<std::vector<int>> local;

    std::ifstream ifs(path);
    if (!ifs) {
        std::lock_guard<std::mutex> lk(g_mtx);
        g_results.push("[ERROR] CSV open failed: " + path);
        g_loaded = true;
        g_cvLoaded.notify_all();
        g_cvResult.notify_all();
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        if (!ParseIntRow(line, row)) continue; // 変な行はスキップ

        local.push_back(std::move(row));
    }

    {
        std::lock_guard<std::mutex> lk(g_mtx);
        g_rows = std::move(local);
        g_loaded = true;
    }
    g_cvLoaded.notify_all();
}

// ===== Workerスレッド：行パターン一致で検索 =====
void MatchWorkerThread() {
    // 読み込み完了待ち
    {
        std::unique_lock<std::mutex> lk(g_mtx);
        g_cvLoaded.wait(lk, [] { return g_loaded; });
    }

    while (!g_exit.load()) {
        std::vector<int> q;

        // クエリ待ち
        {
            std::unique_lock<std::mutex> lk(g_mtx);
            g_cvQuery.wait(lk, [] { return g_exit.load() || !g_queries.empty(); });
            if (g_exit.load()) break;

            q = std::move(g_queries.front());
            g_queries.pop();
        }

        // 検索
        int hit = 0;
        std::ostringstream oss;

        {
            std::lock_guard<std::mutex> lk(g_mtx);
            std::cout << "=== ALL ROWS ===\n";
            for (size_t i = 0; i < g_rows.size(); ++i) {
                std::cout << "[" << i << "] ";
                for (size_t c = 0; c < g_rows[i].size(); ++c) {
                    std::cout << g_rows[i][c];
                    if (c + 1 < g_rows[i].size()) std::cout << ",";
                }
                std::cout << "\n";
            }
            std::cout << "==============\n";
        }



        if (hit == 0) {
            oss << "NOT FOUND\n";
        }
        else {
            oss << "HITS: " << hit << "\n";
        }

        {
            std::lock_guard<std::mutex> lk(g_mtx);
            g_results.push(oss.str());
        }
        g_cvResult.notify_one();
    }
}

int main() {
    const std::string csvPath = "data.csv"; // 同じフォルダに置く想定

    std::thread loader(LoadCSVThread, csvPath);
    std::thread worker(MatchWorkerThread);

    // 読み込み完了待ち
    {
        std::unique_lock<std::mutex> lk(g_mtx);
        g_cvLoaded.wait(lk, [] { return g_loaded; });
    }

    {
        std::lock_guard<std::mutex> lk(g_mtx);

        std::cout << "rows=" << g_rows.size() << "\n";
        std::cout << "=== ALL ROWS ===\n";
        for (size_t i = 0; i < g_rows.size(); ++i) {
            std::cout << "[" << i << "] ";
            for (size_t c = 0; c < g_rows[i].size(); ++c) {
                std::cout << g_rows[i][c];
                if (c + 1 < g_rows[i].size()) std::cout << ",";
            }
            std::cout << "\n";
        }
        std::cout << "==============\n";
    }


    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;
        if (line.empty()) continue;

        std::vector<int> q;
        if (!ParseIntRow(line, q)) {
            std::cout << "[INPUT ERROR] Use comma-separated integers.\n";
            continue;
        }

        // クエリ投入
        {
            std::lock_guard<std::mutex> lk(g_mtx);
            g_queries.push(std::move(q));
        }
        g_cvQuery.notify_one();

        // 結果待ち→表示
        std::string res;
        {
            std::unique_lock<std::mutex> lk(g_mtx);
            g_cvResult.wait(lk, [] { return !g_results.empty(); });
            res = std::move(g_results.front());
            g_results.pop();
        }
        std::cout << res;
    }

    // 終了
    g_exit.store(true);
    g_cvQuery.notify_all();

    loader.join();
    worker.join();
    return 0;
}
