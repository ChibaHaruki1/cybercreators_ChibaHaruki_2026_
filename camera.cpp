//================================
//
//�J��������[camera.cpp]
//Auther:Haruki Chiba
//
//================================


//================================
//�C���N���[�h
#include "camera.h"
#include "object.h"
#include "rendererh.h"
#include "manager.h"
#include "player.x.h"


//========================
//�R���X�g���N�^
//========================
CCamera::CCamera()
{
	m_fAdjustmentPosY = 200.0f; //�J�����̍����𒲐�
	m_fAdjustmentPosZ = 1000;  //�J��������O�Ɉ����悤����
}


//========================
//�f�X�g���N�^
//========================
CCamera::~CCamera()
{

}


//========================
//����������
//========================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 1000.0f); //���_�𒲐�
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�����_�𒲐�
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);   //������̒���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      //�����̒���
	m_fSavePosV = m_posV;                     //���_�Ɠ���������

	return S_OK; //������Ԃ�
}


//========================
//�I������
//========================
void CCamera::Uninit()
{

}


//========================
//�X�V����
//========================
void CCamera::Update()
{
	//Y�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Y) == true)
	{//���_�����i�������j�ɂȂ�
		m_posV.y += MAX_CAMERASPEED;           //�����_��Y���𑝉�������
		m_fAdjustmentPosY += MAX_CAMERASPEED;  //Y���̒������̒l�𑝂₷�i�����Ȃ�j
	}

	//N�L�[�������ꂽ��
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_N) == true)
	{//���_����i�傫���j�Ȃ�
		m_posV.y -= MAX_CAMERASPEED;           //�����_��Y��������������
		m_fAdjustmentPosY -= MAX_CAMERASPEED;  //Y���̒������̒l�������i�Ⴍ�Ȃ�j
	}

	//Z�L�[�������ꂽ
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Z) == true)
	{//���_�����ɓ���
		m_rot.y += MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y); //���_�𒍎��_�ƌ����Ɠ���������
		m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y); //���_�𒍎��_�ƌ����Ɠ���������
	}

	////C�L�[�������ꂽ��
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_C) == true)
	//{//���_���E�ɓ���
	//	rot.y -= MAX_ROTSPEED;
	//	m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) ;
	//	m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) ;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_T) == true)
	//{//�����_�����i�������j�ɂȂ�
	//	m_posR.y += MAX_CAMERASPEED;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_B) == true)
	//{//�����_����i�傫���j�Ȃ�
	//	m_posR.y -= MAX_CAMERASPEED;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Q) == true)
	//{//�����_�����Ɍ���
	//	rot.y -= MAX_ROTSPEED;
	//	m_posR.x = m_posV.x + sinf(rot.y) ;
	//	m_posR.z = m_posV.z + cosf(rot.y) ;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_E) == true)
	//{//�����_���E�Ɍ���
	//	rot.y += MAX_ROTSPEED;
	//	m_posR.x = m_posV.x + sinf(rot.y) ;
	//	m_posR.z = m_posV.z + cosf(rot.y) ;
	//}

	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_V) == true)
	//{
	//	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}

	//�J�������v���C���[�ɂ�����
	m_posR.x = CManager::GetScene()->GetPlayerX()->GetPos().x; //�����_�̂w�����v���C���[�̂w���Ɠ���������
	m_posR.y = CManager::GetScene()->GetPlayerX()->GetPos().y; //�����_�̂x�����v���C���[�̂x���Ɠ���������
	m_posR.z = CManager::GetScene()->GetPlayerX()->GetPos().z; //�����_�̂y�����v���C���[�̂y���Ɠ���������

	//�J�������̂��v���C���[�ɍ��킹�ē���(���ڃ��f���̒l��������ƃJ������]�������I�ɐ��ʂɖ߂���邽�߁j
	m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fAdjustmentPosZ; //���_�̂w���𒍎��_�̂w���ƌ����Ƃ���������������p�̒l�Ɠ���������
	m_posV.y = CManager::GetScene()->GetPlayerX()->GetPos().y + m_fAdjustmentPosY; //���_�̂x�����v���C���[�̂x���ƒ����p�̒l�Ɠ���������
	m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fAdjustmentPosZ; //���_�̂y���𒍎��_�̂y���ƌ����Ƃ���������������p�̒l�Ɠ���������
}


//========================
//�J�����̐ݒ�i�`��j
//========================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = CManager::GetRenderer();    //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice= pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�ʏ�`�揈��
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)CMain::SCREEN_WIDTH / (float)CMain::SCREEN_HEIGHT, 10.0f, 4000.0f);

	//���s���e
	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)CMain::SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 10.0f, 2000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}