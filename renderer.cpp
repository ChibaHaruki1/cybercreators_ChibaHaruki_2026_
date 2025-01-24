//=======================================
//
//�����_���[�̏���[renderer.cpp] 
//Auther:Chiba Haruki
//
//=======================================


//=======================================
//�C���N���[�h
#include "main.h"
#include "rendererh.h"
#include "bg.h"
#include "input.h"
#include "sound.h"
#include "manager.h"
#include "scene.h"


//==================
//�R���X�g���N�^
//==================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;        //DirectX9�̏��̏�����
	m_pD3DDevice = nullptr;  //DirectX9�̃f�o�C�X�̏�����

	m_pFont = nullptr;       //�t�H���g�̏�����
	m_bPause = false;        //�|�[�Y���Ă��Ȃ��ɐݒ�
	m_bDrawShader = false;   //�V�F�[�_�[��`�悵�Ȃ��ɐݒ�
}

//==================
//�f�X�g���N�^
//==================
CRenderer::~CRenderer()
{

}

//==================
//����������
//==================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

	//DirectX�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    //��񂪂Ȃ���
	if (m_pD3D == nullptr)
	{
		return E_FAIL; //���s��Ԃ�
	}

	//���݂̃f�B�X�v���C���[�h�������ł��Ȃ���
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));                          //�p�����[�^�[���N���A
	d3dpp.BackBufferWidth = CMain::SCREEN_WIDTH;                //�Q�[����ʂ̕�
	d3dpp.BackBufferHeight = CMain::SCREEN_HEIGHT;              //�Q�[����ʂ̍���
	d3dpp.BackBufferFormat = d3ddm.Format;                      //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                  //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   //�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;                        //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  //�f�v�X�o�b�t�@�Ƃ��ĂP�U�r�b�g�g�p
	d3dpp.Windowed = bWindow;                                   //�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //�C���^�[�o��

	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL; //���s��Ԃ�
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[state�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
	
	CManager::SetMode(CScene::MODE::MODE_GAME01); //���߂̃V�[����ݒ�

	return S_OK; //������Ԃ�
}

//==================
//�I������
//==================
void CRenderer::Uninit()
{
	//Direct3D�f�o�C�X�̏�񂪂��鎞
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release(); //��������
		m_pD3DDevice = nullptr;  //���𖳂���
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();       //��������
		m_pD3D = nullptr;        //���𖳂���
	}

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();      //��������
		m_pFont = nullptr;       //���𖳂���
	}
}

//==================
//�X�V����
//==================
void CRenderer::Update()
{
	//P�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_P) == true)
	{
		m_bPause = m_bPause ? false : true;
	}

	//pause���ĂȂ�
	if (m_bPause == false)
	{
		CObjectManagerX::UpdateAll();  //�I�u�W�F�N�g�̍X�V����
		CObject::UpdateAll();          //�I�u�W�F�N�g�̍X�V����
	}

	//pause��
	else if (m_bPause == true)
	{
		//CManager::GetSCene()->GetOverhead_Processing()->GetTutorialUI()->Update(0.0f, 0.0f, 0.0f);
		//CManager::GetSCene()->GetOverhead_Processing()->Tutorial();
	}
}


//==================
//�`�揈��
//==================
void CRenderer::Draw()
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//�`��J�n�����������ꍇ

		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);                //�ʏ�`��

		//�܂��V�F�[�_�[��`�悵�ĂȂ���
		if (m_bDrawShader == false)
		{
			m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);       //�ʏ�V�F�[�_�[�ɐݒ�

			//�C�x���g�̏�񂪂��鎞
			if (CManager::GetEvent() != nullptr)
			{
				//�{�X�̉��o���J�n
				if (CManager::GetEvent()->GetBossDirection() == true)
				{
					m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);  //�V�F�[�_�[��ύX�i�RD���f����ʕ\���j
					m_bDrawShader = true;                                          //�V�F�[�_�[��`�悵��
				}
			}
		}

		//���݂̃V�[��
		switch (CManager::GetScene()->GetMode())
		{
			//�^�C�g����
		case CScene::MODE::MODE_TITLE:
			break;

			//���U���g��
		case CScene::MODE::MODE_RESULT:
			break;

			//�Q�[���I�[�o�[��
		case CScene::MODE::MODE_GAMEOVER:
			break;

			//���̑�
		default:
			CManager::GetScene()->GetCamera()->SetCamera(); //�J�����̐ݒ�
			break;
		}

		//�S�Ă̕`��
		CObjectManagerX::DrawAll();
		CObject::DrawAll();

		//DrawFPS(); //debug�`��

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//================
//FPS�̕\��
//================
void CRenderer::DrawFPS()
{
	//�\���p�ϐ�
	RECT rect = { 0,0,CMain::SCREEN_WIDTH,CMain::SCREEN_HEIGHT }; //X,Y,�傫���i���A�c�j�ňʒu�ݒ�

	char aStr[10];                                                //�������ۊǂ���p�̕ϐ�

	//������ɑ��
	wsprintf(&aStr[0], "FPS;%d\n", CManager::GetMain()->GetFPS());

	//�e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}