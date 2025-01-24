//======================================
//
//��v�����Ǘ�����N���X[manager.h]
//Auther:Chiba Hruki
//
//======================================


#pragma once


//======================================
//�C���N���[�h
#include "main.h"
#include "rendererh.h"
#include "input.h"
#include "block.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "instance.h"
#include "scene.h"
#include "object_set.h"
#include "event.h"


class CManager
{
public:
	CManager();                                                  //�R���X�g���N�^
	~CManager();                                                 //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //����������
	void Uninit();                                               //�I������
	void Update();                                               //�X�V����
	void Draw();                                                 //�`�揈��


	//==================================
	//�����擾
	static CRenderer* GetRenderer() { return m_pRenderer; }      //�����_���[�̏����擾
	static CInputKeyBoard* GetKeyBorad() { return m_pKeyBoard; } //�L�[�{�[�h�̏����擾
	static CInputJoyPad* GetJyoPad() { return m_pJyoPad; }       //�W���C�p�b�g�̏����擾
	static CSound* GetSound() { return m_pSound; }               //�����̏����擾
	static CInstance* GetInstance() { return m_pInstance; }      //�C���X�^���X�����擾����
	static CScene* GetScene() { return m_pScene; }               //�V�[���̏����擾
	static CObjectSet* GetObjectSet() { return m_pObjectSet; }   //�I�u�W�F�N�g�z�u�̏����擾
	static CEvent* GetEvent() { return m_pEvent; }               //�C�x���g�̏����擾
	static CMain* GetMain() { return m_pMain; }                  //���C���̏����擾


   //==================================
   //���̐ݒ�
	static void SetMode(CScene::MODE mode);                      //���[�h�̐ݒ�

private:
	static CRenderer* m_pRenderer;       //�����_���[�̃|�C���^�[
	static CInputKeyBoard* m_pKeyBoard;  //�L�[�{�[�h�̃|�C���^�[
	static CInputJoyPad* m_pJyoPad;      //�W���C�p�b�g�̃|�C���^�[
	static CSound* m_pSound;             //�����̃|�C���^�[
	static CScene* m_pScene;             //���݂̃V�[���̃|�C���^�[
	static CInstance* m_pInstance;       //�e�N���X�̃|�C���^�[
	static CObjectSet* m_pObjectSet;     //�I�u�W�F�N�g�z�u�̃|�C���^�[
	static CEvent* m_pEvent;             //�X�e�[�W���̃C�x���g�|�C���^�[
	static CMain* m_pMain;               //���C���̃|�C���^�[
};
