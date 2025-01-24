//===================================
//
//�v���C���[�̐ݒ�����鏈��[player.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "main.h"
#include "player.x.h"
#include "rendererh.h"
#include "manager.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include <time.h>
#include "DxLib.h"


//===================
//�R���X�g���N�^
//===================
CPlayerX::CPlayerX(int nPriority) : CCharacter(nPriority)
{
	SetJumpFlag(false);                                                         //���ł��Ȃ��ɐݒ�
	SetGravity(0.0f);                                                           //�d�͂̏�����

	//�e�L�X�g�t�@�C���ɓo�^���鎞�̗t�z��ԍ��̏�����
	m_nFiledCount = -1;                                   //�n�ʂ̐������̏�����
	m_nTelephonCount = -1;                                //�d���̐������̏�����

	//�e�L�X�g�t�@�C���ɓo�^���邵���S�Ă̔z��ԍ��̏�����
	m_nAllTelephonPoleCount = -1;
	m_nAllFiledCount = -1;

	m_ObjectNumber = 0;                                   //���݂̃I�u�W�F�N�g�̔ԍ��̏�����
							                              
	m_nFrameParticle = 0;                                 //�p�[�e�B�N���̃t���[���̏�����
	m_nPraticlesCount = 0;                                //�p�[�e�B�N���̔z��J�E���g�̏�����
	m_nRandomCol = 0;                                     //������ۊǂ���ׂ̕ϐ�
							                              
	m_pMenyu = nullptr;                                   //���j���[�|�C���^�[�̏�����
	m_pLaserUI = nullptr;                                 //���[�U�[UI�̏�����
	m_pTalkText = nullptr;                                //�b��UI�̏�����
	m_pBuyText = nullptr;                                 //�����e�L�X�g�̏�����
	m_nSelectShopCount = 0;                               //SHOP�őI��ł��镨
	m_nBuyOrSendCount = 0;                                //���������̑I���J�E���g�̏�����
	m_pSelectGage = nullptr;                              //�I���Q�[�W�̏�����
	m_pSelectGage001 = nullptr;                           //�I���Q�[�W001�̏����� 
	SpecialAttack = false;                                //�K�E�Z���g���Ă��邩�ǂ����̏�����
	m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;  //���݂̃v���C���[�̏�Ԃ̐ݒ�
	m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;     //���݂̃t���O�̐ݒ�
	m_nAlpha = 255;                                       //�p�[�e�B�N���̃A���t�@�l�̐ݒ�

	m_nMotionFrame = 0;                                   //�e�������̃t���[���̏�����
	m_nMotionFrame001 = 0;                                //�e001�������̃t���[���̏�����
	m_bPlayerMoveNext = false;                            //���̃X�e�[�W�֍s�����̃v���C���[�̓����̔���p�̕ϐ��̏�����
	m_bNextStage = false;                                 //���̃X�e�[�W�ɍs�����ǂ����̕ϐ��̏�����

	//������ԏ����̏�����
	m_nFlayFrame = 0;                                     //��ԃt���[���̏�����
	m_bFly = false;                                       //���łȂ�

	m_nDieRandom = 0;                                     //���S���̕��������̏�����
	m_nRotNumber = 0;                                     //�����ԍ��̏�����
	m_nSpecialAttackCount = 0;                            //�K�E�Z�̃J�E���g�̏�����
	m_bOneCreate = false;                                 //��x������������t���O�̏�����

	m_nNextStageFrame = 0;                                   //���̃X�e�[�W�ɍs���܂ł̃t���[���̏�����
	m_bLandingFlag = false;                               //���n���ĂȂ�
	m_nLandingFrame = 0;                                  //���n���̎��̓����ւ̃t���[���̏�����

	m_pNowCreateUI = CManager2DUI::Create(CObject::TYPE_UI::NOWCREATE); //���݂̔z�u�I�u�W�F�N�g��UI�̐���
}


//===================
//�f�X�g���N�^
//===================
CPlayerX::~CPlayerX()
{
	//mciSendStringA("close BGM", NULL, 0, NULL);
}


//====================
//����������
//====================
HRESULT CPlayerX::Init()
{
	CCharacter::Init();                                                           //�������������Ă�
	CCharacter::Lood();                                                           //�e�L�X�g�t�@�C����ǂݍ��ޏ���
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));                             //�����̒����i�E�����j
	m_pModelPrts[18]->SetDraw(false);                                             //�p�[�c�̏e�������\���ɐݒ�
	SetPos(D3DXVECTOR3(000.0f,0.0f,0.0f));                                        //�ʒu�̒���
	SetLife(1);                                                                   //���g�̃��C�t
	return S_OK;                                                                  //������Ԃ�
}

//==================
//�I������
//=================
void CPlayerX::Uninit()
{
	//instance��������
	InstanceMakeNull();

	CCharacter::Uninit(); //�p�[�c���Ƃ̔j������
}

//===============================================================================================================================================================================
//instance��nullptr�ɂ���
//===============================================================================================================================================================================
void CPlayerX::InstanceMakeNull()
{
	m_pTalkText = nullptr;      //�b���e�L�X�g�̏��𖳂���
						        
	m_pMenyu = nullptr;         //����̑I�����j���[�̏��𖳂���
						        
	m_pBuyText = nullptr;       //��������e�L�X�g�̏��𖳂���
							    
	m_pSelectGage = nullptr;    //�I���Q�[�W�̏��𖳂���

	m_pSelectGage001 = nullptr; //�I���Q�[�W001�̏����Ȃ���
}

//=======================================
//�V���b�v���̃|�C���^�[�̏�����
//=======================================
void CPlayerX::ShopInstanceMakeNullptr()
{
	//�I���Q�[�W�̏�񂪂��鎞
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage->Release(); //��������
		m_pSelectGage = nullptr;  //���𖳂���
	}

	//�I���Q�[�W001�̏�񂪂��鎞
	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001->Release(); //��������
		m_pSelectGage001 = nullptr;  //���𖳂���
	}

	//�����e�L�X�g�̏�񂪂��鎞
	if (m_pBuyText != nullptr)
	{
		m_pBuyText->Release(); //��������
		m_pBuyText = nullptr;  //���𖳂���
	}

	//���j���[�̏�񂪂��鎞
	if (m_pMenyu != nullptr)
	{
		m_pMenyu->Release(); //��������
		m_pMenyu = nullptr;  //���𖳂���
	}

	//�V���b�v���̔w�i�̏�񂪂��鎞
	if (CManager::GetInstance()->GetShopScreen() != nullptr)
	{
		CManager::GetInstance()->GetShopScreen()->Release();                   //��������
		CManager::GetInstance()->DesignationUninit2D(CObject2D::TYPE::SCREEN); //���𖳂���
	}
}


//===============================================================================================================================================================================
//�X�V����
//===============================================================================================================================================================================
void CPlayerX::Update()
{
	//�����Ă��鎞
	if (GetLife() == 1)
	{
		CCharacter::UpdatePlayer();  //���[�V�����̍X�V

		if (CManager::GetScene()->GetPlay() == true)
		{
			HitAttack();                 //����̍U�����󂯂����̏����֐����Ă�

			//�K�E�Z�J�E���g���K��l���Ⴂ��
			if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
			{
				m_nSpecialAttackCount++; //�J�E���g��i�߂�
			}

			//�Q�[�W��manager����������Ă�����
			if (CManager::GetInstance()->GetPlayerHPGage() != nullptr)
			{
				//HP�Q�[�W���O�ȉ��̎�
				if (CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() <= 0)
				{
					CManager::GetInstance()->GetPlayerHPGage()->GetSaveSizeX() = 0.0f;  //HP�Q�[�W�̃T�C�Y���O�ɂ���
					SetLife(0);                                                         //���C�t���O�ɐݒ�Ŏ��S����ɂ���
				}
			}

			//�������Ă��Ȃ���
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				NormalStateSummarizeFunction(); //��p�̏������Ă�
			}

			//SHOP�Ŕ����������Ă��鎞
			else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE || m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
			{
				ShopStateSummarizeFunction();   //��p�̏������Ă�
			}

			//���̃X�e�[�W�֍s���Ƃ��̃v���[���[�̓�����On�̎�
			if (m_bPlayerMoveNext == true)
			{
				//SceneMode(1); //scene�̐؂�ւ�
				//return;		  //�����𔲂���
				NextStageMotion();
			}

			//����scene�ɍs���t���O��On�̎�
			if (m_bNextStage == true)
			{
				SceneMode(1); //scene�̐؂�ւ�
				return;		  //�����𔲂���
			}

			CObjectX::Update();                 //���N���X�̊��N���X�̍X�V�������Ă�
		}

		//���n�܂łɕK�v�ȏ���
		else
		{
			BlockJudgement();              //�n�ʂɐG��鎖�ł悤�₭�ړ��Ȃǂ��ł���悤�ɂ��邽�߃u���b�N�̓����蔻�菈�����Ă�
			Junp(TYPE::PLAYER, 10.0f);     //�d�͏����֐����ĂԎ��ŗ�����悤�ɂ���
		}
	}

	//���񂾎�
	else if (GetLife() == 0)
	{
		GetDieFrame()++;                //���S�t���[���𑝂₷
		//GetPos().y = -50.0f;          //�ʒu��Ⴍ����
		srand((unsigned)time(NULL));    //�����n���������

		//�����������ĂȂ���
		if (m_nDieRandom == 0)
		{
			m_nDieRandom = -1 + rand() % 3; //����������
		}

		//�p�[�c�̈ʒu��ݒ�
		m_pModelPrts[0]->GetPos() += D3DXVECTOR3(GetDieFrame() * 0.1f * m_nDieRandom, 0.0f, GetDieFrame() * 0.1f * m_nDieRandom);

		CCharacter::Update();  //���N���X�̍X�V�������Ă�
		SetMotion(DIE);        //���[�V���������S�ɐݒ肷��

		//����̐��l
		if (GetDieFrame() >= MAX_DIE_COUNT)
		{
			SceneMode(3); //�V�[���̐ݒ�
			return;       //�����𔲂���
		}
	}
	//SceneMode(2);         //�V�[����I��
}


//==================================================================================================================================================
//������я���
//==================================================================================================================================================
void CPlayerX::BlowAway()
{
	m_nFlayFrame++; //��ԃt���[����i�߂�

	CCharacter::SetMotion(BLOWAWAY); //�Ԃ���у��[�V�����̐ݒ�

	//���s��
	if (m_nFlayFrame <= BLOWAWAY_FRAME_1)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_X; //X���̈ʒu�𑝂₷
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_Y; //Y���̈ʒu�𑝂₷
	}

	//���s��
	else if (m_nFlayFrame <= BLOWAWAY_FRAME_2)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_X-10.0f; //X���̈ʒu�𑝂₷
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_Y-10.0f; //Y���̈ʒu�𑝂₷
	}

	//�I��
	else
	{
		m_bFly = false;   //��ԃt���O��Off�ɂ���
		m_nFlayFrame = 0; //��ԃt���[���̏�����
	}
}


//==================================================================================================================================================
//����̍U�����󂯂����̏���
//==================================================================================================================================================
void CPlayerX::HitAttack()
{
	//�Ռ��j�G�t�F�N�g�̃C���X�^���X��񂪂��鎞
	if (CManager::GetInstance()->GetImpact() != nullptr)
	{
		//���������t���O��ON�̎�
		if (CManager::GetInstance()->GetImpact()->GetHitNumber() == 0)
		{
			m_bFly = true; //���
		}
	}

	//��ԃt���O��ON�̎�
	if (m_bFly == true)
	{
		BlowAway();  //������я������Ă�
	}
}


//==================================================================================================================================================
//����scene����
//==================================================================================================================================================
void CPlayerX::SceneMode(int nType)
{
	//���̃X�e�[�W�ɍs���p�i�Q�[�����[�v�j
	if (nType == 1)
	{
		m_bNextStage = false; //���̃X�e�[�W�̃t���O��Off�ɂ���

		//���݂̃V�[������Q��
		switch (CManager::GetScene()->GetMode())
		{
			//�X�e�[�W�P�̎�
		case CScene::MODE::MODE_GAME01:
			CManager::SetMode(CScene::MODE::MODE_GAME02); //�X�e�[�W�Q�ɑJ��
			return;                                       //�����𔲂���

			//�X�e�[�W�Q�̎�
		case CScene::MODE::MODE_GAME02:
			CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ɑJ��
			return;                                       //�����𔲂���
		}
	}

	//�f�o�b�N�p
	else if (nType == 2)
	{
		//Enter�L�[�������ꂽ���i�f�o�b�N�p�j
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true)
		{
			m_bNextStage = false; //���̃X�e�[�W�̃t���O��Off�ɂ���

			//���݂̃V�[������Q��
			switch (CManager::GetScene()->GetMode())
			{
				//�X�e�[�W�P�̎�
			case CScene::MODE::MODE_GAME01:
				CManager::SetMode(CScene::MODE::MODE_GAME02); //�X�e�[�W�Q�ɑJ��
				return;                                       //�����𔲂���

				//�X�e�[�W�Q�̎�
			case CScene::MODE::MODE_GAME02:
				CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ɑJ��
				return;                                       //�����𔲂���
			}
		}
	}

	//���S�������p
	else if (nType == 3)
	{
		m_bNextStage = false; //���̃X�e�[�W�̃t���O��Off�ɂ���
		CManager::SetMode(CScene::MODE::MODE_GAMEOVER); //�Q�[���I�[�o�[�ɑJ��
		return;                                         //�����𔲂���
	}
}


//===============================================================================================================================================================================
//�ʏ��Ԏ��̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::NormalStateSummarizeFunction()
{
	//�K�E�Z�̃J�E���g���K��l��荂����
	if (m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
	{
		Praticles();               //�p�[�e�B�N���̐��������֐����Ă�

		//�K�E�Z���J�E���g���K��l���Ⴂ��
		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHARGE); //BDM�𗬂�
		}
	}
	BlockJudgement();              //�I�u�W�F�N�g�Ƃ̓����蔻�菈���֐����Ă�
						           
	NowCreateNumberObj();          //�z�u�I�u�W�F�N�g��UI�𐶐����鏈���֐�
	NowCreateObjectUI();           //���ݍ���Ă���I�u�W�F�N�g��UI���o������

	//�K�E�Z�������Ă��Ȃ���
	if (SpecialAttack == false)
	{
		KeySet();                  //�L�[���Ƃ̏����֐����Ă�
	}
	else
	{
		//�e�����t���[�����O�ȏ�̎�
		if (m_nMotionFrame >= 0)
		{
			m_nMotionFrame--;      //�t���[���𑝂₷
		}

		//�e�����t���[��001���O�ȏ�̎�
		if (m_nMotionFrame001 >= 0)
		{
			m_nMotionFrame001--;   //�t���[���𑝂₷
		}

		//�����̃t���[�����O�ȉ��̎�
		else if(m_nMotionFrame<=0&& m_nMotionFrame001<=0)
		{
			SpecialAttack = false; //�K�E�Z�t���O��Off�ɂ���
		}
	}
	Junp(TYPE::PLAYER, 10.0f);     //�W�����v�Əd�͏����֐����Ă�
}


//===============================================================================================================================================================================
//���������̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::ShopStateSummarizeFunction()
{
	BlockJudgement();        //�u���b�N�Ƃ̓����蔻�菈���֐�
	ShopKeySet();            //�L�[���Ƃ̏���
}


//===============================================================================================================================================================================
//�����_������
//===============================================================================================================================================================================
void CPlayerX::Random()
{
	//�ŏ��l�{rand()%�ŏ��l���牽�����₷���@�i�T�������灓�U��������@�T�A�U�A�V�A�W�A�X�A�P�O�̍��v�U�ɂȂ�j
	//srand((unsigned)time(NULL));    //�����n���������
	SetRandom(-50 + rand() % 100);  //-50�`50�̐��l���o���i�͈͎w��j
	m_nRandomCol = rand() % 255;    //0�`255�̐��l���o���i�͈͎w��j
}


//===============================================================================================================================================================================
//�p�[�e�B�N�����o������
//===============================================================================================================================================================================
void CPlayerX::Praticles()
{
	Random();             //�����_���������Ă�
	m_nFrameParticle++;   //�t���[�������Z�����Ă���

	//�t���[��������̐��l�܂ōs������
	if (m_nFrameParticle >= 4)
	{
		m_nFrameParticle = 0; //�t���[��������������

		//�z��̍ő吔���ő吔��艺����
		if (m_nPraticlesCount >= 0 && m_nPraticlesCount <= CInstance::MAX_OBJECT_DATA - 1)
		{
			//�p�[�e�B�N���̐���
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPos().y+50.0f, 0.0f)); //�p�[�e�B�N���̐�������
			CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, 0, 0, m_nAlpha);//�F�̐ݒ�
			m_nPraticlesCount++; //�z���i�߂�
		}

		//�ő吔�ɓ˓�
		else
		{
			m_nPraticlesCount = 0; //�z��J�E���g������������
		}
	}
}


//===============================================================================================================================================================================
//�L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::KeySet()
{
	//=================================================
	//�K�E�Z�̔���
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_K) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_RB) == true)
	{
		//���킪����ꂽ���ƕK�E�Z�J�E���g���K��l��荂����
		if (m_pModelPrts[18]->GetDraw() == true && m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
		{
			SpecialAttack = true;       //�K�E�Z�t���O��On�ɂ���  
			m_nSpecialAttackCount = 0;  //�K�E�Z�J�E���g�̏�����

			//�E�����̎�
			if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�K�E�Z�̃G�t�F�N�g�̐���
				m_nMotionFrame = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                             //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 1;                                                     //�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(GetPosPrts(17).x + 220.0f,                        //�G�t�F�N�g�̏o���ʒu��ݒ�
					GetPosPrts(17).y, GetPosPrts(17).z));
			}

			//�������̎�
			else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�K�E�Z�̃G�t�F�N�g�̐���
				m_nMotionFrame001 = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                          //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 2;											         //�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(GetPosPrts(17).x - 50.0f, 				         //�G�t�F�N�g�̏o���ʒu��ݒ�
					GetPosPrts(17).y, GetPosPrts(17).z));
			}
		}
	}

	//=================================================
	//A�L�[�������ꂽ���i�����ꑱ�������j
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_LEFT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI;                                //�J�����̌����ɍ��킹�Č���
		SetAddjustMove().x -= sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X���̈ړ��ʂ��J�����̌������猸�Z
		SetAddjustMove().z -= cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z���̈ړ��ʂ��J�����̌������猸�Z
		m_nRotNumber = 1;                                                                                        //�����ԍ��̐ݒ�

		//�����ĂȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//=================================================
	//D�L�[�������ꂽ���i�����ꑱ�������j
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_RIGHT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI;                         //�J�����̌����ɍ��킹�Č���
		GetMove().x += sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X���̈ړ��ʂ��J�����̌���������Z
		GetMove().z += cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z���̈ړ��ʂ��J�����̌���������Z
		m_nRotNumber = 2;                                                                                 //�����ԍ��̐ݒ�

		//�����ĂȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//=================================================
	//���̑�
	else
	{
		//�����ĂȂ����Ɛ������łȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0 && m_bFly == false)
		{
			SpecialAttack = false;                                   //�K�E�Z�t���O��Off�ɂ���  
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::NEUTRAL); //�ҋ@���[�V����
		}
	}

	//=================================================
	//space�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_SPACE) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT); //BDM�𗬂�

		//�E�����̎�
		if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
		{
			m_nMotionFrame = 60;   //�e�����t���[����ݒ�

			//�e�̐ݒ�
			CManagerBullet::Create(D3DXVECTOR3(GetPosPrts(17).x + 240.0f, GetPosPrts(17).y, GetPosPrts(17).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, 0.0f), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}

		//�������̎�
		else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
		{
			m_nMotionFrame001 = 60; //�e�����t���[����ݒ�

			//�e�̐ݒ�
			CManagerBullet::Create(D3DXVECTOR3(GetPosPrts(17).x - 50.0f, GetPosPrts(17).y, GetPosPrts(17).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}
	}

	//=================================================
	//X�L�[��A�{�^���������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_X) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetJumpFlag(true);                                       //���ł���ɐݒ�
	}

	//=================================================
	//�L�[��������ĂȂ��A�W�����v�����Ă��鎞
	else if (GetJumpFlag() == true)
	{
		//�R���Q�[�W�̏�񂪂��鎞
		if (CManager::GetInstance()->GetFuelGage() != nullptr)
		{
			//X�L�[�������ꂽ����Joy�L�[��A�L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_X) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
			{
				//�`���[�W���������Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetChage() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = true;   //�R���Q�[�W���g���Ă���ɐݒ�
				}
			}
			else
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false;  //�R���Q�[�W���g���Ă��Ȃ��ɐݒ�
				SetGravityFlag(true);                                      //�d��ON
			}
		}
	}

	//=================================================
	//�E���̏e�Ɋւ���t���[���̏���
	if (m_nMotionFrame >= 0)
	{
		m_nMotionFrame--;                            //�e�����t���[�������炷
		SetMotion(CCharacter::MOTIONSTATE::ACTION);  //���A�N�V�����̐ݒ�
	}

	//=================================================
	//�����̏e�Ɋւ���t���[������
	if (m_nMotionFrame001 >= 0)
	{
		m_nMotionFrame001--;                          //�e�����t���[��001�����炷
		SetMotion(CCharacter::MOTIONSTATE::ACTION);	  //���A�N�V�����̐ݒ�
	}
}


//===============================================================================================================================================================================
//�V���b�v���̃L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::ShopKeySet()
{
	//=======================================================================================================================================================
	//�ʏ��Ԃ̎�
	//=======================================================================================================================================================
	if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
	{
		//F1�L�[��Joy�L�[�̂x�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			//�I���Q�[�W�P�ڂ𐶐�����
			if (m_pSelectGage == nullptr)
			{
				m_pSelectGage = CSelectGage::Create(); //�I���Q�[�W�̐���
			}

			//�I���Q�[�W��ڂ𐶐�����
			if (m_pSelectGage001 == nullptr)
			{
				m_pSelectGage001 = CSelectGage001::Create(); //�I���Q�[�W001�̐���

				//�I���Q�[�W001�̑傫����ݒ�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //��ڂ̃Q�[�W�̑傫���ɍ��킹��
			}

			//�w�iUI�𐶐�����
			if (CManager::GetInstance()->GetShopScreen() == nullptr)
			{
				CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCREEN, 0); //�w�i�̐���
			}

			//���������邩��UI�𐶐�����
			if (m_pBuyText == nullptr)
			{
				m_pBuyText = CBuyText::Create(); //�����e�L�X�g�̐���
			}

			m_PlayerState = CPlayerX::PLAYER_STATE::SHOP_MODE; //���[�h��ύX����
		}
	}

	//=======================================================================================================================================================
	//SHOP��Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE)
	{
		//�t���O��Ԃ��ʏ펞�̎�
		if (m_FlagSate == CPlayerX::PLAYER_STATE::NORMAI_MODE)
		{
			SelectGageUISize(50.0f, 270.0f);                  //�I���Q�[�W1�ڂ̑傫����ݒ肷��
			m_FlagSate = CPlayerX::PLAYER_STATE::SHOP_MODE;   //�t���O��Ԃ�X�̏�Ԃ֕ω�������
		}

		//������I�������Ƃ��i�O����X�^�[�g�������͂O�ɖ߂�j
		if (m_nBuyOrSendCount == 0)
		{
			//Enter�L�[������������Joy�L�[�̂a�L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
			{
				SelectGageUISize(50.0,150.0f);                    //�傫����ݒ�
				m_PlayerState = CPlayerX::PLAYER_STATE::BUY_MODE; //���[�h�𔃂����[�h�ɐݒ�
			}
		}

		//S�L�[�������ꂽ����Joy�L�[���L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			SelectGageUISizeCalculation("Plus", 400.0f, 400.0f); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount += 1;                              //�J�E���g��i�߂�

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount == 2 )
			{
				SelectGageUISize(50.0, 270.0f);  //�T�C�Y�𒲐�
				m_nBuyOrSendCount = 0;           //�J�E���g������������

			}
		}

		//W�L�[�������ꂽ����Joy�L�[�̏�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			SelectGageUISizeCalculation("Minus", 400.0f, 400.0f); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount -= 1;                               //�J�E���g�����炷

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount ==-1)
			{
				SelectGageUISize(450.0, 670.0f); //�T�C�Y�𒲐�
				m_nBuyOrSendCount = 1;           //�J�E���g������������

			}
		}

		//�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;  //�v���C���[�̏�Ԃ�ʏ��Ԃɐݒ�
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;     //�t���O��Ԃ�ʏ�̏�Ԃɐݒ�
		}
	}

	//=======================================================================================================================================================
	//������Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
	{
		//���������邩��UI��j������
		if (m_pBuyText != nullptr)
		{
			m_pBuyText->Release(); //��������
			m_pBuyText = nullptr;  //���𖳂���
			return;                //�����𔲂���
		}

		//���j���[�𐶐�����
		if (m_pMenyu == nullptr)
		{
			m_pMenyu = CManager2DUI::Create(CObject::TYPE_UI::SHOPMENU); //���j���[�̐���
		}

		//F1�L�[�������ꂽ����Joy�L�[�̂`�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();                             //�|�C���^�[�̏����������֐����Ă�
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;   //�v���C���[�̏�Ԃ�ʏ��Ԃɐݒ�
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;      //�t���O��Ԃ�ʏ�̏�Ԃɐݒ�
		}

		//S�L�[���������Ƃ�
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Plus", ADDJUST_SELECT_SIZEY, ADDJUST_SELECT_SIZEY); //�T�C�Y�𒲐�����

				//�I���Q�[�W001�̑傫����ݒ�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount ++; //�I���J�E���g�𑝂₷

				//�I���J�E���g������̒l�ɂȂ�����
				if (m_nSelectShopCount == 4 || m_nSelectShopCount == 5)
				{
					m_pSelectGage->GetSizeY() = 50.0f;   //�I���Q�[�W�̂P�ڂ�Y���̑傫����ݒ�
					m_pSelectGage->GetSize1Y() = 150.0f; //�I���Q�[�W�̂Q�ڂ�Y���̑傫����ݒ�

					//�I���Q�[�W001�̑傫����ݒ�
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 0; //�I���J�E���g�̏�����
				}
			}
		}

		//W�L�[���������Ƃ�
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			//�I���Q�[�W�̏�񂪂��鎞
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Minus", ADDJUST_SELECT_SIZEY, ADDJUST_SELECT_SIZEY); //�T�C�Y�𒲐�����

				//�I���Q�[�W001�̃T�C�Y�𒲐�
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount -= 1; //�I���J�E���g������

				//�I���J�E���g������̒l�̎�
				if (m_nSelectShopCount == -1)
				{
					m_pSelectGage->GetSizeY() = 530.0f;  //�I���Q�[�W�̂P�ڂ�Y���̑傫����ݒ�
					m_pSelectGage->GetSize1Y() = 630.0f; //�I���Q�[�W�̂Q�ڂ�Y���̑傫����ݒ�

					//�I���Q�[�W001�̃T�C�Y�𒲐�
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 3;              //�I���J�E���g��ݒ�
				}
			}
		}

		//Enter�L�[������������Joy�L�[��B�L�[�������ꂽ��
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
		{
			CreateGun(); //�e�̐��������֐����Ă�
		}
	}
}


//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISize(float fSIzeX,float fSIze1X)
{
	m_pSelectGage->GetSizeY() = fSIzeX;   //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ���������
	m_pSelectGage->GetSize1Y() = fSIze1X; //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ���������

	//�I���Q�[�W�Q�ڂ̑傫���𓯊�������
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}

//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISizeCalculation(const char* aSelect,float fSIzeX, float fSIze1X)
{
	//������Ŕ���
	if (aSelect == "Plus")
	{
		m_pSelectGage->SetAddjustSizeY() += fSIzeX;    //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ����������Z����
		m_pSelectGage->SetAddjustSize1Y() += fSIze1X;  //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ����������Z����
	}
	else if (aSelect == "Minus")
	{
		m_pSelectGage->SetAddjustSizeY() -= fSIzeX;    //�I���Q�[�W�̂P�ڂ�Y���̑傫���������Ɠ����������Z����
		m_pSelectGage->SetAddjustSize1Y() -= fSIze1X;  //�I���Q�[�W�̂Q�ڂ�Y���̑傫���������Ɠ����������Z����
	}

	//�I���Q�[�W�Q�ڂ̑傫����ݒ�
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}


//===============================================================================================================================================================================
//���퐶������
//===============================================================================================================================================================================
void CPlayerX::CreateGun()
{
	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 0)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[18]->GetDraw() == false)
		{
			m_pModelPrts[18]->SetDraw(true); //�`�悷��
		}
	}

	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 1)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[18]->GetDraw() == false)
		{
			m_pModelPrts[18]->SetDraw(true); //�`�悷��
		}
	}

	//�O�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 2)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[18]->GetDraw() == false)
		{
			m_pModelPrts[18]->SetDraw(true); //�`�悷��
		}
	}

	//�l�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 3)
	{
		//�e���`�悳��Ă��Ȃ���
		if (m_pModelPrts[18]->GetDraw() == false)
		{
			m_pModelPrts[18]->SetDraw(true); //�`�悷��
		}
	}

}

//===============================================================================================================================================================================
//�`�揈��
//===============================================================================================================================================================================
void CPlayerX::Draw()
{
	CCharacter::DrawPlayer(MAX_PRTS); //�p�[�c���Ƃ̕`�揈��
}

//===============================================================================================================================================================================
//�l�X�ȕ��̓����蔻��
//===============================================================================================================================================================================
void CPlayerX::BlockJudgement()
{
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount <CManager::GetInstance()->GetFieldBlockCount()+1; nCount++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.05f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y + CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}

					//���n���Ă��Ȃ���
					if (m_bLandingFlag == false)
					{
						m_nLandingFrame++; //���n�t���[����ݒ�

						SetMotion(MOTIONSTATE::LANDING); //���n���[�V�����̐ݒ�

						//���n�t���[�����K��l��荂����
						if (m_nLandingFrame >= 60)
						{
							m_bLandingFlag = true;                                                              //���n���Ă���ɐݒ�
							m_nLandingFrame = 0;                                                                //���n�t���[���̏�����
							CManager::GetScene()->SetPlay(true);                                                //�V�ׂ�ɐݒ�
						
						}
					}
				}
			}
		}
	}

	//�オ��p�̃u���b�N�̐���������
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetGoUpBlockCount() + 1; nCount1++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetGoUpBlock(nCount1) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize().y + CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//���p�u���b�N����
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetRoadBlockCount() + 1; nCount2++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//�����蔻��
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether();//�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//�ǌ����p�u���b�N����
	for (int nCount3 = 0; nCount3 < CManager::GetInstance()->GetWallRoadBlockCount() + 1; nCount3++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	//�ǌ���001�p�u���b�N����
	for (int nCount4 = 0; nCount4 < CManager::GetInstance()->GetWallRoadBlock001Count() + 1; nCount4++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//��ɏ���Ă��鎞
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				//�R���Q�[�W���g���Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
				}

				GravityTogether(); //�d�͂̓���

				//�ʒu�̓���
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;

				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}
		}
	}

	//�������u���b�N����
	for (int nCount5 = 0; nCount5 < CManager::GetInstance()->GetSmallBlockCount() + 1; nCount5++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlock(nCount5) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize() * 1.3f, GetMove()) == true)
			{

			}
			else
			{
				//��ɏ���Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), GetMove()) == true)
				{
					//�R���Q�[�W���g���Ă��鎞
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
					}

					GravityTogether(); //�d�͂̓���

					//�ʒu�̓���
					GetPos().y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;

					//���ł���
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
					}
				}
			}
		}
	}

	////��ǃu���b�N����
	//for (int nCount6 = 0; nCount6 < CManager::GetInstance()->GetUpWallBlockCount() + 1; nCount6++)
	//{
	//	if (CManager::GetInstance()->GetUpBlock(nCount6) != nullptr)
	//	{
	//		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//		{
	//			//GetPos().x = 100.0f;
	//		}
	//		else
	//		{
	//			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				GetPos().y = CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize().y + CManager::GetInstance()->GetUpBlock(nCount6)->GetPos().y;//y���̈ʒu��ݒ�
	//				if (GetJumpFlag() == true)
	//				{
	//					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
	//				}
	//			}
	//			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
	//			}
	//		}
	//	}
	//}

	//�������u���b�N001����
	for (int nCount7 = 0; nCount7 < CManager::GetInstance()->GetSmallBlock001Count() + 1; nCount7++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlock001(nCount7) != nullptr)
		{
			//��ɏ���Ă��鎞
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//�R���Q�[�W���g���Ă��鎞
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
				}

				GravityTogether(); //�d�͂̓���

				//�ʒu�̓���
				GetPos().y = CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos().y;


				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}

			//���ɓ������Ă��鎞
			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//���ł���
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
				}
			}
		}
	}
	
	//�{�X��̑���
	if (CManager::GetInstance()->GetFinalBlock() != nullptr)
	{
		//��ɏ���Ă��鎞
		if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFinalBlock()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalBlock()->GetModelSize(), GetMove()) == true)
		{
			//�R���Q�[�W���g���Ă��鎞
			if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false; //�R���Q�[�W��s�g�p�ɐݒ�
			}

			GravityTogether(); //�d�͂̓���

			//�ʒu�̓���
			GetPos().y = CManager::GetInstance()->GetFinalBlock()->GetModelSize().y + CManager::GetInstance()->GetFinalBlock()->GetPos().y;

			//���ł���
			if (GetJumpFlag() == true)
			{
				SetJumpFlag(false); //���ł��Ȃ��ɐݒ�
			}
		}
	}

	//�{�X��̓V��
	if (CManager::GetInstance()->GetFinalCeiling() != nullptr)
	{
		//���ɓ������Ă��鎞
		if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize()*5.0f, GetMove()) == true)
		{
			//���ɓ������Ă��鎞
			if (GetCollision()->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize() * 3.0f, GetMove()) == true)
			{
				SetGravityFlag(true);//�d��ON
			}
			CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = 0.0f;
		}
		//else
		//{
		//	CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CEvent::CANERA_POSY;    //�J�����̂x���̒l��ݒ�
		//}
	}

	//�o�g���V�b�v�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetSpeceBattleShip(1) != nullptr)
	{
		//�����蔻��
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSpeceBattleShip(1)->GetModelSize() * 1.1f) == true)
		{
			//NextStageMotion();
			m_bPlayerMoveNext = true; //����scene�֍s���t���t��ON�ɂ���
		}
	}

	//SHOP�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetShop() != nullptr)
	{
		//�����蔻��
		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize(), GetMove()) == true)
		{

		}

		//�~�̓����蔻��
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize() * 1.5f) == true)
		{
			//�b��text�̏�񂪂Ȃ���
			if (m_pTalkText == nullptr)
			{
				m_pTalkText = CUI::Create(CObject3D::TYPE_UI::TALKTEXTR); //����

				//�ʒu�̐ݒ�
				m_pTalkText->GetPos() = D3DXVECTOR3(CManager::GetInstance()->GetShop()->GetPos().x, CManager::GetInstance()->GetShop()->GetPos().y + 150.0f, CManager::GetInstance()->GetShop()->GetPos().z); //�ʒu�̏�����
			}

			//�v���C���[�̏�Ԃ��ʏ��Ԃ̎�
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				ShopKeySet(); //�X�p�̃L�[�Z�b�g�����֐����Ă�
			}
		}

		//�������Ă��Ȃ���
		else
		{
			//�b��text�̏�񂪂��鎞
			if (m_pTalkText != nullptr)
			{
				m_pTalkText->Release(); //��������
				m_pTalkText = nullptr;  //���𖳂���
			}
		}
	}
}

//=====================================================================
//���̃X�e�[�W�ɍs�����̃��[�V��������(��ɃX�y�[�X�V�b�v�̏���)
//=====================================================================
void CPlayerX::NextStageMotion()
{
	m_nNextStageFrame++;        //�t���[���𑝂₷

	SetPos(D3DXVECTOR3(
		CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().x,
		CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().y+100.0f,
		CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().z-250.0f));
	//GetPos().y= CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().y;

	//���s��
	if (m_nNextStageFrame <= 1)
	{
		CManager::GetInstance()->GetSpeceBattleShip(1)->GetRot().y = -D3DX_PI_ORI;  //Y���̌�����ݒ�
	}

	//���s��
	else if (m_nNextStageFrame <= 60*3)
	{
		//X���̈ړ�
		CManager::GetInstance()->GetSpeceBattleShip(1)->SetAddjustPos().x += (float)m_nNextStageFrame* MAX_POS_NEXTSTAGE; 
		SetAddjustPos().x+= (float)m_nNextStageFrame * MAX_POS_NEXTSTAGE;                                                
	}

	//�I��
	else
	{
		m_bNextStage = true; //����scene�֍s���t���t��ON�ɂ���
	}
}

//===============================================================================================================================================================================
//���f���̎擾
//===============================================================================================================================================================================
CPlayerX* CPlayerX::Create()
{
	CPlayerX* pPlayerX = new CPlayerX(3); //���I�m��

	//�������ɐ���������
	if (SUCCEEDED(pPlayerX->Init()))
	{
		pPlayerX->SetType(TYPE::PLAYER); //�^�C�v��PLAYER�ɐݒ�
		return pPlayerX;                 //�v���C���[�̏���Ԃ�
	}

	return nullptr; //����Ԃ�
}


//===============================================================================================================================================================================
//���ݍ���Ă���I�u�W�F�N�g��UI���o������
//===============================================================================================================================================================================
void CPlayerX::NowCreateObjectUI()
{
	//�P�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_1) == true)
	{
		//���̑Ώۂ̃I�u�W�F�N�g�̔ԍ����O�ȉ�
		if (m_ObjectNumber <= 0)
		{
			m_ObjectNumber = MAX_TEXT_OBJECT; //������Ă��鐔�ɂ���
		}
		else
		{
			m_ObjectNumber -= 1;              //���炷
		}

		//��񂪂��鎞
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //��������
			m_pNowCreateUI = nullptr;  //���𖳂���
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}

		//��񂪂Ȃ���
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}
	}

	//�Q�L�[�������ꂽ��
	else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_2) == true)
	{
		//�I�u�W�F�N�g�i���o�[����������Ă��鐔�ȏ�̎�
		if (m_ObjectNumber >= MAX_TEXT_OBJECT)
		{
			m_ObjectNumber = 0; //������
		}
		else
		{
			m_ObjectNumber += 1; //���₷
		}

		//��񂪂��鎞
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //��������
			m_pNowCreateUI = nullptr;  //����Ԃ�
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}

		//��񂪂Ȃ���
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //��������
		}
	}
}

//===============================================================================================================================================================================
//�ԍ��ō��I�u�W�F�N�g���w�肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::NowCreateNumberObj()
{
	//�d������鎞�̂�m_pLaserUI���K�v

	switch (m_ObjectNumber)
	{
	case 0:
		CObjectX::ObjectArrangement(TYPE::FIELDBLOCK, nullptr);      //�n�ʂ̔z�u����
		break;

	case 1:
		CObjectX::ObjectArrangement(CObjectX::TYPE::TELEPHONPOLE, m_pLaserUI); //�d���̔z�u����
		break;

	case 2:
		CObjectX::ObjectArrangement(TYPE::GOUPBLOCK, nullptr);       //�オ��p�u���b�N�̔z�u����
		break;
	}
}