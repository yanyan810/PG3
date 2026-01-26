#pragma once
#include "Novice.h"

class Selector;

class Unit {
public:
    void Init(int x, int y, int id) { mapX_ = x; mapY_ = y; id_ = id; }
    void Move(int dx, int dy) { mapX_ += dx; mapY_ += dy; }

    int GetMapX() const { return mapX_; }
    int GetMapY() const { return mapY_; }
    void SetSelected(bool v) { isSelected_ = v; }

    void Draw(int tile) const {
        int x = mapX_ * tile;
        int y = mapY_ * tile;

        const int pad = 2; // グリッド線と被らないように
        Novice::DrawBox(x + pad, y + pad, tile - pad * 2, tile - pad * 2,
            0.0f, WHITE, kFillModeSolid);

        if (isSelected_) {
          
            Novice::DrawBox(x + pad, y + pad, tile - pad * 2, tile - pad * 2,
                0.0f, 0xFFB0B0FF, kFillModeSolid);
        }
    }
private:
    int mapX_ = 0, mapY_ = 0;
    int id_ = 0;
    bool isSelected_ = false;
};
