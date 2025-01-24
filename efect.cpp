//===================================
//
//�G�t�F�N�g�̏���[efect.cpp]
//Auther:Chiba Haruki
//
//===================================


//===================================
//�C���N���[�h
#include "main.h"
#include "rendererh.h"
#include "efect.h"
#include "manager.h"


//==================================================================================
//���o�p�G�t�F�N�g�̃X�g���e�W�[�N���X��ꏈ��
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CEffectDirection::CEffectDirection()
{
	m_aEffectFileName = nullptr;  //�t�@�C���p�X�̏�����
	m_nLife = 0;                  //���C�t�̏�����
	m_pVtxBuffMine = nullptr;     //�o�b�t�@�̏�����
}

//========================
//�f�X�g���N�^
//========================
CEffectDirection::~CEffectDirection()
{

}

//==================================================================================
//�e�N�X�`���̐ݒ菈��
//==================================================================================
void CEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(fTexSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexSize, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================
//�e�N�X�`���̍X�V����
//==================================================================================
void CEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex)
{
	m_nLife++;  //�J�E���g����

	//���C�t������̐��l�ɂȂ�����
	if (m_nLife >=MAX_EXPLOSION_LIFE * dLifeCount)
	{
		VERTEX_3D* pVtx;

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
//���̃G�t�F�N�g
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CThunder::CThunder()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\thunder.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CThunder::~CThunder()
{

}


//==================================================================================
//�����G�t�F�N�g
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CExplotion::CExplotion()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\explosion001.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CExplotion::~CExplotion()
{

}


//==================================================================================
//���̔����G�t�F�N�g
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CExplotionPillar::CExplotionPillar()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\Fire000.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CExplotionPillar::~CExplotionPillar()
{

}


//==================================================================================
//����̉��G�t�F�N�g
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CExplotionPillar001::CExplotionPillar001()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\PillarOfFireAll.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CExplotionPillar001::~CExplotionPillar001()
{

}


//==================================================================================
//�j�ЃG�t�F�N�g�̃X�g���e�W�[�N���X�̌p������
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CFormerDebris::CFormerDebris()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\010.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CFormerDebris::~CFormerDebris()
{

}


//==================================================================================
//�K�E�Z
//==================================================================================

//========================
//�R���X�g���N�^
//========================
CSourceSpecialAttack::CSourceSpecialAttack()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\SpecialGage\\SpecialGageRE.png"); //�t�@�C���p�X��ݒ�
}

//========================
//�f�X�g���N�^
//========================
CSourceSpecialAttack::~CSourceSpecialAttack()
{

}


//=======================================================================================================================================================================
//�G�t�F�N�g�̊Ǘ��ҏ���
//=======================================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CManagerEffect::CManagerEffect(int nPriority) : CObject3D(nPriority)
{
	SetLife(SET_BULLET_LIFE);          //���C�t�̐ݒ�
	m_pEffectDirection000 = nullptr;   //�X�g���e�W�[���N���X�̃|�C���^�[�̏�����
	m_nEffectNumber = -1;              //�G�t�F�N�g�i���o�[�̏�����
	m_dLifeCount = 0.0;                //�A�j���[�V�����̑��x�̏�����
	m_fMaxTex = 0.0f;                  //�e�N�X�`���̑傫���̏�����
}

//===========================
//�f�X�g���N�^
//===========================
CManagerEffect::~CManagerEffect()
{
	//�X�g���e�W�[���N���X�̃|�C���^�[�̏�񂪂��鎞
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;    //��������
		m_pEffectDirection000 = nullptr; //���𖳂���
	}
}

//============================
//����������
//============================
HRESULT CManagerEffect::Init()
{
	//�������Ɏ��s������
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;            //���s��Ԃ�
	}

	return S_OK;                  //������Ԃ�
}

//============================
//�j������
//============================
void CManagerEffect::Uninit()
{
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}

//============================
//�X�V����
//============================
void CManagerEffect::Update()
{
	//�A�j���[�V�����̑��x���O�ȊO�̎�
	if (m_dLifeCount != 0.0)
	{
		m_pEffectDirection000->Effect(GetTexture(), GetBuffer(), m_dLifeCount, m_fMaxTex); //�X�g���e�W�[�̊��N���X�̏������Ă�
	}

	SetAddjustLife()--;                       //���C�t�����炷

	//�G�t�F�N�g�i���o�[���P�ȊO�̎�
	if (m_nEffectNumber != 1)
	{
		if (GetAlpha() > 0)
		{
			SetAddjustAlpha() -= MINUS_ALPHA; //�A���t�@�l�����炷
		}
	}

	SetCol(RED, GREEN, BLUE, GetAlpha());     //�F�̐ݒ�

	//���C�t���s������
	if (GetLife() <= 0)
	{
		//���G�t�F�N�g��
		if (m_nEffectNumber == 1)
		{
			this->SetEffect(GetPos());  //���g�̃G�t�F�N�g���Ă�
			SetAlpha(200);              //�A���t�@�l�̐ݒ�
			SetLife(60);                //���C�t�̐ݒ�
			m_nEffectNumber = -1;       //�G�t�F�N�g�i���o�[�̏������i���̌�������߁j
		}

		//���̑��̎�
		else
		{
			CObject3D::Release(); //���g������
			return;               //�����𔲂���
		}
	}

	CObject3D::Update();          //�X�V�������Ă�
}

//============================
//�`�揈��
//============================
void CManagerEffect::Draw()
{
	CObject3D::DrawEffect(); //�`�揈�����Ă�
}


//============================
//�G�t�F�N�g�̐ݒ�
//============================
void CManagerEffect::SetEffect(D3DXVECTOR3 pos)
{
	SetPos(pos); //�ʒu�������Ɠ���������
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CManagerEffect* CManagerEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CManagerEffect* pEffect = nullptr; //���N���X�̃|�C���^�[

	//��
	if (type == CObject3D::TYPE::THENDER)
	{
		pEffect = new CNatureEffect(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;                                                                   //�G�t�F�N�g�i���o�[�̐ݒ�
			pEffect->m_pEffectDirection000 = new CThunder();                                                //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CNatureEffect::MAX_THANDER_TEX);  //�ꕪ��
			pEffect->m_fMaxTex = CNatureEffect::MAX_THANDER_TEX;                                            //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CNatureEffect::THANDER_SIZEX, CNatureEffect::THANDER_SIZEY, 0.0f);             //�傫����ݒ�
			pEffect->m_dLifeCount = 0.0;                                                                    //�A�j���[�V�����̑��x�̐ݒ�
			
		}
	}

	//����
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		pEffect = new CExplosion(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                             //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CExplosion::MAX_EXPLOSION_TEX);  //������
			pEffect->m_fMaxTex = CExplosion::MAX_EXPLOSION_TEX;                                            //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CExplosion::EXPLSION_SIZEX, CExplosion::EXPLSION_SIZEY, 0.0f);                //�傫����ݒ�
			pEffect->m_dLifeCount = CExplosion::MAX_EXPLOSION_ANIMETION_SPEED;                             //�A�j���[�V�����̑��x�̐ݒ�
		}
	}

	//�����O�O�P
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		pEffect = new CExplosion001(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                                        //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\explosion004.png");  //�e�N�X�`���̃t�@�C���p�X��ݒ�
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CExplosion001::MAX_EXPLOSION001_TEX);       //������
			pEffect->m_fMaxTex = CExplosion001::MAX_EXPLOSION001_TEX;                                                 //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CExplosion001::EXPLSION001_SIZEX, CExplosion001::EXPLSION001_SIZEY, 0.0f);               //�傫����ݒ�
			pEffect->m_dLifeCount = CExplosion001::MAX_EXPLOSION001_ANIMETION_SPEED;                                  //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//��
	else if (type == CObject3D::TYPE::FIRE)
	{
		pEffect = new CFire(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar();                            //�p���N���X
			pEffect->m_nEffectNumber = 1;                                                       //�G�t�F�N�g�i���o�[�̐ݒ�
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CFire::MAX_FIRE_TEX); //������     
			pEffect->m_fMaxTex = CFire::MAX_FIRE_TEX;                                           //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CFire::FIRE_SIZEX, CFire::FIRE_SIZEY, 0.0f);                       //�傫���̐ݒ�
			pEffect->m_dLifeCount = CFire::MAX_FIRE_ANIMETION_SPEED;                            //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//����̉�
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		pEffect = new CPillarOfFire(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar001();                                           //�X�g���e�W�[�̌p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CPillarOfFire::MAX_PILLAROFFIRE_TEX);   //������
			pEffect->m_fMaxTex = CPillarOfFire::MAX_PILLAROFFIRE_TEX;                                             //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CPillarOfFire::PILLAROFFIRE_SIZEX, CPillarOfFire::PILLAROFFIRE_SIZEY, 0.0f);         //�傫���̐ݒ�
			pEffect->m_dLifeCount = CPillarOfFire::MAX_PILLAROFFIRE_ANIMETION_SPEED;                              //�A�j���[�V�����̐i�߂鑬����ݒ�
		}
	}

	//�j��
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		pEffect = new CDebris(); //�p���N���X

		//�������ɐ���������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CFormerDebris();                                   //�X�g���e�W�[�p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CDebris::MAX_DEBRIS_TEX); //�ꕪ��
			pEffect->m_fMaxTex = CDebris::MAX_DEBRIS_TEX;                                           //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
		}
	}

	//�K�E�Z
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		pEffect = new CSpecialAttack(); //�p���N���X

		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttack();                                          //�X�g���e�W�[�p���N���X
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CSpecialAttack::MAX_SPECIALATTACK_TEX); //������
			pEffect->m_fMaxTex = CSpecialAttack::MAX_SPECIALATTACK_TEX;                                           //�e�N�X�`���̍ő�T�C�Y�̐ݒ�
			pEffect->SetSize(CSpecialAttack::SPECIALATTACK_SIZEX, CSpecialAttack::SPECIALATTACK_SIZEY, 0.0f);     //�傫���̐ݒ�
		}
	}

	//�e�N�X�`���[��ʒu�̓���
	if (pEffect != nullptr)
	{
		pEffect->SetFileNamePass(pEffect->m_pEffectDirection000->GetEffectFileNamePass());  //�e�N�X�`���̃t�@�C���p�X�̓���
		pEffect->SetPos(pos);                                                               //�ʒu�̓���
		pEffect->Lood();                                                                    //�e�N�X�`���̓ǂݍ��݊֐�
		return pEffect;                                                                     //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//=======================================================================================================================================================
//���R�n�̃G�t�F�N�g����
//=======================================================================================================================================================
CNatureEffect::CNatureEffect()
{

}
CNatureEffect::~CNatureEffect()
{

}


//==============================================================================================================================================================
//�����G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CExplosion::CExplosion()
{

}

//===========================
//�R���X�g���N�^
//===========================
CExplosion::~CExplosion()
{

}


//==============================================================================================================================================================
//���G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CFire::CFire()
{
	SetLife(FIRELIFE); //���C�t�̐ݒ�
}

//===========================
//�R���X�g���N�^
CFire::~CFire()
{

}

//===========================
//�`�揈��
//===========================
void CFire::Draw()
{
	CObject3D::DrawEffect1(); //�`�揈�����Ă�
}


//==============================================================================================================================================================
//����̉�
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CPillarOfFire::CPillarOfFire()
{
	SetLife(PILLARFIRELIFE); //���C�t�̐ݒ�
}

//===========================
//�R���X�g���N�^
CPillarOfFire::~CPillarOfFire()
{

}

//============================
//����������
//============================
HRESULT CPillarOfFire::Init()
{
	//����������������������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//============================
//�X�V����
//============================
void CPillarOfFire::Update()
{
	this->GetEffectDirection()->Effect(GetTexture(), GetBuffer(), 0.5, MAX_PILLAROFFIRE_TEX); //���g�̃X�g���e�W�[�p���N���X�̏������Ă�
	SetCol(RED, GREEN, BLUE, GetAlpha());                                                     //�F�̐ݒ�

	//�����蔻��
	if (CObject3D::CollisionPrtsPlayer(PILLAROFFIRE_SIZEX, PILLAROFFIRE_SIZEY, PILLAROFFIRE_SIZEZ) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.01f; //�v���C���[��HP�Q�[�W�����炷
	}

	//���C�t���O�ȉ��̎�
	if (GetLife() <= 0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA;  //�A���t�@�l�����炷

		//�A���t�@�l���O�ȉ��̎�
		if (GetAlpha() <= 0)
		{
			CObject::Release(); //���g���폜
			return;             //�����𔲂���
		}
	}
	else
	{
		SetAddjustLife()--;    //���C�t�����炷
	}
}


//==============================================================================================================================================================
//�e�ɂ��G�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\effect000.jpg");  //�e�N�X�`���̃t�@�C���p�X��ݒ�
}


//===========================
//�f�X�g���N�^
//===========================
CEffect::~CEffect()
{

}


//============================
//����������
//============================
HRESULT CEffect::Init()
{
	//������������������
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;           //���s��Ԃ�
	}

	SetSize(SIZEX, SIZEY, 0.0f); //�傫���̐ݒ�
	return S_OK;                 //������Ԃ�
}


//============================
//�j������
//============================
void CEffect::Uninit()
{
	CObject3D::Uninit(); //���N���X�̔j���������Ă�
}


//============================
//�X�V����
//============================
void CEffect::Update()
{
	SetAddjustLife()--; //���C�t�����炷

	//���C�t���O�ȉ��̎�
	if (GetLife() <= 0)
	{
		CObject3D::Release(); //���g������
		return;               //�����𔲂���
	}

	CObject3D::Update();      //�X�V�������Ă�
}


//============================
//�`�揈��
//============================
void CEffect::Draw()
{
	CObject3D::DrawEffect(); //�`�揈�����Ă�
}


//===========================
//�G�t�F�N�g�̐���
//===========================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pEffect = new CEffect(0); //���I�m��

	//��񂪂��鎞
	if (pEffect != nullptr)
	{
		//������������������
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->SetPos(pos);      //�ʒu�������Ɠ���������
			pEffect->Lood();           //�e�N�X�`���̓ǂݍ���
			return pEffect;            //����Ԃ�
		}						       
	}							       
								       
	return nullptr;                    //����Ԃ�
}


//==============================================================================================================================================================
//�����G�t�F�N�g001
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CExplosion001::CExplosion001()
{

}


//===========================
//�R���X�g���N�^
//===========================
CExplosion001::~CExplosion001()
{

}


//==============================================================================================================================================================
//�j�ЃG�t�F�N�g
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CDebris::CDebris()
{
	SetLife(DEBRISLIFE); //���C�t�̐ݒ�
	SetSizeX(SIZEX);     //�����̑傫����ݒ�
}


//===========================
//�R���X�g���N�^
//===========================
CDebris::~CDebris()
{

}

//===========================
//�X�V����
//===========================
void CDebris::Update()
{
	SetAddjustLife()--;                       //���C�t�����炷
	SetAddjustSizeX() += PLUS_SIZEX;          //�����̃T�C�Y��傫������
	SetSize(GetSizeX(), GetSizeX(), 0.0f);    //�T�C�Y�̐ݒ�

	//���C�t���O�ȉ��̎�
	if (GetLife() <= 0)
	{
		CObject3D::Release(); //���g������
	}
}


//==============================================================================================================================================================
//�K�E�Z
//==============================================================================================================================================================

//===========================
//�R���X�g���N�^
CSpecialAttack::CSpecialAttack()
{
	SetLife(SPECIALATTACKLIFE);   //���C�t�̐ݒ�
	SetSizeX(m_fSepecialAttackX); //�����̑傫����ݒ�
	m_nRotNumber = 0;             //�����ԍ��̏�����
}

//===========================
//�R���X�g���N�^
CSpecialAttack::~CSpecialAttack()
{

}

//============================
//�X�V����
//============================
void CSpecialAttack::Update()
{
	this->GetEffectDirection()->Effect(GetTexture(), GetBuffer(), 0.3, MAX_SPECIALATTACK_TEX); //���g�̃X�g���e�W�[�p���N���X�̏������Ă�

	SetCol(RED, GREEN, BLUE, GetAlpha());        //�F�̐ݒ�

	//�����̑傫�����K��l��菬������
	if (GetSizeX() <= MAXIMUM_SIZEX)
	{
		SetAddjustSizeX() += PLUS_SIZEX;         //�T�C�Y��傫������
	}

	//�����ԍ����P�̎�
	if (m_nRotNumber == 1)
	{
		SetEffectSize(GetSizeX(), m_fSepecialAttackY, 0.0f);    //�T�C�Y�̐ݒ�
	}

	//�����ԍ����Q�̎�
	else if (m_nRotNumber == 2)
	{
		SetEffectSize(-GetSizeX(), m_fSepecialAttackY, 0.0f);   //�T�C�Y�̐ݒ�
	}

	HitEnemy(); //�����蔻�菈�����Ă�

	//���C�t���O�ȉ��̎�
	if (GetLife() <= 0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA;                       //�A���t�@�l�����炷

		//�A���t�@�l���O�ȉ��̎�
		if (GetAlpha() <= 0)
		{
			CObject::Release(); //���g���폜
			return;             //�����𔲂���
		}
	}
	else
	{
		SetAddjustLife()--;     //���C�t�����炷
	}
}

//============================
//�G�Ƃ̓����蔻�菈��
//============================
void CSpecialAttack::HitEnemy()
{
	//�{�X�̏�񂪂��鎞
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		//�{�X�̍ő�p�[�c������
		for (int nCount2 = 0; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//�����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
				m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), GetSizeX()))
			{
				CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= CMain::SCREEN_WIDTH * MAX_DAMAGE_BOSS; //�{�X��HP�Q�[�W�����炷
			}
		}
	}

	//���[�V�����t���̓G�̍��ꂽ����
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count() + 1; nMotionInEnemy001++)
	{
		//��񂪂��鎞
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			//���[�V�����t���̓G�̍ő�p�[�c������
			for (int nCount1 = 0; nCount1 < CObjectX::MAX_ENEMYPARTS; nCount1++)
			{
				//�����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nCount1),
					m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(nCount1), GetSizeX()))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() = 0; //���C�t������

					//���[�V�����t���̓G�̃��C�t���s������
					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //�|�C���^�[��nullptr�ɂ���
						return;                                                                                                 //�����𔲂���
					}
				}
			}
		}
	}
}