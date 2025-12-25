#pragma once
#include <iostream>

class Animal {
public:
    virtual ~Animal() = default;

    virtual void Speak() const {
        std::cout << "動物が鳴く" << std::endl;
    }
};
