// SceneManager.cpp
#include "SceneManager.h"
#include "IScene.h"

void SceneManager::ChangeScene(std::unique_ptr<IScene> next) {
    current_ = std::move(next);
}

void SceneManager::Update() {
    if (current_) {
        current_->Update(*this);
    }
}

void SceneManager::Draw() {
    if (current_) {
        current_->Draw();
    }
}
