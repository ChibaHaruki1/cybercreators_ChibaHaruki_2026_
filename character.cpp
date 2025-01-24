//===========================================================================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================


//=============================
//�C���N���[�h
#include "character.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//=====================~
CCharacter::CCharacter(int nPriority) : CObjectX(nPriority)
{
	//�v���C���[�̃p�[�c������
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_pModelPrts[nCount] = nullptr;                         //�v���C���[�̃p�[�c�̏�����
		SaveMotionPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�e�p�[�c�̏ꏊ�̕ۊǏꏊ�̏�����
		m_pSaveModelPrtInfo[nCount] = {};                       //���f���p�[�c�̕ۊǏ��̏�����
	}

	//�{�X�̃p�[�c������
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_pModelPrtsBoss[nCount1] = nullptr;                         //�{�X�̃p�[�c�̏�����
		SaveMotionPosBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 //�e�p�[�c�̏ꏊ�̕ۊǏꏊ�̏�����
		m_pSaveModelPrtInfoBoss[nCount1] = {};						 //���f���p�[�c�̕ۊǏ��̏�����
	}

	m_nMotionFrameBoss = 0;              //�{�X�̃��[�V�������̃t���[����������
	MotionCount = 0;                     //�v���C���[�̃��[�V�����J�E���g�̏�����
	MotionCountBoss = 0;                 //�{�X�̃��[�V�����J�E���g�̏�����
	m_bMotionType = false;               //�v���C���[�̃��[�V��������̏�����
	m_bMotionBossType = false;           //�{�X�̃��[�V��������̏�����
	m_MotionState = NEUTRAL;             //�v���C���[�̃��[�V�����̏�Ԃ̏�����
	m_MotionStateBoss = BOSSNEUTRAL;     //�{�X�̃��[�V������Ԃ̏�����
}


//======================
//�f�X�g���N�^
//======================
CCharacter::~CCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CCharacter::Init()
{
	//�������ɐ������邩�ǂ���
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //�����Ԃ�
}


//========================
//�j������
//========================
void CCharacter::Uninit()
{
	CObjectX::Uninit(); //�j���������Ă�

	//�v���C���[�̃p�[�c����
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Uninit();  //�j���������Ă�
			delete m_pModelPrts[nCount];     //�����폜����
			m_pModelPrts[nCount] = nullptr;  //���𖳂���
		}
	}

	//�{�X�̃p�[�c����
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nCount1] != nullptr)
		{
			m_pModelPrtsBoss[nCount1]->Uninit();  //�j������
			delete m_pModelPrtsBoss[nCount1];     //�����폜����
			m_pModelPrtsBoss[nCount1] = nullptr;  //���𖳂���
		}
	}
}

//========================
//�v���C���[�X�V����
//========================
void CCharacter::UpdatePlayer()
{
	MotionInfo(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < MAX_PRTS-1; nCount++)
	{
		GetPosPrts(nCount) = D3DXVECTOR3(SaveMotionPos[nCount].x +CManager::GetScene()->GetPlayerX()->GetPos().x, SaveMotionPos[nCount].y + CManager::GetScene()->GetPlayerX()->GetPos().y, SaveMotionPos[nCount].z + CManager::GetScene()->GetPlayerX()->GetPos().z);            //�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
	}
	
	//����̍X�V
	for (int nCount1 = 1; nCount1 < 4; nCount1++)
	{
		GetPosPrts(17) = D3DXVECTOR3(SaveMotionPos[nCount1 + 2].x + GetPos().x, SaveMotionPos[nCount1 + 2].y + GetPos().y, SaveMotionPos[nCount1 + 2].z + GetPos().z); //�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
	}
}


//============================
//�{�X�̍X�V����
//============================
void CCharacter::UpdateBoss()
{
	MotionInfoBoss(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < MAX_BOSSPARTS; nCount++)
	{
		if (nCount <= 9)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y, SaveMotionPosBoss[nCount].z + GetPos().z);           //�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
		}
		if (nCount >= 10)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y + 200.0f, SaveMotionPosBoss[nCount].z + GetPos().z);  //�e�p�[�c��ۊǒl�{���݂̒l�ŏC��
		}
	}

	//����̍X�V
	for (int nCount1 = 0; nCount1 < 4; nCount1++)
	{
		GetPosPrtsBoss(17) = D3DXVECTOR3(SaveMotionPosBoss[nCount1 + 2].x + GetPos().x, SaveMotionPosBoss[nCount1 + 2].y + GetPos().y, SaveMotionPosBoss[nCount1 + 2].z + GetPos().z);     //����p�[�c��ۊǒl�{���݂̒l�ŏC��
	}
}

//========================
//�v���C���[�̕`�揈��
//========================
void CCharacter::DrawPlayer(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                      //�ʒu�ƌ������擾����ׂ̕ϐ�

	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//========================
//�{�X�̕`�揈��
//========================
void CCharacter::DrawBoss(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();  //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                       //�ʒu�ƌ������擾����ׂ̕ϐ�

	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nCount] != nullptr)
		{
			m_pModelPrtsBoss[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}


//======================
//���[�h����
//======================
void CCharacter::Lood()
{
	int nCount = 0;              //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = 0;           //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = 0;     //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	char aPrtsPass[100];         //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[2024];    //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�

	int nMotionCount = 0;        //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = 0;        //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�

	FILE* m_pFile=nullptr;       //�t�@�C���|�C���^�[

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normal.txt", "r"); //�t�@�C�����J��

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}


	//���[�v
	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		//���̕�����ǂݎ������
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//���[�v
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					//���f���p�[�c�J�E���g���ő吔��菬������
					if (nModelPrtsCount < MAX_PRTS)
					{
						if (m_pModelPrts[nModelPrtsCount] == nullptr)
						{
							m_pModelPrts[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //�p�[�c�̐���
							m_pModelPrts[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrts(nModelPrtsCount));                                                             //���𓯊�������
						}
						nModelPrtsCount++; //�z���i�߂�
					}
				}

				//�I������
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //�����𔲂���
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						//�I������
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //�����𔲂���
						}

						//�����𑱍s���������
						if (m_aDataSearch[0] == '#')
						{
							continue; //���s
						}

						//�p�[�c�̏��̓ǂݍ���
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//���[�v
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

								//�I������
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //�����𔲂���
								}

								//�C���f�b�N�X��ǂݎ�����
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexPrts()); //�p�[�c�̃C���f�b�N�X��ǂݎ��
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexModelPrts()); //�e�p�[�c����ǂݎ��

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pModelPrts[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrts[nCount]->SetParent(nullptr); //��񖳂�
									}

									//���̑�
									else
									{
										m_pModelPrts[nCount]->SetParent(m_pModelPrts[m_pModelPrts[nCount]->GetIndexModelPrts()]); //�e�ł����������
									}
								}

								//�ʒu�̓ǂݍ��ݏ���
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetPos().x, &m_pModelPrts[nCount]->GetPos().y, &m_pModelPrts[nCount]->GetPos().z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrts[nCount]->GetPos();                     //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfo[nCount].pos += MotionSetPlayer[0].KeySet[0].aKey[nCount].pos;  
								}

								//�����̓ǂݍ��ݏ���
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetRot().x, &m_pModelPrts[nCount]->GetRot().y, &m_pModelPrts[nCount]->GetRot().z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrts[nCount]->GetRot();                     //������ۊǂ���
									//m_pSaveModelPrtInfo[nCount].rot += MotionSetPlayer[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //�ǂݎ��p�[�c�̔ԍ��𑝂₷
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0; //���[�v���邩�ǂ����̔���p�ϐ�

					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						//�����𑱍s�������
						if (m_aDataSearch[0] == '#')
						{
							continue;                           //���s
							fgets(m_aDataSearch, 40, m_pFile);  //�t�@�C�����當�����ǂݍ���
						}

						//�I������
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //�����𔲂���
						}

						//���[�v���ǂ������肷�����
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //����
							(void)fscanf(m_pFile, "%d", &LoopType);     //���[�v���邩�ǂ�������

							//�ǂݍ��񂾒l���O�̎�
							if (LoopType == 0)
							{
								MotionSetPlayer[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								MotionSetPlayer[nMotionCount].Loop = true;  //���[�v����
							}
						} 

						//�L�[�̓ǂݍ��ݏ���
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                         //����
							(void)fscanf(m_pFile, "%d", &MotionSetPlayer[nMotionCount].NumKey);  //�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//���[�v
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile); //�t�@�C�����當�����ǂݍ���
									continue;                          //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //�����𔲂���
								}

								//�t���[����ǂݎ�����
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].Frame); //�t���[����������
								}
									
								//�L�[�̒��g�̏���ǂݎ�����
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//���[�v
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[0] == '#')
										{
											continue;                           //�����𑱂���
											fgets(m_aDataSearch, 40, m_pFile);  //�t�@�C�����當�����ǂݍ���
										}

										//�ʒu�̏���ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
											//GetPos() = MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nCount].pos;
										}

										//�����̏���ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
										}

										//�I������
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //�����𔲂���
										}
									}
									nKeyCount++; //�L�[�J�E���g�̉��Z
								}
							}
							nKeyCount = 0;   //�L�[�J�E���g��������
							nKeySetCount++;  //�f�[�^�̉��Z
						}
					}
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++;   //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile); //�t�@�C�������
			break;           //�����𔲂���
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================

	//�㔼�g�̈ʒu���擾����
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���݂̃p�[�c�̎��̃p�[�c����
		for (int Next = 0; Next < nCount + 1; Next++)
		{
			SaveMotionPos[nCount + 2] += m_pModelPrts[Next + 2]->GetPos();  //�����̃p�[�c��
			SaveMotionPos[nCount + 6] += m_pModelPrts[Next + 6]->GetPos();  //�E���̃p�[�c��
		}

		SaveMotionPos[nCount + 6] += m_pModelPrts[0]->GetPos(); //�ʒu�����Z
		SaveMotionPos[nCount + 2] += m_pModelPrts[0]->GetPos(); //�ʒu�����Z
	}

	//�����g��parts�̈ʒu���擾
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPos[nCount1 + 11] += m_pModelPrts[nCount1 + 11]->GetPos(); //�����g�̊e�p�[�c
		SaveMotionPos[nCount1 + 11] -= m_pModelPrts[10]->GetPos();           //���̕�����
	}

	//���Ƒ̂̈ʒu���擾����
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPos[nCount2] += m_pModelPrts[nCount2]->GetPos(); //�ʒu�����Z
		GetPosPrts(nCount2) = D3DXVECTOR3(SaveMotionPos[nCount2].x + GetPos().x, SaveMotionPos[nCount2].y + GetPos().y + 20.0f, SaveMotionPos[nCount2].z + GetPos().z); //�p�[�c�̈ʒu���C��
	}

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount3 = 0; nCount3 < NUM_RIGHTLEFTPRTS*2; nCount3++)
	{
		GetPosPrts(nCount3 + 2) = D3DXVECTOR3(SaveMotionPos[nCount3 + 2].x + GetPos().x, SaveMotionPos[nCount3 + 2].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 2].z + GetPos().z);      //�p�[�c�̈ʒu���C��
		GetPosPrts(nCount3 + 10) = D3DXVECTOR3(SaveMotionPos[nCount3 + 10].x + GetPos().x, SaveMotionPos[nCount3 + 10].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 10].z + GetPos().z);  //�p�[�c�̈ʒu���C��
	}
}

//======================
//�{�X�̃��[�h����
//======================
void CCharacter::LoodBoss()
{
	int nCount = 0;              //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = 0;           //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = 0;     //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	char aPrtsPass[100];         //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[2024];    //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�

	int nMotionCount = 0;        //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = 0;        //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�

	FILE* m_pFile = nullptr;     //�t�@�C���|�C���^�[

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normalBoss.txt", "r"); //�t�@�C�����J��

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//���[�v
	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		//���̕������ǂݍ��܂ꂽ��
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//���[�v
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					//���f���p�[�c�J�E���g���ő吔��菬�����Ƃ�
					if (nModelPrtsCount < MAX_BOSSPARTS)
					{
						m_pModelPrtsBoss[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //�p�[�c�̐���
						m_pModelPrtsBoss[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrtsBoss(nModelPrtsCount));														  //���𓯊�������
						nModelPrtsCount++; //�z���i�߂�
					}
				}

				//�I������
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //�����𔲂���
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						//�I������
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //�����𔲂���
						}

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[0] == '#')
						{
							continue; //���s
						}
						
						//�p�[�c�̏��̓ǂݍ���
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//���[�v
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

								//�I������
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //�����𔲂���
								}

								//�C���f�b�N�X��ǂݎ�����
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexPrts()); //�p�[�c�̃C���f�b�N�X��ǂݎ��
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexModelPrts()); //�e�p�[�c����ǂݎ��

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pModelPrtsBoss[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrtsBoss[nCount]->SetParent(nullptr); //��񖳂�
									}

									//���̑�
									else
									{
										m_pModelPrtsBoss[nCount]->SetParent(m_pModelPrtsBoss[m_pModelPrtsBoss[nCount]->GetIndexModelPrts()]); //�e�ł����������
									}
								}

								//�ʒu�̓ǂݎ�����
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetPos().x, &m_pModelPrtsBoss[nCount]->GetPos().y, &m_pModelPrtsBoss[nCount]->GetPos().z); //�ʒu�̓���
									m_pSaveModelPrtInfoBoss[nCount].pos = m_pModelPrtsBoss[nCount]->GetPos();                //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfoBoss[nCount].pos += MotionSetBoss[0].KeySet[0].aKey[nCount].pos;
								}

								//�����̏���ǂݎ�����
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetRot().x, &m_pModelPrtsBoss[nCount]->GetRot().y, &m_pModelPrtsBoss[nCount]->GetRot().z); //�ʒu�̓���
									m_pSaveModelPrtInfoBoss[nCount].rot = m_pModelPrtsBoss[nCount]->GetRot();                //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfoBoss[nCount].rot += MotionSetBoss[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //�ǂݎ��p�[�c�̔ԍ��𑝂₷
						}

					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0; //���[�v���邩�ǂ����̔���p�ϐ�

					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[0] == '#')
						{
							continue;                          //���s
							fgets(m_aDataSearch, 40, m_pFile); //�t�@�C�����當����ǂݍ���
						}

						//�I������
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //�����𔲂���
						}

						//���[�v���邩�ǂ����ǂݎ�����
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //����
							(void)fscanf(m_pFile, "%d", &LoopType);     //���[�v���邩�ǂ�������

							//�ǂݍ��񂾒l���O�̎�
							if (LoopType == 0)
							{
								MotionSetBoss[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								MotionSetBoss[nMotionCount].Loop = true;  //���[�v����
							}
						}

						//�L�[�̓ǂݎ�����
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                       //����
							(void)fscanf(m_pFile, "%d", &MotionSetBoss[nMotionCount].NumKey);  //�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//���[�v
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile); //�t�@�C�����當����ǂݎ��
									continue;                          //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //�����𔲂���
								}

								//�t���[����ǂݍ��ޏ���
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].Frame); //�t���[����������
								}

								//�L�[�̒��g�̏���ǂݎ�����
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//���[�v
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[0] == '#')
										{
											continue;                          //�����𑱂���
											fgets(m_aDataSearch, 40, m_pFile); //�t�@�C�����當����ǂݎ��
										}

										//�ʒu��ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
										}

										//������ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
										}

										//�I������
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //�����𔲂���
										}
									}
									nKeyCount++; //�L�[�J�E���g�̉��Z
								}
							}
							nKeyCount = 0;  //�L�[�J�E���g�̏�����
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++;   //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile); //�t�@�C�������
			break;           //�����𔲂���
		}
	}

	//=================================================================================================================================================================
	//�e�p�[�c�̈ʒu�̎擾
	//=================================================================================================================================================================
	
	//�㔼�g�̈ʒu���擾����
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���݂̃p�[�c�̎��̃p�[�c����
		for (int nNext = 0; nNext < nCount + 1; nNext++)
		{
			//�e�p�[�c�̈ʒu�𑫂����킹��
			SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[nNext + 2]->GetPos();  //�����̃p�[�c��
			SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[nNext + 6]->GetPos();  //�E���̃p�[�c��
		}

		//�̂̈ʒu�𑫂����킹��
		SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[0]->GetPos(); //�ʒu�����Z
		SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[0]->GetPos(); //�ʒu�����Z
	}

	//�����g��parts�̈ʒu���擾
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPosBoss[nCount1 + 11] += m_pModelPrtsBoss[nCount1 + 11]->GetPos(); //�����g�̊e�p�[�c
		SaveMotionPosBoss[nCount1 + 11] -= m_pModelPrtsBoss[10]->GetPos();           //���̕�����
	}

	//���Ƒ̂̈ʒu���擾
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPosBoss[nCount2] += m_pModelPrtsBoss[nCount2]->GetPos();                                                                  //�ʒu�����Z
		GetPosPrtsBoss(nCount2) = D3DXVECTOR3(SaveMotionPosBoss[nCount2].x, SaveMotionPosBoss[nCount2].y, SaveMotionPosBoss[nCount2].z); //�ʒu���C��
	}

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTSBOSS; nCount3++)
	{
		GetPosPrtsBoss(nCount3 + 2) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 2].x + GetPos().x, SaveMotionPosBoss[nCount3 + 2].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 2].z + GetPos().z);      //�ʒu���C��
		GetPosPrtsBoss(nCount3 + 10) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 10].x + GetPos().x, SaveMotionPosBoss[nCount3 + 10].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 10].z + GetPos().z);  //�ʒu���C��
	}
}


//===============================
//�v���C���[���[�V�������s��
//===============================
void CCharacter::MotionInfo()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrts[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCount != MotionSetPlayer[m_MotionState].NumKey - 1)
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
			}
			else
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].pos; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].rot; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
			}

			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //�ʒu���������ʒu����t���[��������
			rot = Moverot / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //��������������������t���[��������

			//�����̕��������Z
			m_pModelPrts[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrts[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}
	
	GetFrame()++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (GetFrame() == MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame)
	{
		SetFrame(0);   //�t���[����������
		MotionCount++; //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCount == MotionSetPlayer[m_MotionState].NumKey)
		{
			MotionCount = 0; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCount + 1 == MotionSetPlayer[m_MotionState].NumKey && MotionSetPlayer[m_MotionState].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionType = false; //���[�V�����̔����off�ɂ���
			//SetMotion(NEUTRAL);    //���[�V�����̏��̐؂�ւ�
		}
	}
}

//===============================
//�{�X�̃��[�V�������s��
//===============================
void CCharacter::MotionInfoBoss()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsBoss[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountBoss != MotionSetBoss[m_MotionStateBoss].NumKey - 1)
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
			}
			else
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].pos; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].rot; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
			}

			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������

			//���[�V�����������Ń��[�v���I�t�̎�
			if (MotionSetBoss[BOSSWALK].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃ��[�V�����J�E���g���P�̎��i�L�[�Z�b�g���Ō�̎��j
				if (m_MotionStateBoss == BOSSWALK && MotionCountBoss == 1)
				{
					MotionSetBoss[BOSSWALK].KeySet[MotionCountBoss].Frame = 0; //���[�V�����t���[����������
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       //�ʒu��������
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       //������������
				}
			}

			//���[�V���������S�Ń��[�v���I�t�̎�
			if (MotionSetBoss[BOSSDIE].Loop == false)
			{
				//���[�V�����̏�Ԃ����S�Őݒ肳��Ă��鎞�ƃ��[�V�����J�E���g���R�̎��i�L�[�Z�b�g���Ō�̎��j
				if (m_MotionStateBoss == BOSSDIE && MotionCountBoss == 3)
				{
					MotionSetBoss[BOSSDIE].KeySet[MotionCountBoss].Frame = 0; //���[�V�����t���[����������
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                      //�ʒu��������
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                      //������������
				}
			}

			//�����̕��������Z
			m_pModelPrtsBoss[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsBoss[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}

	m_nMotionFrameBoss++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_nMotionFrameBoss == MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //�J�E���g��������
		MotionCountBoss++;      //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountBoss + 1 == MotionSetBoss[m_MotionStateBoss].NumKey && MotionSetBoss[m_MotionStateBoss].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionBossType = false; //���[�V�����̔����off�ɂ���
			//SetMotionBoss(BOS);      //���[�V�����̏��̐؂�ւ�
		}
	}
}


//================================
//�v���C���[�̃��[�V�����̐ݒ�
//================================
void CCharacter::SetMotion(MOTIONSTATE motiontype)
{
	//���݂̃��[�V�����ƈ������
	if (m_MotionState != motiontype && m_bMotionType == false)
	{
		m_MotionState = motiontype; //���[�V������ݒ�
		MotionCount = 0;            //���[�V�����̃J�E���g��������
		SetFrame(0);                //�t���[����������

		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
		{
			//���f���p�[�c�̏�񂪂��鎞
			if (m_pModelPrts[nModelCount] != nullptr)
			{
				m_pModelPrts[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                            //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrts[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);                            //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrts[nModelCount]->GetPos() += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].pos; //���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrts[nModelCount]->GetRot() += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].rot; //���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}


//================================
//�{�X�̃��[�V�����̐ݒ�
//================================
void CCharacter::SetMotionBoss(BOSSMOTIONSTATE motiontype)
{
	//���݂̃��[�V�����ƈ������
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false)
	{
		m_MotionStateBoss = motiontype; //���[�V������ݒ�
		MotionCountBoss = 0;            //���[�V�����̃J�E���g��������
		m_nMotionFrameBoss = 0;         //�t���[���̃J�E���g�̏�����
		
		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
		{
			//���f���p�[�c�̏�񂪂��鎞
			if (m_pModelPrtsBoss[nModelCount] != nullptr)
			{
				m_pModelPrtsBoss[nModelCount]->SetPos(m_pSaveModelPrtInfoBoss[nModelCount].pos);                        //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrtsBoss[nModelCount]->SetRot(m_pSaveModelPrtInfoBoss[nModelCount].rot);					    //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrtsBoss[nModelCount]->GetPos() += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].pos;	//���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrtsBoss[nModelCount]->GetRot() += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].rot;	//���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}
