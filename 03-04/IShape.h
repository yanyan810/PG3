#pragma once
#include <iostream>

class IShape {
public:
    virtual ~IShape() = default;

    // 面積を返す
    virtual float Size() const = 0;

    // 描画（今回はコンソール出力）
    virtual void Draw() const = 0;
};
