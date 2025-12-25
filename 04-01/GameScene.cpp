// GameScene.cpp
#include "GameScene.h"
#include "SceneManager.h"
#include "ClearScene.h"
#include <Novice.h>

void GameScene::Update(SceneManager& manager) {
    // 仮：Zキーで敵を倒したことにする
    if (Novice::CheckHitKey (DIK_Z)) {
        enemyCount_--;
    }

    if (enemyCount_ <= 0) {
        manager.ChangeScene(std::make_unique<ClearScene>());
    }
}

void GameScene::Draw() {
    Novice::ScreenPrintf(360, 300, "GAME");
    Novice::ScreenPrintf(360, 340, "ENEMY : %d", enemyCount_);
}
