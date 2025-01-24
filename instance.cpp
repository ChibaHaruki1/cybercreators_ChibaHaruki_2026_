//=============================================
//
//�C���X�^���X���Ǘ����鏈��[instance.cpp]
//Auther;HARUKI CHIBA
//
//=============================================


//=============================================
//�C���N���[�h
#include "instance.h"


//=======================
//�R���X�g���N�^
//=======================
CInstance::CInstance()
{
	//�I�u�W�F�N�g�̍ő吔����
	for (int nCount = 0; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;         //�n�ʗp�u���b�N�̃|�C���^�[�̏�����
		m_pGoUpBlock[nCount] = nullptr;          //�オ�邽�߂̃u���b�N�̃|�C���^�[�̏�����
		m_pRoadBlock[nCount] = nullptr;          //���p�u���b�N�̃|�C���^�[�̏�����
		m_pWallRoadBlock[nCount] = nullptr;      //�ǌ����p�u���b�N�̃|�C���^�[�̏�����
		m_pWallRoadBlock001[nCount] = nullptr;   //�ǌ����p�u���b�N001�̃|�C���^�[�̏�����
		m_pSmallBlock[nCount] = nullptr;         //�������u���b�N�̃|�C���^�[�̏�����
		m_pSmallBlock001[nCount] = nullptr;      //�������u���b�N001�̃|�C���^�[�̏�����
		m_pUpWallBlock[nCount] = nullptr;        //��ǂ̃|�C���^�[�̏�����
		m_pDebrisX[nCount] = nullptr;            //�j�Ѓ|�C���^�[�̏�����
		m_pPraticles001[nCount] = nullptr;       //�p�[�e�B�N��001�̃|�C���^�[�̏�����
	}

	//�X�e�[�W�I�u�W�F�N�g�̍ő吔����
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;            //�d���̃|�C���^�[�̏�����
		m_pSurveillanceCameraUp[nCount1] = nullptr;    //�Ď��J�����̏�̕����̃|�C���^�[�̏�����
		m_pSurveillanceCameraDown[nCount1] = nullptr;  //�Ď��J�����̉��̕����̃|�C���^�[�̏�����
	}

	//���ꂫ�̍ő吔����
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;  //�؂̔Q�̃|�C���^�[�̏�����
	}

	//�G�̍ő吔����
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;     //�G001�̃|�C���^�[�̏�����
		m_pEnemy002[nCount3] = nullptr;     //�G001�̃|�C���^�[�̏�����
	}

	//��ꂽ�ƕ���
	for (int nCount4=0 ;nCount4< MAX_BREAKHOUSE;nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;   //��ꂽ�Ƃ̃|�C���^�[�̏�����
	}

	//���[�V�����t���̓G�̕���
	for (int nCount5 = 0; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr; //���[�V�����t���̓G�̃|�C���^�[�̏�����
		m_pEnemyInMotion001[nCount5] = nullptr; //���[�V�����t���̓G001�̃|�C���^�[�̏�����
	}

	//2D�̃C���X�^���X�̏�����
	m_pShopScreen = nullptr;    //�V���b�v���̔w�i�̃|�C���^�[�̏�����
	m_pPlayerHPGage = nullptr;  //
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	//�RD�̏�����
	m_pFuelGage = nullptr;
	for (int nShip = 0; nShip < MAX_SHIP; nShip++)
	{
		m_pSpeceBattleShip000[nShip] = nullptr; //���̃X�e�[�W�֍s���I�u�W�F�N�g�̏�����
	}
	m_pShop = nullptr;               //�X�̏�����
	m_pEffect = nullptr;             //�v���C���[�̒e�ɂ��G�t�F�N�g�̏�����
	m_pExplosion = nullptr;          //�����G�t�F�N�g�̏�����
	m_pExplosion001 = nullptr;       //�����G�t�F�N�g001�̏�����
	m_pThander = nullptr;            //���G�t�F�N�g�̏�����
	m_pFire = nullptr;               //���G�t�F�N�g�̃|�C���^�[�̏�����
	m_pImpact = nullptr;             //�Ռ��g�̃|�C���^�[�̏�����
	m_pDebris = nullptr;             //�j�Ђ̃|�C���^�[�̏�����
	m_pPillarOfFire = nullptr;       //����̉��̃|�C���^�[�̏�����
	m_pSepecialAttack = nullptr;     //�K�E�Z�̃|�C���^�[�̏�����
	m_pBossSpecialAttack = nullptr;  //�{�X�̕K�E�Z�̃|�C���^�[�̏�����
	m_pEnemy000 = nullptr;           //�G�̃|�C���^�[�̏�����
	m_pBoss = nullptr;               //�{�X�̃|�C���^�[�̏�����

	//X�I�u�W�F�N�g�̏�����
	m_pFinalBlosk = nullptr;         //�ŏI�X�e�[�W�̒n�ʃu���b�N�̃|�C���^�[�̏�����
	m_pFinalCeiling = nullptr;       //�ŏI�X�e�[�W�̓V��u���b�N�̃|�C���^�[�̏�����

	//���ꂽ���̏������i���O�ɃC���N�������g���邽�߁[�P�ŏ������j
	m_nNumFiledBlock = -1;           //�n�ʗp�u���b�N�̐���������
	m_nNumGoUpBlock = -1;            //�オ��p�u���b�N�̐���������
	m_nRoadBlock = -1;               //���p�u���b�N�̐���������
	m_nWallRoadBlock = -1;           //�ǌ����p�u���b�N�̐���������
	m_nWallRoadBlock001 = -1;        //�ǌ����p�u���b�N001�̐���������
	m_nSmallBlock = -1;              //�������u���b�N�̐���������
	m_nSmallBlock001 = -1;           //�������u���b�N001�̐���������
	m_nUpWallBlock = -1;             //��Ǘp�u���b�N�̐���������
	m_nEnemy001 = -1;                //�G001�̐���������
	m_nEnemy002 = -1;                //�G002�̐���������
	m_nEnemyInMotion = -1;           //���[�V�����t���̓G�̐���������
	m_nEnemyInMotion001 = -1;        //���[�V�����t���̓G001�̐���������
	m_nWoodenBoard = -1;             //�؂̔Q�̐���������
	m_nBreakHouse = -1;              //��ꂽ�Ƃ̐���������
	m_nShip = -1;                    //�X�y�[�X�V�b�v�̐���������
}


//=======================
//�f�X�g���N�^
//=======================
CInstance::~CInstance()
{

}


//=======================
//����������
//=======================
HRESULT CInstance::Init()
{
	return S_OK;
}


//=======================
//�j������
//=======================
void CInstance::Uninit()
{
	//�I�u�W�F�N�g�̍ő吔����
	for (int nCount = 0; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;         //�n�ʗp�u���b�N�̃|�C���^�[�̏�����
		m_pGoUpBlock[nCount] = nullptr;          //�オ�邽�߂̃u���b�N�̃|�C���^�[�̏�����
		m_pRoadBlock[nCount] = nullptr;          //���p�u���b�N�̃|�C���^�[�̏�����
		m_pWallRoadBlock[nCount] = nullptr;      //�ǌ����p�u���b�N�̃|�C���^�[�̏�����
		m_pWallRoadBlock001[nCount] = nullptr;   //�ǌ����p�u���b�N001�̃|�C���^�[�̏�����
		m_pSmallBlock[nCount] = nullptr;         //�������u���b�N�̃|�C���^�[�̏�����
		m_pSmallBlock001[nCount] = nullptr;      //�������u���b�N001�̃|�C���^�[�̏�����
		m_pUpWallBlock[nCount] = nullptr;        //��ǂ̃|�C���^�[�̏�����
		m_pDebrisX[nCount] = nullptr;            //�j�Ѓ|�C���^�[�̏�����
		m_pPraticles001[nCount] = nullptr;       //�p�[�e�B�N��001�̃|�C���^�[�̏�����
	}

	//�X�e�[�W�I�u�W�F�N�g�̍ő吔����
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;            //�d���̃|�C���^�[�̏�����
		m_pSurveillanceCameraUp[nCount1] = nullptr;    //�Ď��J�����̏�̕����̃|�C���^�[�̏�����
		m_pSurveillanceCameraDown[nCount1] = nullptr;  //�Ď��J�����̉��̕����̃|�C���^�[�̏�����
	}

	//���ꂫ�̍ő吔����
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;  //�؂̔Q�̃|�C���^�[�̏�����
	}

	//�G�̍ő吔����
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;     //�G001�̃|�C���^�[�̏�����
		m_pEnemy002[nCount3] = nullptr;     //�G001�̃|�C���^�[�̏�����
	}

	//��ꂽ�ƕ���
	for (int nCount4 = 0; nCount4 < MAX_BREAKHOUSE; nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;   //��ꂽ�Ƃ̃|�C���^�[�̏�����
	}

	//���[�V�����t���̓G�̕���
	for (int nCount5 = 0; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr; //���[�V�����t���̓G�̃|�C���^�[�̏�����
		m_pEnemyInMotion001[nCount5] = nullptr; //���[�V�����t���̓G001�̃|�C���^�[�̏�����
	}

	//2D�̃C���X�^���X�̏�����
	m_pShopScreen = nullptr;    //�V���b�v���̔w�i�̃|�C���^�[�̏�����
	m_pPlayerHPGage = nullptr;  //
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	//�RD�̏�����
	m_pFuelGage = nullptr;

	for (int nShip = 0; nShip < MAX_SHIP; nShip++)
	{
		m_pSpeceBattleShip000[nShip] = nullptr; //���̃X�e�[�W�֍s���I�u�W�F�N�g�̏�����
	}
	m_pShop = nullptr;               //�X�̏�����
	m_pEffect = nullptr;             //�v���C���[�̒e�ɂ��G�t�F�N�g�̏�����
	m_pExplosion = nullptr;          //�����G�t�F�N�g�̏�����
	m_pExplosion001 = nullptr;       //�����G�t�F�N�g001�̏�����
	m_pThander = nullptr;            //���G�t�F�N�g�̏�����
	m_pFire = nullptr;               //���G�t�F�N�g�̃|�C���^�[�̏�����
	m_pImpact = nullptr;             //�Ռ��g�̃|�C���^�[�̏�����
	m_pDebris = nullptr;             //�j�Ђ̃|�C���^�[�̏�����
	m_pPillarOfFire = nullptr;       //����̉��̃|�C���^�[�̏�����
	m_pSepecialAttack = nullptr;     //�K�E�Z�̃|�C���^�[�̏�����
	m_pBossSpecialAttack = nullptr;  //�{�X�̕K�E�Z�̃|�C���^�[�̏�����
	m_pEnemy000 = nullptr;           //�G�̃|�C���^�[�̏�����
	m_pBoss = nullptr;               //�{�X�̃|�C���^�[�̏�����

	//X�I�u�W�F�N�g�̏�����
	m_pFinalBlosk = nullptr;         //�ŏI�X�e�[�W�̒n�ʃu���b�N�̃|�C���^�[�̏�����
	m_pFinalCeiling = nullptr;       //�ŏI�X�e�[�W�̓V��u���b�N�̃|�C���^�[�̏�����
}


//============================================================================================================================
//�G�̏��𖳂���
//============================================================================================================================
void CInstance::DesignationUninitXEnemy(CObjectX::TYPE type, int nNumber)
{
	//�^�C�v���G�̎�
	if (type == CObjectX::TYPE::ENEMY)
	{
		m_pEnemy000 = nullptr;           //���𖳂���
	}

	//�^�C�v���G001�̎�
	else if (type == CObjectX::TYPE::ENEMY001)
	{
		m_pEnemy001[nNumber] = nullptr; //�w�肵���ԍ��̏��𖳂���
	}

	//�^�C�v���G002�̎�
	else if (type == CObjectX::TYPE::ENEMY002)
	{
		m_pEnemy002[nNumber] = nullptr; //�w�肵���ԍ��̏��𖳂���
	}

	//�^�C�v���{�X�̎�
	else if(type==CObjectX::TYPE::BOSS)
	{
		m_pBoss = nullptr;               //���𖳂���
	}

	//�^�C�v�����[�V�����t���̓G�̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_pEnemyInMotion000[nNumber] = nullptr; //���𖳂���
	}

	//�^�C�v�����[�V�����t���̓G001�̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_pEnemyInMotion001[nNumber] = nullptr; //���𖳂���
	}

}


//============================================================================================================================
//3D���f����nullptr�ɂ��������̂��w�肷�鏈��
//============================================================================================================================
void CInstance::DesignationUninitX(CObjectX::TYPE type, int nNumber)
{
	//�^�C�v���Ď��J�����̏㕔���̎�
	if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		m_pSurveillanceCameraUp[nNumber] = nullptr; //�w�肵���ԍ��̏����Ȃ���
	}

	//�^�C�v���j�Ђ̎�
	else if (type == CObjectX::TYPE::DEBRIS)
	{
		if (m_pDebrisX[nNumber] != nullptr)
		{
			m_pDebrisX[nNumber] = nullptr;          //�w�肵���ԍ��̏����Ȃ���
		}
	}

	//�^�C�v���X�y�[�X�V�b�v�̎�
	else if (type == CObjectX::TYPE::SPECEBATTLESHIP000)
	{
		if (m_pSpeceBattleShip000[nNumber] != nullptr)
		{
			m_pSpeceBattleShip000[nNumber] = nullptr; //�w�肵���ԍ��̏����Ȃ���
		}
	}
}


//============================================================================================================================
//�QD��nullptr�ɂ��������̂��w�肷�鏈��
//============================================================================================================================
void CInstance::DesignationUninit2D(CObject2D::TYPE type)
{
	//�^�C�v���w�i�̎�
	if (type == CObject2D::TYPE::SCREEN)
	{
		m_pShopScreen = nullptr; //�����Ȃ���
	}
}


//============================================================================================================================
//�RD��nullptr�ɂ��������̂��w�肷�鏈��
//============================================================================================================================
void CInstance::DesignationUninit3D(CObject3D::TYPE type)
{
	//�^�C�v���Ռ��g�̎�
	if (type == CObject3D::TYPE::IMPACT)
	{
		m_pImpact = nullptr; //�����Ȃ���
	}
}


//============================================================================================================================
//2D�̃C���X�^���X�𐶐����鏈��
//============================================================================================================================
CObject2D* CInstance::GetCreateObjectInstnace2D(CObject2D::TYPE type, int nNumber)
{
	//�^�C�v���w�i�̎�
	if (type == CObject2D::TYPE::SCREEN)
	{
		return m_pShopScreen = CShopScreen::Create(); //�w�i�𐶐�
	}

	//�^�C�v��HP�̎�
	else if (type==CObject2D::TYPE::HP)
	{
		return m_pPlayerHPGage = CManagerGage::Create(type); //HP�Q�[�W�̐���
	}

	//�^�C�v���{�X��HP�̎�
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		return m_pBossHPGage = dynamic_cast<CBossHPGage*>(CManagerGage::Create(type)); //�{�X��HP�Q�[�W�̐���
	}

	//�^�C�v���X�R�A�̎�
	else if (type == CObject2D::TYPE::SCORE)
	{
		m_pGameScore = CManagerScore::Create(CScene::MODE::MODE_GAME01, nNumber);      //�X�R�A�̐���
	}

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//3D�̃C���X�^���X�𐶐����鏈��
//============================================================================================================================
CObject3D* CInstance::GetCreateObjectInstnace(CObject3D::TYPE type, int nNumber, D3DXVECTOR3 pos)
{

	//�^�C�v���p�[�e�B�N��001�̎�
	if (type == CObject3D::TYPE::PRTICLES001)
	{
		return m_pPraticles001[nNumber] = CParticles001::Create(pos);   //�p�[�e�B�N��001�̐���
	}

	//�^�C�v���G�t�F�N�g�̎�
	else if (type == CObject3D::TYPE::EFFECT)
	{
		return m_pEffect = CEffect::Create(pos);                        //�G�t�F�N�g�̐���
	}

	//�^�C�v�������̎�
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		return m_pExplosion = CManagerEffect::Create(pos, type);        //�����̃G�t�F�N�g�̐���
	}

	//�^�C�v������001�̎�
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		return m_pExplosion001 = CManagerEffect::Create(pos,type);      //�����G�t�F�N�g001�̐���
	}

	//�^�C�v�����̎�
	else if (type == CObject3D::TYPE::THENDER)
	{
		return m_pThander = CManagerEffect::Create(pos, type);          //���G�t�F�N�g�̐���
	}

	//�^�C�v�����̎�
	else if (type == CObject3D::TYPE::FIRE)
	{
		return m_pFire = CManagerEffect::Create(pos, type);             //���G�t�F�N�g�̐���
	}

	//�^�C�v���Ռ��g�̎�
	else if (type == CObject3D::TYPE::IMPACT)
	{
		return m_pImpact = CManagerBossEffect::Create(pos, type);       //�Ռ��g�̐���
	}

	//�^�C�v���j�Ђ̎�
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		return m_pDebris = CManagerEffect::Create(pos, type);           //�j�Ђ̐���
	}

	//�^�C�v������̉��̎�
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		return m_pPillarOfFire = CManagerEffect::Create(pos, type);     //����̉��̃G�t�F�N�g�̐���
	}

	//�^�C�v���K�E�Z�̎�
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		return m_pSepecialAttack = dynamic_cast<CSpecialAttack*>(CManagerEffect::Create(pos, type)); //�K�E�Z�̃G�t�F�N�g�̐���
	}

	//�^�C�v���{�X�̕K�E�Z�̎�
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		return m_pBossSpecialAttack = CManagerBossEffect::Create(pos, type); //�{�X�̕K�E�Z�̃G�t�F�N�g�̐���
	}

	//�^�C�v���R���Q�[�W�̎�
	else if (type==CObject3D::TYPE::FUELGAGE)
	{
		return 	m_pFuelGage = CFuelGage::Create();  //�R���Q�[�W�̐���
	}

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//X�I�u�W�F�N�g�̃C���X�^���X�𐶐����鏈��
//============================================================================================================================
CObjectX* CInstance::GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos)
{
	//�^�C�v���j�Ђ̎�
	if (type == CObjectX::TYPE::DEBRIS)
	{
		return m_pDebrisX[nNumber] = CDebrisX::Create(pos); //�j�Ђ̐���
	}

	//�^�C�v���d���̎�
	else if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		return m_pTelephonPole[nNumber] = CStageObj::Create(pos, type); //�d���̐���
	}

	//�^�C�v���Ď��J�����̏�̕����̎�
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		return m_pSurveillanceCameraUp[nNumber] = CStageObj::Create(pos, type);  //�Ď��J�����̏�̕����̐���
	}

	//�^�C�v���Ď��J�����̉��̕����̎�
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERADOWN)
	{
		return m_pSurveillanceCameraDown[nNumber] = CStageObj::Create(pos, type); //�Ď��J�����̉��̕����̐���
	}

	//�^�C�v����ꂽ�Ƃ̎�
	else if (type == CObjectX::TYPE::BREAKHOUSE)
	{
		m_nBreakHouse++;                                                    //���ꂽ���𑝂₷
		return m_pBreakHouse[m_nBreakHouse] = CStageObj::Create(pos, type); //��ꂽ�Ƃ̐���
	}

	//�^�C�v���X�̎�
	else if (type == CObjectX::TYPE::SHOP)
	{
		return m_pShop = CStageObj::Create(pos, type); //�X�̐���
	}

	//�^�C�v���G�̎�
	else if (type == CObjectX::TYPE::ENEMY)
	{
		return m_pEnemy000 = CManagerEnemy::Create(pos,type); //�G�̐���
	}

	//�^�C�v���G001�̎�
	else if (type == CObjectX::TYPE::ENEMY001)
	{
		m_nEnemy001++;
		return m_pEnemy001[m_nEnemy001] = CManagerEnemy::Create(pos, type); //�G001�̐���
	}

	//�^�C�v���G001�̎�
	else if (type == CObjectX::TYPE::ENEMY002)
	{
		m_nEnemy002++;
		return m_pEnemy002[m_nEnemy002] = CManagerEnemy::Create(pos, type); //�G002�̐���
	}

	//�^�C�v�����[�V�����t���̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_nEnemyInMotion++;
		return m_pEnemyInMotion000[m_nEnemyInMotion] = CManagerEnemyInMotion::Create(pos,type);      //���[�V�����t���̓G�̐���
	}

	//�^�C�v�����[�V�����t���̓G001�̎�
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_nEnemyInMotion001++;
		return m_pEnemyInMotion001[m_nEnemyInMotion001] = CManagerEnemyInMotion::Create(pos, type);  //���[�V�����t���̓G001�̐���
	}

	//�^�C�v���{�X�̎�
	else if (type == CObjectX::TYPE::BOSS)
	{
		return m_pBoss = CBoss::Create(pos); //�{�X�̐���
	}

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//�u���b�N�̐�������
//============================================================================================================================
CObjectX* CInstance::CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//�^�C�v���n�ʗp�u���b�N�̎�
	if (type == CObjectX::STRATEGYTYPE::FIELDBLOCK)
	{
		m_nNumFiledBlock++;                                                                  //���ꂽ���𑝂₷
		return m_pFieldBlock[m_nNumFiledBlock] = CManagerBlock::Create(pos, type);           //�n�ʗp�̃u���b�N�̐���
	}																			            
																				            
	//�^�C�v���オ��p�u���b�N�̎�												  	        
	else if (type == CObjectX::STRATEGYTYPE::GOUPBLOCK)							            
	{																			            
		m_nNumGoUpBlock++;                                                                   //���ꂽ���𑝂₷
		return m_pGoUpBlock[m_nNumGoUpBlock] = CManagerBlock::Create(pos, type);             //�オ�邽�߂̃u���b�N�̐���
	}																			            
																				            
	//�^�C�v�����p�u���b�N�̎�													            
	else if (type == CObjectX::STRATEGYTYPE::ROADBLOCK)							            
	{																			            
		m_nRoadBlock++;                                                                      //���ꂽ���𑝂₷
		return m_pRoadBlock[m_nRoadBlock] = CManagerBlock::Create(pos, type);                //���p�u���b�N�̐���
	}																				        
																					        
	//�^�C�v���ǌ����p�u���b�N�̎�													        
	else if (type == CObjectX::STRATEGYTYPE::WALLROADBLOCK)							        
	{																				        
		m_nWallRoadBlock++;                                                                  //���ꂽ���𑝂₷
		return m_pWallRoadBlock[m_nWallRoadBlock] = CManagerBlock::Create(pos, type);        //�ǌ����p�u���b�N�̐���
	}

	//�^�C�v���ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::STRATEGYTYPE::WALLROADBLOCK001)
	{
		m_nWallRoadBlock001++;                                                               //���ꂽ���𑝂₷
		return m_pWallRoadBlock001[m_nWallRoadBlock001] = CManagerBlock::Create(pos, type);  //�ǌ����p�u���b�N001�̐���
	}

	//�^�C�v���������u���b�N�̎�
	else if (type == CObjectX::STRATEGYTYPE::SMALLBLOCK)
	{
		m_nSmallBlock++;                                                                     //���ꂽ���𑝂₷
		return m_pSmallBlock[m_nSmallBlock] = CManagerBlock::Create(pos, type);              //�������u���b�N�̐���
	}

	//�^�C�v���������u���b�N001�̎�
	else if (type == CObjectX::STRATEGYTYPE::SMALLBLOCK001)
	{
		m_nSmallBlock001++;                                                                  //���ꂽ���𑝂₷
		return m_pSmallBlock001[m_nSmallBlock001] = CManagerBlock::Create(pos, type);        //�������u���b�N001�̐���
	}

	//�^�C�v����ǂ̎�
	else if (type == CObjectX::STRATEGYTYPE::UPWALLBLOCK)
	{
		m_nUpWallBlock++;                                                                    //���ꂽ���𑝂₷
		return m_pUpWallBlock[m_nUpWallBlock] = CManagerBlock::Create(pos, type);            //��ǂ̐���
	}

	//�^�C�v���X�y�[�X�V�b�v�̎�
	else if (type == CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		m_nShip++;
		return m_pSpeceBattleShip000[m_nShip] = CManagerBlock::Create(pos, type);                     //�X�y�[�X�V�b�v�̐���
	}

	//�^�C�v���ŏI�X�e�[�W�̒n�ʂ̎�
	else if (type == CObjectX::STRATEGYTYPE::FINALBLOCK)
	{
		return m_pFinalBlosk = CManagerBlock::Create(pos,type);                              //�ŏI�X�e�[�W�̒n�ʂ̐���
	}

	//�^�C�v���ŏI�X�e�[�W�̓V��̎�
	else if (type == CObjectX::STRATEGYTYPE::FINALCEILLING)
	{
		return m_pFinalCeiling = CManagerBlock::Create(pos, type);                           //�ŏI�X�e�[�W�̓V��̐���
	}

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//���ꂫ�̐���
//============================================================================================================================
CObjectX* CInstance::CreateRubble(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//�^�C�v���؂̔Q�̎�
	if (type == CObjectX::STRATEGYTYPE::WODDENBORAD)
	{
		m_nWoodenBoard++;                                                         //���ꂽ���𑝂₷
		return m_pWoodenBoard[m_nWoodenBoard] = CManagerBlock::Create(pos,type);  //�؂̔Q�̐���
	}

	return nullptr; //����Ԃ�
}

