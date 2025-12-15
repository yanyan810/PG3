#include "Enemy.h"

void (Enemy::* Enemy::spFuncTable[])() = {
    &Enemy::Approach,
    &Enemy::Shoot,
    &Enemy::Withdrawal
};

Enemy::Enemy()
{
    std::cout << "[State] -> Approach\n";
}

void Enemy::Update() {
    // ★ enum class はそのまま添字にできないので size_t にキャスト
    (this->*spFuncTable[static_cast<std::size_t>(phase_)])();
}

void Enemy::Approach() {
    timer_++;
    if (timer_ >= 60) {
        phase_ = Phase::Shoot;
        timer_ = 0;
        std::cout << "[State] -> Shoot\n";
    }
}

void Enemy::Shoot() {
    timer_++;
    if (timer_ >= 30) {
        phase_ = Phase::Withdrawal;
        timer_ = 0;
        std::cout << "[State] -> Withdrawal\n";
    }
}

void Enemy::Withdrawal() {
    timer_++;
    if (timer_ >= 45) {
        // ここで終わりにするなら何もしないでもOK
        // ループさせたいなら phase_ = Phase::Approach; にする
    }
}
