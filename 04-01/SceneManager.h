// SceneManager.h
#pragma once
#include <memory>

class IScene;

class SceneManager {
public:
    void ChangeScene(std::unique_ptr<IScene> next);
    void Update();
    void Draw();

private:
    std::unique_ptr<IScene> current_;
};
