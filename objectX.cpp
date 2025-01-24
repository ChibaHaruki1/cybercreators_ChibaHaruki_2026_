//=========================================
//
//X�I�u�W�F�N�g�̏���[objectX.cpp]
//Auther:Chiba Haruki
//
//=========================================


//============================
//�C���N���[�h
#include "objectX.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObjectX::CObjectX(int nPriority) : CObjectManagerX(nPriority)
{
	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr;
	}

	//�v���C���[�̃p�[�c������
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_minPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //�p�[�c�̑傫���̍ŏ��l
		m_maxPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //�p�[�c�̑傫���̍ő�l
		m_ModelSizePrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�[�c�̑傫��
		m_posPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //�p�[�c�̈ʒu
	}

	//�{�X�̃p�[�c������
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_ModelSizePrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�[�c�̑傫��
		m_posPrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //�p�[�c�̈ʒu
	}

	m_pMesh = nullptr;                      //���b�V���|�C���^�[�̏�����
	m_pBuffMat = nullptr;                   //�o�b�t�@�|�C���^�[�̏�����
	m_dwNumMat = 0;                         //�}�e���A�����̏�����
	m_pMat = nullptr;                       //�}�e���A���|�C���^�[�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����������������
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�F�̏�����

	m_nLife = 0;                            //���C�t�̏�����
	m_nRandom = 0;                          //�����̏�����
	m_nFrame = 0;                           //�t���[���̏�����
	m_nDieFrame = 0;                        //���S�t���[���̏�����
	m_fGravity = 0.0f;                      //�d�͉����x�̏�����
	m_fAngle = 0.0f;                        //�p�x���璷�������߂�l�̏�����
	m_pCollision = nullptr;                 //�����蔻��̃|�C���^�[�̏�����
	m_aFileName = nullptr;                  //�t�@�C���p�X�̏�����
	m_bGravityFlag = true;                  //�d�̓t���O�̏�����
	m_bJumpFlag = false;                    //���ł��邩�̔���p�̏�����
	m_bOneFlag = false;                     //��x����������ʂ������t���O�̏�����
	pUI = nullptr;                          //UI�|�C���^�[�̏�����
}


//=====================
//�f�X�g���N�^
//=====================
CObjectX::~CObjectX()
{
	//�����蔻��̏�񂪂��鎞
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;     //��������
		m_pCollision = nullptr;  //���𖳂���
	}
}


//=====================
//����������
//=====================
HRESULT CObjectX::Init()
{
	m_pCollision = new CCollision(); //�����蔻��̏����擾����
	return S_OK;                     //������Ԃ�
}


//=====================
//�I������
//=====================
void CObjectX::Uninit()
{
	//���b�V���̏�񂪂��鎞
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release(); //��������
		m_pMesh = nullptr;  //���𖳂���
	}

	//�o�b�t�@�̏�񂪂��鎞
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release(); //��������
		m_pBuffMat = nullptr;  //���𖳂���
	}

	//�}�e���A���̏�񂪂��鎞
	if (m_pMat != nullptr)
	{
		m_pMat = nullptr;      //���𖳂���
	}

	//�e�N�X�`���̍ő吔����
	for (int nCntMat = 0; nCntMat < MAX_TEXTURE; nCntMat++)
	{
		//�e�N�X�`���̏�񂪂��鎞
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release(); //��������
			m_pTexture[nCntMat] = nullptr;  //���𖳂���
		}
	}
}


//=======================
//�X�V����
//=======================
void CObjectX::Update()
{
	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V�i����������j
	m_move.x += (0.0f - m_move.x) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_move.y += (0.0f - m_move.y) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_move.z += (0.0f - m_move.z) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
}


//=======================
//�`�揈��
//=======================
void CObjectX::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;         //���݂̃}�e���A���̕ۑ��p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^������
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�}�e���A���̕���
	for (int nCntMat1 = 0; nCntMat1 < (int)m_dwNumMat; nCntMat1++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat1]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat1);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===============================================================================================================================================================================
//�d�͏���(�����ł���������)
//===============================================================================================================================================================================
void CObjectX::Gravity()
{
	//�d��ON�̎�
	if (m_bGravityFlag == true)
	{
		m_fGravity += MAX_GRAVITY_G; //�d�͉����x
		m_pos.y -= m_fGravity;       //�v���C���[�̂�pos�ɏd�͉����x������
	}
}

//======================================================================================================================================
//�ʒu�̓�������
//======================================================================================================================================
void CObjectX::GravityTogether()
{
	m_fGravity = 0.0f; //�d�͂̏�����

	//���̂ݔ��
	if (m_bJumpFlag == true)
	{
		m_bJumpFlag = false; //�t���O��flase�ɂ���
	}
	m_bGravityFlag = true;   //�d�͂�On�ɂ���
}

//======================================================================================================================================
//�W�����v����
//======================================================================================================================================
void CObjectX::Junp(TYPE type,float fJumpPwer)
{
	//�W�����v�t���OON�̎�
	if (m_bJumpFlag == true)
	{
		m_pos.y += fJumpPwer;  //pos.y�l�����Z������

		//�^�C�v���v���C���[�̎�
		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->CCharacter::SetMotion(CCharacter::MOTIONSTATE::JUMP); //�W�����v���[�V�����ɐݒ�
			CManager::GetScene()->GetPlayerX()->SetMotionType(true);                                  //���[�V�����^�C�v�̐ݒ�i���ꃂ�[�V�����j
		}

		//�^�C�v�����[�V�����t���̓G�̎�
		else if (type == TYPE::ENEMYINMOTION)
		{
			//�W�����v���[�V�����ɐݒ�
			CManager::GetInstance()->GetEnemyInMotion(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			//CManager::GetInstance()->GetEnemyInMotion(0)->SetMotionType(true); //���[�V�����^�C�v�̐ݒ�i���ꃂ�[�V�����j
			m_pos.x += 3.0f;                                                   //X���̈ʒu�𑝂₷
		}
		else if (type == TYPE::ENEMYINMOTION001)
		{
			//�W�����v���[�V�����ɐݒ�
			CManager::GetInstance()->GetEnemyInMotion001(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			//CManager::GetInstance()->GetEnemyInMotion001(0)->SetMotionType(true);
			m_pos.x += 3.0f;                                                   //X���̈ʒu�𑝂₷
		}
	}
	else
	{
		//�^�C�v���v���C���[�̎�
		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->SetMotionType(false); //���ꃂ�[�V������Off
		}
	}

	Gravity();  //�d�͏������Ă�
}

//======================================================================================================================================
//�����Ŏw�肵���ڕW�Ɍ���������
//======================================================================================================================================
void CObjectX::TargetHeadingTowards(CObjectX*pObject,float MAX_SPEED)
{
	//�Ίp���̊p�x���Z�o����i�ڕW�[���@�j
	m_fAngle = atan2f(pObject->m_pos.x - m_pos.x, pObject->m_pos.z - m_pos.z);

	//�ړ�����
	m_move.x = sinf(m_fAngle) * MAX_SPEED;
	m_move.z = cosf(m_fAngle) * MAX_SPEED;

	m_rot.y = m_fAngle * -1; //�������v���C���[�ɍ��킹��
}


//================================================
//�v���C���[�ƃ{�X�̓����蔻��
bool CObjectX::CollisionBossPrts()
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_BOSSPARTS-1; nCount++)
	{
		//�����蔻��
		if (m_pCollision->CircleCollisionAll(m_posPrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), m_ModelSizePrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true; //��������
		}
	}
	
	return false;        //�������Ă��Ȃ�
}

//=============================
//�p��obj�̉E���̓����蔻��
bool CObjectX::CollisionRightSelectPlayer(CObjectX* pObject)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		//�E���̓����蔻��
		if (m_pCollision->ColiisionBoxRight(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true; //��������
		}
	}

	return false;        //�������Ă��Ȃ�
}

//=============================
//�p��obj�̍����̓����蔻��
bool CObjectX::CollisionLeftSelectPlayer(CObjectX* pObject)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		//�����̓����蔻��
		if (m_pCollision->ColiisionBoxLeft(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true; //�������Ă���
		}
	}

	return false;        //�������Ă��Ȃ�
}

//=============================
//�v���C���[�Ƒ��̓����蔻��
//=============================
bool CObjectX::CollisionPlayerSelect(CObjectX* pObject)
{
	//�����蔻��
	if (m_pCollision->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0), pObject->m_ModelSize) == true)
	{
		return true; //��������
	}

	return false;    //�������Ă��Ȃ�
}

//=============================
//�v���C���[�ƓG�̓����蔻��
//=============================
bool CObjectX::CollisionPlayerInEnemy(CObjectX* pObject,float fMagnification)
{
	//�v���C���[�ƓG�̓����蔻��
	if (m_pCollision->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->GetPos(), CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0) * fMagnification, pObject->GetModelSizePrtsEnemy(0)* fMagnification) == true)
	{
		return true; //��������
	}

	return false;    //�������Ă��Ȃ�
}


//==============================
//X�t�@�C���̃T�C�Y�̎擾
//==============================
void CObjectX::Size()
{
	int nNumVertex; //���_���̊i�[
	DWORD dSIze;    //���_�̃t�H�[�}�b�g�T�C�Y�擾����ۊǂ���
	BYTE* pVtxByte; //���_�t�H�[�}�b�g�̎擾

	//���_�����擾
	nNumVertex = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_���b�V���̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//�ʒu�������邽�߂̕ϐ�
		D3DXVECTOR3 mtx; 

		mtx = *(D3DXVECTOR3*)pVtxByte; //���_�t�H�[�}�b�g��D3DXVECTOR3�ɕϊ�


		//=================================
		//X���p
		//================================= 

		//�擾�������l����ԑ傫����
		if (mtx.x > max.x)
		{
			max.x = mtx.x; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.x < min.x)
		{
			min.x = mtx.x; //���
		}


		//=================================
		//Y���p
		//=================================  

		//�擾�������l����ԑ傫����
		if (mtx.y > max.y)
		{
			max.y = mtx.y; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.y < min.y)
		{
			min.y = mtx.y; //���
		}


		//=================================
		//Z���p
		//================================= 

		//�擾�������l����ԑ傫����
		if (mtx.z > max.z)
		{
			max.z = mtx.z; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.z < min.z)
		{
			min.z = mtx.z; //���
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxByte += dSIze;
	}

	//Y���̍ŏ��l���O�ȉ��̎�
	if (min.y < 0)
	{
		//Y���̍ő�l���ŏ��l��菬������
		if (max.y < min.y)
		{
			max.y = min.y * -1.0f; //���]������
		}
		min.y = 0; //������
	}

	//�I�u�W�F�N�g�̃T�C�Y���v�Z����
	m_ModelSize = max - min;
}


//==================================
//�I�u�W�F�N�g�̔z�u
//==================================
void CObjectX::ObjectArrangement(CObjectX::TYPE type, CUI* pUI1)
{
	//O�L�[�������ꂽ���ɐ������鏈����ʂ�
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_O) == true)
	{
		//UI�̏�񂪂Ȃ���
		if (pUI == nullptr)
		{
			pUI = CCreateInObject::Create(CObject3D::TYPE_UI::CLING); //����
			pUI->SetSize(50.0f, 0.0f, 50.0f);                         //�傫���̐ݒ�
		}

		//�^�C�v���d���̎�
		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //�d���J�E���g��i�߂�
			CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //�S�Ă̓d���J�E���g��i�߂�

			//�d���̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), m_pos);

			//�Ď��J�����̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 180.0f, m_pos.z - 50.0f));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 170.0f, m_pos.z - 50.0f));

			//���[�U�[UI�̐����ƈʒu�𓯊�������
			pUI1 = CLaserCamare::Create(CObject3D::TYPE_UI::LASER);

			//���������I�u�W�F�N�g�̈ʒu�ɓ���
			pUI->GetPos() = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos();
		}

		//�n�ʗp�u���b�N�̎�
		else if (type == CObjectX::TYPE::FIELDBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(m_pos.x + 600.0f, m_pos.y, m_pos.z)); 
		}

		//�オ��p�u���b�N�̎�
		else if (type == CObjectX::TYPE::GOUPBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z)); 
		}

		//���p�u���b�N�̎�
		else if (type == CObjectX::TYPE::ROADBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));  
		}

		//�ǌ����p�u���b�N�̎�
		else if (type == CObjectX::TYPE::WALLROADBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//�ǌ����p001�u���b�N�̎�
		else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//�������p�u���b�N�̎�
		else if (type == CObjectX::TYPE::SMALLBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}

		//�������p001�u���b�N�̎�
		else if (type == CObjectX::TYPE::SMALLBLOCK_001)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}

		//��ɐݒu����p�u���b�N�̎�
		else if (type == CObjectX::TYPE::UPWALLBLOCK)
		{
			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
	}

	//�^�C�v���d���̎�
	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		//�d���J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() < CInstance::MAX_STAGEOBJECT && CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() > -1 && CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
		{
			/*if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y += 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y -= 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x += 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x -= 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}*/

			//M�L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->TextFileWrite(CObjectX::TYPE::TELEPHONPOLE, 
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y,
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z);

				return; //�����𔲂���
			}
		}
	}

	//�n�ʗp�u���b�N�̎�
	else if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		//�n�ʗp�u���b�N�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetFieldBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetFieldBlockCount() > -1 && CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x,
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y,
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//�オ��p�u���b�N�̎�
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		//�オ��p�u���b�N�̃J�E���g���ő吔���Ⴍ�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetGoUpBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetGoUpBlockCount() > -1 && CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���L�[�������ꂽ��
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x,
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y,
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//���p�u���b�N�̎�
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
	    //���p�u���b�N�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂���
		if (CManager::GetInstance()->GetRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetRoadBlockCount() > -1 && CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//�ǌ����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
	    //�ǌ����p�u���b�N�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlockCount() > -1 && CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//�ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
	    //�ǌ����p�u���b�N001�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetWallRoadBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlock001Count() > -1 && CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->TextFileWrite(
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//�������p�u���b�N�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
	//�������u���b�N�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlockCount() > -1 && CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}

	//�������p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
	    //�������u���b�N001�̃J�E���g���ő吔���Ⴍ�A�[�P��荂���A��񂪂��鎞
		if (CManager::GetInstance()->GetSmallBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlock001Count() > -1 && CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count()) != nullptr)
		{
			//��L�[�������ꂽ��
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//��Ɉړ�
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//�E�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//�E�Ɉړ�
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//���L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//���Ɉړ�
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//M�L�[�������ꂽ��
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//�e�L�X�g�t�@�C���ɏ������ޏ���
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->TextFileWrite(
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x,
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y,
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().z, type);

				return; //�����𔲂���
			}
		}
	}
}


//==================================
//X�t�@�C���̓ǂݍ���
//==================================
HRESULT CObjectX::Lood()
{
	int nNumTexture = 0;                                //�e�N�X�`���̔z���i�߂�ׂ̕ϐ�
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//�t�@�C�������邩�ǂ����m���߂�
	if (FAILED(D3DXLoadMeshFromX(m_aFileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_dwNumMat, &m_pMesh)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�}�e���A���f�[�^�ւ̃|�C���^������
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�}�e���A���i�e�N�X�`���j����
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pMat[nCntMat].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C�������݂���

			D3DXCreateTextureFromFile(pDevice, m_pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++; //�z���i�߂�
		}
	}

	return S_OK; //������Ԃ�
}