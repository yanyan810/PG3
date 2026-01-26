#include "StageSceneInputHandler.h"
#include "Novice.h"
#include "Command.h"
#include "Selector.h"
#include "Unit.h"

void StageSceneInputHandler::UpdateKeyState() {

    bool aNow = (Novice::CheckHitKey(DIK_A) != 0) || (Novice::CheckHitKey(DIK_LEFT) != 0);
    bool dNow = (Novice::CheckHitKey(DIK_D) != 0) || (Novice::CheckHitKey(DIK_RIGHT) != 0);
    bool wNow = (Novice::CheckHitKey(DIK_W) != 0) || (Novice::CheckHitKey(DIK_UP) != 0);
    bool sNow = (Novice::CheckHitKey(DIK_S) != 0) || (Novice::CheckHitKey(DIK_DOWN) != 0);

    // ★トリガー（押した瞬間だけ true）
    aTrig_ = aNow && !aPrev_;
    dTrig_ = dNow && !dPrev_;
    wTrig_ = wNow && !wPrev_;
    sTrig_ = sNow && !sPrev_;

    // 次フレーム用に保存
    aPrev_ = aNow;
    dPrev_ = dNow;
    wPrev_ = wNow;
    sPrev_ = sNow;

    // Space は今のままでOK
    space_ = (Novice::CheckHitKey(DIK_SPACE) != 0);
    spaceTrig_ = space_ && !spacePrev_;
    spacePrev_ = space_;

    // Undo も “押した瞬間” にしたいなら prev を持つ（下に例）
    bool ctrl = (Novice::CheckHitKey(DIK_LCONTROL) != 0) || (Novice::CheckHitKey(DIK_RCONTROL) != 0);
    bool zNow = (Novice::CheckHitKey(DIK_Z) != 0);
    static bool undoPrev = false;              // 簡易（メンバにしてもOK）
    bool undoNow = ctrl && zNow;
    undoTrig_ = undoNow && !undoPrev;
    undoPrev = undoNow;

    bool decideNow = (Novice::CheckHitKey(DIK_RETURN) != 0); // Enter
    decideTrig_ = decideNow && !decidePrev_;
    decidePrev_ = decideNow;


}


std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::HandleSelector(Selector* selector) {
    if (aTrig_) return std::make_unique<SelectorMoveCommand>(selector, -1, 0);
    if (dTrig_) return std::make_unique<SelectorMoveCommand>(selector, +1, 0);
    if (wTrig_) return std::make_unique<SelectorMoveCommand>(selector, 0, -1);
    if (sTrig_) return std::make_unique<SelectorMoveCommand>(selector, 0, +1);
    return nullptr;
}

std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::HandleUnit(Unit* unit) {
    if (aTrig_) return std::make_unique<UnitMoveCommand>(unit, -1, 0);
    if (dTrig_) return std::make_unique<UnitMoveCommand>(unit, +1, 0);
    if (wTrig_) return std::make_unique<UnitMoveCommand>(unit, 0, -1);
    if (sTrig_) return std::make_unique<UnitMoveCommand>(unit, 0, +1);
    return nullptr;
}
