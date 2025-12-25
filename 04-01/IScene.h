// IScene.h
#pragma once

class SceneManager;

class IScene {
public:
    virtual ~IScene() = default;

    virtual void Update(SceneManager& manager) = 0;
    virtual void Draw() = 0;
};
