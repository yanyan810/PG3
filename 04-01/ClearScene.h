// ClearScene.h
#pragma once
#include "IScene.h"

class ClearScene : public IScene {
public:
    void Update(SceneManager& manager) override;
    void Draw() override;
};
