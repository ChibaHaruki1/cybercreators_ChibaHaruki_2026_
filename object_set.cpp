//======================================================================
//
//�I�u�W�F�N�g�̏���Text�t�@�C������ǂݎ�鏈��
//Auther:Haruki Chiba[object_set.cpp]
//
//======================================================================


//============================
//�C���N���[�h
#include "object_set.h"
#include "manager.h"
#include "score.h"


//============================
//static�ϐ��̏�����
int CObjectSet::m_nClearScore = 0;


//=========================
//�R���X�g���N�^
//=========================
CObjectSet::CObjectSet()
{
	//�ǂݍ��ރp�X�̖��O��ݒ�
	m_aFieldBlockStratName = "FIELDBLOCKSET";               //�n�ʗp�u���b�N�̖��O��ݒ�
	m_aGoUpBlockStratName = "GOUPBLOCKSET";                 //�オ��p�u���b�N�̖��O��ݒ�
	m_aRoadBlockStratName = "ROADBLOCKSET";                 //���p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlockStratName = "WALLROADBLOCKSET";         //�ǌ����p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlock001StratName = "WALLROADBLOCK001SET";   //�ǌ����p�u���b�N001�̖��O��ݒ�
	m_aSmallBlockStratName = "SMALLBLOCKSET";               //�������u���b�N�̖��O��ݒ�
	m_aSmallBlock001StratName = "SMALLBLOCK001SET";         //�������u���b�N001�̖��O��ݒ�
	m_aUpWallBlockStratName = "UPWALLBLOCKSET";             //��ǂ̖��O��ݒ�

	//�I������p�X�̖��O��ݒ�
	m_aFieldBlockEndName = "END_FIELDBLOCKSET";             //�n�ʗp�u���b�N�̖��O��ݒ�
	m_aGoUpBlockEndName = "END_GOUPBLOCKSET";				//�オ��p�u���b�N�̖��O��ݒ�
	m_aRoadBlockEndName = "END_ROADBLOCKSET";				//���p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlockEndName = "END_WALLROADBLOCKSET";		//�ǌ����p�u���b�N�̖��O��ݒ�
	m_aWallRoadBlock001EndName = "END_WALLROADBLOCK001SET";	//�ǌ����p�u���b�N001�̖��O��ݒ�
	m_aSmallBlockEndName = "END_SMALLBLOCKSET";				//�������u���b�N�̖��O��ݒ�
	m_aSmallBlock001EndName = "END_SMALLBLOCK001SET";		//�������u���b�N001�̖��O��ݒ�
	m_aUpWallBlockEndName = "END_UPWALLBLOCKSET";			//��ǂ̖��O��ݒ�

	//�ǂݎ���ő吔����
	for (int nCount = 0; nCount < MAX_DATAMOJI; nCount++)
	{
		m_aData[nCount] = {}; //�����̓ǂݎ��z��̏�����
	}
}


//=========================
//�f�X�g���N�^
//=========================
CObjectSet::~CObjectSet()
{
	m_nClearScore = 0; //�X�R�A�̏�����
}


//=========================
//����������
//=========================
HRESULT CObjectSet::Init()
{
	//���݂̃��[�h��ǂݎ��
	switch (CManager::GetScene()->GetMode())
	{
		//�X�e�[�W�P�̎�
	case CScene::MODE::MODE_GAME01:
		StageOneInformation("data\\TEXT\\OBJECT\\TelephonPole.txt"); //�d���̓ǂݍ���
		StageOneInformation("data\\TEXT\\OBJECT\\Block.txt");        //�u���b�N�̓ǂݍ���
		StageOneInformation("data\\TEXT\\OBJECT\\BreakHouse.txt");   //��ꂽ�Ƃ̓ǂݍ���
		StageOneInformation("data\\TEXT\\OBJECT\\Enemy.txt");        //�G�̓ǂݍ���
		StageOneInformation("data\\TEXT\\OBJECT\\MotionEnemy.txt");  //���[�V�����t���̓G�̓ǂݍ���

		return S_OK;  //�����𔲂���

		//�X�e�[�W�Q�̎�
	case CScene::MODE::MODE_GAME02:
		StageOneInformation("data\\TEXT\\OBJECT\\Block1.txt");       //�u���b�N1�̓ǂݍ���
		
		CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALCEILLING, D3DXVECTOR3(4335.0f, 790.0f, 0.0f)); //�{�X��̑���

		return S_OK; //�����𔲂���

		//���U���g���̎�
	case CScene::MODE::MODE_RESULT:
		ResultScoreWrite("data\\TEXT\\ResultScore.txt");        //���U���g�X�R�A�̏�������
		ResultScoreInformation("data\\TEXT\\ResultScore.txt");  //���U���g�X�R�A�̓ǂݍ���

		return S_OK;
	}
	return E_FAIL;
}


//================================================================================
//�X�e�[�W�P�Ԗڂ̃I�u�W�F�N�g�̏���ݒ�
//================================================================================
void CObjectSet::StageOneInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//�O���t�@�C���ǂݍ��� (����)
	while (1)
	{
		(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

		//�R�����g��ǂݍ��񂾎�
		if (m_aData[0] == '#')
		{
			continue; //���s
		}

		//���̕�������������
		if (!strcmp(m_aData, "END_SCRIPT"))
		{
			fclose(pFile);        //�t�@�C�������
			pFile = nullptr;      //�t�@�C���̏��𖳂���
			break;                //�����𔲂���
		}						  
								  
		LoodTelephonPole(pFile);  //�d���̏���ǂݎ��
		LoodBlock(pFile);         //�u���b�N�̏���ǂݎ��
		LoodBreakHouse(pFile);    //��ꂽ�Ƃ̏���ǂݎ��
		LoodEnemy(pFile);         //�G�̏���ǂݍ���
		LoodMotionInEnemy(pFile); //���[�V�����t���̓G�̏���ǂݍ���
	}
}

//================================================================================
//���U���g�X�R�A�̏���ǂݍ���
//================================================================================
void CObjectSet::ResultScoreInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	LoodResultScore(pFile); //���U���g�X�R�A�̓ǂݍ��ݏ������Ă�

	fclose(pFile);          //�t�@�C�������
}

//================================================================================
//���U���g�X�R�A�̏�����������
//================================================================================
void CObjectSet::ResultScoreWrite(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "w"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (pFile == nullptr)
	{
		return; //�����𔲂���
	}

	fprintf(pFile, "%d", m_nClearScore); //��������������

	fclose(pFile);                       //�t�@�C�������
}


//=================================
//�d���̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodTelephonPole(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	///���ꂪ������Ă�����
	if (!strcmp(m_aData, "TELEPHONPOLESET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_TELEPHONPOLESET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //�d���̔z���i�߂�
				CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //���ꂽ�S�̐����J�E���g����[�����₷

				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX, PosY, PosZ));                                    //�d���̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + 20.0f, PosY + 180.0f, PosZ - 50.0f));   //�Ď��J�����̏�̕����̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + 20.0f, PosY + 170.0f, PosZ - 50.0f)); //�Ď��J�����̉��̕����̐���
				CLaserCamare::Create(CObject3D::TYPE_UI::LASER); //���[�U�[�̐���
			}
		}
	}
}

//=================================
//��ꂽ�Ƃ̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodBreakHouse(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "BREAKHOUSESET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_BREAKHOUSESET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BREAKHOUSE, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //��ꂽ�Ƃ̐���
			}
		}
	}
}

//=================================
//�G�̏���ǂݍ��ޏ���
//=================================
void CObjectSet::LoodEnemy(FILE* pFile)
{
	int nNumber = 0;               //�����ԍ�
	float PosX, PosY, PosZ = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "ENEMYSET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_ENEMYSET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);      //�O�Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%d", &nNumber);   //��������G�̏T�ނ�ԍ��Ŏ擾

				//�ԍ��Ŕ���
				switch (nNumber)
				{
				case 0:
					CManagerEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CObjectX::TYPE::ENEMY);                                   //�G�̐���
					break; //�����𔲂���

				case 1:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //�G001�̐���
					break; //�����𔲂���

				case 2:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY002, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //�G002�̐���
					break; //�����𔲂���
				}
			}
		}
	}
}

//==============================================
//���[�V�����t���̓G�̏���ǂݍ��ޏ���
//==============================================
void CObjectSet::LoodMotionInEnemy(FILE*pFile)
{
	//int nNumber = 0;               //�����ԍ�
	float PosX, PosY, PosZ = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, "MOTIONENEMYSET"))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, "END_MOTIONENEMYSET"))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);      //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);      //�O�Ԗڂ̒l���i�[
				//(void)fscanf(pFile, "%d", &nNumber);   //��������G�̏T�ނ�ԍ��Ŏ擾

				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //�G001�̐���
			}
		}
	}
}

//========================================
//�u���b�N�̏���ǂݍ��ޏ���
//========================================
void CObjectSet::LoodBlock(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //pos�̈ʒu��ۊǂ��邽�߂̕ϐ�

	//���ꂪ������Ă�����
	if (!strcmp(m_aData, m_aFieldBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aFieldBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(PosX,PosY,PosZ)); //�n�ʗp�u���b�N�̐���
			}
		}
	}

	//�オ��p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aGoUpBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aGoUpBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(PosX,PosY,PosZ)); //�オ��p�u���b�N�̐���
			}
		}
	}

	//���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aRoadBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aRoadBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //���p�u���b�N�̐���
			}
		}
	}

	//�ǌ����p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(PosX,PosY,PosZ)); //�ǌ����p�u���b�N�̐���
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aWallRoadBlock001StratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aWallRoadBlock001EndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(PosX,PosY,PosZ)); //�ǌ����p�u���b�N001�̐���
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aSmallBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(PosX,PosY,PosZ)); //�������u���b�N�̐���
			}
		}
	}

	// ���p�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aSmallBlock001StratName))
	{
	//���[�v(��������)
	while (1)
	{
		(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

		//�薼��END_TELEPHONPOLESET��������
		if (!strcmp(m_aData, m_aSmallBlock001EndName))
		{
			break; //�����𔲂���
		}

		//�薼��POS��������
		if (!strcmp(m_aData, "POS"))
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
			(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
			(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
			(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

			//��������
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(PosX,PosY,PosZ)); //�������u���b�N001�̐���
		}
	}
	}
	// ��̕Ǘp�u���b�N�̏���ǂݍ���
	else if (!strcmp(m_aData, m_aUpWallBlockStratName))
	{
		//���[�v(��������)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //������ǂݎ��

			//�薼��END_TELEPHONPOLESET��������
			if (!strcmp(m_aData, m_aUpWallBlockEndName))
			{
				break; //�����𔲂���
			}

			//�薼��POS��������
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //������ǂݎ�� �X�̏ꍇ�u���v��ǂݎ��
				(void)fscanf(pFile, "%f", &PosX);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosY);   //��Ԗڂ̒l���i�[
				(void)fscanf(pFile, "%f", &PosZ);   //�O�Ԗڂ̒l���i�[

				//��������
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(PosX,PosY,PosZ)); //��ǂ̃u���b�N�̐���
			}
		}
	}
}


//================================================
//result�X�R�A�̏���ǂݍ���
//================================================
void CObjectSet::LoodResultScore(FILE* pFile)
{
	(void)fscanf(pFile, "%d", &m_nClearScore); //��Ԗڂ̒l���i�[

	CManagerScore::Create(CScene::MODE::MODE_RESULT, m_nClearScore); //���U���g�X�R�A�̐���
}


//========================================
//text�t�@�C���̏��𐶐�
//========================================
CObjectSet* CObjectSet::Create()
{
	CObjectSet* m_pObjectSet = new CObjectSet(); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(m_pObjectSet->Init()))
	{
		return m_pObjectSet; //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//==========================================
//�u���b�N�̓ǂݍ��ޖ��O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetStratBlockName(CObjectX::TYPE type)
{
	//�^�C�v���n�ʗp�u���b�N�̎�
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockStratName;           //���O��Ԃ�
	}

	//�^�C�v���オ��悤�u���b�N�̎�
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockStratName;            //���O��Ԃ�
	}

	//�^�C�v�����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockStratName;            //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockStratName;        //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001StratName;     //���O��Ԃ�
	}

	//�^�C�v���������u���b�N�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockStratName;           //���O��Ԃ�
	}

	//�^�C�v���������u���b�N001�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001StratName;        //���O��Ԃ�
	}

	//��ǂ̎�
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockStratName;          //���O��Ԃ�
	}

	return nullptr; //����Ԃ�
}


//==========================================
//�u���b�N�̏I�����閼�O�̃p�X�̎擾����
//==========================================
const char* CObjectSet::GetEndBlockName(CObjectX::TYPE type)
{
	//�^�C�v���n�ʗp�u���b�N�̎�
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockEndName;           //���O��Ԃ�
	}

	//�^�C�v���オ��悤�u���b�N�̎�
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockEndName;            //���O��Ԃ�
	}

	//�^�C�v�����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockEndName;            //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockEndName;        //���O��Ԃ�
	}

	//�^�C�v���ǌ����p�u���b�N001�̎�
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001EndName;     //���O��Ԃ�
	}

	//�^�C�v���������u���b�N�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockEndName;           //���O��Ԃ�
	}

	//�^�C�v���������u���b�N001�̎�
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001EndName;        //���O��Ԃ�
	}

	//��ǂ̎�
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockEndName;          //���O��Ԃ�
	}

	return nullptr; //����Ԃ�
}
