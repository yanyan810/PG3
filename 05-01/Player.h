#pragma once
#include "Novice.h"

class Player
{

	struct Vector {

		int x;
		int y;

	};

public:

	//Player();

	void Init();
	void Update();
	void Draw();


	void MoveRight();
	void MoveLeft();

private:

	Vector pos;
	int speed = 2;
	

};

