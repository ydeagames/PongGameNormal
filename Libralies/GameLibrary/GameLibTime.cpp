//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibTime.cpp
//!
//! @brief  DxLibの時間関連への追加機能のソースファイル
//!
//! @date   2017/3/27
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <DxLib.h>




// 定数の定義 ==============================================================
#define ONE_SECOND 1000000    // 1秒 (=1,000,000μ秒)




// ファイルスコープ変数の定義 ==============================================
static float s_frameDeltaTime = 0.0f;    // フレームの経過時間[s]
static float s_frameRate      = 0.0f;    // フレームレート[fps]




// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief フレームタイマーの更新
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateFrameTimer(void)
{
	static LONGLONG previousTime = 0;                             // 前回の計測時間
	static LONGLONG currentTime  = GetNowHiPerformanceCount();    // 現在の計測時間
	static LONGLONG startTime    = 0;                             // フレームレート計測開始時間
	static int      frameCount   = 0;                             // フレーム数


	// 時間の計測
	previousTime = currentTime;
	currentTime  = GetNowHiPerformanceCount();


	// フレームの経過時間の更新
	s_frameDeltaTime = (float)(currentTime - previousTime) / ONE_SECOND;


	// 1秒毎にフレームレートの更新
	frameCount++;
	if ((currentTime - startTime) > ONE_SECOND)
	{
		s_frameRate = (float)(frameCount * ONE_SECOND) / (currentTime - startTime);
		startTime   = currentTime;
		frameCount  = 0;
	}
}



//------------------------------------------------------------------
//! @brief フレームの経過時間の取得
//!
//! @param[in] なし
//!
//! @return フレームの経過時間[s]
//------------------------------------------------------------------
float GetFrameDeltaTime(void)
{
	return s_frameDeltaTime;
}



//------------------------------------------------------------------
//! @brief フレームレートの取得
//!
//! @param[in] なし
//!
//! @return フレームレート[fps]
//------------------------------------------------------------------
float GetFrameRate(void)
{
	return s_frameRate;
}
