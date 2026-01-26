#include "Command.h"
#include "Selector.h"
#include "Unit.h"

void SelectorMoveCommand::Exec() { s_->Move(dx_, dy_); }

void UnitMoveCommand::Exec() { u_->Move(dx_, dy_); }
void UnitMoveCommand::Undo() { u_->Move(-dx_, -dy_); }
