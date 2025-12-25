#pragma once
#include "Animal.h"

class Cat : public Animal {
public:
    void Speak() const override {
        std::cout << "猫：ニャー" << std::endl;
    }
};
