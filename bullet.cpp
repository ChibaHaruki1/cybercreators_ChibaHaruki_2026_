//==================================
//
//�e�̏���[bullet.h]
//Auther:Chiba Haruki
//
//==================================

//==================================
//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "bullet.h"


//==============================================================================================================
//==================================================3D�e�̏���==================================================
//==============================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CManagerBullet::CManagerBullet(int nPriority) :CObject3D(nPriority)
{
	
}

//=====================
//�f�X�g���N�^
//=====================
CManagerBullet::~CManagerBullet()
{

}


//=====================
//����������
//=====================
HRESULT CManagerBullet::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	SetRot(D3DXVECTOR3(0.0f, INIT_ROTY, 0.0f));     //������ݒ�
	SetSizeX(MAX_BULLET3D_SIZE_X);                  //X���̑傫���̐ݒ�
	SetSize(GetSizeX(), MAX_BULLET3D_SIZE_Y, 0.0f); //�T�C�Y�̒���
	return S_OK;                                    //������Ԃ�
}


//=====================
//�I������
//=====================
void CManagerBullet::Uninit()
{
	CObject3D::Uninit();  //���N���X�̔j������
}


//=====================
//�X�V����
//=====================
void CManagerBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                         //�G�t�F�N�g�̃��C�t�̐ݒ�
	CManager::GetInstance()->GetEffect()->SetCol(255, 160, 0, GetAlpha());                  //�F�̐ݒ�

	//�A���t�@�l���O���傫����
	if (GetAlpha() >0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z����
	}

	SetAddjustLife()--; //���C�t�����炷

	//�������s����
	if (GetLife() <= 0)
	{
		//CallEffect(false);
		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@
}


//=====================
//�`�揈��
//=====================
void CManagerBullet::Draw()
{
	CObject3D::DrawBillboard(); //�`�揈�����Ă�
}


//====================
//�e�̈ʒu�̐ݒ菈��
//====================
void CManagerBullet::SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	SetPos(pos);    //�e�̈ʒu�������Ɠ�������
	SetMove(move);  //�e�̈ړ��ʂ������Ɠ�������
	SetLife(nLife); //������ݒ肷��
}


//=========================
//�e�̂̐���
//=========================
CManagerBullet* CManagerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject::TYPE type)
{
	CManagerBullet* pBullet3D = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���e�̎�
	if (type == CObject3D::TYPE::BULLET)
	{
		pBullet3D = new CBullet3D(3); //���I�m��

		//������������������
		if (SUCCEEDED(pBullet3D->Init()))
		{

		}
	}

	//�^�C�v���G�̒e�̎�
	else if (type == CObject3D::TYPE::ENEMYBULLET)
	{
		pBullet3D = new CEnemyBullet(3); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //�T�C�Y�̐ݒ�
		}
	}

	//�^�C�v����͂̒e�̎�
	else if (type == CObject3D::TYPE::BATTLESHIPBULLET)
	{
		pBullet3D = new CEnemyBulletBattleShip(3); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //�T�C�Y�̐ݒ�
		}
	}

	//�^�C�v���{�X�̒e�̎�
	else if (type == CObject3D::TYPE::BOSSBULLET)
	{
		pBullet3D = new CBossBullet(3); //���I�m��

		//������������������
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CBossBullet::MAX_BOSSBULLET_SIZE_X, CBossBullet::MAX_BOSSBULLET_SIZE_Y, CBossBullet::MAX_BOSSBULLET_SIZE_Z);      //�T�C�Y�̐ݒ�
		}
	}

	//���𖳂���
	if (pBullet3D != nullptr)
	{
		pBullet3D->SetFileNamePass("data\\TEXTURE\\bullet001.png"); //�t�@�C���p�X��ݒ�
		pBullet3D->SetInfo(pos, move, nLife);                       //�e�̏��������Ɠ���
		pBullet3D->Lood();                                          //�e�N�X�`���̓ǂݍ���
		return pBullet3D;                                           //���𖳂���
	}

	return nullptr;                                                 //����Ԃ�
}


//================================================================================================================================================
//�v���C���[�̒ʏ�e����
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CBullet3D::CBullet3D(int nPriority) : CManagerBullet(nPriority)
{
	
}

//======================
//�R���X�g���N�^
//======================
CBullet3D::~CBullet3D()
{

}

//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBullet3D::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g�𐶐��i1�ځj
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g�𐶐��i2�ځj
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //���G�t�F�N�g���Ă�
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //�j�ЃG�t�F�N�g���Ă�


	CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
	CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos());                                                     //�����G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetThander()->SetEffect(GetPos());                                                          //���G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetDebris()->SetEffect(GetPos());                                                           //�j�ЃG�t�F�N�g�̈ʒu��ݒ�
}

//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBullet3D::CollisionOnObject()
{
	//�G001�̏�񂪂��鎞
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetEnemy001Count() + 1; nCount1++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetEnemy001(nCount1) != nullptr)
		{
			//�����蔻��
 			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy001(nCount1)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy001(nCount1)->GetModelSize() * 0.5f, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy001(nCount1)->SetAddjustLife() -= MINUS_ENEMY001_LIFE;          //�G�̃��C�t�����炷

				//�G�̃��C�t���O�ȉ��̎�
				if (CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY001, nCount1);         //�|�C���^�[��nullptr�ɂ���
				}

				CallEffect(false); //�G�t�F�N�g�������Ă�
				SetLife(0);        //���C�t���O�ɂ���
				return;            //�����𔲂���
			}
		}
	}

	//�G002�̏�񂪂��鎞
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetEnemy002Count() + 1; nCount2++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetEnemy002(nCount2) != nullptr)
		{
			//�����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy002(nCount2)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy002(nCount2)->GetModelSize() * 0.5f, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy002(nCount2)->SetAddjustLife() -= MINUS_ENEMY001_LIFE;          //�G�̃��C�t�����炷

				//�G�̃��C�t���O�ȉ��̎�
				if (CManager::GetInstance()->GetEnemy002(nCount2)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY002, nCount2);         //�|�C���^�[��nullptr�ɂ���
				}

				CallEffect(false); //�G�t�F�N�g�������Ă�
				SetLife(0);        //���C�t���O�ɂ���
				return;            //�����𔲂���
			}
		}
	}

	//�J�����̏㕔���̏�񂪂��鎞
	if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
	{
		//�J�����Ƃ̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(),
			GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
			CManager::GetInstance()->GetSurveillanceCameraUp(0)->GetModelSize()))
		{
			CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->Release(); //�J�����̏㕔���̍폜
			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SURVEILLANCECAMERAUP, 0);                                    //�|�C���^�[��nullptr�ɂ���

			SetLife(0); //���C�t���O�ɂ���
			return;     //�����𔲂���
		}
	}

	//���[�V�����t���̓G001�̏�񂪂��鎞
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count()+1; nMotionInEnemy001++)
	{
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			for (int nMotionEnemy001 = 0; nMotionEnemy001 < CObjectX::MAX_ENEMYPARTS; nMotionEnemy001++)
			{
				//���[�V�����t���̓G001�̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nMotionEnemy001),
					GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(nMotionEnemy001) * ADDJUST_HIT_MOTIONENENY001))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->SetAddjustLife() -= MINUS_ENEMYMOTION001_LIFE;

					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{                                     
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //�|�C���^�[��nullptr�ɂ���
					}

					CallEffect(false); //�G�t�F�N�g�������Ă�
					SetLife(0);        //���C�t���O�ɂ���
					return;            //�����𔲂���
				}
			}
		}
	}

	//�{�X�̏�񂪂��鎞
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		//�{�X�̍ő�p�[�c������
		for (int nCount2 = 2; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//�p�[�c�̕`�悪����Ă��鎞
			if (CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->GetDraw() == true)
			{
				//�{�X�Ƃ̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
					MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), GetSizeX(), nCount2))
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= CMain::SCREEN_WIDTH * MINUS_BOSS_HPGAGE; //�{�X��HP�Q�[�W�����炷

					//�w���parts��`�悵�Ȃ��{��������O�������ɂ���(�E�����)
					if ( nCount2 == 11 || nCount2 == 12 || nCount2 == 13)
					{
						CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->SetDraw(false); //�`������Ȃ��ɐݒ�
					}

					CallEffect(false);       //�G�t�F�N�g�������Ă�
					CObject3D::Release();    //���g�̉��
					return;                  //�����𔲂���
				}
			}
		}
	}
}


//======================================================================================================================================================================
//�G�̒e�̏���
//======================================================================================================================================================================

//static�ϐ��̏�����
float CEnemyBullet::m_fAdditionPosY = MINUS_ROTY; //�ʒu�������ݒ�

//=====================
//�R���X�g���N�^
//=====================
CEnemyBullet::CEnemyBullet(int nPriority) :CManagerBullet(nPriority)
{
	
}

//=====================
//�f�X�g���N�^
//=====================
CEnemyBullet::~CEnemyBullet()
{
	
}


//=====================
//�X�V����
//=====================
void CEnemyBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, BLUE, GetAlpha());                   //�F�̐ݒ�
	SetAddjustPos().y -= m_fAdditionPosY;                                                   //Y���̈ʒu�����炷

	//�A���t�@�l��0���傫����
	if (GetAlpha() > 0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
	}

	SetAddjustLife()--; //�����J�E���g

	//�������s����
	if (GetLife() <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CEnemyBullet::CallEffect(bool bUse)
{
	
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CEnemyBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * ADDJUST_HIT, MAX_BULLET3D_SIZE_Y * ADDJUST_HIT, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HP�Q�[�W�����炷

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}


//======================================================================================================================================================================
//��͂̒e�̏���
//======================================================================================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CEnemyBulletBattleShip::CEnemyBulletBattleShip(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//�f�X�g���N�^
//=====================
CEnemyBulletBattleShip::~CEnemyBulletBattleShip()
{

}


//=====================
//�X�V����
//=====================
void CEnemyBulletBattleShip::Update()
{
	SetAddjustFrame()++; //�t���[���𑝂₷

	//�t���[�����K��l��荂����
	if (GetFrame() >= 10)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //�G�t�F�N�g�i�O�Ձj�𐶐�����
		CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                         //�G�t�F�N�g�̃��C�t��ݒ�
		CManager::GetInstance()->GetEffect()->SetCol(0, 0, BLUE, GetAlpha());                   //�F�̐ݒ�
		SetFrame(0);                                                                            //�t���[���̏�����

		//�A���t�@�l��0���傫����
		if (GetAlpha() > 0)
		{
			SetAddjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
		}
	}
	
	SetAddjustPos().y -= 2.5f;     //Y���̈ʒu�����炷

	SetAddjustLife()--;            //�����J�E���g

	//�������s����
	if (GetLife() <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CEnemyBulletBattleShip::CallEffect(bool bUse)
{

}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CEnemyBulletBattleShip::CollisionOnObject()
{
	//�̂̓����蔻��݂̂ŏ������y������
	D3DXVECTOR3 pos = CManager::GetScene()->GetPlayerX()->GetPosPrts(0);

	//�v���C���[�̓����蔻��
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), pos,
		MAX_BULLET3D_SIZE_X * ADDJUST_HIT, MAX_BULLET3D_SIZE_Y * ADDJUST_HIT, MAX_BULLET3D_SIZE_Z,
		CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0), 0.0f) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HP�Q�[�W�����炷

		CallEffect(true);         //�G�t�F�N�g�������Ă�
		CObject3D::Release();     //���g�̉��
		return;                   //�����𔲂���
	}
}


//======================================================================================================================================================================
//�{�X�̒e�̏���
//======================================================================================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CBossBullet::CBossBullet(int nPriority) :CManagerBullet(nPriority)
{
	
}

//=====================
//�f�X�g���N�^
//=====================
CBossBullet::~CBossBullet()
{
	CObject3D::Uninit();
}


//=====================
//�X�V����
//=====================
void CBossBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, GetAlpha());                    //�F�̐ݒ�

	SetAddjustPos().y -= MINUS_POSY;                                                        //Y���̈ʒu�����Z����

	//�A���t�@�l��0���傫����
	if (GetAlpha() >0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����Z
	}

	SetAddjustLife()--; //���C�t�����炷

	//�������s����
	if (GetLife() <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBossBullet::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //����̉��G�t�F�N�g���Ă�
	CManager::GetInstance()->GetPillarOfFire()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 200.0f, GetPos().z));   //����̉��G�t�F�N�g�̈ʒu��ݒ�
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBossBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HP�Q�[�W�����炷

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}