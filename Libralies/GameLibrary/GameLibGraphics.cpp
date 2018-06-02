//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibGraphics.cpp
//!
//! @brief  DxLibのグラフィック関連への追加機能のソースファイル
//!
//! @date   2017/3/27
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <DxLib.h>
#include <math.h>
#include <stdio.h>




// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief 破線を描画
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness)
{
	int vx = x2 - x1;
	int vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = (float)(length*cos(angle));
	float dy = (float)(length*sin(angle));

	int count = (int)(sqrt(vx*vx + vy*vy) / length);

	float x = (float)x1;
	float y = (float)y1;

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLine((int)x, (int)y, (int)(x + dx), (int)(y + dy), color, thickness))
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLine((int)x, (int)y, x2, y2, color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 破線を描画(アンチエイリアス効果付き)
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = (float)(length*cos(angle));
	float dy = (float)(length*sin(angle));

	int count = (int)(sqrt(vx*vx + vy*vy) / length);

	float x = x1;
	float y = y1;

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLineAA(x, y, (x + dx), (y + dy), color, thickness))
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLineAA(x, y, x2, y2, color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 画像ファイルのメモリへの読みこみ(エラー処理付き)
//!
//! @param[in] filename 読み込み対象の画像ファイルの名前
//!
//! @retval -1以外 グラフィックのハンドル
//! @retval -1     エラー発生
//----------------------------------------------------------------------
int LoadGraphWithErrorHandling(const char* filename)
{
	HGRP imageHandle = LoadGraph(filename);

	if (imageHandle == -1)
	{
		char errorMessage[MAX_PATH];
		snprintf(errorMessage, sizeof(errorMessage), "以下のファイルが見つかりません。\n\"%s\"", filename);
		MessageBox(NULL, errorMessage, NULL, MB_OK | MB_ICONEXCLAMATION);
		ExitGame();
	}

	return imageHandle;
}
