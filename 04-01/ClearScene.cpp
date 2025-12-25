// ClearScene.cpp
#include "ClearScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include <Novice.h>

void ClearScene::Update(SceneManager& manager) {
    if (Novice::CheckHitKey(DIK_SPACE)) {
        manager.ChangeScene(std::make_unique<TitleScene>());
    }
}

void ClearScene::Draw() {
    Novice::ScreenPrintf(360, 300, "CLEAR!");
    Novice::ScreenPrintf(300, 340, "PRESS SPACE TO TITLE");
}
