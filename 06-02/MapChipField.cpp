#include "MapChipFiled.h"
#include <cassert>
#include <cstdint>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>


namespace {
std::map<std::string, MapChipField::MapChipType> mapChipTable = {
    {"0", MapChipField::MapChipType::kBlank},
    {"1", MapChipField::MapChipType::kBlock},
};

}

// デストラクタ
MapChipField::~MapChipField() {
	if (worker_.joinable()) {
		worker_.join();
	}
}

//非同期ロード開始
void MapChipField::StartLoadMapChipCsvAsync(const std::string& filePath) {

    // 連打対策：動いてたら回収（課題なら1回でもOK）
    if (worker_.joinable()) {
        worker_.join();
    }

    isLoading_ = true;
    hasPending_ = false;

    worker_ = std::thread([this, filePath]() {

        // localに読み込む（ワーカー専用）
        MapChipData local{};
        local.data.clear();
        local.data.resize(kNumBlockVirtical);
        for (auto& line : local.data) {
            line.resize(kNumBlockHorizontal, MapChipType::kBlank);
        }

        std::ifstream file(filePath);
        if (!file.is_open()) {
            // 別スレッドでassertは危ないのでやめる
            isLoading_ = false;
            return;
        }

        std::stringstream mapChipCsv;
        mapChipCsv << file.rdbuf();
        file.close();

        for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
            std::string line;
            if (!std::getline(mapChipCsv, line)) break;

            std::istringstream line_stream(line);

            for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
                std::string word;
                if (!std::getline(line_stream, word, ',')) break;

                if (mapChipTable.contains(word)) { // C++20
                    local.data[i][j] = mapChipTable[word];
                }
            }
        }

        // 結果をpendingへ（mutexで保護）
        {
            std::lock_guard<std::mutex> lock(mutex_);
            pending_ = std::move(local);
            hasPending_ = true;
        }

        isLoading_ = false;
        });
}

// メインスレッドで差し替え
bool MapChipField::ApplyLoadedIfReady() {
    if (!hasPending_) return false;

    std::lock_guard<std::mutex> lock(mutex_);
    mapChipData_ = std::move(pending_);
    pending_.data.clear();
    hasPending_ = false;
    return true;
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