//=================================
//
//DirectX���C������[main.h]
//Auther:Chiba Haruki
//
//=================================

#pragma once

//=================================
//�C���N���[�h
#include <Windows.h>
#define DIRECTINPUT_VERSION   (0x0800) //�r���h���̌x���Ώ��p�}�N��(���Ԃɒ���)

#include "d3dx9.h"   //DirectX9���g�p
#include "dinput.h"  //���͏����ɕK�v
#include "Xinput.h"  //�W���C�p�b�h�����ɕK�v
#include "xaudio2.h" //����ǉ�


//=================================
//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")    //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")   //�u���R���X�D���k�h�a�v�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")  //�c�h�q�d�b�s�w�R���|�[�l���g�i���i�j�ɕK�v
#pragma comment(lib,"winmm.lib")   //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v
#pragma comment(lib, "xinput.lib") //�W���C�p�b�h�����ɕK�v


//=================================
//�}�N����`
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)              //2D�pVERTWX�̏���ݒ�
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)   //3D�pVERTWX�̏���ݒ�

//���_���̍\����
typedef struct
{
	D3DXVECTOR3 pos; //���_���
	float rhw;       //���W�ϊ��p�W���i�P�D�O���ŌŒ�j
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos; //���_���
	D3DXVECTOR3 nor; //�@�����
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;


class CMain
{
public:
	CMain();                         //�R���X�g���N�^
	~CMain();                        //�f�X�g���N�^
	void Uninit();                   //�j������
	int& GetFPS() {return m_nFPS; }  //FPS�̒l���擾����

	//�}�N����`
	constexpr static int SCREEN_WIDTH = 1280; //�E�B���h�E�̕�
	constexpr static int SCREEN_HEIGHT = 720; //�E�B���h�E�̍���


private:
	int m_nFPS; //FPS�̒l��ۊǂ���p�̕ϐ�
};