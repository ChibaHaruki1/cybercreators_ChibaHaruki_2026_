//=========================================================================
//
//���[�V�����t���̓G�̏���[enemyinmotion.cpp]
//Auther;Haruki Chiba
//
//=========================================================================


//==============================
//�C���N���[�h
#include "enemyinmotion.h"
#include "manager.h"
#include <time.h>


//=============================
//�R���X�g���N�^
//=============================
CManagerEnemyInMotion::CManagerEnemyInMotion(int nPriority) : CEnemyCharacter(nPriority)
{
	m_nJumpFrame = 0;   //��Ԃ܂ł̎��Ԃ̏�����
	JumpNumber = 0;     //��Ԕԍ��̏�����
	JumpRecastTime = 0; //��Ԃ܂ł̃��L���X�g�^�C���̏�����
}

//=============================
//�f�X�g���N�^
//=============================
CManagerEnemyInMotion::~CManagerEnemyInMotion()
{

}

//=============================
//����������
//=============================
HRESULT CManagerEnemyInMotion::Init()
{
	//�������ɐ���������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;                           //���s��Ԃ�
	}

	CEnemyCharacter::LoodEnemy(GetFileName());   //�ǂݍ��ރt�@�C���p�X��ݒ�
	CEnemyCharacter::SetMotionEnemy(ENEMYWALK);  //���[�V�����̏�����

	return S_OK;                                 //������Ԃ�
}

//==============================
//�j������
//==============================
void CManagerEnemyInMotion::Uninit()
{
	CEnemyCharacter::Uninit(); //�e�p�[�c�̔j������
}

//==============================
//�X�V����
//==============================
void CManagerEnemyInMotion::Update()
{
	
}

//==============================
//�`�揈��
//==============================
void CManagerEnemyInMotion::Draw()
{
	CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //�`�揈��
}

//==============================
//��������
//==============================
CManagerEnemyInMotion* CManagerEnemyInMotion::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemyInMotion* pEnemyInMotion = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v�����[�V�����t���̓G�̎�
	if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		pEnemyInMotion = new CEnemyInMotion();   //���I�m��
		pEnemyInMotion->SetFileName("Enemy000"); //�t�@�C���p�X�̐ݒ�
	}

	//�^�C�v�����[�V�����t���̓G001�̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		pEnemyInMotion = new CEnemyInMotion001(); //���I�m��
		pEnemyInMotion->SetFileName("Enemy001");  //�t�@�C���p�X�̐ݒ�
	}

	//��񂪂��鎞
	if (pEnemyInMotion != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pEnemyInMotion->Init()))
		{
			pEnemyInMotion->SetPos(pos); //�ʒu�̓���
			return pEnemyInMotion;       //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//====================================================================================================================================
//�G�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion::CEnemyInMotion(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetAddjustRot().y -= D3DX_PI_ORI; //�����̐ݒ�
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion::~CEnemyInMotion()
{

}

//==============================
//�X�V����
//==============================
void CEnemyInMotion::Update()
{
	CEnemyCharacter::UpdateEnemy001();                                                       //���[�V�����̏����X�V����

	//�v���C���[�Ɠ������Ă��鎞
	if (CObjectX::CollisionPlayerInEnemy(this,4.0f)==true)
	{
		CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);     //���[�V�����̎�ނ�ݒ�

		SetAddjustFrame()++; //�t���[���𑝂₷

		//�t���[�����K��l��荂����	
		if (GetFrame()>= MAX_FRAME_BUULET)
		{
			//�e�̐���
			CManagerBullet::Create(D3DXVECTOR3(this->GetPosPrtsEnemy(0).x, this->GetPosPrtsEnemy(0).y, this->GetPosPrtsEnemy(0).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				CManagerBullet:: SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

			SetFrame(0); //�t���[�����O�ɂ���
		}
	}

	//�������Ă��Ȃ���
	else
	{
		//���ł��Ȃ���
		if (GetJumpFlag() == false)
		{
			CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�
			TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //�v���C���[�Ɍ������悤�ɐݒ�
		}
	}

	Junp(TYPE::ENEMYINMOTION, 15.0f);                          //�W�����v�Əd�͏����֐����Ă�

	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//�n�ʗp�u���b�N�̏�񂪂��鎞
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			//���
			if (JumpNumber == -1)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (GetCollision() ->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, GetMove()) == true)
				{
					//��Ԏ��̃��L���X�g�^�C�����O�ȉ��̎�
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++; //��Ԃ܂ł̎��Ԃ𑝂₷

						//��Ԃ܂ł̎��Ԃ��K��l��荂����
						if (m_nJumpFrame >= MAX_FRAME_JUMP)
						{
							SetJumpFlag(true); //��ԃt���O��On�ɂ���

							m_nJumpFrame = 0;  //��Ԃ܂ł̎��Ԃ̏�����
							JumpNumber++;      //��Ԕԍ��̑���
							return;            //�����𔲂���
						}
					}

					//��Ԏ��Ԃ̃��L���X�g�^�C�����O�ȏ�̎�
					else if (JumpRecastTime >= 0)
					{
						JumpRecastTime--; //���炷
					}

				}
				else
				{
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						//y���̈ʒu��ݒ�
						SetAddjustPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
					}
				}
			}

			//��΂Ȃ�
			else if (JumpNumber == 0)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (GetCollision() ->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, GetMove()) == true)
				{
					JumpRecastTime = 5; //���L���X�g�^�C���̐ݒ�
					JumpNumber = -1;    //��Ԕԍ��̎��͔�Ԃɐݒ�
					return;             //�����𔲂���
				}
				else
				{
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						//y���̈ʒu��ݒ�
						SetAddjustPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
					}
				}
			}

		}
	}

	CObjectX::Update(); //�ʒu�̍X�V
}


//====================================================================================================================================
//�G001�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	GetRot().y = -D3DX_PI_ORI; //������ݒ�i�E�����j
	SetLife(MAX_LIFE);         //���C�t�̐ݒ�
	m_nHitFrame = 0;           //�����������Ƀt���[���̏�����
	m_bHit = false;            //�������Ă��Ȃ��ɐݒ�
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion001::~CEnemyInMotion001()
{

}


//==============================
//�X�V����
//==============================
void CEnemyInMotion001::Update()
{
	//�v���C���[������͈͓̔��ɗ�����X�V���������s����
	if (CObjectX::CollisionPlayerInEnemy(this, 10.0f) == true)
	{
		//�����Ă��鎞
		if (GetLife() > 0)
		{
			CEnemyCharacter::UpdateEnemy001();                                                    //���[�V�����̏����X�V����

			//�v���C���[�Ɠ������Ă��鎞
			if (CObjectX::CollisionPlayerInEnemy(this, 4.0f) == true)
			{
				CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //���[�V�����̎�ނ�ݒ�

				SetAddjustFrame()++;     //�e�����ۂ̃t���[���𑝂₷

				//�t���[�����K�萔�ɒB������
				if (GetFrame()>= 60)
				{
					//�e�̐���
					CManagerBullet::Create(D3DXVECTOR3(this->GetPosPrtsEnemy(4).x + 100.0f, this->GetPosPrtsEnemy(4).y + 30.0f, this->GetPosPrtsEnemy(4).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED),
						CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

					SetFrame(0); //�t���[�����O�ɂ���
				}

				//�v���C���[���G�ɐڐG������
				if (CObjectX::CollisionPlayerInEnemy(this, 1.5f) == true)
				{
					m_bHit = true; //�������������On�ɂ���
				}
			}

			//�v���C���[�Ɠ������ĂȂ���
			else
			{
				//�����̏�����
				m_pModelPrtsEnemy[0]->GetRot().x = 0.0f;                  //�p�[�c�̌����̏�����
				CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY);  //�e�̌����̏�����

				//���ł��Ȃ��Ƃ�
				if (GetJumpFlag() == false)
				{
					CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�

					//�W�����v�̃��L���X�g�^�C�����؂ꂽ��
					if (m_nJumpFrame == 0)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);        //�v���C���[�Ɍ������悤�ɐݒ�
					}
				}
			}

			//�v���C���[���G�ɓ���������
			if (m_bHit == true)
			{
				PlayerBloWwaway();               //�v���C���[�̐�����я������Ă�
			}

			Junp(TYPE::ENEMYINMOTION001, 15.0f); //�W�����v�Əd�͏����֐����Ă�
			WhenCollisionBlock();                //�n�ʗp�̃u���b�N�ɐG��Ă��鎞�̏���
			CObjectX::Update();                  //move�l�̍X�V
		}

		//���񂾎�
		else if (GetLife() <= 0)
		{
			SetAddjustDieFrame()++; //���S�t���[���𑝂₷

			//srand((unsigned)time(NULL));  //�����n���������

			//���s��
			if (GetDieFrame() <= 1)
			{
				//�����G�t�F�N�g���Ă�
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//�����G�t�F�N�g�̑傫����ݒ�
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);                                 
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);      


				//�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());         
				CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos());      
			}

			//���s��
			else if (GetDieFrame() <= 20)
			{

			}

			//��O�s��
			else if (GetDieFrame() <= 21)
			{
				SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //�����̐���

				//�����G�t�F�N�g���Ă�
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//�����G�t�F�N�g�̑傫����ݒ�
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);


				//�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//��l�s��
			else if (GetDieFrame() <= 40)
			{

			}

			//��܍s��
			else if (GetDieFrame() <= 41)
			{
				SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //�����̐���

				//�����G�t�F�N�g���Ă�
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//�����G�t�F�N�g�̑傫����ݒ�
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);

				//�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//��Z�s��
			else if (GetDieFrame() <= 60)
			{

			}

			//�掵�s��
			else if (GetDieFrame() <= 61)
			{

				SetRandom(-MIN_RANDOM2 + rand() % MAX_RANDOM2); //�����̐���

				//�����G�t�F�N�g���Ă�
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//�����G�t�F�N�g�̑傫����ݒ�
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, 0.0);

				//�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//�I��
			else
			{
				CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);  //�X�R�A�����Z
				CObjectX::Release();                                            //���g���폜
				return;                                                         //�����𔲂���
			}
		}
	}
}

//===============================================
//�v���C���[���G�ɓ���������
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //���������t���[���𑝂₷

	//���������u��
	if (m_nHitFrame <= 1)
	{
		//�v���C���[��HP�����
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * MAX_DAMAGE;
	}

	//Hitframe������l�ւ�������
	else if (m_nHitFrame <= 20)
	{

		//�������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += 10.0f;  //�E�Ɉړ�
		}

		//�E�����̎�
		else if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= 10.0f;  //���Ɉړ�
		}
	}

	//�I��
	else
	{
		m_nHitFrame = 0; //hitframe��������
		m_bHit = false;  //�������������off�ɂ���
	}
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//�������̎�
	if (GetRot().y >= D3DX_PI_ORI)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber()==1)
		{
			m_pModelPrtsEnemy[0]->GetRot().x += ADDJUST_PRTAS_ROTX;         //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() -= ADDJUST_BULLET_ROTY;  //�e��X���̌��������Z����
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			m_pModelPrtsEnemy[0]->GetRot().x -= ADDJUST_PRTAS_ROTX;        //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() += ADDJUST_BULLET_ROTY; //�e��X���̌��������Z����
		}
	}

	//�E�����̎�
	else if (GetRot().y <= -D3DX_PI_ORI)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 1)
		{
			m_pModelPrtsEnemy[0]->GetRot().x -= ADDJUST_PRTAS_ROTX;        //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() += ADDJUST_BULLET_ROTY; //�e��X���̌��������Z����
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			m_pModelPrtsEnemy[0]->GetRot().x += ADDJUST_PRTAS_ROTX;        //�p�[�c��X���̌��������Z����
			CEnemyBullet::SetAddjustAdditionPosY() -= ADDJUST_BULLET_ROTY; //�e��X���̌��������Z����
		}
	}

	Correctionrot(); //�������C������֐����Ă�
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//�G�̍ő�p�[�c������
		for (int nEnemyCount = 0; nEnemyCount < MAX_ENEMYPARTS; nEnemyCount++)
		{
			//�n�ʗp�u���b�N�̏�񂪂��鎞
			if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
			{
				//���
				if (JumpNumber == -1)
				{
					//���@�ƒn�ʗp�u���b�N������������
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, GetMove()) == true)
					{
						//���L���X�g�^�C�����O�ȉ��̎�
						if (JumpRecastTime <= 0)
						{
							m_nJumpFrame++;             //��ԃt���[���𑝂₷

							SetMotionEnemy(ENEMYJUMP);  //�W�����v���[�V�����̐ݒ�

							//�W�����v�t���[�����K��l��荂����
							if (m_nJumpFrame >= 40)
							{
								SetJumpFlag(true); //���
								m_nJumpFrame = 0;  //�t���[���̏�����
								JumpNumber++;      //�W�����v�i���o�[�𑝂₷�i���͔�΂Ȃ��ɐݒ�j

								return;            //�����𔲂���
							}
						}

						//���L���X�g�^�C�����O�ȏ�̎�
						else if (JumpRecastTime >= 0)
						{
							JumpRecastTime--; //���炷
						}
						return; //�����𔲂���
					}
					else
					{
						//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //�d�͂𓯊�������

							//y���̈ʒu��ݒ�
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
						}
					}
				}

				//��΂Ȃ�
				else if (JumpNumber == 0)
				{
					//���@�ƒn�ʗp�u���b�N������������
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, GetMove()) == true)
					{
						JumpRecastTime = 5; //���L���X�g�^�C���̐ݒ�
						JumpNumber = -1;    //�W�����v�i���o�[�̐ݒ�i���͔�Ԃɐݒ�j
						return;             //�����𔲂���
					}
					else
					{
						//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //�d�͂𓯊�������

							//y���̈ʒu��ݒ�
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

							SetJumpFlag(false); //��΂Ȃ�
						}
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
			//�������Ă��鎞
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.01f, GetMove()) == true)
			{

			}
			else
			{
				//��ɓ������Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether(); //�d�͂̓���

					//y���̈ʒu��ݒ�
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					SetJumpFlag(false); //�W�����v�t���O��Off
				}
			}
		}
	}

	//�ǌ����p�u���b�N����
	for (int nCount3 = 0; nCount3 < CManager::GetInstance()->GetWallRoadBlockCount() + 1; nCount3++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			//�������Ă��鎞
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * 1.01f, GetMove()) == true)
			{

			}
			else
			{
				//��ɓ������Ă��鎞
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether(); //�d�͂̓���

					//y���̈ʒu��ݒ�
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					SetJumpFlag(false); //�t���O��Off�ɂ���
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
			//��ɓ������Ă��鎞
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				GravityTogether(); //�d�͂̓���

				//y���̈ʒu��ݒ�
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;


				SetJumpFlag(false); //�t���O��Off�ɂ���
			}
		}
	}
}

//===============================================
//�������C��
//===============================================
void CEnemyInMotion001::Correctionrot()
{
	//�����Z���Ă����ϐ��̒l������̈ʒu�͈͓̔��̎�
	if (CEnemyBullet::GetAdditionPosY() <= -CEnemyBullet::MINUS_ROTY && CEnemyBullet::GetAdditionPosY() >= -CEnemyBullet::MINUS_ROTY+1.0f)
	{
		GetRot().y = -D3DX_PI_ORI;                                                                     //�������t�ɐݒ�
		m_pModelPrtsEnemy[0]->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));                                     //�����̏�����
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY * MULTIPLICATIOB_ADDJUST_BULLET_ROTY);  //�e�̏o������𒲐�
	}
	else if (CEnemyBullet::GetAdditionPosY() >= CEnemyBullet::MINUS_ROTY * IF_ADDJUST_BULLET_ROTY && CEnemyBullet::GetAdditionPosY() <= CEnemyBullet::MINUS_ROTY * IF_ADDJUST_BULLET_ROTY+1.0f)
	{
		GetRot().y = D3DX_PI_ORI;                                                                      //�������t�ɐݒ�
		m_pModelPrtsEnemy[0]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));                                   //�����̏�����
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY * MULTIPLICATIOB_ADDJUST_BULLET_ROTY);  //�e�̏o������𒲐�
	}
}