#pragma once
#include "ISceneCommand.h"
class Selector;
class Unit;

class SelectorMoveCommand : public IStageSceneCommand {
public:
    SelectorMoveCommand(Selector* s, int dx, int dy) : s_(s), dx_(dx), dy_(dy) {}
    void Exec() override;
private:
    Selector* s_ = nullptr;
    int dx_ = 0, dy_ = 0;
};

class UnitMoveCommand : public IStageSceneCommand {
public:
    UnitMoveCommand(Unit* u, int dx, int dy) : u_(u), dx_(dx), dy_(dy) {}
    void Exec() override;
    void Undo() override;
    bool IsUndoable() const override { return true; }
private:
    Unit* u_ = nullptr;
    int dx_ = 0, dy_ = 0;
};
