//=============================================================
//
//���o�p�RD�I�u�W�F�N�g�̃N���X�Ǘ�[direction_obj.h]
//Auther:HARUKI CHIBA
//
//=============================================================

#pragma once

//==============================================================
//�C���N���[�h
#include "objectX.h"


//=============================================================================
//�j�ЃN���X
class CDebrisX : public CObjectX
{
public:
	CDebrisX(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CDebrisX()override;                          //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Uninit()override;                        //�j������
	void Update() override;                       //�X�V����
	void Draw()override;                          //�`�揈��

	static CDebrisX* Create(D3DXVECTOR3 pos);     //��������

private:
	constexpr static int MAX_LIFE = 30;
};
