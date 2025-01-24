//==========================================
//
//UI�̃N���X�Ǘ��錾������t�@�C��[ui.h]
//Author:chiba haruki
//
//==========================================

#pragma once

//==========================================
//�C���N���[�h
#include "object3D.h"
#include <cstdio>


//======================================================
//UI�̃}�l�[�W���[�Ǘ��N���X
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CUI()override;							//�f�X�g���N�^
	HRESULT Init()override;					//����������
	void Uninit()override;					//�j������
	void Update()override;					//�X�V����
	void Draw()override;					//�`�揈��

	static CUI* Create(CObject3D::TYPE_UI typeui); //��������
};


//======================================================
//���݂̔z�u�����I�u�W�F�N�g�̏ꏊ��UI���o���N���X�Ǘ�
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CCreateInObject()override;                         //�f�X�g���N�^
};


//======================================================
//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�������N���X�Ǘ�
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CTalkText()override;                         //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Draw()override;                          //�`�揈��

private:
	//�}�N����`
	constexpr static float SIZEX = 40.0f; //X���̑傫��
	constexpr static float SIZEY = 40.0f; //Y���̑傫��
	constexpr static float SIZEZ = 40.0f; //Z���̑傫��
};


//======================================================
//�Ď��J��������ł郌�[�U�[�N���X
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CLaserCamare()override;                         //�f�X�g���N�^
	HRESULT Init()override;                          //����������
	void Update()override;                           //�X�V����
	void Draw()override;                             //�`�揈��

private:
	//�}�N����`
	constexpr static float SIZEX = 80.0f;                //X���̑傫��
	constexpr static float SIZEY = 20.0f;                //Y���̑傫��
	constexpr static float SIZEZ = 20.0f;                //Z���̑傫��
	constexpr static float ADDJUST_POSY = 20.0f;         //Y���̈ʒu�̒����l
	constexpr static float ADDJUST_POSZ = 35.0f;         //Z���̈ʒu�̒����l
	constexpr static float ADDJUST_ROTY = 0.54f;         //Y���̌����̒����l
	constexpr static float ADDJUST_ROTZ = 1.54f;         //Z���̌����̒����l
	constexpr static float ADDJUST_CREATE_POSZ = 100.0f; //Z���̐����ʒu�̒����l
};
