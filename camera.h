//========================================
//
//�J�����N���X�Ǘ�[camera.h]
//Auther:Haruki Chiba
//
//========================================

#ifndef _CAMERA_H_
#define _CAMERA_H_


//========================================
//�C���N���[�h
#include "main.h"
#include "input.h"


//==============================================================
//�J�����̃N���X
class CCamera
{
public:
	CCamera();                                                //�R���X�g���N�^
	~CCamera();                                               //�f�X�g���N�^
	HRESULT Init();                                           //����������
	void Uninit();                                            //�j������
	void Update();                                            //�X�V����
	void SetCamera();                                         //�J�����̏��̐ݒ�	


	//======================================
	//���̎擾
	D3DXVECTOR3& GetRot() { return m_rot; }                     //�������擾
	int& GetAdjustmentPosZ() { return m_fAdjustmentPosZ; }    //Z���̈ʒu�𒲐��l���擾
	float& GetAdjustmentPosY() { return m_fAdjustmentPosY; }  //Y���̈ʒu�𒲐��l���擾


	//======================================
	//���̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	//�}�N����`
	static constexpr float MAX_ROTSPEED = 0.01f;   //�J�����̉�]�̑����𒲐�����
	static constexpr float MAX_CAMERASPEED = 1.0f; //�J�����̈ړ��̑����𒲐�

	D3DXVECTOR3 m_rot;                  //����
	D3DXVECTOR3 m_fSavePosV;          //Y���̈ʒu��ۊǂ���p�̕ϐ�
	D3DXVECTOR3 m_posV;               //���_
	D3DXVECTOR3 m_posR;               //�����_
	D3DXVECTOR3 m_vecU;               //�����
	D3DXMATRIX m_mtxProjection;       //�v���W�F�N�V����
	D3DXMATRIX m_mtxView;             //�r���[�s��
	int m_fAdjustmentPosZ;            //Z���p�̈ʒu�𒲐�����p�̕ϐ�
	float m_fAdjustmentPosY;          //Y���p�̈ʒu�𒲐�����p�̕ϐ�
};

#endif // !_CAMERA_H_

