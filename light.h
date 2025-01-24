//=======================================
//
//�����N���X�Ǘ�[light.h]
//Auther:Haruki Chiba
//
//=======================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

class CLight
{
public:
	CLight();         //�R���X�g���N�^
	~CLight();        //�f�X�g���N�^
	HRESULT Init();   //����������
	void Uninit();    //�j������
	void Update();    //�X�V����

private:
	static const int MAX_LIGHT = 4; //�����̍ő吔
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //�����̏��
};

#endif // !_LIGHT_H_

