#include "InputHandle.h"
#include "Novice.h"


void InputHandle::AssignMoveLeftCommand2PressKeyA() {

	Command* command = new MoveLeftCommand();
	this->preKeyA = command;
}

void InputHandle::AssignMoveLeftCommand2PressKeyD() {

	Command* command = new MoveRightCommand();
	this->preKeyD = command;
}

Command* InputHandle::HandleInput() {
	if (Novice::CheckHitKey(DIK_D)) {
		return preKeyD;

	}

	if (Novice::CheckHitKey(DIK_A)) {
		return preKeyA;

	}

	return nullptr;
}