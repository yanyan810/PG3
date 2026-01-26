#pragma once
#include "Novice.h"

class Selector {
public:
    void Init() { mapX_ = 2; mapY_ = 2; mapSize_ = 32; }

    void Move(int dx, int dy) { mapX_ += dx; mapY_ += dy; }
    void SetMode(bool unitMode) { unitMode_ = unitMode; }
    bool IsUnitMode() const { return unitMode_; }

    int GetMapX() const { return mapX_; }
    int GetMapY() const { return mapY_; }
    int GetSize() const { return mapSize_; }

    void Draw() const {
        int x = mapX_ * mapSize_;
        int y = mapY_ * mapSize_;
        unsigned int col = RED; // ピンク枠（ABGR）

        // 枠だけ
        Novice::DrawBox(x, y, mapSize_, mapSize_, 0.0f, col, kFillModeWireFrame);
    }

    void SetMapPos(int x, int y) { mapX_ = x; mapY_ = y; }
private:
    int mapX_ = 0, mapY_ = 0, mapSize_ = 32;
    bool unitMode_ = false; // false=selector mode, true=unit mode
};
