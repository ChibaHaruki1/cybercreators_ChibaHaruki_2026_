//==========================================
//
//�����_���[�N���X�Ǘ�[renderer.h]
//Auther:Chiba Haruki
//
//==========================================

#pragma once

//==========================================
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "objectmanagerX.h"
#include "objectX.h"

class CRenderer
{
public:
	CRenderer();                                                 //�R���X�g���N�^
	~CRenderer();                                                //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //����������
	void Uninit();                                               //�j������
	void Update();                                               //�X�V����
	void Draw();                                                 //�`�揈��
	void DrawFPS();                                              //FPS��`�悷�鏈��
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }       //�RD�f�o�C�X���擾
	bool& GetPause() { return m_bPause; }                        //�|�[�Y�����ǂ����̔�����擾
	bool& GetDrawShader() { return m_bDrawShader; }              //�V�F�[�_�[���g�����ǂ����̔�����擾

private:
	LPDIRECT3D9 m_pD3D;             //Direct3D�̎�v���
	LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3D�f�o�C�X
	LPD3DXFONT m_pFont;             //�t�H���g�̏��
	bool m_bPause;                  //�|�[�Y�����ǂ����̔��������p�̕ϐ�
	bool m_bDrawShader;             //�V�F�[�_�[��`�悷�邩�ǂ���
};

