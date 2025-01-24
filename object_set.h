//======================================================
//
//�O���t�@�C������z�u����N���X�Ǘ�[object_set.h]
//Auther:Haruki Chiba
//
//======================================================


#pragma once


//======================================================
//�C���N���[�h
#include "main.h"
#include "stage_obj.h"


class CObjectSet
{
public:
	CObjectSet();   //�R���X�g���N�^
	~CObjectSet();  //�f�X�g���N�^
	HRESULT Init(); //����������

	//�X�e�[�W���̓ǂݍ��ފ֐����܂Ƃ߂�֐�
	void StageOneInformation(const char*pFileName);       //�X�e�[�W�P�Ԗڂ̃I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���
	void ResultScoreInformation(const char* pFileName);	  //���U���g�̃I�u�W�F�N�g�̈ʒu�Ȃǂ�ǂݍ���
	
	//�t�@�C���ɏ������ފ֐�
	void ResultScoreWrite(const char* pFileName);         //���U���g�X�R�A�̏���ǂݍ���

	//���ꂼ��̃I�u�W�F�N�g�̓ǂݍ��ݏ����{��������֐��itxt�t�@�C���̒��g�̏���ǂݍ��ށj
	void LoodTelephonPole(FILE*pFile);         //�d���̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBlock(FILE* pFile);               //�u���b�N�̏��Ɋւ���f�[�^��ǂݍ��ފ֐�
	void LoodBreakHouse(FILE* pFile);          //��ꂽ�Ƃ̓ǂݍ��ݏ���
	void LoodResultScore(FILE* pFile);         //���U���g�̏��ǂݍ��ݐ���
	void LoodEnemy(FILE* pFile);               //�G�̓ǂݍ��ݏ���
	void LoodMotionInEnemy(FILE* pFile);       //���[�V�����t���̓G�̓ǂݍ��ݏ���

	static CObjectSet* Create();               //���̐���

	//�擾�p�̊֐�
	const char* GetStratBlockName(CObjectX::TYPE type); //�u���b�N�̓ǂݍ��ޖ��O�̃p�X�̎擾����
	const char* GetEndBlockName(CObjectX::TYPE type);   //�u���b�N�̏I�����閼�O�̃p�X�̎擾����

	int& GetClearScore() { return m_nClearScore; }      //���݂̃X�R�A��ۊǂ���p�̕ϐ����擾

private:

	//�}�N����`
	constexpr static int MAX_DATAMOJI = 200; //������̔z��̍ő吔

	//�e�L�X�g�t�@�C������ǂݍ��ގ��Ɏg�������o�ϐ�
	char m_aData[MAX_DATAMOJI];  //�������ǂݎ��@
	static int m_nClearScore;    //���݂̃X�R�A��ۊǂ���p�̕ϐ�

	//�e�L�X�g�t�@�C���̓ǂݏ����Ɏg�������o�ϐ�
	const char* m_aFieldBlockStratName;         //�n�ʗp�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aGoUpBlockStratName;	        //�オ��p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aRoadBlockStratName;	        //���p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlockStratName;	    //�ǌ����p�̃u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aWallRoadBlock001StratName;   //�ǌ����p�̃u���b�N001�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlockStratName;	        //�������u���b�N�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aSmallBlock001StratName;	    //�������u���b�N001�̓ǂݍ��ݗp�̖��O�ϐ�
	const char* m_aUpWallBlockStratName;	    //��ǃu���b�N�̓ǂݍ��ݗp�̖��O�ϐ�

	const char* m_aFieldBlockEndName;           //�n�ʗp�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aGoUpBlockEndName;     		//�オ��p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aRoadBlockEndName;     		//���p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlockEndName;     	//�ǌ����p�̃u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aWallRoadBlock001EndName;     //�ǌ����p�̃u���b�N001�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlockEndName;    		//�������u���b�N�̏I���p�̖��O�ϐ�
	const char* m_aSmallBlock001EndName;    	//�������u���b�N001�̏I���p�̖��O�ϐ�
	const char* m_aUpWallBlockEndName;     		//��ǃu���b�N�̏I���p�̖��O�ϐ�
};
