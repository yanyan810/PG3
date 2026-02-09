#include "MapChipFiled.h"
#include <cassert>
#include <cstdint>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
// #include "Matrix4x4.h"

namespace {
std::map<std::string, MapChipField::MapChipType> mapChipTable = {
    {"0", MapChipField::MapChipType::kBlank},
    {"1", MapChipField::MapChipType::kBlock},
};

}

MapChipField::~MapChipField() {
	if (loader_.joinable()) {
		loader_.join();
	}
}

void MapChipField::LoadCsvTo_(const std::string& filePath, MapChipData& out) {
    // out を初期化（スレッド側のローカル結果）
    out.data.clear();
    out.data.resize(kNumBlockVirtical);
    for (auto& line : out.data) {
        line.resize(kNumBlockHorizontal, MapChipType::kBlank);
    }

    std::ifstream file(filePath);
    assert(file.is_open());

    std::stringstream ss;
    ss << file.rdbuf();

    for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
        std::string line;
        if (!std::getline(ss, line)) break;

        std::istringstream line_stream(line);

        for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
            std::string word;
            if (!std::getline(line_stream, word, ',')) break;

            if (mapChipTable.contains(word)) {
                out.data[i][j] = mapChipTable[word];
            }
        }
    }
}

void MapChipField::StartLoadMapChipCsvAsync(const std::string& filePath) {
    // すでに動いてたら一旦待つ（簡単運用）
    if (loader_.joinable()) {
        loader_.join();
    }

    loaded_ = false;
    loading_ = true;

    // pending_ をスレッドが作って、最後にロックして格納する
    loader_ = std::thread([this, filePath]() {
        MapChipData local;
        LoadCsvTo_(filePath, local);

        {
            std::lock_guard<std::mutex> lock(mtx_);
            pending_ = std::move(local);
        }

        loading_ = false;
        loaded_ = true;
        });
}

// メインスレッドから毎フレ呼ぶ：完了していたら差し替える
void MapChipField::UpdateAsync() {
    if (!loaded_.load()) return;

    // swap する（メインスレッド側のデータ更新）
    {
        std::lock_guard<std::mutex> lock(mtx_);
        mapChipData_ = std::move(pending_);
        pending_.data.clear();
    }

    // ここまで来たら、スレッドは終わってるはず。joinして後始末
    if (loader_.joinable()) {
        loader_.join();
    }

    // loaded_ を「取り込み完了」にしたいなら false に戻す運用でもOK
    // （今回は “読み込み完了状態” を維持するならこのままでOK）
}

// 既存の同期ロードも残すなら、そのまま（あなたの LoadMapChipCsv はOK）
void MapChipField::LoadMapChipCsv(const std::string& filePath) {
    ResetMapChipData();

    std::ifstream file;
    file.open(filePath);
    assert(file.is_open());

    std::stringstream mapChipCsv;
    mapChipCsv << file.rdbuf();
    file.close();

    for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
        std::string line;
        getline(mapChipCsv, line);

        std::istringstream line_stream(line);

        for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
            std::string word;
            getline(line_stream, word, ',');

            if (mapChipTable.contains(word)) {
                mapChipData_.data[i][j] = mapChipTable[word];
            }
        }
    }
}

MapChipField::IndexSet MapChipField::GetMapChipIndexByPosition(const KamataEngine::Vector3& position) const {
	MapChipField::IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((position.x + MapChipField::kBlockWidth / 2.0f) / MapChipField::kBlockWidth);

	indexSet.yIndex = static_cast<uint32_t>((MapChipField::kBlockHeight * (MapChipField::kNumBlockVirtical - 1) - position.y + MapChipField::kBlockHeight / 2.0f) / MapChipField::kBlockHeight);
	return indexSet;
}

void MapChipField::ResetMapChipData() {
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

MapChipField::MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) const {
	if (xIndex >= kNumBlockHorizontal || yIndex >= kNumBlockVirtical) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

KamataEngine::Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return KamataEngine::Vector3{
	    kBlockWidth * xIndex,
	    kBlockHeight * (kNumBlockVirtical - 1 - yIndex),
	    0.0f,
	};
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {

	KamataEngine::Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	MapChipField::Rect rect;
	rect.left = center.x - MapChipField::kBlockWidth / 2.0f;
	rect.right = center.x + MapChipField::kBlockWidth / 2.0f;
	rect.top = center.y - MapChipField::kBlockHeight / 2.0f;
	rect.bottom = center.y + MapChipField::kBlockHeight / 2.0f;

	return rect;
}