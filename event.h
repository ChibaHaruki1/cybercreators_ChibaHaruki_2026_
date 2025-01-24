//================================================================
//
//�X�e�[�W���̃C�x���g�����N���X[event.h]
//Auther:Haruki Chiba
//
//================================================================

#pragma once

//=====================
//�C���N���[�h
#include <vector>
#include "instance.h"

//=====================================================================================================
//event�̊��N���X
//=====================================================================================================
class CEvent
{
public:
	CEvent();                  //�f�X�g���N�^
	~CEvent();                 //�R���X�g���N�^
	void Update();             //�X�V����
	void DropObj();            //obj�̗��Ƃ�����
	void BossDirection();      //�{�X�̉��o����	
	void DropMeteorite();      //覐΂𗎂Ƃ�����
	void CreateEnemy();        //�G�̐���


	//==========================
	//���̎擾
	bool& GetBossDirection() { return m_bBossDirection; } //�{�X�̐���������Ă��邩�ǂ����̏����擾


	//==========================
	//�}�N����`
	constexpr static float CANERA_POSY = 400.0f;                //�J������Y���̈ʒu

private:
	//�}�N����`
	constexpr static int CANERA_POSZ = 1400;                    //�J������Z���̈ʒu
	constexpr static int RAND_ROTX = 15;                        //�؂̔R�̗��Ƃ��Ƃ��̌�����X���̒l
	constexpr static int RAND_ROTY = 31;                        //�؂̔R�̗��Ƃ��Ƃ��̌�����Y���̒l
	constexpr static int INIT_DROP_POS = 18;                    //�؂̔R�̗��Ƃ��ʒu�����炩���ߐݒ肷�邽�߂̒l
	constexpr static float ADJUST_ROT = 0.1f;                   //�����ŏo�����l�������ɒ����ׂ̒l
	constexpr static float EVENT_BOSS_FIGHT_POS = 3650.0f;      //�{�X��̎n�܂�ɂȂ�ʒu
	constexpr static float CREATE_BOSS_POSX = 4700.0f;          //�{�X������������X���̈ʒu
	constexpr static float CREATE_MOTIONINENEMY_POSX = 9500.0f; //���[�V�����t���̓G������������X���̈ʒu
	constexpr static float CREATE_WOODENBOARD_POSX = 3250.0f;   //�؂̔Q������������X���̈ʒu
	constexpr static float CREATE_WOODENBOARD_POSY = 350.0f;    //�؂̔Q������������Y���̈ʒu
	constexpr static float WOODENBOARD_DROPY = 10.0f;           //�؂̔Q�̗��Ƃ��ʒu�𑝂₷�l
	constexpr static float WOODENBOARD_PLUSY = 0.12f;           //�؂̔Q�̗��Ƃ����x�𑝂₷�l


	int m_nCreateWoodenBoradsCounter;            //�������鐔
	int m_nRandomRotX;                           //�����̃����_������ۊǂ���
	int m_nRandomRotY;                           //�����̃����_������ۊǂ���
	float m_nPosY;                               //��������Y����pos
	float m_fDropSpeed[CInstance::MAX_RUBBLE];   //���Ƃ����x�����߂�ϐ�
	float m_fDropPosY[CInstance::MAX_RUBBLE];    //���Ƃ��ʒu�����炩���ߌ��߂�ϐ�
	bool m_bBossDirection;                       //�{�X�̉��o��1�񂾂��o�����߂̏���
	bool m_bOneflag;                             //��񂾂�������ʂ��p�̕ϐ�
	bool m_bOneCreate;                           //��񂾂���������p�̕ϐ�
};
