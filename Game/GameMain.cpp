//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  Pong ノーマル課題
//!
//! @date   2018/06/01
//!
//! @author GF1 26 山口 寛雅
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"


// 列挙型の定義 ============================================================

// <シーン状態> --------------------------------------------------------
enum GameState
{
	// デモ
	STATE_DEMO,

	// サーブ
	STATE_SERVE,

	// プレイ
	STATE_PLAY
};


// 定数の定義 ==============================================================

// <ボール> ------------------------------------------------------------
#define BALL_VEL_X 6
#define BALL_VEL_Y 6
#define BALL_SIZE 8
#define BALL_Y_MANIPULATOR 1.f/3.f

// <パドル> ------------------------------------------------------------
#define PADDLE_VEL 6
#define PADDLE_WIDTH  8
#define PADDLE_HEIGHT 28


// グローバル変数の宣言 ====================================================

// <入力> --------------------------------------------------------------
int g_input_state;

// <シーン状態> --------------------------------------------------------
int g_game_state;

// <ボール> ------------------------------------------------------------
float g_ball_pos_x, g_ball_pos_y;
float g_ball_vel_x, g_ball_vel_y;

// <パドル1> -----------------------------------------------------------
float g_paddle1_pos_x, g_paddle1_pos_y;
float g_paddle1_vel_x, g_paddle1_vel_y;
float g_paddle1_target_pos_x, g_paddle1_target_pos_y;

// <パドル2> -----------------------------------------------------------
float g_paddle2_pos_x, g_paddle2_pos_y;
float g_paddle2_vel_x, g_paddle2_vel_y;
float g_paddle2_target_pos_x, g_paddle2_target_pos_y;


// 関数の宣言 ==============================================================

// <ゲームの更新処理> --------------------------------------------------
void UpdateGameDemo(void);
void UpdateGameServe(void);
void UpdateGamePlay(void);

void UpdateGameCommon(void);

float getTargetY(float paddle_enemy_pos_x, float paddle_myself_pos_x, int k);
int IsHit(float ball_pos_x, float ball_pos_y, float paddle_pos_x, float paddle_pos_y);

// <ゲームの描画処理> --------------------------------------------------
void RenderGameDemo(void);
void RenderGameServe(void);
void RenderGamePlay(void);

void RenderGameCommon(void);
void RenderObj(float x, float y, float w, float h, unsigned int color);

// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	// シーン状態
	g_game_state = STATE_DEMO;

	// ボール
	g_ball_pos_x = (float)(SCREEN_CENTER_X);
	g_ball_pos_y = (float)(SCREEN_CENTER_Y);
	g_ball_vel_x = BALL_VEL_X;
	g_ball_vel_y = BALL_VEL_Y;

	// パドル1
	g_paddle1_pos_x = (float)(SCREEN_LEFT + (PADDLE_WIDTH / 2 + 64));
	g_paddle1_pos_y = (float)(SCREEN_CENTER_Y);
	g_paddle1_vel_x = 0.f;
	g_paddle1_vel_y = 0.f;
	g_paddle1_target_pos_x = g_paddle1_pos_x;
	g_paddle1_target_pos_y = g_paddle1_pos_y;

	// パドル2
	g_paddle2_pos_x = (float)(SCREEN_RIGHT - (PADDLE_WIDTH / 2 + 64));
	g_paddle2_pos_y = (float)(SCREEN_CENTER_Y);
	g_paddle2_vel_x = 0.f;
	g_paddle2_vel_y = 0.f;
	g_paddle2_target_pos_x = g_paddle2_pos_x;
	g_paddle2_target_pos_y = g_paddle2_pos_y;
}


//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	// キーボード取得
	g_input_state = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	switch (g_game_state)
	{
	case STATE_DEMO:
		UpdateGameDemo();
		break;
	case STATE_SERVE:
		UpdateGameServe();
		break;
	case STATE_PLAY:
		UpdateGamePlay();
		break;
	}
}

// <ゲームの更新処理:デモ> ---------------------------------------------
void UpdateGameDemo(void)
{
	UpdateGameCommon();
}

// <ゲームの更新処理:サーブ> -------------------------------------------
void UpdateGameServe(void)
{
	UpdateGameCommon();
}

// <ゲームの更新処理:プレイ> -------------------------------------------
void UpdateGamePlay(void)
{
	UpdateGameCommon();
}

// <ゲームの共通更新> -------------------------------------------
void UpdateGameCommon(void)
{
	// 座標更新
	{
		// posにvelを足す
		g_ball_pos_x += g_ball_vel_x;
		g_ball_pos_y += g_ball_vel_y;

		// posにvelを足す
		g_paddle1_pos_x += g_paddle1_vel_x;
		g_paddle1_pos_y += g_paddle1_vel_y;

		// posにvelを足す
		g_paddle2_pos_x += g_paddle2_vel_x;
		g_paddle2_pos_y += g_paddle2_vel_y;
	}

	// 当たり判定
	{
		if (IsHit(g_ball_pos_x, g_ball_pos_y, g_paddle1_pos_x, g_paddle1_pos_y))
		{
			g_ball_vel_x *= -1;

			g_ball_vel_y = (g_ball_pos_y - g_paddle1_pos_y) / 3;

			if (g_ball_vel_x < 0)
				g_ball_pos_x = g_paddle1_pos_x - PADDLE_WIDTH / 2 - BALL_SIZE / 2;
			else
				g_ball_pos_x = g_paddle1_pos_x + PADDLE_WIDTH / 2 + BALL_SIZE / 2;
		}
		else if (IsHit(g_ball_pos_x, g_ball_pos_y, g_paddle2_pos_x, g_paddle2_pos_y))
		{
			g_ball_vel_x *= -1;

			g_ball_vel_y = (g_ball_pos_y - g_paddle2_pos_y) / 3;

			if (g_ball_vel_x < 0)
				g_ball_pos_x = g_paddle2_pos_x - PADDLE_WIDTH / 2 - BALL_SIZE / 2;
			else
				g_ball_pos_x = g_paddle2_pos_x + PADDLE_WIDTH / 2 + BALL_SIZE / 2;
		}
	}

	{
		//*
		if (g_ball_pos_x < SCREEN_LEFT || SCREEN_RIGHT <= g_ball_pos_x)
		{
			g_ball_vel_x *= -1.f;
			g_ball_pos_x += g_ball_vel_x; // 壁にめり込まないように修正
		}
		if (g_ball_pos_y < SCREEN_TOP || SCREEN_BOTTOM <= g_ball_pos_y)
		{
			g_ball_vel_y *= -1.f;
			g_ball_pos_y += g_ball_vel_y; // 壁にめり込まないように修正
		}
		g_paddle1_pos_x = ClampF(g_paddle1_pos_x, padding_left, padding_right);
		g_paddle1_pos_y = ClampF(g_paddle1_pos_y, padding_top, padding_bottom);

		float padding_left = SCREEN_LEFT + (PADDLE_WIDTH / 2);
		float padding_right = SCREEN_RIGHT - (PADDLE_WIDTH / 2);
		float padding_top = SCREEN_TOP + (PADDLE_HEIGHT / 2);
		float padding_bottom = SCREEN_BOTTOM - (PADDLE_HEIGHT / 2);
		{
			if (g_paddle1_pos_x < padding_left || padding_right <= g_paddle1_pos_x)
				g_paddle1_vel_x *= -1.f;
			if (g_paddle1_pos_y < padding_top || padding_bottom <= g_paddle1_pos_y)
				g_paddle1_vel_y *= -1.f;
			// 壁にめり込まないように調整
			g_paddle1_pos_x = ClampF(g_paddle1_pos_x, padding_left, padding_right);
			g_paddle1_pos_y = ClampF(g_paddle1_pos_y, padding_top, padding_bottom);
		}
		{
			if (g_paddle2_pos_x < padding_left || padding_right <= g_paddle1_pos_x)
				g_paddle2_vel_x *= -1.f;
			if (g_paddle2_pos_y < padding_top || padding_bottom <= g_paddle2_pos_y)
				g_paddle2_vel_y *= -1.f;
			// 壁にめり込まないように調整
			g_paddle2_pos_x = ClampF(g_paddle2_pos_x, padding_left, padding_right);
			g_paddle2_pos_y = ClampF(g_paddle2_pos_y, padding_top, padding_bottom);
		}
	}
}

//----------------------------------------------------------------------
//! @brief 当たり判定
//!
//! @param[ball_pos_x] ボールのX座標
//! @param[ball_pos_y] ボールのY座標
//! @param[paddle_pos_x] パドルのX座標
//! @param[paddle_pos_y] パドルのY座標
//!
//! @return 当たり判定結果
//----------------------------------------------------------------------
int IsHit(float ball_pos_x, float ball_pos_y, float paddle_pos_x, float paddle_pos_y)
{
	float b_x1 = ball_pos_x - BALL_SIZE / 2;
	float b_y1 = ball_pos_y - BALL_SIZE / 2;
	float b_x2 = ball_pos_x + BALL_SIZE / 2;
	float b_y2 = ball_pos_y + BALL_SIZE / 2;

	float p_x1 = paddle_pos_x - PADDLE_WIDTH / 2;
	float p_y1 = paddle_pos_y - PADDLE_HEIGHT / 2;
	float p_x2 = paddle_pos_x + PADDLE_WIDTH / 2;
	float p_y2 = paddle_pos_y + PADDLE_HEIGHT / 2;

	return (p_x1 < b_x2&&b_x1 < p_x2&&p_y1 < b_y2&&b_y1 < p_y2);
}

//----------------------------------------------------------------------
//! @brief Bot AI
//! ボール着弾点予想アルゴリズム
//!
//! @param[paddle_enemy_pos_x] 敵パドルのX座標
//! @param[paddle_myself_pos_x] 自パドルのX座標
//! @param[k] 自パドルから放つボールの向き (1: 右向き, 2: 左向き)
//!
//! @return 予測Y座標
//----------------------------------------------------------------------
float getTargetY(float paddle_enemy_pos_x, float paddle_myself_pos_x, int k)
{
	// ボール、パドルサイズを考慮した敵パドル、自パドルのX座標
	float enemy_pos_x, myself_pos_x;
	// ボールから何pxで自パドルに到着するのかを算出
	float length_x, length_y;
	// ボールの基準位置
	float ball_base_y;
	// 目標の座標
	float ball_absolute_y;
	// ボールの移動可能範囲
	float screen_top_y, screen_bottom_y, screen_height;
	// 目標の画面内座標
	float target_pos_y;

	// ボール、パドルサイズを考慮した敵パドル、自パドルのX座標
	{
		enemy_pos_x = paddle_myself_pos_x - k*(BALL_SIZE / 2 + PADDLE_WIDTH / 2);
		myself_pos_x = paddle_enemy_pos_x + k*(BALL_SIZE / 2 + PADDLE_WIDTH / 2);
	}

	{
		// ボールから何pxで自パドルに到着するのかを算出
		{
			length_x = 0;
			if (k*g_ball_vel_x > 0)
			{
				// ボールが右に進んでいるとき 自分→敵→自分
				// ボール～敵までの距離 (行き)
				length_x += k*(enemy_pos_x - g_ball_pos_x);
				// 敵～自分の距離 (帰り)
				length_x += k*(enemy_pos_x - myself_pos_x);
			}
			else
			{
				// ボールが左に進んでいるとき 敵→自分
				// ボール～自分までの距離
				length_x += k*(g_ball_pos_x - myself_pos_x);
			}
		}

		// 跳ね返りを無視したとき、自パドルに到着時ボールのY座標
		{
			length_y = length_x / g_ball_vel_x * g_ball_vel_y;
			if (length_y < 0)
				length_y *= -1; // 絶対値
		}
	}

	// ボールのY座標
	{
		ball_base_y = g_ball_pos_y;
		if (g_ball_vel_y < 0)
			ball_base_y *= -1; // 速度が上向きのとき、上にターゲットが存在する
	}

	// ターゲットの算出
	ball_absolute_y = ball_base_y + length_y;

	{
		// ボールサイズを考慮した上下の壁
		screen_bottom_y = SCREEN_BOTTOM - BALL_SIZE / 2;
		screen_top_y = SCREEN_TOP + BALL_SIZE / 2;
		// ボールサイズを考慮したボールの移動範囲
		screen_height = screen_bottom_y - screen_top_y;
	}

	// 画面の範囲外だったらheightずつ足して範囲内にする
	// このとき、操作の回数を数える
	{
		int count = 0;
		float pos_y_loop = ball_absolute_y;
		while (pos_y_loop < screen_top_y)
		{
			pos_y_loop += screen_height;
			count++;
		}
		while (pos_y_loop > screen_bottom_y)
		{
			pos_y_loop -= screen_height;
			count++;
		}

		// 範囲を調整する回数が奇数であればY軸を中心に反転させる
		if (count % 2 == 0)
			target_pos_y = pos_y_loop;
		else
			target_pos_y = screen_bottom_y - pos_y_loop;
	}

	return target_pos_y;
}


//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
	switch (g_game_state)
	{
	case STATE_DEMO:
		RenderGameDemo();
		break;
	case STATE_SERVE:
		RenderGameServe();
		break;
	case STATE_PLAY:
		RenderGamePlay();
		break;
	}
}

// <ゲームの描画処理:デモ> ---------------------------------------------
void RenderGameDemo(void)
{
	RenderGameCommon();
}

// <ゲームの描画処理:サーブ> -------------------------------------------
void RenderGameServe(void)
{
	RenderGameCommon();
}

// <ゲームの描画処理:プレイ> -------------------------------------------
void RenderGamePlay(void)
{
	RenderGameCommon();
}

// <ゲームの共通描画処理> ----------------------------------------------
void RenderGameCommon(void)
{
	// ガイド表示
	RenderObj(g_paddle1_target_pos_x, g_paddle1_target_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x222222);
	RenderObj(g_paddle2_target_pos_x, g_paddle2_target_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x222222);

	// ボール表示
	RenderObj(g_ball_pos_x, g_ball_pos_y, BALL_SIZE, BALL_SIZE, COLOR_WHITE);

	// パドル表示
	RenderObj(g_paddle1_pos_x, g_paddle1_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
	RenderObj(g_paddle2_pos_x, g_paddle2_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
}

//----------------------------------------------------------------------
//! @brief オブジェクト描画
//!
//! @param[x] X座標
//! @param[y] Y座標
//! @param[w] 幅
//! @param[h] 高さ
//! @param[color] 色
//!
//! @return なし
//----------------------------------------------------------------------
void RenderObj(float x, float y, float w, float h, unsigned int color)
{
	DrawBox((int)(x - w / 2), (int)(y - h / 2), (int)(x + w / 2), (int)(y + h / 2), color, TRUE);
}


//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{

}
