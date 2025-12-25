#pragma once
#include "IShape.h"

class Rectangle : public IShape {
public:
    Rectangle(float w, float h) : width_(w), height_(h) {}

    float Size() const override {
        return width_ * height_;
    }

    void Draw() const override {
        std::cout << "Rectangle Area: " << Size() << std::endl;
    }

private:
    float width_;
    float height_;
};
