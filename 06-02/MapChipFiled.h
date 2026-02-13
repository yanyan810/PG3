#pragma once
#include "KamataEngine.h"
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <atomic>

using namespace KamataEngine;

class MapChipField {
public:
    enum class MapChipType {
        kBlank,
        kBlock
    };

    struct Rect {
        float left;
        float right;
        float bottom;
        float top;
    };

    struct MapChipData {
        std::vector<std::vector<MapChipType>> data;
    };

    struct IndexSet {
        uint32_t xIndex;
        uint32_t yIndex;
    };

    static inline const float kBlockWidth = 2.0f;
    static inline const float kBlockHeight = 2.0f;
    static inline const uint32_t kNumBlockVirtical = 20;
    static inline const uint32_t kNumBlockHorizontal = 100;

    void ResetMapChipData();
    void LoadMapChipCsv(const std::string& filePath);

    // 非同期ロード開始
    void StartLoadMapChipCsvAsync(const std::string& filePath);

    //ロード完了時適応
    bool ApplyLoadedIfReady();

    // ★追加：ロード中か
    bool IsLoading() const { return isLoading_.load(); }

    MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) const;
    KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

    uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }
    uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }

    IndexSet GetMapChipIndexByPosition(const KamataEngine::Vector3& position) const;
    Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

    // 終了時join用
    ~MapChipField();

private:
    MapChipData mapChipData_;

    // ★追加：非同期用
    std::thread worker_;
    std::mutex mutex_;
    std::atomic<bool> hasPending_{ false };
    std::atomic<bool> isLoading_{ false };
    MapChipData pending_;
};
