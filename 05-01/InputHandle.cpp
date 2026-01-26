//#include "InputHandle.h"
//#include "Novice.h"
//
//InputHandle::InputHandle() = default;
//
//InputHandle::~InputHandle() {
//    delete preKeyA_;
//    delete preKeyD_;
//}
//
//void InputHandle::AssignMoveLeftCommand2PressKeyA() {
//    delete preKeyA_;               
//    preKeyA_ = new MoveLeftCommand();
//}
//
//void InputHandle::AssignMoveRightCommand2PressKeyD() {
//    delete preKeyD_;
//    preKeyD_ = new MoveRightCommand();
//}
//
//Command* InputHandle::HandleInput() {
//    if (Novice::CheckHitKey(DIK_D)) { return preKeyD_; }
//    if (Novice::CheckHitKey(DIK_A)) { return preKeyA_; }
//    return nullptr;
//}
