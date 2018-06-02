//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibGraphics.h
//!
//! @brief  DxLibのグラフィック関連への追加機能のヘッダファイル
//!
//! @date   2017/3/27
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 定数の定義 ==============================================================

// <色コード(標準カラー16色)> ----------------------------------------------
enum ColorCode : unsigned int
{
	COLOR_BLACK   = 0xFF000000,    // 黒色
	COLOR_NAVY    = 0xFF000080,    // 濃紺色
	COLOR_GREEN   = 0xFF008000,    // 緑色
	COLOR_TEAL    = 0xFF008080,    // 青緑色
	COLOR_MAROON  = 0xFF800000,    // マルーン色
	COLOR_PURPLE  = 0xFF800080,    // 紫色
	COLOR_OLIVE   = 0xFF808000,    // オリーブ色
	COLOR_GRAY    = 0xFF808080,    // 灰色
	COLOR_SILVER  = 0xFFC0C0C0,    // 銀色
	COLOR_BLUE    = 0xFF0000FF,    // 青色
	COLOR_LIME    = 0xFF00FF00,    // ライムグリーン色
	COLOR_AQUA    = 0xFF00FFFF,    // 水色
	COLOR_RED     = 0xFFFF0000,    // 赤色
	COLOR_FUCHSIA = 0xFFFF00FF,    // 赤紫色
	COLOR_YELLOW  = 0xFFFFFF00,    // 黄色
	COLOR_WHITE   = 0xFFFFFFFF,    // 白色
};




// 関数の宣言 ==============================================================

// <図形描画関連> ------------------------------------------------------

// 破線を描画
int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness);

// 破線を描画(アンチエイリアス効果付き)
int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness);


// <グラフィックデータ制御関連> ----------------------------------------

// 画像ファイルのメモリへの読みこみ(エラー処理付き)
int LoadGraphWithErrorHandling(const char* filename);
