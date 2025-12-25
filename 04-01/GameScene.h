// GameScene.h
#pragma once
#include "IScene.h"

class GameScene : public IScene {
public:
    void Update(SceneManager& manager) override;
    void Draw() override;

private:
    int enemyCount_ = 5;
};
