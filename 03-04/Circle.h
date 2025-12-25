#pragma once
#include "IShape.h"

class Circle : public IShape {
public:
    Circle(float radius) : radius_(radius) {}

    float Size() const override {
        return radius_ * radius_ * 3.14159f;
    }

    void Draw() const override {
        std::cout << "Circle Area: " << Size() << std::endl;
    }

private:
    float radius_;
};
