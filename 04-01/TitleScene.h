// TitleScene.h
#pragma once
#include "IScene.h"

class TitleScene : public IScene {
public:
    void Update(SceneManager& manager) override;
    void Draw() override;
};
