//====================================
//
//��ʑJ�ڏ���[scene.cpp]
//Auther:Haruki Chiba
//
//====================================


//====================================
//�C���N���[�h
#include "scene.h"
#include "manager.h"
#include "rendererh.h"
#include "bullet.h"
#include "enemy.h"
#include "efect.h"
#include "collision.h"
#include "score.h"
#include "objectX.h"
#include "stage_obj.h"
#include "block.h"
#include "gage.h"
#include "enemyinmotion.h"
#include "bg.h"


//================================
//�O���[�o���ϐ�
CManagerBg* g_pBG; //�w�i��BG�̃O���[�o���ϐ�(���ł�bg.h��scene.h���C���N���[�h���Ă���׃����o�[�ϐ��Ɏ��ĂȂ��@�O���錾�Ȃ玝�Ă�H)


//=======================
//�R���X�g���N�^
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;          //�J�����|�C���^�[�̏�����
	m_pLight = nullptr;           //�����|�C���^�[�̏�����
	m_pPlayerX = nullptr;         //�v���C���[�|�C���^�[�̏�����
	m_bOneSound = false;          //�P�x���������𗬂��t���O�̏�����
	m_bOneScene = false;          //�P�x�������̃V�[���̏�����ʂ��t���O�̏�����
	m_bPlay = false;              //�V�ׂ��ԂɂȂ��Ă��邩�ǂ����̃t���O�̏�����
	m_Mode = MODE::MODE_RESULT;   //���[�h�̐ݒ�
	m_nFrame = 0;
}


//=======================
//�f�X�g���N�^
//=======================
CScene::~CScene()
{

}


//=======================
//����������
//=======================
HRESULT CScene::Init()
{
	m_pCamera = new CCamera(); //�J�����̓��I�m��
	m_pLight = new CLight();   //�����̓��I�m��
	m_pCamera->Init();         //�J�����̏�����
	m_pLight->Init();          //�����̏�����

	CManager::GetRenderer()->GetDrawShader() = false; //�V�F�[�_�[�����Ȃ�

	return S_OK;               //������Ԃ�
}


//=======================
//�I������
//=======================
void CScene::Uninit()
{
	CObject::ReleaseAll();         //�S�Ă�Uninit()���ĂсAdelete����
	CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����

	m_pPlayerX = nullptr;          //���𖳂���

	//�J�����̏�񂪂��鎞
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //�J�����̏I������
		delete m_pCamera;    //�������̉��
		m_pCamera = nullptr; //���𖳂���
	}

	//�����̏�񂪂��鎞
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //�����̏I������
		delete m_pLight;    //�������̉��
		m_pLight = nullptr; //���𖳂���
	}
}


//=======================
//�X�V����
//=======================
void CScene::Update()
{
	m_pCamera->Update(); //�J�����̍X�V����
	m_pLight->Update();  //�����̍X�V����
}

//=======================
//���̕���Update���Ă�
//=======================
void CScene::AnyUpdate()
{
	//�X�e�[�W�Q�ɂ̎�
	if (m_Mode == MODE::MODE_GAME02)
	{
		CManager::GetEvent()->Update(); //�C�x���g�̍X�V�������Ă�
	}
}


//=======================
//����
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //���N���X�̓��I�m��

	//�Q�[�����[�h���P�̎�
	if (mode == MODE::MODE_GAME01)
	{
		pScene = new CGame01();               //���I�m��
		pScene->m_Mode = mode;                //���݂̃��[�h�������Ɠ���������
											  
		//�������ɐ���������				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //����Ԃ�
		}									  
	}										  
											  
	//�Q�[�����[�h���Q�̎�				   	  
	else if (mode == MODE::MODE_GAME02)		  
	{										  
		pScene = new CGame02();               //���I�m��
		pScene->m_Mode = mode;                //���݂̃��[�h�������Ɠ���������
											  
		//�������ɐ���������				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //����Ԃ�
		}									  
	}										  
											  
	//�^�C�g���̎�						   	  
	else if (mode == MODE::MODE_TITLE)		  
	{										  
		pScene = new CTitle();                //���I�m��
		pScene->m_Mode = mode;                //���݂̃��[�h�������Ɠ���������
											  
		//�������ɐ���������				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //����Ԃ�
		}									  
	}										  
											  
	//���U���g�̎�						   	  
	else if (mode == MODE::MODE_RESULT)		  
	{										  
		pScene = new CResult();               //���I�m��
		pScene->m_Mode = mode;                //���݂̃��[�h�������Ɠ���������
											  
		//�������ɐ���������				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //����Ԃ�
		}
	}

	//�Q�[�����[�h�̎�
	else if (mode == MODE::MODE_GAMEOVER)
	{
		pScene = new CGameOver();             //���I�m��
		pScene->m_Mode = mode;                //���݂̃��[�h�������Ɠ���������

		//�������ɐ���������
		if (SUCCEEDED(pScene->Init()))
		{
			return pScene;                    //����Ԃ�
		}
	}

	return nullptr;                           //����Ԃ�
}


//================================================================================================================================
//                                                    �Q�[�����[�h�̏���
//================================================================================================================================


//================================================================================================================================
//                                                    �X�e�[�W�P
//================================================================================================================================


//=======================
//�R���X�g���N�^
//=======================
CGame01::CGame01()
{
	m_pFade = nullptr; //�t�F�[�h�|�C���^�[�̏�����
}


//=======================
//�f�X�g���N�^
//=======================
CGame01::~CGame01()
{

}


//=======================
//����������
//=======================
HRESULT CGame01::Init()
{
	//�������Ɏ��s������
	if (FAILED(CScene::Init()))
	{
		return E_FAIL;                                        //���s��Ԃ�
	}

	g_pBG = CManagerBg::Create(MODE::MODE_TITLE);             //�w�i��UI����
	m_pFade = CFade::Create();                                //�t�F�[�h�̐���
													          
	GetCamera()->GetAdjustmentPosZ() = 500;                   //�J������Z���̒���
	GetCamera()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));        //�J�����̌����̐ݒ�
													          
	InitCreate();                                             //�^�C�g���ɕK�v�Ȑ���
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING); //�v���C���[�̃��[�V������T���ɐݒ�
	GetPlayerX()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));       //�v���C���[�̌�����ݒ�
	
	GetPlayerX()->SetAddjustPos().y = 2050.0f;                //�v���C���[��Y���̈ʒu��ݒ�
										                      
	return S_OK;                                              //������Ԃ�
}


//=======================
//�I������
//=======================
void CGame01::Uninit()
{
	CScene::Uninit(); //�j������
}


//=======================
//�X�V����
//=======================
void CGame01::Update()
{
	//�V�[���̏������ʂ�����
	if (GetOneScene() == true)
	{
		//�t�F�[�h�̏�񂪂��鎞
		if (m_pFade != nullptr)
		{
			m_pFade->CFade::SetFade(CFade::FADE::FADE_OUT); //�t�F�[�h�A�E�g�ɐݒ�

			//�t�F�[�h�̏������I�������i���S�ɈÂ��Ȃ�����j
			if (m_pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
			{
				m_pFade->Release();                                           //��������
				g_pBG->Release();                                             //��������
				m_pFade = nullptr;                                            //���𖳂���
				g_pBG = nullptr;                                              //���𖳂���
				GetPlayerX()->SetGravityFlag(true);                           //�d��ON
				GetCamera()->GetAdjustmentPosZ() = 800;                       //�J������Z���̒���
				GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //�J�����̌����̏�����
				GetPlayerX()->SetRot(D3DXVECTOR3(0.0f, -CObjectX::D3DX_PI_ORI, 0.0f));           //�J�����̌����̏�����
				GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP); //�v���C���[�̃��[�V������ݒ�
				CompileCreate();                                              //create���������̂��֐������ČĂ�
				return;                                                       //�����𔲂���
			}
		}

		//�X�y�[�X�V�b�v�O�Ԗڂ̏�񂪂��鎞
		if (CManager::GetInstance()->GetSpeceBattleShip(0) != nullptr)
		{
			SetAddjustFrame()++; //�t���[���𑝂₷

			//�t���[�����K��l��荂����
			if (GetFrame() >= 180)
			{
				CManager::GetInstance()->GetSpeceBattleShip(0)->Release();							//�X�y�[�X�V�b�v������
				CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SPECEBATTLESHIP000, 0); //�X�y�[�X�V�b�v�̃|�C���^�[�̏�����
			}
		}
	}

	//�V�[���̏������ʂ��Ă��Ȃ���
	else if (GetOneScene() == false)
	{
		GetPlayerX()->SetGravityFlag(false); //�v���C���[�̏d��Off

		//Enter�L�[�������ꂽ����A�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
		{
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING);    //�w��̉������~�߂�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);  //BDM�𗬂�
			SetOneScene(true);                                                            //�V�[���̏������ʂ����ɐݒ�
		}
	}

	//����������Ă��Ȃ���
	if (GetOneSound() == false)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDM�𗬂�
		SetOneSound(true);                                                         //��x��������
	}

	CScene::Update(); //�X�V����
}


//=======================
//����������Cretae�֐����Ă�
//=======================
void CGame01::InitCreate()
{
	GetPlayerX() = CPlayerX::Create();                                                                                     //�v���C���[�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(0.0f, 2000.0f, 100.0f));  //�X�y�[�X�V�b�v1�Ԗڂ̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 1);                                                                  //��̐���
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame01::CompileCreate()
{
	//X�t�@�C����create
	//CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));          //�X�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(12700.0f, 1900.0f, 0.0f));   //�X�y�[�X�V�b�v�Q�Ԗڂ̐���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE,0);                                             //�X�R�A�̐���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0);                                               //�v���C���[��HP�Q�[�W�̐���
}


//================================================================================================================================
//                                                    �X�e�[�W2
//================================================================================================================================


//=======================
//�R���X�g���N�^
//=======================
CGame02::CGame02()
{
	SetPlay(false); //�V�ׂ�ɐݒ�
}


//=======================
//�f�X�g���N�^
//=======================
CGame02::~CGame02()
{

}


//=======================
//����������
//=======================
HRESULT CGame02::Init()
{
	//�������Ɏ��s������
	if (FAILED(CScene::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CompileCreate();                                                                      //create���������̂��֐������ČĂ�
	GetPlayerX()->SetPos(D3DXVECTOR3(-POS_X,200.0f,0.0f));                                //�v���C���[�̈ʒu�̐ݒ�
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING);                             //�v���C���[�̃��[�V������T���ɐݒ�
	CManager::GetInstance()->GetSpeceBattleShip(0)->GetRot().y = -CObjectX::D3DX_PI_ORI;  //Y���̌�����ݒ�

	return S_OK;       //������Ԃ�
}


//=======================
//�I������
//=======================
void CGame02::Uninit()
{
	CScene::Uninit(); //�j������
}


//=======================
//�X�V����
//=======================
void CGame02::Update()
{
	//�V�[���̏������ʂ�����
	if (GetOneScene() == false)
	{
		SetAddjustFrame()++;

		if (GetFrame() <= 80)
		{
			GetPlayerX()->SetGravityFlag(false);                                                //�v���C���[�̏d��Off
			CManager::GetInstance()->GetSpeceBattleShip(0)->SetAddjustPos().x += PLUS_POS_X;    //X���̈ʒu�̑���
			GetPlayerX()->SetAddjustPos().x += PLUS_POS_X;                                      //X���̈ʒu�̑���
		}																					   
		else if(GetFrame ()<=81)															   
		{																					   
			GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);                       //�v���C���[�̃��[�V������ݒ�
			GetPlayerX()->SetGravityFlag(true);                                                 //�d��ON
		}																					   
		else if (GetFrame() <= 300)															   
		{																					   
			CManager::GetInstance()->GetSpeceBattleShip(0)->SetAddjustPos().x += PLUS_POS_X;    //X���̈ʒu�̑���
			CManager::GetInstance()->GetSpeceBattleShip(0)->SetAddjustPos().y += 3.0f;         //X���̈ʒu�̑���
		}																					   
		else																				   
		{
			SetOneScene(true);                                                                  //�t���O��Off
			CManager::GetInstance()->GetSpeceBattleShip(0)->Release();                          //�X�y�[�X�V�b�v������
			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SPECEBATTLESHIP000, 0); //�X�y�[�X�V�b�v�̃|�C���^�[�̏�����
			return;
		}
	}
	CScene::Update(); //�X�V����
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame02::CompileCreate()
{
	//X�t�@�C����create
	GetPlayerX() = CPlayerX::Create();                                                                                        //�v���C���[�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(-POS_X, 200.0f, 100.0f));    //�X�y�[�X�V�b�v�̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                                     //��̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));            //�X�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(4335.0f, -200.0f, 0.0f));            //�{�X��̑���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());    //�X�R�A�̐���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0);                                               //�v���C���[��HP�Q�[�W�̐���
}


//================================================================================================================================
//                                                    �^�C�g�����[�h�̏���
//================================================================================================================================

//======================
//�R���X�g���N�^
//======================
CTitle::CTitle()
{
	m_pFade = nullptr;
}


//======================
//�f�X�g���N�^
//======================
CTitle::~CTitle()
{

}


//======================
//������
//======================
HRESULT CTitle::Init()
{
	//CManagerBg::Create(MODE::MODE_TITLE);
	//////CBgText::Create();
	//pFade = CFade::Create();

	CScene::Init();

	GetCamera()->GetAdjustmentPosZ() = 700;

	return S_OK;
}


//======================
//�I������
//======================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
	//CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����
}


//=======================
//�X�V����
//=======================
void CTitle::Update()
{
	////Enter�L�[�������ꂽ�Ƃ�
	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true && pFade->GetAlph() <= 245)
	//{
	//	SetOneScene(true);
	//}

	//else if (GetOneScene() == true)
	//{
	//	pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

	//	//�t�F�[�h�̏������I�������i���S�ɈÂ��Ȃ�����j
	//	if (pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
	//	{
	//		CManager::SetMode(CScene::MODE::MODE_GAME01);
	//		return; //�����𔲂���
	//	}

	//	//CManager::SetMode(CScene::MODE_GAME01);
	//}

	//if (GetOneSound() == false)
	//{
	//	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDM�𗬂�
	//	SetOneSound(true);
	//}

	CScene::Update();
}


//=============================
//�^�C�g���Q�[����ʏ���
//=============================
void CTitle::Game()
{

}


//================================================================================================================================
//                                                   ���U���g���[�h�̏���
//================================================================================================================================


//======================
//�R���X�g���N�^
//======================
CResult::CResult()
{
	
}


//======================
//�f�X�g���N�^
//======================
CResult::~CResult()
{

}


//======================
//������
//======================
HRESULT CResult::Init()
{
	CManagerBg::Create(MODE::MODE_RESULT); //���U���gBG�̐���

	return S_OK;                           //������Ԃ�
}


//======================
//�I������
//======================
void CResult::Uninit()
{
	CScene::Uninit(); //�j������
}


//=======================
//�X�V����
//=======================
void CResult::Update()
{
	//Enter�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetOneScene(true);                            //�V�[���̏������ʂ����ɐݒ�
	}

	//�V�[���̏������ʂ�����
	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_GAME01); //���[�h�̐ݒ�
		return;                                       //�����𔲂���
	}
}


//================================================================================================================================
//                                                   �Q�[���I�[�o�[���[�h�̏���
//================================================================================================================================


//======================
//�R���X�g���N�^
//======================
CGameOver::CGameOver()
{
	
}


//======================
//�f�X�g���N�^
//======================
CGameOver::~CGameOver()
{

}


//======================
//������
//======================
HRESULT CGameOver::Init()
{
	CManagerBg::Create(MODE::MODE_GAMEOVER); //�Q�[���I�[�o�[BG�̐���

	return S_OK;                             //������Ԃ�
}


//======================
//�I������
//======================
void CGameOver::Uninit()
{
	CScene::Uninit(); //�j������
}


//=======================
//�X�V����
//=======================
void CGameOver::Update()
{
	//Enter�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A)==true)
	{
		SetOneScene(true);                             //�V�[���̏������ʂ����ɐݒ�
	}

	//�V�[���̏������ʂ�����
	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);  //���[�h�̐ݒ�
		return;                                        //�����𔲂���
	}
}