#include <Novice.h>
#include "Enemy.h"
#include "math.h"

const char kWindowTitle[] = "LC1B_21_ホリケ_ハヤト_確認課題13_01";

int Enemy::isAlive = true;

template <typename T>
struct Vector2 {
	T x;
	T y;
};

struct Circle {

	Vector2<int> pos = { 0, 0 };
	Vector2<int> speed = { 0, 0 };
	int radius = 16;
	int isShoot = false;

};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Enemy* enemyA = new Enemy(100, 200);
	Enemy* enemyB = new Enemy(200, 300);

	// プレイヤーの変数
	Circle player;
	player = {
		100, 600,
		5, 5,
		32,
		false
	};

	// 弾の変数
	Circle bullet[32];
	for (int i = 0; i < 32; i++) {
		bullet[i] = {
			0, 0,
			0, 5,
			16,
			false
		};
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// プレイヤーの移動処理
		if (keys[DIK_W]) {

			player.pos.y -= player.speed.y;

		}

		if (keys[DIK_S]) {

			player.pos.y += player.speed.y;

		}

		if (keys[DIK_A]) {

			player.pos.x -= player.speed.x;

		}

		if (keys[DIK_D]) {

			player.pos.x += player.speed.x;

		}

		// 弾の発射処理
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

			for (int i = 0; i < 32; i++) {
				if (!bullet[i].isShoot) {

					bullet[i].pos.x = player.pos.x;
					bullet[i].pos.y = player.pos.y;
					bullet[i].isShoot = true;
					break;

				}
			}
		}

		// rキーでリセット
		if (keys[DIK_R] && !preKeys[DIK_R]) {
			Enemy::isAlive = true;
		}

		for (int i = 0; i < 32; i++) {

			// 弾の移動処理
			if (bullet[i].isShoot) {
				bullet[i].pos.y -= bullet[i].speed.y;
			}

			// 画面外でリセット
			if (bullet[i].pos.y < 0.0f - bullet[i].radius) {

				bullet[i].isShoot = false;

			}
		}

		// 敵の移動処理
		if (Enemy::isAlive) {

			enemyA->Move();
			enemyB->Move();

		}

		// 当たり判定
		if (Enemy::isAlive) {
			for (int i = 0; i < 32; i++) {
				if (bullet[i].isShoot) {
					if (enemyA->radius_ + bullet[i].radius >=
						sqrtf(static_cast<float>(

							pow(enemyA->posX_ - bullet[i].pos.x, 2) +
							pow(enemyA->posY_ - bullet[i].pos.y, 2)))) {

						Enemy::isAlive = false;
						bullet[i].isShoot = false;
					}
				}
			}
		}

		if (Enemy::isAlive) {
			for (int i = 0; i < 32; i++) {
				if (bullet[i].isShoot) {
					if (enemyB->radius_ + bullet[i].radius >=
						sqrtf(static_cast<float>(

							pow(enemyB->posX_ - bullet[i].pos.x, 2) +
							pow(enemyB->posY_ - bullet[i].pos.y, 2)))) {

						Enemy::isAlive = false;
						bullet[i].isShoot = false;
					}
				}
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 敵の描画処理
		enemyA->Draw();
		enemyB->Draw();

		// 弾の描画処理
		for (int i = 0; i < 32; i++) {
			if (bullet[i].isShoot) {
				Novice::DrawEllipse(
					bullet[i].pos.x,
					bullet[i].pos.y,
					bullet[i].radius,
					bullet[i].radius,
					0.0f, 0xFF0000FF, kFillModeSolid
				);
			}
		}

		// プレイヤーの描画処理
		Novice::DrawEllipse(
			player.pos.x,
			player.pos.y,
			player.radius,
			player.radius,
			0.0f, 0xFFFFFFFF, kFillModeSolid
		);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete enemyA;
	delete enemyB;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
