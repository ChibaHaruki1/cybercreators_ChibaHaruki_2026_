//========================================
//
//��̔w�i�p�N���X�Ǘ�[skydoom.h]
//Auther:HARUKI CHIBA
//
//========================================

#pragma once

//========================================
//�C���N���[�h
#include "main.h"
#include "objectX.h"


class CSkyDoom : public CObjectX
{
private:
	CSkyDoom(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CSkyDoom()override;						  //�f�X�g���N�^
	HRESULT Init()override;						  //����������
	void Uninit()override;						  //�j������
	void Update() override;						  //�X�V����
	void Draw()override;						  //�`�揈��

public:
	static CSkyDoom* Create(D3DXVECTOR3 pos, int nNumber); //��������
};