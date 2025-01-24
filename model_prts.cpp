//======================================
//
//�p�[�c���̏���[model_prts.cpp]
//Auther: Haruki Chiba
//
//======================================


//======================================
//�C���N���[�h
#include "model_prts.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CModelPrts::CModelPrts()
{
	m_nIndexPrts = 0;         //�p�[�c�ԍ��̏�����
	m_nIndexModelPrts = 0;    //�e�p�[�c�ԍ��̏�����
	m_bDraw = true;           //�`�������
	m_nNumMat = 0;            //�}�e���A���̐��̏�����
	m_pMesh = nullptr;        //���b�V���̏�����
	m_pBuffMat = nullptr;     //�o�b�t�@�̏�����
	m_pParentlPrts = nullptr; //���g�̃|�C���^�[�̏�����

	//�e�N�X�`���̍ő吔����
	for (int nCount = 0; nCount < MAX_MODEL_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr; //�e�N�X�`���̏�����
	}
}

//=======================
//�f�X�g���N�^
//=======================
CModelPrts::~CModelPrts()
{

}

//======================
//����������
//======================
HRESULT CModelPrts::Init()
{
	return S_OK; //������Ԃ�
}

//========================
//�j������
//========================
void CModelPrts::Uninit()
{
	//���b�V���̏�񂪂��鎞
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release(); //���b�V���̍폜
		m_pMesh = nullptr;  //���𖳂���
	}

	//�o�b�t�@�̏�񂪂��鎞
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release(); //�o�b�t�@�̍폜
		m_pBuffMat = nullptr;  //���𖳂���
	}

	//�e�N�X�`���̍ő吔����
	for (int nCntMat = 0; nCntMat < MAX_MODEL_TEXTURE; nCntMat++)
	{
		//�e�N�X�`���̏�񂪂��鎞
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release(); //�e�N�X�`���̍폜
			m_pTexture[nCntMat] = nullptr;  //���𖳂���
		}
	}
}

//========================
//�X�V����
//========================
void CModelPrts::Update()
{

}

//========================
//�`�揈��
//========================
void CModelPrts::Draw(D3DXMATRIX MtxWolrd)
{
	//�`�悷�鎞
	if (m_bDraw == true)
	{
		CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

		D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent; //�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;                              //���݂̃}�e���A���̕ۑ��p
		D3DXMATERIAL* pMat;                               //�}�e���A���̃|�C���^�[

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//-----�����𔽉f-----
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		//�}�g���b�N�X�ɑ��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//-----�ʒu�𔽉f-----
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		//�}�g���b�N�X�ɑ��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���g�̃|�C���^�[�̏�񂪂��鎞
		if (m_pParentlPrts != nullptr)
		{
			mtxParent = m_pParentlPrts->GetWorldMtx(); //�}�g���b�N�X�����g�̕��Ɠ���������
		}
		else
		{
			mtxParent = MtxWolrd;                      //�}�g���b�N�X�������̕��Ɠ���������
		}

		//�}�g���b�N�X�ɑ��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//material�|�C���^�[�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		//�}�e���A���̐�����
		for (int nCount = 0; nCount < (int)m_nNumMat; nCount++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCount].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCount]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCount);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//============================================
//�p�[�c�̓ǂݍ��ݏ���
//============================================
void CModelPrts::Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL* pMat)
{
	//CRenderer* pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	//HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);


	CRenderer* pRenderer = CManager::GetRenderer();      //�����_���[�̎擾

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();  //�f�o�C�X�̎擾


	HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh); //X�t�@�C���̓ǂݍ���

	m_pMesh = pMesh;          //���b�V���������Ɠ���������
	m_pBuffMat = pBufferMat;  //�o�b�t�@�������Ɠ���������
	m_nNumMat = dw_NumMat;    //�}�e���A���̐��������Ɠ���������

	//�}�e���A���f�[�^�ւ̃|�C���^������
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nNumTexture = 0; //�e�N�X�`���̐����J�E���g���邽�߂̕ϐ�

	//�}�e���A���̐�����
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`���t�@�C�������݂���
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]); //�e�N�X�`���t�@�C�������
			nNumTexture++;                                                                                //�J�E���g��i�߂�
		}
	}
}

//=========================
//����
//=========================
CModelPrts* CModelPrts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat)
{
	CModelPrts* pModelPrts = new CModelPrts(); //���I�m��

	//��񂪂��鎞
	if (pModelPrts != nullptr)
	{
		pModelPrts->Init();                                             //����������
		pModelPrts->m_pos = pos;                                        //�ʒu�������Ɠ���������
		pModelPrts->m_rot = rot;                                        //�����������Ɠ���������
		pModelPrts->Lood(m_aPrtsPass,pMesh,pBufferMat,dw_NumMat,pMat);  //���t�@�C���̓ǂݍ��ݏ���(�����ŏ���n��)
		pModelPrts->Size();                                             //�T�C�Y�̎擾

		return pModelPrts; //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//==================
//�T�C�Y�̎擾
//==================
void CModelPrts::Size()
{
	int nNumVertex; //���_���̊i�[
	DWORD dSIze;    //���_�̃t�H�[�}�b�g�T�C�Y�擾����ۊǂ���
	BYTE* pVtxByte; //���_�t�H�[�}�b�g�̎擾

	//���_�����擾
	nNumVertex = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_���b�V���̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	//���_������
	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//�ʒu�������邽�߂̕ϐ�
		D3DXVECTOR3 mtx;

		mtx = *(D3DXVECTOR3*)pVtxByte; //���_�t�H�[�}�b�g��D3DXVECTOR3�ɕϊ�


		//=================================
		//X���p
		//=================================

		//�擾�������l����ԑ傫����
		if (mtx.x > m_max.x)
		{
			m_max.x = mtx.x; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.x < m_min.x)
		{
			m_min.x = mtx.x; //���
		}


		//=================================
		//Y���p
		//=================================  

		//�擾�������l����ԑ傫����
		if (mtx.y > m_max.y)
		{
			m_max.y = mtx.y; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.y < m_min.y)
		{
			m_min.y = mtx.y; //���
		}


		//=================================
		//Z���p
		//================================= 
		 
		//�擾�������l����ԑ傫����
		if (mtx.z > m_max.z)
		{
			m_max.z = mtx.z; //���
		}

		//�擾�����l����ԏ�������
		else if (mtx.z < m_min.z)
		{
			m_min.z = mtx.z; //���
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxByte += dSIze;
	}

	//�ŏ��l���O��菬������
	if (m_min.y < 0)
	{
		//�ŏ��l���ő�l���傫����
		if (m_max.y < m_min.y)
		{
			m_max.y = m_min.y * -1.0f; //�ŏ��l�̃v���X�l��������
		}
		m_min.y = 0; //�ŏ��l�̏�����
	}

	//�I�u�W�F�N�g�̃T�C�Y���v�Z����
	m_ModelSize = m_max - m_min;
}


//==================================================
//���𓯊������鏈��
//==================================================
void CModelPrts::BindSize(D3DXVECTOR3& max, D3DXVECTOR3& min, D3DXVECTOR3& ModelSize)
{
	//�����̒l�����݂̒l�Ɠ���������
	max = m_max;              //���f���̍ő�l�𓯊�������
	min = m_min;              //���f���̍ŏ��l�𓯊�������
	ModelSize = m_ModelSize;  //���f���̑傫���𓯊�������
}