// TitleScene.cpp
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <Novice.h>

void TitleScene::Update(SceneManager& manager) {
    if (Novice::CheckHitKey(DIK_SPACE)) {
        manager.ChangeScene(std::make_unique<GameScene>());
    }
}

void TitleScene::Draw() {
    Novice::ScreenPrintf(400, 300, "TITLE");
    Novice::ScreenPrintf(360, 340, "PRESS SPACE");
}
