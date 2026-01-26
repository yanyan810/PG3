#pragma once
#include <memory>
#include "ISceneCommand.h"

class Selector;
class Unit;

class StageSceneInputHandler {
public:
    void UpdateKeyState();

    std::unique_ptr<IStageSceneCommand> HandleSelector(Selector* selector);
    std::unique_ptr<IStageSceneCommand> HandleUnit(Unit* unit);

    bool TriggerDecide() const { return spaceTrig_; }
    bool TriggerUndo() const { return undoTrig_; }

private:
    bool a_ = false, d_ = false, w_ = false, s_ = false;
    bool aPrev_ = false, dPrev_ = false, wPrev_ = false, sPrev_ = false;
    bool aTrig_ = false, dTrig_ = false, wTrig_ = false, sTrig_ = false;
    bool space_ = false, spacePrev_ = false, spaceTrig_ = false;
    bool undoTrig_ = false;

    bool decidePrev_ = false;
    bool decideTrig_ = false;

};
