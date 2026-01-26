#pragma once
#include "Command.h"

class InputHandle
{
public:
	Command* HandleInput();

	void AssignMoveLeftCommand2PressKeyA();

	void AssignMoveLeftCommand2PressKeyD();

private:

	Command* preKeyD;
	Command* preKeyA;

};

