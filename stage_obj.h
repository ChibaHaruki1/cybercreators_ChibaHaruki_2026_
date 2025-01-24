//============================================================
//
//�X�e�[�W�ɒu���I�u�W�F�N�g�̃N���X�Ǘ�[statge_obj.h]
//Auther:Chiba Haruki
//
//============================================================

#pragma once

//===========================
//�C���N���[�h
#include "objectX.h"

//====================================================
//�X�e�[�W�ɒu���I�u�W�F�N�g�̊��N���X�Ǘ�
class CStageObj : public  CObjectX
{
public:
	CStageObj(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CStageObj()override;                         //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Uninit()override;                        //�j������
	void Update() override;                       //�X�V����
	void Draw()override;                          //�`�揈��
	void TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ); //�e�L�X�g�t�@�C���ɏ�����������
	static CStageObj* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);                       //�p���N���X���^�C�v���Ƃɐ���

private:
	static int m_nTelephonPoleCount;  //�d���̍��ꂽ�����J�E���g����ׂ̕ϐ�
};


//====================================================
//�d���̃N���X�Ǘ�
class CTelephonPole : public CStageObj
{
public:
	CTelephonPole(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CTelephonPole()override;                         //�f�X�g���N�^
};


//====================================================
//�Ď��J�����̏�̕���
class CSurveillanceCameraUP : public CStageObj
{
public:
	CSurveillanceCameraUP(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CSurveillanceCameraUP()override;                         //�f�X�g���N�^
	HRESULT Init()override;                                   //����������
	void Uninit()override;                                    //�j������
	void Update() override;                                   //�X�V����
	void Draw()override;                                      //�`�揈��
};


//====================================================
//�Ď��J�����̉��̕���
class CSurveillanceCameraDown : public CStageObj
{
public:
	CSurveillanceCameraDown(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CSurveillanceCameraDown()override;                         //�f�X�g���N�^
};


//====================================================
//�Ď��J�����̉��̕���
class CShop : public CStageObj
{
public:
	CShop(int nPriority = DEFAULT_PRIORITY1);                   //�R���X�g���N�^
	~CShop()override;                                           //�f�X�g���N�^
};

//====================================================
//��ꂽ��
class CBreakHouse : public CStageObj
{
public:
	CBreakHouse(int nPriority = DEFAULT_PRIORITY1);             //�R���X�g���N�^
	~CBreakHouse()override;                                     //�f�X�g���N�^
	void Update()override;                                      //�X�V����
};
