#pragma once
#include "Unit.h"
#include "Selector.h"
#include "ISceneCommand.h"

class SelectorMoveCommand :public IStageSceneCommand {
public:
	SelectorMoveCommand(Selector* selector, int x, int y);

	void Exec() override;

private:
	Selector* selector;
	int x_;
	int y_;


};

class SelectUnitCommand :public IStageSceneCommand{
public:
	SelectUnitCommand(Selector* selector);
	void Exec() override;

private :
	Selector* selector_;

};

class UnintMoveCommand : public IStageSceneCommand {
public:
	UnintMoveCommand(Unit* unit, int x, int y);
	void Exec()override;
	
private:
	Unit* unit_;
	Selector* selector_;

	int x_;
	int y_;
};