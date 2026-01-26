#include "Player.h"

void Player::Init() {
    pos.x = 100;
    pos.y = 100;
}

void Player::Update() {
}

void Player::Draw() {
    Novice::DrawBox(pos.x, pos.y, 32, 32, 0.0f, WHITE, kFillModeSolid);
}

void Player::MoveLeft() {
    pos.x -= speed;
}

void Player::MoveRight() {
    pos.x += speed;
}
