//=========================================
//
//�Q�c�I�u�W�F�N�g�̏���[object2D.cpp]
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//�C���N���[�h
#include "main.h"
#include "object2D.h"
#include "rendererh.h"
#include "manager.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "collision.h"
#include "score.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;                   //�e�N�X�`���̃|�C���^�[�̏�����
	m_pVtxBuff = nullptr;                   //�o�b�t�@�̃|�C���^�[�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����������������
	m_nRandom = 0;                          //�����̏�����
	m_nFrame = 0;                           //�t���[���̏�����
	m_aFileName = nullptr;                  //�t�@�C���p�X�̏�����
	m_nAlpha = 0;                           //�A���t�@�l�̏�����
}


//=====================
//�f�X�g���N�^
//=====================
CObject2D::~CObject2D()
{

}


//=====================
//����������
//=====================
HRESULT CObject2D:: Init()
{
	CRenderer *pRenderer = CManager::GetRenderer(); //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice;                      //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D* pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, CMain::SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, CMain::SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK; //������Ԃ�
}

//=====================
//�I��������������
//=====================
HRESULT CObject2D::SelectInit(int nPieces,float nTexture)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice;                      //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * nPieces, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	VERTEX_2D* pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//��������
	for (int nCutScore = 0; nCutScore < nPieces; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
		pVtx[1].tex = D3DXVECTOR2(nTexture, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nTexture, 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================
//�I�������i�j���j
//=====================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release(); //��������
		m_pVtxBuff = nullptr;  //���𖳂���
	}
}


//=====================
//�X�V����
//=====================
void CObject2D::Update ()
{
	
}

//=====================
//�`�揈��
//=====================
void CObject2D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================
//�����`�悷�鏈��
//=====================
void CObject2D::MultipleDraw(int nPieces)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nPieces*4, 2);
}



//==================
//�T�C�Y�̐ݒ�
//==================
void CObject2D::SetSIze(float SIZE_X, float SIZE1_X, float SIZE_Y, float SIZE1_Y)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SIZE1_X, SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SIZE_X, SIZE1_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SIZE1_X, SIZE1_Y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================
//�T�C�Y�̐ݒ�
//==================
void CObject2D::SetCol(int Red, int Green, int Blue, int Alph)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===============================
//�e�N�X�`���̓ǂݍ��ݏ���
//===============================
HRESULT CObject2D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//�e�N�X�`���̃t�@�C�����Ȃ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL; //���s��Ԃ�

	}
	return S_OK; //������Ԃ�
}
