//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibInput.cpp
//!
//! @brief  DxLibの入力関連への追加機能のソースファイル
//!
//! @date   2017/7/1
//!
//! @author 高木 晋
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <DxLib.h>




// ファイルスコープ変数の定義 ==============================================
static int s_currentInputState;
static int s_lastInputState;




// 関数の定義 ==============================================================

//------------------------------------------------------------------
//! @brief ジョイパッドの入力状態の更新処理
//!
//! @param[in] なし
//!
//! @return なし
//------------------------------------------------------------------
void UpdateJoypadInputState(void)
{
	// 状態の履歴を保存
	s_lastInputState = s_currentInputState;


	// ゲームパッドの現在の状態を取得
	s_currentInputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されているかどうかを判断
//!
//! @param[in] button 判定したいボタンの入力マスク
//!
//! @retval TRUE  指定されたボタンが押されている場合
//! @retval FALSE それ以外の場合
//------------------------------------------------------------------
BOOL IsButtonDown(int button)
{
	if ((s_currentInputState & button) == button)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されていないかどうかを判断
//!
//! @param[in] button 判定したいボタンの入力マスク
//!
//! @retval TRUE  指定されたボタンが押されていない場合
//! @retval FALSE それ以外の場合
//------------------------------------------------------------------
BOOL IsButtonUp(int button)
{
	if ((s_currentInputState & button) != button)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが押されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの入力マスク
//!
//! @retval TRUE  指定されたキーが押された場合
//! @retval FALSE それ以外の場合
//------------------------------------------------------------------
BOOL IsButtonPressed(int button)
{
	if (((~s_lastInputState & s_currentInputState) & button) == button)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



//------------------------------------------------------------------
//! @brief 指定されたボタンが離されたかどうかを判断
//!
//! @param[in] button 判定したいボタンの入力マスク
//!
//! @retval TRUE  指定されたキーが離された場合
//! @retval FALSE それ以外の場合
//------------------------------------------------------------------
BOOL IsButtonReleased(int button)
{
	if (((s_lastInputState & ~s_currentInputState) & button) == button)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
