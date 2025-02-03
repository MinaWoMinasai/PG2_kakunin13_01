#include "Enemy.h"
#include "Novice.h"

// 画面の端
const int LeftX = 0;
const int RightX = 1280;

Enemy::Enemy(int posX, int posY) {

	posX_ = posX;
	posY_ = posY;

}

void Enemy::Move() {

	// 横へ移動
	posX_ += speedX_;

	// 壁で反転
	if (posX_ < LeftX +  radius_ ||
		posX_ > RightX - radius_) {

		speedX_ = -speedX_;

	}
}

void Enemy::Draw() {

	if (Enemy::isAlive) {
		Novice::DrawEllipse(
			posX_, posY_,
			radius_, radius_,
			0.0f, 0xFFFFFFFF, kFillModeSolid
		);
	}

}