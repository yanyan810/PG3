#include "StageScene.h"

void StageScene::Init() {
	inputHandle_ = new InputHandle;

	//Assin command
	inputHandle_->AssignMoveLeftCommand2PressKeyA();
	inputHandle_->AssignMoveLeftCommand2PressKeyD();

	player_ = new Player();

	player_->Init();

}

void StageScene::Update() {

	command_ = inputHandle_->HandleInput();

	if (this->command_) {



		command_->Exec(*player_);
	}

	player_->Update();


}

void StageScene::Draw() {

	player_->Draw();

}