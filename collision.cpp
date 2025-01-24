//===========================================
//
//�����蔻�菈��[collision.cpp]
//Auther:Haruki Chiba
//
//===========================================


//===========================================
//�C���N���[�h
#include "collision.h"
#include "manager.h"
#include "player.x.h"


//============================
//�R���X�g���N�^
//============================
CCollision::CCollision()
{

}


//===========================
//�f�X�g���N�^
//===========================
CCollision::~CCollision()
{

}


//======================
//�e�����̔���
//======================
bool CCollision::ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		move.x = move.x + CPlayerX::MAX_MOVESPEED; //�E���ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	//���̓����蔻��
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		move.x = move.x - CPlayerX::MAX_MOVESPEED; //�����ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	//��O����̔���
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z + Size.z / 2 <= pos1.z - (Size1.z / 2) + 10.0f)
	{
		move.z = move.z - CPlayerX::MAX_MOVESPEED; //��O�ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	//��납��̔���
	else  if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2) + 10.0f
		&& pos.z - Size.z / 2 >= pos1.z + (Size1.z / 2))
	{
		move.z = move.z + CPlayerX::MAX_MOVESPEED; //���ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//==============================
//���E�݂̂̔���(�����o������)
//==============================
bool CCollision::ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		return true; //�������Ă��锻���Ԃ�
	}

	//���̓����蔻��
	else if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//==============================
//���E�݂̂̔���(�����o���L��)
//==============================
bool CCollision::ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//���̓����蔻��
	if (pos.x + (Size.x / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (Size.x / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		move.x = move.x - CPlayerX::MAX_MOVESPEED; //�����ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	//�E�̓����蔻��
	if (pos.x - (Size.x / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2)
		&& pos.z + Size.z / 2 >= pos1.z - (Size1.z / 2)
		&& pos.z - Size.z / 2 <= pos1.z + (Size1.z / 2))
	{
		move.x = move.x + CPlayerX::MAX_MOVESPEED; //�E���ɉ���
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//======================
//�S���ʂ̔���
//======================
bool CCollision::AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 10.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 10.0f
		&& pos.y + (Size.y / 2) >= pos1.y - (Size1.y / 2) - 10.0f
		&& pos.y - (Size.y / 2) <= pos1.y + (Size1.y / 2) + 10.0f
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) - 10.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) + 10.0f)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false; //�������Ă��Ȃ������Ԃ�
}

//==========================================================================================================
//�^�񒆂���E���̔���
//==========================================================================================================
bool CCollision::ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//�^�񒆂���E�����̓����蔻��i���������j
	if (pos.x <=pos1.x + (Size1.x / 2) 
		&& pos.x + (Size.x / 2)>=pos1.x + (Size1.x / 2))
		
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}

//==========================================================================================================
//�^�񒆂��獶�����̔���
//==========================================================================================================
bool CCollision::ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//�^�񒆂��獶�����̓����蔻��i���������j
	if (pos.x >= pos1.x + (Size1.x / 2)
		&& pos.x - (Size.x / 2) <= pos1.x + (Size1.x / 2))

	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//==================
//�㑤�̔���
//==================
bool CCollision::ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�㑤�̔���
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 1.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 1.0f
		&& pos.y >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)
	{
		return true;  //�������Ă��锻���Ԃ�
	}
	return false;     //�������Ă��Ȃ������Ԃ�
}


//==================
//�����̔���
//==================
bool CCollision::ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�����̔���
	if (pos.x + (Size.x / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x - (Size.x / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y <= pos1.y
		&& pos.y >= pos1.y - (Size1.y*0.1f)
		&& pos.z + (Size.z / 2) >= pos1.z - (Size1.z / 2) + 5.0f
		&& pos.z - (Size.z / 2) <= pos1.z + (Size1.z / 2) - 5.0f)
	{
		move.y -= CPlayerX::MAX_MOVESPEED * 2.0f; //�����ɖ߂�
		return true; //�������Ă��锻���Ԃ�
	}
	return false;    //�������Ă��Ȃ������Ԃ�
}


//====================
//�~�̓����蔻��
//====================
bool CCollision::CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSum = (Size.x * 0.5f + Size.y * 0.5f + Size.z * 0.5f)*0.5f;      //�P�ڂ̔��a
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f)*0.5f;  //�Q�ڂ̔��a

	//�������Ώۂ̔��a��菬�����i�G��Ă���j��
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//==============================================================================================================================
//�R���|���S���ƃ��f���̔���
//==============================================================================================================================

//======================
//�S�����̔���
//======================
bool CCollision::ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X / 2) <= pos1.x + (Size1.x / 2) + 5.0f
		&& pos.x + (X / 2) >= pos1.x - (Size1.x / 2) - 5.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 5.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 5.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 5.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 5.0f)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//======================
//�E�����̔���
//======================
bool CCollision::ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	//�E���̓����蔻��𑝂₷
	if (pos.x + (X / 2) >= pos1.x - (Size1.x / 2)
		&& pos.x + (X / 2) <= pos1.x - (Size1.x / 2) + 10.0f
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��锻���Ԃ�
}


//======================
//�������̔���
//======================
bool CCollision::ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	//�E���̓����蔻��𑝂₷
	if (pos.x - (X / 2) >= pos1.x + (Size1.x / 2) - 10.0f
		&& pos.x - (X / 2) <= pos1.x + (Size1.x / 2)
		&& pos.y + (Y / 2) >= pos1.y - (Size1.y / 2) - 1.0f
		&& pos.y - (Y / 2) <= pos1.y + (Size1.y / 2) + 1.0f
		&& pos.z + (Z / 2) >= pos1.z - (Size1.z / 2) - 1.0f
		&& pos.z - (Z / 2) <= pos1.z + (Size1.z / 2) + 1.0f)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//=========================
//�{�X�̉~�̓����蔻��
//=========================
bool CCollision::Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSum = (X * 0.5f + m_fSizeX + Y * 0.5f + Z * 0.5f) * 0.5f;          //�P�ڂ̔��a
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;  //�Q�ڂ̔��a

	//�������Ώۂ̔��a��菬�����i�G��Ă���j��
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//====================
//�~�̓����蔻��
//====================
bool CCollision::Coliision3Dcircle(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	float lengthX = pos.x - pos1.x; //pos��pos1�̂��̋�������ɔ�r
	float lengthY = pos.y - pos1.y; //pos��pos1�̂��̋�������ɔ�r
	float lengthZ = pos.z - pos1.z; //pos��pos1�̂��̋�������ɔ�r

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//pos��pos1�̋������v�Z

	float radiuSum = (X * 0.5f + m_fSizeX + Y * 0.5f + Z * 0.5f) * 0.5f;          //�P�ڂ̔��a
	float radiuSum1 = (Size1.x * 0.5f + Size1.y * 0.5f + Size1.z * 0.5f) * 0.5f;  //�Q�ڂ̔��a

	//�������Ώۂ̔��a��菬�����i�G��Ă���j��
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}


//=========================
//�~�̓����蔻��(����)
//=========================
bool CCollision::TenCricale(D3DXVECTOR3& pos1, float SX, float BY, float BX, float SY) //�Q�Ɠn�������ς���l�̂ݎQ�Ƃ��Ȃ���staic�Ɠ����ɂȂ�
{
	//�Ђ��`�i���j��̓����蔻��̏�����
	if (SX <= pos1.x && BY >= pos1.y && BX >= pos1.x && SY <= pos1.y)
	{
		return true; //�������Ă��锻���Ԃ�
	}

	return false;    //�������Ă��Ȃ������Ԃ�
}
