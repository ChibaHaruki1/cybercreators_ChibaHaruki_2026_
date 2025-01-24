//=================================
//
//��������[light.cpp]
//Auther:Haruki Chiba
//
//=================================


//=================================
//�C���N���[�h
#include "light.h"
#include "rendererh.h"
#include "manager.h"


//=======================
//�R���X�g���N�^
//=======================
CLight::CLight()
{
	//�����̍ő吔����
	for (int Light = 0; Light < MAX_LIGHT; Light++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_aLight[Light], sizeof(D3DLIGHT9));
	}
}


//=======================
//�f�X�g���N�^
//=======================
CLight::~CLight()
{

}


//=======================
//����������
//=======================
HRESULT CLight::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice;                      //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//�����̈ʒu���擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//�����̍ő吔����
	for (int LightCount = 0; LightCount < MAX_LIGHT; LightCount++)
	{
		//���C�g�̎�ނ�ݒ�
		m_aLight[LightCount].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.0f, -1.0f, 1.2f);
		vecDir[1] = D3DXVECTOR3(0.0f, -1.0f, -0.8f);
		vecDir[2] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vecDir[3] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir[LightCount], &vecDir[LightCount]);

		//����
		m_aLight[LightCount].Direction = vecDir[LightCount];

		//�F
		m_aLight[LightCount].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g��ݒ肷��
		pDevice->SetLight(LightCount, &m_aLight[LightCount]);

		//���C�g��ݒ肷��
		pDevice->LightEnable(LightCount, TRUE);
	}
	return S_OK; //������Ԃ�
}


//=======================
//�I������
//=======================
void CLight::Uninit()
{

}


//=======================
//�X�V����
//=======================
void CLight::Update()
{

}