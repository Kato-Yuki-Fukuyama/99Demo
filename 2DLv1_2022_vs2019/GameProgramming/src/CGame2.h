#pragma once
#include "CUi.h"
#include "CPlayer3.h"

//�萔�̒�`
#define TEXTURE "image.png" //�e�N�X�`���̃t�@�C����
#define TIPSIZE 20.0f //�}�b�v�v�f�̃T�C�Y
/*
* CGame�N���X
* �Q�[���N���X
* �Q�[���̃}�b�v���쐬���A
* �L�����N�^��z�u����
*/
class CGame2
{
public:
	//�f�X�g���N�^
	~CGame2();
	//�Q�[���N���A����
	bool IsClear();
	//�Q�[���N���A����
	void Clear();
	//�Q�[���I�[�o�[����
	bool IsOver();
	//�Q�[���I�[�o�[����
	void Over();
	//�X�^�[�g����
	void Start();
	CGame2(); //�f�t�H���g�R���X�g���N�^�i���������j
	void Update(); //�X�V����
private:
	int mCdx, mCdy; //�J�����ƃv���C���[�̍��W�̍���
	void CameraSet(); //�J�����ݒ�
	CPlayer3* mpPlayer; //�v���C���[�̃|�C���^
	int mTime; //�o�ߎ���
	CUi* mpUi; //UI�N���X�̃|�C���^
};