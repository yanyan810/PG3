#pragma once
#include "InputHandle.h"
#include "Command.h"
#include "Player.h"


class StageScene
{
public:
	//StageScene();


	void Init();
	void Update();
	void Draw();

private:

	InputHandle* inputHandle_ = nullptr;
	Command* command_ = nullptr;
	Player* player_;

};

