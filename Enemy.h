#pragma once
class Enemy
{

public:

	// 静的メンバ変数の宣言
	static int isAlive;
	
	// コンストラクタ
	Enemy(int posX, int posY);

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	// メンバ変数
	int posX_ = 0;
	int posY_ = 0;
	int speedX_ = 8;
	int radius_ = 16;

};

