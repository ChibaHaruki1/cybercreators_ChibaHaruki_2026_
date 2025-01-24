//===================================================
//
//�n�ʂ̃v���g�^�C�v�錾������t�@�C��[field.h]
//Author:chiba haruki
//
//===================================================

#pragma once

//===================================================
//�C���N���[�h
#include "object3D.h"

class CField : public CObject3D
{
public:
	CField(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CField()override;						   //�f�X�g���N�^
	HRESULT Init()override;					   //����������
	void Uninit()override;					   //�j������
	void Update()override;					   //�X�V����
	void Draw()override;					   //�`�揈��
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ); //�e�L�X�g�t�@�C���ɏ����������ޏ���

	static CField* Create(D3DXVECTOR3 pos);    //��������

private:
	//�}�N����`
	constexpr static float SIZEX = 200.0f;     //�����̑傫��

	static int m_nCountField;                  //�������ꂽ�n�ʂ̐����i�[����p�̕ϐ�
};
