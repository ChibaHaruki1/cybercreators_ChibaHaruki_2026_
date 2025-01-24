//==========================================
//
//�{�X�p�G�t�F�N�g�̏���[bossefect.cpp]
//Auther:Chiba Haruki
//
//==========================================


//==========================================
//�C���N���[�h
#include "main.h"
#include "rendererh.h"
#include "bosseffect.h"
#include "manager.h"


//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X��ꏈ��
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CBossEffectDirection::CBossEffectDirection()
{
	m_aEffectFileName = nullptr; //�t�@�C���p�X�̏�����
	m_nLife = 0;                 //���C�t�̏�����
	m_pVtxBuffMine = nullptr;    //�o�b�t�@�̏�����
}

//==========================================
//�f�X�g���N�^
//==========================================
CBossEffectDirection::~CBossEffectDirection()
{

}

//==================================================================================
//�e�N�X�`���̐ݒ菈��
//==================================================================================
void CBossEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	VERTEX_3D* pVtx; //�o�[�e�N�X�̃|�C���^�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexSize, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================
//�e�N�X�`���̍X�V����
//==================================================================================
void CBossEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount ,float fMaxTex)
{
	m_nLife++;  //�J�E���g����

	//���C�t������̐��l�ȏ�ɂȂ�����
	if (m_nLife >= CManagerBossEffect::MAX_BOSSANIMATION_LIFE * dLifeCount)
	{
		VERTEX_3D* pVtx; //�o�[�e�N�X�̃|�C���^�[

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex.x = pVtx[0].tex.x + fMaxTex;
		pVtx[1].tex.x = pVtx[1].tex.x + fMaxTex;
		pVtx[2].tex.x = pVtx[2].tex.x + fMaxTex;
		pVtx[3].tex.x = pVtx[3].tex.x + fMaxTex;

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		m_nLife = 0; //���C�t������������
	}
}


//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X�̌p������
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CAttackEffect::CAttackEffect()
{
	SetFileNamePass("data\\TEXTURE\\UI\\Impact.png"); //�t�@�C���p�X��ݒ�
}

//==========================================
//�f�X�g���N�^
//==========================================
CAttackEffect::~CAttackEffect()
{

}


//==================================================================================
//�K�E�Z�̃X�g���e�W�[�N���X�̌p������
//==================================================================================

//==========================================
//�R���X�g���N�^
//==========================================
CSourceSpecialAttackBoss::CSourceSpecialAttackBoss()
{
	SetFileNamePass("data\\TEXTURE\\UI\\SpecialGage\\BossSpecialAllGage002.png"); //�t�@�C���p�X��ݒ�
}

//==========================================
//�f�X�g���N�^
//==========================================
CSourceSpecialAttackBoss::~CSourceSpecialAttackBoss()
{

}


//=======================================================================================================================================================================
//�G�t�F�N�g�̊Ǘ��ҏ���
//=======================================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CManagerBossEffect::CManagerBossEffect(int nPriority) : CObject3D(nPriority)
{               
	m_pEffectDirection000 = nullptr;  //�X�g���e�W�[���N���X�̃|�C���^�[�̏�����
	m_nBossRotNumber = 0;             //�����ő傫���𔻒肷��ϐ��̏�����(�K�E�Z)
	m_nHitNumber = -1;                //��������������ԍ��Ŕ��肷��ϐ��̏�����(�Ռ��g)
	m_dLifeCount = 0.0;               //�A�j���[�V�����̑��x�̏�����
}


//===========================
//�f�X�g���N�^
//===========================
CManagerBossEffect::~CManagerBossEffect()
{
	//���N���X�̃|�C���^�[�̏�񂪂��鎞
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;     //��������
		m_pEffectDirection000 = nullptr;  //���𖳂���
	}
}


//============================
//����������
//============================
HRESULT CManagerBossEffect::Init()
{
	//�����������s������
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	SetSizeX(MAX_SIZEX);                         //�����̑傫���̐ݒ�
	SetSizeY(MAX_SIZEY);                         //�����̑傫���̐ݒ�
	SetSize(GetSizeX(), GetSizeY(), MAX_SIZEZ);  //�傫���̐ݒ�
	return S_OK;                                 //������Ԃ�
}


//============================
//����������
//============================
void CManagerBossEffect::Uninit()
{
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}


//============================
//����������
//============================
void CManagerBossEffect::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, fMaxTex);
	//m_nLife--;                           //���C�t�����炷

	//SetCol(255, 255, 255, m_nAlpha);     //�F�̐ݒ�

	////���C�t���s������
	//if (m_nLife <= 0)
	//{
	//	CManager::GetInstance()->DesignationUninit3D(IMPACT);
	//	CObject3D::Release();
	//	return;
	//}

	//CObject3D::Update();
}

//============================
//����������
//============================
void CManagerBossEffect::Draw()
{
	CObject3D::DrawEffect(); //�`�揈�����Ă�
}


//============================
//�G�t�F�N�g�̐ݒ�
//============================
void CManagerBossEffect::SetEffect(D3DXVECTOR3 pos)
{
	SetPos(pos); //�ʒu�������Ɠ���
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CManagerBossEffect* CManagerBossEffect::Create(D3DXVECTOR3 pos, CObject3D::TYPE type)
{
	CManagerBossEffect* pEffect = nullptr; //���N���X�̃|�C���^�[


	//�^�C�v���Ռ��g�̎�
	if (type == CObject3D::TYPE::IMPACT)
	{
		pEffect = new CImpact(); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CAttackEffect();                                   //�X�g���e�W�[�p���N���X�̓��I�m��
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), MAX_IMPACT_TEXTURESIZE);  //�e�N�X�`���̐ݒ�
			pEffect->SetLife(CImpact::MAX_IMPACT_LIFE);                                             //���C�t�̐ݒ�
		}
	}

	//�^�C�v���K�E�Z�̎�
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		pEffect = new CBossSpecialAttack(); //���I�m��

		//�������ɐ��������Ƃ�
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttackBoss();                                                   //�X�g���e�W�[�p���N���X�̓��I�m��
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), MAX_BOSSANIMETION_TEX);                              //�e�N�X�`���̐ݒ�
			pEffect->SetSize(CBossSpecialAttack::MAX_SPECIALATTACK_SIZEX, CBossSpecialAttack::MAX_SPECIALATTACK_SIZEX, 0.0f);  //�傫���̐ݒ�
			pEffect->SetLife(CBossSpecialAttack::MAX_BOSSSPZECIALATTACK_LIFE);                                                 //���C�t�̐ݒ�
		}
	}
	
	//��񂪂��鎞
	if (pEffect != nullptr)
	{
		pEffect->SetFileNamePass(pEffect->m_pEffectDirection000->GetFileNamePass()); //�t�@�C���p�X��ݒ�
		pEffect->SetPos(pos);                                                        //�ʒu�������Ɠ���
		pEffect->Lood();                                                             //�e�N�X�`���̓ǂݍ���
		return pEffect;                                                              //����Ԃ�
	}

	return nullptr;                                                                  //����Ԃ�
}


//=======================================================================================================================================================
//�Ռ��g�̃G�t�F�N�g�̏���
//=======================================================================================================================================================

//============================
//�R���X�g���N�^
//============================
CImpact::CImpact()
{
	
}

//============================
//�f�X�g���N�^
//============================
CImpact::~CImpact()
{

}

//============================
//�X�V����
//============================
void CImpact::Update()
{
	SetAddjustLife()--;                                 //���C�t�����炷
	SetAddjustSizeX() += PLUS_SIZEX;                    //�����̃T�C�Y��傫������
	SetAddjustSizeY() += PLUS_SIZEY;                    //�����̃T�C�Y��傫������

	SetCol(RED, GREEN, BLUE, GetAlpha());               //�F�̐ݒ�
	SetSize(GetSizeX(), GetSizeY(), MAX_SIZEZ);         //�傫���̍X�V

	//�E���ɓ���������
	if (CObject3D::CollisionPrts1Right(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		SetHitNumber(0); //�������������̔ԍ���ݒ�
	}

	//�����ɓ���������
	else if (CObject3D::CollisionPrts1Left(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		SetHitNumber(1); //�������������̔ԍ���ݒ�
	}

	//���C�t���s������
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->DesignationUninit3D(TYPE::IMPACT); //�C���X�^���X�̃|�C���^�[�̏��𖳂���
		CObject3D::Release();                                       //���g��j������
		return;                                                     //�����𔲂���
	}

	CObject3D::Update();                                            //�X�V�������Ă�
}


//=======================================================================================================================================================
//�K�E�Z�̃G�t�F�N�g�̏���
//=======================================================================================================================================================

//============================
//�R���X�g���N�^
//============================
CBossSpecialAttack::CBossSpecialAttack()
{
	
}

//============================
//�f�X�g���N�^
//============================
CBossSpecialAttack::~CBossSpecialAttack()
{

}

//============================
//�X�V����
//============================
void CBossSpecialAttack::Update()
{
	this->GetBossEffectDirection()->Effect(GetTexture(), GetBuffer(), ANIMETION_DLLIFE, MAX_BOSSANIMETION_TEX); //�e�N�X�`���̃T�C�Y�̍X�V

	SetCol(RED, GREEN, BLUE, GetAlpha());          //�F�̐ݒ�

	//�T�C�Y���K��l��菬������
	if (GetSizeX() <= MAXIMUM_SIZEX)
	{
		SetAddjustSizeX() += PLUS_SIZEX;           //�T�C�Y��傫������
	}

	float fPosY = GetPos().y - CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(17).y * ADJUST_PLAYER_POSY; //�v���C���[��pos.y���v�Z+����=�����蔻��̈�ԉ���ݒ�

	//�����ԍ����P�̎�
	if (GetRotNumber() == 1)
	{
		SetEffectSize(GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);    //�T�C�Y�̐ݒ�

		//�_BX���v���C���[���傫������ɂ���������T�C�Y�̍X�V����������
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), GetPos().x, GetPos().y + PLUS_POS_Y,
			GetSizeX()*ADJUST_SIZE_X + GetPos().x, fPosY) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE; //�v���C���[��HP�Q�[�W�����炷
		}
	}

	//�����ԍ����Q�̎�
	else if (GetRotNumber() == 2)
	{
		SetEffectSize(-GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);   //�T�C�Y�̐ݒ�

		//�_SX���v���C���[��菬��������ɂ���������T�C�Y�̍X�V����������
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), -GetSizeX()* ADJUST_SIZE_X + GetPos().x, GetPos().y + PLUS_POS_Y,
			GetPos().x, fPosY) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE; //�v���C���[��HP�Q�[�W�����炷
		}
	}

	//���C�t���O�ȉ��̎�
	if (GetLife() <= 0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA;          //alpha�l�����炷
		//�A���t�@�l���O�ȉ��̎�
		if (GetAlpha() <= 0)
		{
			CObject::Release();                    //���g���폜
			return;                                //�����𔲂���
		}					                       
	}						                       
	else					                       
	{						                       
		SetAddjustLife()--;                        //���C�t�����炷
	}
}