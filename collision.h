//===========================================
//
//�����蔻��N���X�Ǘ�[collision.h]
//Auther:Chiba Haruki
//
//===========================================

#ifndef COLLISION_H_
#define COLLISION_H_

//===========================================
//�C���N���[�h
#include "main.h"
#include "input.h"


//================================================================
//�����蔻��N���X
class CCollision
{
public://�O������̃A�N�Z�X�\
	CCollision();
	~CCollision();
	bool ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);             //���ꂼ��̓����蔻��(�v���C���[�p)
	bool ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);            //���E�̓����蔻��(�v���C���[�p)
	bool ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move); //���̃u���b�N�̎��̓����蔻��

	bool AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                          //�S���ʂ̓����蔻��
	bool ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);       //��̓����蔻��
	bool ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);      //���̓����蔻��
	bool ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                           //�^�񒆂���E���̔���
	bool ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                            //�^�񒆂��獶�̔���

	bool CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                        //�~�̓����蔻��

	//3D�|���S���ƃ��f���̓����蔻��
	bool ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1);      //���ꂼ��̓����蔻��(�v���C���[�p)
	bool ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1); //���ꂼ��̓����蔻��(�v���C���[�p)
	bool ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1);  //���ꂼ��̓����蔻��(�v���C���[�p)

	//fSizeX�ł����̑��ʒl��n�����a�𑝉�������
	bool Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float fSizeX, int nNumber); //�r�[���n�̓����蔻��Ŏg����
	bool Coliision3Dcircle(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float fSizeX);     //�r�[���n�̓����蔻��Ŏg����[
	bool TenCricale(D3DXVECTOR3& pos1, float SX, float BY, float BX, float SY); //�Ђ��`�̓����蔻��i�r��small,�a��big�̗��j
};

#endif // !COLLISION_H_

