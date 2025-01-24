//=====================================
//
//�{�X�̏���[boss.cpp]
//Auther:Haruki Chiba
//
//=====================================


//=====================================
//�C���N���[�h
#include "boss.h"
#include "manager.h"
#include <time.h>
#include <iostream>


//========================
//�R���X�g���N�^
//========================
CBoss::CBoss(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::BOSSHP, 0); //�{�X��HP�Q�[�W�̐���
	
	m_nCoolTime = 0;                              //�N�[���^�C���̏�����
	SetRandom(1);                                 //�����̏�����
	m_nSize = 0;                                  //�z�񐔂̏�����
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;  //�ǂ���ɂ��邩�̏�����

	m_nSaveData.clear();                          //�ۊǗp�x�N�^�[�̏�����
	m_nDataX.clear();                             //�����̈ʒu�̏�����
	m_nDataY.clear();                             //�����̈ʒu�̏�����
							                      
	m_bOneCreateFlag = false;                     //�����t���O�̏�����
}

//========================
//�f�X�g���N�^
//========================
CBoss::~CBoss()
{
	//�ۊǗp�x�N�^�[�̔j��
	m_nSaveData.clear();         //��������
	m_nSaveData.shrink_to_fit(); //���𖳂���

	//X���p�̃x�N�^�[�̔j��
	m_nDataX.clear();            //��������
	m_nDataX.shrink_to_fit();    //���𖳂���

	//Y���p�̃x�N�^�[�̔j��
	m_nDataY.clear();            //��������
	m_nDataY.shrink_to_fit();    //���𖳂���
}

//========================
//����������
//========================
HRESULT CBoss::Init()
{
	//�x�N�^�[�̍ő吔����
	for (int nCount = 0; nCount < MAX_VECTOR_SIZE; nCount++)
	{
		m_nSaveData.push_back((float)nCount); //nCount��float�^��cast���đ������
	}

	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //X���p�̕ϐ��ɑ��
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //Y���p�̕ϐ��ɑ��

	CCharacter::Init();                       //������
	CCharacter::LoodBoss();                   //���t�@�C���̓ǂݍ���
	CCharacter::SetMotionBoss(BOSSJUMP);      //���[�V�����̏����ݒ�
	return S_OK;                              //������Ԃ�
}

//========================
//�j������
//========================
void CBoss::Uninit()
{
	CCharacter::Uninit();  //�j������
}

//========================
//�X�V����
//========================
void CBoss::Update()
{
	CCharacter::UpdateBoss();    //���[�V�����̏����X�V����

	//�{�X�������Ă��鎞
	if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() > 0)
	{
		Collision();             //���E�ǂ���ɂ��邩�������Ă���֐����Ă�
		AttackPatternSelect();   //�U���̎�ނ�I������֐����Ă�
	}

	//�{�X�����񂾎�
	else if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() <= 0)
	{
		SetAddjustDieFrame()++;                                                     //���S�J�E���g�𑝂₷
		SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSDIE);                        //���[�V�����̎�ނ�ݒ�
		CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::BOSS, 0);  //�{�X�́i���g�j�C���X�^���X�̏��𖳂���

		//frame���K��l�ȏ�̎�
		if (GetDieFrame() >= DIE_FRAME)
		{
			CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ֈڍs
			return;                                       //�����𔲂���
		}
	}

	CObjectX::Update();      //���N���X�̊��N���X��m_move���X�V
}

//====================================================================
//�����蔻��ō��E�̂ǂ���ɂ��邩���肷��֐�
//====================================================================
void CBoss::Collision()
{
	//�E���ɂ��鎞
	if (CollisionRightSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_RIGHT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�����ɂ��鎞
	else if (CollisionLeftSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_LEFT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�{�X�ɓ���������
	if (CollisionBossPrts() == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_TOUCH_DAMAGE; //�v���C���[��HP�Q�[�W�����炷
	}
}

//==============================
//�U���̎�ނ�I�����鏈��
//==============================
void CBoss::AttackPatternSelect()
{
	//�U���̃N�[���^�C�����߂�����
	if (m_nCoolTime >= 120)
	{
		//�������O�̎�
		if (GetRandom() == 0)
		{
			AttackPattern();    //�����U�����Ă�
		}

		//�������P�̎�
		else if (GetRandom() == 1)
		{
			AttackPattern001(); //���U�����Ă�
		}

		//�������Q�̎�
		else if (GetRandom() == 2)
		{
			SpecialAttack();    //�K�E�Z���Ă�
		}
	}

	//�N�[���^�C����
	else
	{
		//�������R�̎��i�S�Ă̍U���p�^�[�������s�j
		if (GetRandom() == 3)
		{
			//srand((unsigned)time(NULL));  // �����n���������
			//SetRandom(rand() % 3);
			SetRandom(0); //������������
		}
		m_nCoolTime++;    //�N�[���^�C���𑝂₷
	}
}

//==============================
//�s���ɂ܂�镨�̏�����
//==============================
void CBoss::StatusInit()
{
	CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSNEUTRAL); //���[�V�����̎�ނ�ݒ�

	//vector�̏�����
	m_nDataX.clear();          //���g�̑S�폜
	m_nDataX.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	m_nDataY.clear();          //���g�̑S�폜
	m_nDataY.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	//vector�̒l�擾�i�R�s�[�j
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //�����p�̈ʒu�̏�����
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //�����p�̈ʒu�̏�����

	//�����o�ϐ��̏�����
	SetFrame(0);                                   //�t���[���̏�����
	SetAddjustRandom() += 1;                       //�����𑝂₷
	m_nCoolTime = 0;                               //�N�[���^�C���̏�����
	m_nSize = 0;                                   //vector�̔z�񐔂�������
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;   //���E�̂ǂ���ɋ��邩�̏�����
	m_bOneCreateFlag = false;                      //�Ռ��g���o���t���O�̏�����
}

//==============================
//�~���U��
//==============================
void CBoss::AttackPattern()
{
	SetAddjustFrame()++; //�t���[�������Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN1_FRAME_1)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                      //���[�V�����̎�ނ�ݒ�
		
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_1);  //�v���C���[�Ɍ������悤�ɐݒ�
	}

	//���s��
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_2)
	{
		SetAddjustRot().y = 0.0f;                                                            //Y���̌����̏�����
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSIMPACT);                  //���[�V�����̎�ނ�ݒ�
		SetAddjustPos().y += PopY() * MAX_MOVE_SPEED;                                        //Y���̈ʒu��ۊǂ��Ă���l����Ɉړ�
	}

	//��O�s��
	else if (GetFrame() <= ATTACKPATTEN1_FRAME_3)
	{
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));     //Y���p�̈ʒu�̏�����
	}

	//��l�s��
	else if (GetFrame()<= ATTACKPATTEN1_FRAME_4)
	{
		SetAddjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_1;                                 //Y���̈ʒu��ۊǂ��Ă���l�����Ɉړ�
	}

	//�Ռ��g
	else  if (GetFrame() <= ATTACKPATTEN1_FRAME_5)
	{
		//�t���O��off�̎�
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::IMPACT, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //�Ռ��g�𐶐�
			CManager::GetInstance()->GetImpact()->SetEffect(GetPos());                                                   //�Ռ��g�G�t�F�N�g���Ă�

			m_bOneCreateFlag = true; //�t���O��On�ɂ��Ēʂ�Ȃ�����
		}
	}

	//�I��
	else
	{
		SetAddjustPos().y = 0.0f; //Y���̈ʒu��������
		SetAddjustRot().y = 0.0f; //Y���̌�����������
		StatusInit();             //������
	}
}

//==============================
//���U��
//==============================
void CBoss::AttackPattern001()
{
	SetAddjustFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN2_FRAME)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK);                       //���[�V�����̎�ނ�ݒ�
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_MOVE_SPEED_IN_PLAYER_2);   //�v���C���[�Ɍ������悤�ɐݒ�
	}

	//���s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*3)
	{
		SetAddjustRot().y = 0.0f;                                           //Y���̌�����������
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSATTACK); //���[�V�����̎�ނ�ݒ�
		SetAddjustPos().y += PopY() * MAX_DROP_MOVE_Y_SPEED_2;              //Y���̈ʒu��ۊǂ��Ă���l����Ɉړ�     
	}

	//��O�s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*3+1)
	{
		//�e�̐���(�e�ɃG�t�F�N�g���Ăԏ��������Ă��邽�߃G�t�F�N�g��ύX���������͒e�̏�����������)
		CManagerBullet::Create(D3DXVECTOR3(GetPosPrtsBoss(17).x+100.0f, GetPosPrtsBoss(17).y-150.0f, GetPosPrtsBoss(17).z), D3DXVECTOR3(-sinf(GetRot().y) * 0, 0.0f, -cosf(GetRot().y) * 0), CManagerBullet::SET_BULLET_LIFE,CObject3D::TYPE::BOSSBULLET);
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));      //�����p�̈ʒu�̏�����
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX));      //�����p�̈ʒu�̏�����
	}

	//��l�s��
	else if (GetFrame() <= ATTACKPATTEN2_FRAME*4)
	{
		SetAddjustPos().y -= PopY() * MAX_DROP_MOVE_Y_SPEED_2; //Y���̈ʒu��ۊǂ��Ă���l�����Ɉړ� 

		//���ɂ��鎞
		if (m_nWhichSideNumber == WICHI_SIDE_LEFT_NUMBER)
		{
			SetAddjustRot().y = D3DX_PI_ORI;                     //Y���̌�����ݒ�
			SetAddjustMove().x -= PopX() * MAX_MOVE_SPEED_SIDE;  //Y���̈ړ��ʂ����Z�ݒ�
		}

		//�E�ɂ��鎞
		else if (m_nWhichSideNumber == WICHI_SIDE_RIGHT_NUMBER)
		{
			SetAddjustRot().y = -D3DX_PI_ORI;                    //Y���̌�����ݒ�
			SetAddjustMove().x += PopX() * MAX_MOVE_SPEED_SIDE;  //Y���̈ړ��ʂ����Z�ݒ�
		}
	}

    //�I��
	else
	{
		SetAddjustPos().y = 0.0f; //Y���̈ʒu��������
		SetAddjustRot().y = 0.0f; //Y���̌�����������
		StatusInit();             //������
	}
}

//=======================================================================================================================================================
//�K�E�Z�̏���
//=======================================================================================================================================================
void CBoss::SpecialAttack()
{
	SetAddjustFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= ATTACKPATTEN3_FRAME_1)
	{
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 10.0f);    //�v���C���[�Ɍ������悤�ɐݒ�
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSACTION); //���[�V�����̎�ނ�ݒ�
	}

	//���s��
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_2)
	{

	}

	//��O�s��
	else if (GetFrame() <= ATTACKPATTEN3_FRAME_3)
	{
		//�����t���O��Off�̎�
		if (m_bOneCreateFlag == false)
		{
			//�K�E�Z�̃G�t�F�N�g�̐���
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::BOSSSPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 

			//�����̏�����
			if (GetRot().y >= D3DX_PI_ORI*0.5f)
			{
				//�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(2);

				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3
				(
					GetPosPrtsBoss(17).x,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));

			}

			//�����̏�����
			else if (GetRot().y <= -D3DX_PI_ORI * 0.5f)
			{
				//�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(1);

				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x + 300.0f,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));
			}

			m_bOneCreateFlag = true; //�����t���OOn�ɂ���
		}
	}

	//�I��
	else if(CManager::GetInstance()->GetBossSpecialAttack()->GetAlpha()<=0)
	{
		SetAddjustPos().y = 0.0f; //Y���̈ʒu��������
		SetAddjustRot().y = 0.0f; //Y���̌�����������
		StatusInit();             //������
	}
}


//=======================================================================================================================================================
//  �X�^�b�N�\���̏���
//=======================================================================================================================================================

//============================
//�X�^�b�N��X�l���폜
//============================
float CBoss::PopX()
{
	int nSize = m_nDataX.size() - 1;        //�T�C�Y�̐ݒ�

	//�傫�����O�ȏ�̎�
	if (nSize > 0)
	{
		nSize--;                            //�傫�������炷
		m_nDataX.erase(m_nDataX.end() - 1); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataX[nSize];             //����Ԃ�
	}

	return 0;                               //�O��Ԃ�
}

//============================
//�X�^�b�N��Y�l���폜
//============================
float CBoss::PopY()
{
	int nSize = m_nDataY.size() - 1;        //�T�C�Y�̐ݒ�

	//�T�C�Y���O�ȏ�̎�
	if (nSize > 0)
	{
		nSize--;                            //�T�C�Y�����炷
		m_nDataY.erase(m_nDataY.end() - 1); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataY[nSize];             //����Ԃ�
	}

	return 0;                               //�O��Ԃ�
}

//========================
//�`�揈��
//========================
void CBoss::Draw()
{
	CCharacter::DrawBoss(MAX_BOSSPARTS); //�p�[�c���Ƃ̕`�揈��
}

//========================
//��������
//========================
CBoss* CBoss::Create(D3DXVECTOR3 pos)
{
	CBoss* pBoss = new CBoss(3); //���I�m��

	//������������������
	if (SUCCEEDED(pBoss->Init()))
	{
		pBoss->SetPos(pos); //�ʒu�������Ɠ���������
		return pBoss;       //�v���C���[�̏���Ԃ�
	}

	return nullptr;             //����Ԃ�
}