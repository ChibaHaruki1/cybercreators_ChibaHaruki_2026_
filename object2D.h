//===============================================
//
//�Q�c�I�u�W�F�N�g�̃N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//===============================================

#pragma once

//===============================================
//�C���N���[�h
#include "object.h"
#include "input.h"


class CObject2D : public CObject
{
public:
	CObject2D(int nPriority=DEFAULT_PRIORITY);       //�R���X�g���N�^
	~CObject2D() override;                           //�f�X�g���N�^
	HRESULT Init() override;                         //����������
	HRESULT SelectInit(int nPieces,float nTexture);  //���A�e�N�X�`���̃T�C�Y�̑I��������������
	void Uninit() override;                          //�j������
	void Update() override;                          //�X�V����
	void Draw() override;                            //�`�揈��
	void MultipleDraw(int nPieces) ;                 //�����`�悷�鏈��
	void SetSIze(float SIZE_X,float SIZE1_X, float SIZE_Y, float SIZE1_Y); //polygon�̃T�C�Y�𒲐����鏈��
	void SetCol(int Red,int Green,int Blue,int Alph);                      //�F��ݒ�
	HRESULT Lood();	                                                       //�e�N�X�`���t�@�C���̓ǂݍ���

	//==================================================
	//���ꂼ��̏����ɕK�v�ȏ����擾����
	LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; } //�o�b�t�@�̎擾
	D3DXVECTOR3& GetCol() {return m_col;}                       //�F�̎擾
	int& GetAlph() { return m_nAlpha; }                          //�A���t�@�l���擾
	int& GetRandom() { return m_nRandom; }                      //�������擾
	int& GetFrame() { return m_nFrame; }                        //�t���[�����擾

	//==================================================
	//�e���̐ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }               //�ʒu�̐ݒ�	
	void SetAlph(int nAlph) { m_nAlpha = nAlph; }                //�A���t�@�l��ݒ�
	void SetRandom(int nRandom) { m_nRandom = nRandom; }        //������ݒ�
	void SetFrame(int nFrame) { m_nFrame = nFrame; }            //�t���[����ݒ�
	void SetFileNamePass(const char* aFileName) { m_aFileName = aFileName; } //�t�@�C���p�X��ݒ�

	//==================================================
	///�O���{���̎擾
	D3DXVECTOR3& GetPos() { return m_pos; }                     //�ʒu�̎擾
	D3DXVECTOR3& GetMove() { return m_move; }                   //�ړ��ʂ̎擾
	D3DXVECTOR3& GetRot() { return m_rot; }                     //�����̎擾


	//==================================================
	//���̒l���v���Đݒ�
	int& SetAddjustAlpha() { return m_nAlpha; }                 //�A���t�@�l�̕ύX�������Ƃ��̐ݒ�

private:
	LPDIRECT3DTEXTURE9 m_pTexture;      //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_move; //�ړ���
	D3DXVECTOR3 m_rot;  //����
	D3DXVECTOR3 m_col;  //�F

	int m_nAlpha;        //�A���t�@�l��ۊǂ���p�̕ϐ�
	int m_nRandom;      //������ۊǂ���p�̕ϐ�
	int m_nFrame;       //�t���[�����ϑ�����p�̕ϐ�

	const char* m_aFileName; //�t�@�C���p�X��ۊǂ���p�̕ϐ�
};
 