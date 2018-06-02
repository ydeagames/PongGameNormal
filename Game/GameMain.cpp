//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  Pong �m�[�}���ۑ�
//!
//! @date   2018/06/01
//!
//! @author GF1 26 �R�� ����
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"


// �񋓌^�̒�` ============================================================

// <�V�[�����> --------------------------------------------------------
enum GameState
{
	// �f��
	STATE_DEMO,

	// �T�[�u
	STATE_SERVE,

	// �v���C
	STATE_PLAY
};


// �萔�̒�` ==============================================================

// <�{�[��> ------------------------------------------------------------
#define BALL_VEL_X 6
#define BALL_VEL_Y 6
#define BALL_SIZE 8
#define BALL_Y_MANIPULATOR 1.f/3.f

// <�p�h��> ------------------------------------------------------------
#define PADDLE_VEL 6
#define PADDLE_WIDTH  8
#define PADDLE_HEIGHT 28


// �O���[�o���ϐ��̐錾 ====================================================

// <����> --------------------------------------------------------------
int g_input_state;

// <�V�[�����> --------------------------------------------------------
int g_game_state;

// <�{�[��> ------------------------------------------------------------
float g_ball_pos_x, g_ball_pos_y;
float g_ball_vel_x, g_ball_vel_y;

// <�p�h��1> -----------------------------------------------------------
float g_paddle1_pos_x, g_paddle1_pos_y;
float g_paddle1_vel_x, g_paddle1_vel_y;
float g_paddle1_target_pos_x, g_paddle1_target_pos_y;

// <�p�h��2> -----------------------------------------------------------
float g_paddle2_pos_x, g_paddle2_pos_y;
float g_paddle2_vel_x, g_paddle2_vel_y;
float g_paddle2_target_pos_x, g_paddle2_target_pos_y;


// �֐��̐錾 ==============================================================

// <�Q�[���̍X�V����> --------------------------------------------------
void UpdateGameDemo(void);
void UpdateGameServe(void);
void UpdateGamePlay(void);

void UpdateGameCommon(void);

float getTargetY(float paddle_enemy_pos_x, float paddle_myself_pos_x, int k);
int IsHit(float ball_pos_x, float ball_pos_y, float paddle_pos_x, float paddle_pos_y);

// <�Q�[���̕`�揈��> --------------------------------------------------
void RenderGameDemo(void);
void RenderGameServe(void);
void RenderGamePlay(void);

void RenderGameCommon(void);
void RenderObj(float x, float y, float w, float h, unsigned int color);

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	// �V�[�����
	g_game_state = STATE_DEMO;

	// �{�[��
	g_ball_pos_x = (float)(SCREEN_CENTER_X);
	g_ball_pos_y = (float)(SCREEN_CENTER_Y);
	g_ball_vel_x = BALL_VEL_X;
	g_ball_vel_y = BALL_VEL_Y;

	// �p�h��1
	g_paddle1_pos_x = (float)(SCREEN_LEFT + (PADDLE_WIDTH / 2 + 64));
	g_paddle1_pos_y = (float)(SCREEN_CENTER_Y);
	g_paddle1_vel_x = 0.f;
	g_paddle1_vel_y = 0.f;
	g_paddle1_target_pos_x = g_paddle1_pos_x;
	g_paddle1_target_pos_y = g_paddle1_pos_y;

	// �p�h��2
	g_paddle2_pos_x = (float)(SCREEN_RIGHT - (PADDLE_WIDTH / 2 + 64));
	g_paddle2_pos_y = (float)(SCREEN_CENTER_Y);
	g_paddle2_vel_x = 0.f;
	g_paddle2_vel_y = 0.f;
	g_paddle2_target_pos_x = g_paddle2_pos_x;
	g_paddle2_target_pos_y = g_paddle2_pos_y;
}


//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	// �L�[�{�[�h�擾
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

// <�Q�[���̍X�V����:�f��> ---------------------------------------------
void UpdateGameDemo(void)
{
	UpdateGameCommon();
}

// <�Q�[���̍X�V����:�T�[�u> -------------------------------------------
void UpdateGameServe(void)
{
	UpdateGameCommon();
}

// <�Q�[���̍X�V����:�v���C> -------------------------------------------
void UpdateGamePlay(void)
{
	UpdateGameCommon();
}

// <�Q�[���̋��ʍX�V> -------------------------------------------
void UpdateGameCommon(void)
{
	// ���W�X�V
	{
		// pos��vel�𑫂�
		g_ball_pos_x += g_ball_vel_x;
		g_ball_pos_y += g_ball_vel_y;

		// pos��vel�𑫂�
		g_paddle1_pos_x += g_paddle1_vel_x;
		g_paddle1_pos_y += g_paddle1_vel_y;

		// pos��vel�𑫂�
		g_paddle2_pos_x += g_paddle2_vel_x;
		g_paddle2_pos_y += g_paddle2_vel_y;
	}

	// �����蔻��
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
			g_ball_pos_x += g_ball_vel_x; // �ǂɂ߂荞�܂Ȃ��悤�ɏC��
		}
		if (g_ball_pos_y < SCREEN_TOP || SCREEN_BOTTOM <= g_ball_pos_y)
		{
			g_ball_vel_y *= -1.f;
			g_ball_pos_y += g_ball_vel_y; // �ǂɂ߂荞�܂Ȃ��悤�ɏC��
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
			// �ǂɂ߂荞�܂Ȃ��悤�ɒ���
			g_paddle1_pos_x = ClampF(g_paddle1_pos_x, padding_left, padding_right);
			g_paddle1_pos_y = ClampF(g_paddle1_pos_y, padding_top, padding_bottom);
		}
		{
			if (g_paddle2_pos_x < padding_left || padding_right <= g_paddle1_pos_x)
				g_paddle2_vel_x *= -1.f;
			if (g_paddle2_pos_y < padding_top || padding_bottom <= g_paddle2_pos_y)
				g_paddle2_vel_y *= -1.f;
			// �ǂɂ߂荞�܂Ȃ��悤�ɒ���
			g_paddle2_pos_x = ClampF(g_paddle2_pos_x, padding_left, padding_right);
			g_paddle2_pos_y = ClampF(g_paddle2_pos_y, padding_top, padding_bottom);
		}
	}
}

//----------------------------------------------------------------------
//! @brief �����蔻��
//!
//! @param[ball_pos_x] �{�[����X���W
//! @param[ball_pos_y] �{�[����Y���W
//! @param[paddle_pos_x] �p�h����X���W
//! @param[paddle_pos_y] �p�h����Y���W
//!
//! @return �����蔻�茋��
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
//! �{�[�����e�_�\�z�A���S���Y��
//!
//! @param[paddle_enemy_pos_x] �G�p�h����X���W
//! @param[paddle_myself_pos_x] ���p�h����X���W
//! @param[k] ���p�h��������{�[���̌��� (1: �E����, 2: ������)
//!
//! @return �\��Y���W
//----------------------------------------------------------------------
float getTargetY(float paddle_enemy_pos_x, float paddle_myself_pos_x, int k)
{
	// �{�[���A�p�h���T�C�Y���l�������G�p�h���A���p�h����X���W
	float enemy_pos_x, myself_pos_x;
	// �{�[�����牽px�Ŏ��p�h���ɓ�������̂����Z�o
	float length_x, length_y;
	// �{�[���̊�ʒu
	float ball_base_y;
	// �ڕW�̍��W
	float ball_absolute_y;
	// �{�[���̈ړ��\�͈�
	float screen_top_y, screen_bottom_y, screen_height;
	// �ڕW�̉�ʓ����W
	float target_pos_y;

	// �{�[���A�p�h���T�C�Y���l�������G�p�h���A���p�h����X���W
	{
		enemy_pos_x = paddle_myself_pos_x - k*(BALL_SIZE / 2 + PADDLE_WIDTH / 2);
		myself_pos_x = paddle_enemy_pos_x + k*(BALL_SIZE / 2 + PADDLE_WIDTH / 2);
	}

	{
		// �{�[�����牽px�Ŏ��p�h���ɓ�������̂����Z�o
		{
			length_x = 0;
			if (k*g_ball_vel_x > 0)
			{
				// �{�[�����E�ɐi��ł���Ƃ� �������G������
				// �{�[���`�G�܂ł̋��� (�s��)
				length_x += k*(enemy_pos_x - g_ball_pos_x);
				// �G�`�����̋��� (�A��)
				length_x += k*(enemy_pos_x - myself_pos_x);
			}
			else
			{
				// �{�[�������ɐi��ł���Ƃ� �G������
				// �{�[���`�����܂ł̋���
				length_x += k*(g_ball_pos_x - myself_pos_x);
			}
		}

		// ���˕Ԃ�𖳎������Ƃ��A���p�h���ɓ������{�[����Y���W
		{
			length_y = length_x / g_ball_vel_x * g_ball_vel_y;
			if (length_y < 0)
				length_y *= -1; // ��Βl
		}
	}

	// �{�[����Y���W
	{
		ball_base_y = g_ball_pos_y;
		if (g_ball_vel_y < 0)
			ball_base_y *= -1; // ���x��������̂Ƃ��A��Ƀ^�[�Q�b�g�����݂���
	}

	// �^�[�Q�b�g�̎Z�o
	ball_absolute_y = ball_base_y + length_y;

	{
		// �{�[���T�C�Y���l�������㉺�̕�
		screen_bottom_y = SCREEN_BOTTOM - BALL_SIZE / 2;
		screen_top_y = SCREEN_TOP + BALL_SIZE / 2;
		// �{�[���T�C�Y���l�������{�[���̈ړ��͈�
		screen_height = screen_bottom_y - screen_top_y;
	}

	// ��ʂ͈̔͊O��������height�������Ĕ͈͓��ɂ���
	// ���̂Ƃ��A����̉񐔂𐔂���
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

		// �͈͂𒲐�����񐔂���ł����Y���𒆐S�ɔ��]������
		if (count % 2 == 0)
			target_pos_y = pos_y_loop;
		else
			target_pos_y = screen_bottom_y - pos_y_loop;
	}

	return target_pos_y;
}


//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
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

// <�Q�[���̕`�揈��:�f��> ---------------------------------------------
void RenderGameDemo(void)
{
	RenderGameCommon();
}

// <�Q�[���̕`�揈��:�T�[�u> -------------------------------------------
void RenderGameServe(void)
{
	RenderGameCommon();
}

// <�Q�[���̕`�揈��:�v���C> -------------------------------------------
void RenderGamePlay(void)
{
	RenderGameCommon();
}

// <�Q�[���̋��ʕ`�揈��> ----------------------------------------------
void RenderGameCommon(void)
{
	// �K�C�h�\��
	RenderObj(g_paddle1_target_pos_x, g_paddle1_target_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x222222);
	RenderObj(g_paddle2_target_pos_x, g_paddle2_target_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x222222);

	// �{�[���\��
	RenderObj(g_ball_pos_x, g_ball_pos_y, BALL_SIZE, BALL_SIZE, COLOR_WHITE);

	// �p�h���\��
	RenderObj(g_paddle1_pos_x, g_paddle1_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
	RenderObj(g_paddle2_pos_x, g_paddle2_pos_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_WHITE);
}

//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�`��
//!
//! @param[x] X���W
//! @param[y] Y���W
//! @param[w] ��
//! @param[h] ����
//! @param[color] �F
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderObj(float x, float y, float w, float h, unsigned int color)
{
	DrawBox((int)(x - w / 2), (int)(y - h / 2), (int)(x + w / 2), (int)(y + h / 2), color, TRUE);
}


//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{

}
