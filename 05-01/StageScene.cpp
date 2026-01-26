#include "StageScene.h"
#include "Novice.h"
#include "StageSceneInputHandler.h"
#include "Selector.h"
#include "Unit.h"

void StageScene::Init() {
    input_ = std::make_unique<StageSceneInputHandler>();
    selector_ = std::make_unique<Selector>();
    selector_->Init();

    units_.clear();
    units_.push_back(std::make_unique<Unit>()); units_.back()->Init(18, 2, 0);
    units_.push_back(std::make_unique<Unit>()); units_.back()->Init(26, 1, 1);
    units_.push_back(std::make_unique<Unit>()); units_.back()->Init(18, 10, 2);
    units_.push_back(std::make_unique<Unit>()); units_.back()->Init(30, 14, 3);
    units_.push_back(std::make_unique<Unit>()); units_.back()->Init(8, 6, 4);

    // ★最初は選択なし
    SetSelected(nullptr);

    // ★最初はセレクタモードにしておく
    selector_->SetMode(false);
}

void StageScene::Update() {
    input_->UpdateKeyState();

    // ★Space：選択 / 解除
    if (input_->TriggerDecide()) {
        if (!selector_->IsUnitMode()) {
            // セレクタモード：重なったユニットを選択
            Unit* hit = FindUnitAtSelector();
            if (hit) {
                SetSelected(hit);
                selector_->SetMode(true); // ユニットモードへ（セレクタ非表示になる）
            }
        }
        else {
            // ★ユニットモード：解除 → セレクタをユニットの最終位置へ
            if (selectedUnit_) {
                selector_->SetMapPos(selectedUnit_->GetMapX(), selectedUnit_->GetMapY());
            }

            undoStack_.clear();

            SetSelected(nullptr);
            selector_->SetMode(false); // セレクタモードへ（セレクタ表示される）
        }
    }


    // Undo（ユニットモードのみ）
    if (input_->TriggerUndo() && selector_->IsUnitMode()) {
        if (!undoStack_.empty()) {
            undoStack_.back()->Undo();
            undoStack_.pop_back();
        }
    }

    // 入力→コマンド→実行
    std::unique_ptr<IStageSceneCommand> cmd;
    if (!selector_->IsUnitMode()) {
        cmd = input_->HandleSelector(selector_.get());
    }
    else {
        if (selectedUnit_) {
            cmd = input_->HandleUnit(selectedUnit_);
        }
    }

    if (cmd) {
        cmd->Exec();

        if (cmd->IsUndoable()) {
            // 上限を超えたら古いのを捨てる（任意）
            if ((int)undoStack_.size() >= maxUndo_) {
                undoStack_.erase(undoStack_.begin());
            }
            undoStack_.push_back(std::move(cmd));
        }
    }

}


void StageScene::DrawGrid() const {
    const int w = 1280;
    const int h = 720 - 64; // 下部UIの分ちょい空ける感じ
    // 背景
    Novice::DrawBox(0, 0, w, h, 0.0f, 0xFFB06A2B, kFillModeSolid); // ABGR: 青っぽい背景（好みで）
    // グリッド線（白）
    for (int x = 0; x <= w; x += tile_) {
        Novice::DrawLine(x, 0, x, h, 0xFFFFFFFF);
    }
    for (int y = 0; y <= h; y += tile_) {
        Novice::DrawLine(0, y, w, y, 0xFFFFFFFF);
    }
}

void StageScene::Draw() {
    DrawGrid();

    // ユニット
    for (auto& u : units_) u->Draw(tile_);

    // セレクタ
    if (!selector_->IsUnitMode()) {
        selector_->Draw();
    }

    // 下部UI
    const int baseY = 720 - 56;
    if (!selector_->IsUnitMode()) {
        Novice::ScreenPrintf(10, baseY, "WASD||arrow keys: move / space key: change unit mode");
        Novice::ScreenPrintf(10, baseY + 20, "In Selector Mode, you cannot use the 'Undo' action.");
    }
    else {
        int remain = (int)undoStack_.size();
        Novice::ScreenPrintf(10, baseY, "WASD||arrow keys: move / space key: change selector mode / ctrl+z: undo");
        Novice::ScreenPrintf(10, baseY + 20, "You have %d more 'UnDo' actions available.", remain);
    }

    if (!selectedUnit_) {
        Novice::ScreenPrintf(10, 720 - 76, "No unit selected. Move selector and press Enter.");
    }


}

Unit* StageScene::FindUnitAtSelector() const {
    const int sx = selector_->GetMapX();
    const int sy = selector_->GetMapY();
    for (auto& u : units_) {
        if (u->GetMapX() == sx && u->GetMapY() == sy) {
            return u.get();
        }
    }
    return nullptr;
}

void StageScene::SetSelected(Unit* u) {
    if (selectedUnit_) selectedUnit_->SetSelected(false);
    selectedUnit_ = u;
    if (selectedUnit_) selectedUnit_->SetSelected(true);
}

