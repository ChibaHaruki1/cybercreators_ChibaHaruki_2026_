//===================================
//
//�X�R�A�̏���[score.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CManagerScore::CManagerScore(int nPriority) : CObject2D(nPriority)
{
	m_nSocre = 0;     //������
	m_fPosX = 0.0f;   //X���̈ʒu�̏�����
	m_fPosY = 0.0f;   //Y���̈ʒu�̏�����
}

//======================
//�f�X�g���N�^
//======================
CManagerScore::~CManagerScore()
{

}

//======================
//����������
//======================
HRESULT CManagerScore::Init()
{
	//�����������s������
	if (FAILED(SelectInit(MAX_SCORE, DIVISION_SCORE)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	PosScore();        //�z�u����

	return S_OK;       //������Ԃ�
}

//======================
//�I������
//======================
void CManagerScore::Uninit()
{
	CObject2D::Uninit(); //�j���������Ă�
}

//=======================
//�X�V����
//=======================
void CManagerScore::Update()
{

}

//=====================
//�`�揈��
//=====================
void CManagerScore::Draw()
{
	//�ő吔����
	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		//�X�R�A���g�p����Ă���
		if (m_aScore[nCountScore].bUse == true)
		{
			CObject2D::MultipleDraw(nCountScore); //�`�揈�����Ă�
		}
	}
}

//=======================
//�ʒu����
//=======================
void CManagerScore::SetScorepos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx; //�o�[�e�N�X�̃|�C���^�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	//�ő吔����
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		//�X�R�A���g�p����Ă��Ȃ�
		if (m_aScore[nCutScore].bUse == false)
		{
			m_aScore[nCutScore].pos = pos;   //�ʒu�������Ɠ���������
			m_aScore[nCutScore].bUse = true; //�g�p���Ă����Ԃ�

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);

			break; //�����𔲂���
		}
		pVtx += 4; //�o�[�e�N�X�̈ړ�
	}

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}

//=======================
//�ݒ菈��
//=======================
void CManagerScore::SetScore(int nScore)
{
	int nPosTexU[MAX_SCORE]; //�e�N�X�`���̕��������ʒu��ۊ�
	int nDight = 1;          //���Ǘ��p

	VERTEX_2D* pVtx;         //�o�[�e�N�X�̃|�C���^�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	m_nSocre = nScore;       //�����Ɠ���������

	//�ő吔����
	for (int nCalculationScore = 0; nCalculationScore < MAX_SCORE; nCalculationScore++)
	{
		nDight *= DIGIT;                                                                      //���𑝂₷���߂ɂP�O�ŏ�Z���Ă���
		nPosTexU[MAX_SCORE - nCalculationScore - 1] = (nScore % nDight * MAX_SCORE) / nDight; //�e�N�X�`���̕������������̈ʒu���v�Z����
	}

	//�ő吔����
	for (int nScoreTexture = 0; nScoreTexture < MAX_SCORE; nScoreTexture++)
	{
		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)) + (1.0f / FMAX_SCORE), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)) + (1.0f / FMAX_SCORE), 1.0f);

		pVtx += 4; //�o�[�e�N�X�̈ړ�
	}

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}

//==============================
//�X�R�A�����Z���鏈��
//==============================
void CManagerScore::AddScore(int nValue)
{
	//�I�u�W�F�N�g�̔z�u��񂪂��鎞
	if (CManager::GetObjectSet() != nullptr)
	{
		CManager::GetObjectSet()->GetClearScore() += nValue; //���Z
	}

	SetScore(m_nSocre + nValue);                             //�e�N�X�`���̃X�R�A�����Z
}

//==============================
//���������̃X�R�A�����Z���鏈��
//==============================
void CManagerScore::InitAddScore(int nValue)
{
	SetScore(m_nSocre + nValue);                             //�e�N�X�`���̃X�R�A�����Z
}

//=====================
//�ʒu�ݒ�
//=====================
void CManagerScore::PosScore()
{
	//�ő吔����
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		SetScorepos(D3DXVECTOR3(m_fPosX, SCORE_POSY, 0.0f));   //�ʒu
		m_fPosX += PLUSSCORE_POSX;                             //�����̈ʒu�𑝂₷
	}
}

//================
//��������
//================
CManagerScore* CManagerScore::Create(CScene::MODE mode, int Number)
{
	CManagerScore* pScore = nullptr; //���N���X�̃|�C���^�[

	//�Q�[���P�̎�
	if (mode == CScene::MODE::MODE_GAME01)
	{
		pScore = new CResultScore(3);                                        //�p���N���X�œ��I�m��
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number001.png");  //�e�N�X�`���̃p�X�ݒ�
		pScore->m_fPosX = CORE_POSX;                                         //�ʒu�𒲐�
	}

	//���U���g�̎�
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pScore = new CResultScore(3);                                        //�p���N���X�œ��I�m
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number002.png");  //�e�N�X�`���̃p�X��
		pScore->m_fPosX = CORE_POS1X;									     //�ʒu�𒲐�
	}

	//��񂪂��鎞
	if (pScore != nullptr)
	{
		//������������������
		if (SUCCEEDED(pScore->Init()))
		{
			pScore->Lood();                //�e�N�X�`���̓ǂݍ���
			pScore->InitAddScore(Number);  //�X�R�A�̏����l�������Ɠ���
			return pScore;                 //����Ԃ�
		}
	}

	return nullptr;                    //����Ԃ�
}


//=======================================================================================================================
//�Q�[�����̃X�R�A����
//=======================================================================================================================

//======================
//�R���X�g���N�^
//======================
CGameScore::CGameScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//�f�X�g���N�^
//======================
CGameScore::~CGameScore()
{

}


//=======================================================================================================================
//���U���g�̃X�R�A����
//=======================================================================================================================

//======================
//�R���X�g���N�^
//======================
CResultScore::CResultScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//�f�X�g���N�^
//======================
CResultScore::~CResultScore()
{

}