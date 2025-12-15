#pragma once
#include <iostream>
#include <cstddef> // size_t

class Enemy {
public:
    // enum class にする（課題スライドのやつ）
    enum class Phase : std::size_t {
        Approach = 0,
        Shoot,
        Withdrawal,
        Count
    };

    Enemy();
    void Update();

private:
    void Approach();
    void Shoot();
    void Withdrawal();

private:
    static void (Enemy::* spFuncTable[])();

    Phase phase_ = Phase::Approach; // ★これ1本にする
    int timer_ = 0;
};
