/********************************************************************
** ��T�� �~�j�Q�[��������i�Q�j
** ���[�X�������Q�[
********************************************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
/***********************************************
* �ϐ��̐錾
***********************************************/
int g_OldKey; // �O��̓��̓L�[
int g_NowKey; // ����̓��̓L�[
int g_KeyFlg; // ���̓L�[���
int g_GameState = 0; // �Q�[�����[�h
int g_TitleImage; // �摜�p�ϐ�
int g_Menu, g_Cone, g_Help, g_End, g_Clear, g_Over; //���j���[�摜�ϐ�

/***********************************************
* �֐��̃v���g�^�C�v�錾
***********************************************/
void GameInit(void); //�Q�[������������
void GameMain(void); //�Q�[�����C������
void DrawGameTitle(void); //�^�C�g���`�揈��
void DrawGameOver(void); //�Q�[���I�[�o�[��ʕ`�揈��
void DrawEnd(void); //�Q�[���G���h�`�揈��
void DrawHelp(void); //�Q�[���w���v�`�揈��
void DrawRanking(void); //�����L���O�`�揈��
void InputRanking(void); //�����L���O����
int LoadImages(); // �摜�Ǎ���

/***********************************************
* �v���O�����̊J�n
***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("PacMan"); // �^�C�g����ݒ�
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ŋN��
	if (DxLib_Init() == -1) return -1; // DX ���C�u�����̏���������
	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���
	if (LoadImages() == -1) return -1; // �摜�Ǎ��݊֐����Ăяo��
									   // �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
		ClearDrawScreen(); // ��ʂ̏�����
		switch (g_GameState) {
		case 0:
			DrawGameTitle(); //�Q�[���^�C�g���`�揈��
			break;
		case 1:
			GameInit(); //�Q�[����������
			break;
		case 2:
			DrawRanking(); //�����L���O�`�揈��
			break;
		case 3:
			DrawHelp(); //�Q�[���w���v�`�揈��
			break;
		case 4:
			DrawEnd(); //�Q�[���G���h�`�揈��
			break;
		case 5:
			GameMain(); //�Q�[�����C������
			break;
		case 6:
			DrawGameOver(); //�Q�[���I�[�o�[�`�揈��
			break;
		case 7:
			InputRanking(); //�����L���O���͏���
			break;
		}
		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End(); // DX ���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}
/***********************************************
* �Q�[���^�C�g���\���i���j���[��ʁj
***********************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;
	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3) MenuNo = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0) MenuNo = 3;
	}
	// �y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;
	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);
	// ���j���[
	//DrawGraph(120, 200, g_Menu, TRUE);
	// ���j���[�J�[�\��
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);

	DrawString(50, 50, "GameState" + MenuNo, GetColor(255, 255, 255));
	DrawString(0, 0, "Title", GetColor(255, 255, 255));
}
/***********************************************
* �Q�[����������
***********************************************/
void GameInit(void)
{


	// �Q�[�����C��������
	g_GameState = 5;
}
/***********************************************
* �Q�[�������L���O�`��\��
***********************************************/
void DrawRanking(void)
{
	// �y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Ranking", GetColor(255, 255, 255));
}
/***********************************************
* �Q�[���w���v�`�揈��
***********************************************/
void DrawHelp(void)
{
	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_Help, FALSE);

	// �y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Help", GetColor(255, 255, 255));
}
/***********************************************
* �Q�[���G���h�`�揈��
***********************************************/
void DrawEnd(void)
{
	DrawString(0, 0, "End", GetColor(255, 255, 255));
}
/***********************************************
* �Q�[�����C��
***********************************************/
void GameMain(void)
{
	// �y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = 0;

	DrawString(0, 0, "Main", GetColor(255, 255, 255));
}
/***********************************************
* �Q�[���I�[�o�[��ʕ`�揈��
***********************************************/
void DrawGameOver(void)
{
	DrawString(0, 0, "GameOver", GetColor(255, 255, 255));
}
/***********************************************
* �����L���O���͏���
***********************************************/
void InputRanking(void)
{
	DrawString(0, 0, "Input Ranking", GetColor(255, 255, 255));
}
/***********************************************
* �摜�Ǎ���
***********************************************/
int LoadImages()
{
	//�^�C�g��
	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) return -1;
	//���j���[
	if ((g_Menu = LoadGraph("images/menu.png")) == -1) return -1;
	//���j���[
	if ((g_Help = LoadGraph("images/help.png")) == -1) return -1;
	return 0;
}