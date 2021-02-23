//#include "PlayerController.h"
//
//const float PlayerController::DEFAULT_MOVING_FORCE = 2.0f;
//
//PlayerController::PlayerController(PhysicsObject* po, Game::MonsterChaseGame* MC)
//{
//	po_ = po;
//	MC_ = MC;
//}
//
//void PlayerController::Move()
//{
//	if(MC_->isKey_D_Down)
//	po_->ApplyForce(Vector2(DEFAULT_MOVING_FORCE,0.0f));
//
//	if (MC_->isKey_A_Down)
//	po_->ApplyForce(Vector2(-DEFAULT_MOVING_FORCE, 0.0f));
//}
