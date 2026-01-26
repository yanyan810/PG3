#pragma once
class IStageSceneCommand {
public:
    virtual ~IStageSceneCommand() = default;
    virtual void Exec() = 0;
    virtual void Undo() {}             
    virtual bool IsUndoable() const { return false; }
};
