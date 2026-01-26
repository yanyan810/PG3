#pragma once
#include <memory>
#include <vector>
#include "StageSceneInputHandler.h"
#include "Selector.h"
#include "Unit.h"
#include "ISceneCommand.h"

class StageScene {
public:
    void Init();
    void Update();
    void Draw();

private:
    void DrawGrid() const;

    std::unique_ptr<StageSceneInputHandler> input_;
    std::unique_ptr<Selector> selector_;
    std::vector<std::unique_ptr<Unit>> units_;

    Unit* selectedUnit_ = nullptr;


    std::vector<std::unique_ptr<IStageSceneCommand>> undoStack_;
    int maxUndo_ = 999999; 
    Unit* FindUnitAtSelector() const;
    void SetSelected(Unit* u);

    int tile_ = 32;
};
