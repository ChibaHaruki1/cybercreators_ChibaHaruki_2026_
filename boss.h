//================================================
//
//�{�X�̃N���X�Ǘ�[boss.h]
//Auther:Haruki Chiba
//
//================================================

#pragma once

//================================================
//�C���N���[�h
#include "character.h"
#include "enemycharacter.h"
#include<vector>


//==================================================================
//�{�X�̏���
class CBoss : public CCharacter
{
public: //�A�N�Z�X�\

	CBoss(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CBoss()override;                           //�f�X�g���N�^
	HRESULT Init()override;                     //����������
	void Uninit()override;                      //�j������
	void Update() override;                     //�X�V����
	void Draw()override;                        //�`�揈��
	void AttackPattern();                       //�U���̎�ނ��Ƃ̊֐�
	void AttackPattern001();                    //�U���̎�ނ��Ƃ̊֐�
	void StatusInit();                          //�����̕ϐ��̏����������֐�
	void AttackPatternSelect();                 //�U���̎�ނ�I������֐�
	void Collision();                           //�����蔻�菈���֐�
	void SpecialAttack();                       //�K�E�Z

	float PopX(); //�l���폜
	float PopY(); //�l���폜
	float PopZ(); //�l���폜

	static CBoss* Create(D3DXVECTOR3 pos);

private: //�A�N�Z�X�s��
	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_VECTOR_SIZE = 50;                  //vector�z��̍ő吔
	constexpr static int DIE_FRAME = 180;                       //���̃V�[���֍s���܂ł̎���
	constexpr static int INIT_WICHI_SIDE_NUMBER = -1;           //���E�ǂ���̈ʒu�ɋ��邩�̏����ԍ�
	constexpr static int WICHI_SIDE_LEFT_NUMBER = 0;            //���E�ǂ���̈ʒu�ɋ��邩�̍����̔ԍ�
	constexpr static int WICHI_SIDE_RIGHT_NUMBER = 1;           //���E�ǂ���̈ʒu�ɋ��邩�̉E���̔ԍ�


	//==============================================
	//�U���p�^�[���P�̎��̃}�N����`
	constexpr static int ATTACKPATTEN1_FRAME_1 = 30;            //���s�����̃t���[��
	constexpr static int ATTACKPATTEN1_FRAME_2 = 140;           //���s�����̃t���[��
	constexpr static int ATTACKPATTEN1_FRAME_3 = 141;           //��O�s�����̃t���[��
	constexpr static int ATTACKPATTEN1_FRAME_4 = 162;           //��l�s�����̃t���[��
	constexpr static int ATTACKPATTEN1_FRAME_5 = 170;           //��܍s�����̃t���[��
	constexpr static float MAX_DROP_MOVE_Y_SPEED_1 = 0.35f;       //Y���̃{�X�̗�����ړ����x��ݒ�
	constexpr static float MAX_MOVE_SPEED_IN_PLAYER_1 = 12.0f;  //�����U�����v���C���[�Ɍ���������


	//==============================================
	//�U���p�^�[���Q�̎��̃}�N����`
	constexpr static int ATTACKPATTEN2_FRAME = 40;              //�s�����̃t���[��
	constexpr static float MAX_DROP_MOVE_Y_SPEED_2 = 0.25f;     //Y���̃{�X�̗�����ړ����x��ݒ�
	constexpr static float MAX_MOVE_SPEED_IN_PLAYER_2 = 8.0f;   //���U�����v���C���[�Ɍ���������
	constexpr static float MAX_MOVE_SPEED_SIDE = 0.1f;          //���E�̂ǂ��炩�ɂɈړ����鎞�̑���


	//==============================================
	//�U���p�^�[���R�̎��̃}�N����`
	constexpr static int ATTACKPATTEN3_FRAME_1 = 20;            //���s�����̃t���[��
	constexpr static int ATTACKPATTEN3_FRAME_2 = 60;            //���s�����̃t���[��
	constexpr static int ATTACKPATTEN3_FRAME_3 = 61;            //��O�s�����̃t���[��


	constexpr static float MAX_MOVE_SPEED = 0.25f;              //�{�X�̈ړ����x��ݒ�
	constexpr static float MAX_TOUCH_DAMAGE = 0.0005f;          //�{�X�ɐG��Ă��鎞�̃_���[�W��


	int m_nCoolTime;        //�U���I���㎟�̍U���ɍs���܂ł̎���
	int m_nSize;            //vector�̔z�񐔂��擾���邽�߂̕ϐ�
	int m_nWhichSideNumber; //���E�̂ǂ���ɋ��邩�𐔎��œn�����߂̕ϐ�

	bool m_bOneCreateFlag;  //�Ռ��g���P��̂݌ĂԂ��߂�

	//vector�Ɋւ���ϐ�
	std::vector<float> m_nSaveData; //�z������m�ۂ���ׂ̕ϐ�
	std::vector<float> m_nDataX;    //X���p�̃f�[�^��ۊǂ���p�̕ϐ�
	std::vector<float> m_nDataY;    //Y���p�̃f�[�^��ۊǂ���p�̕ϐ�
};
