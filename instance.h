//=======================================================================
//
//�I�u�W�F�N�g�̃C���X�^���X���܂Ƃ߂�N���X�Ǘ�[instance.h]
//Auther:HARUKI CHIBA
//
//=======================================================================

#ifndef _INSTANCE_H_  //���̃}�O����`������Ă��Ȃ���������
#define _INSTANCE_H_  //��d�C���N���[�h�h�~�̃}�N����`

//=======================================================================
//�C���N���[�h
#include "main.h" 
#include "field.h"
#include "block.h"
#include "bullet.h"
#include "2d_ui.h"
#include "stage_obj.h"
#include "particles.h"
#include "efect.h"
#include "direction_obj.h"
#include "bg.h"
#include "enemy.h"
#include "enemyinmotion.h"
#include <vector>
#include "boss.h"
#include "bosseffect.h"
#include "gage.h"
#include "score.h"

class CInstance
{
public:
	CInstance();
	~CInstance();
	HRESULT Init();
	void Uninit();

	void DesignationUninitX(CObjectX::TYPE type,int nNumber);           //�RD���f����nullptr�ɂ���������nullptr�ɂ��鏈��
	void DesignationUninitXEnemy(CObjectX::TYPE type, int nNumber);     //�G��nullptr�ɂ���������nullptr�ɂ��鏈��
	void DesignationUninit2D(CObject2D::TYPE type);                     //2D��nullptr�ɂ���������nullptr�ɂ��鏈��
	void DesignationUninit3D(CObject3D::TYPE type);                     //3D��nullptr�ɂ���������nullptr�ɂ��鏈��

	CObject2D* GetCreateObjectInstnace2D(CObject2D::TYPE type, int nNumber);               //�QD�I�u�W�F�N�g����
	CObject3D* GetCreateObjectInstnace(CObject3D::TYPE type,int nNumber,D3DXVECTOR3 pos);  //�RD�I�u�W�F�N�g����
	CObjectX*GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos);  //�RD���f���̃I�u�W�F�N�g����
	CObjectX* CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos);                   //�u���b�N�̐���
	CObjectX* CreateRubble(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos);                  //���ꂫ�̐���

	//�u���b�N�̃C���X�^���X���擾
	CManagerBlock* GetFiledBlock(int nNumber) { return m_pFieldBlock[nNumber]; }                  //�n�ʗp�u���b�N�̎擾
	CManagerBlock* GetGoUpBlock(int nNumber) { return m_pGoUpBlock[nNumber]; }                    //�オ�邽�߂̃u���b�N�̎擾
	CManagerBlock* GetRoadBlock(int nNumber) { return m_pRoadBlock[nNumber]; }                    //���p�u���b�N�̎擾
	CManagerBlock* GetWallRoadBlock(int nNumber) { return m_pWallRoadBlock[nNumber]; }            //�ǌ����p�u���b�N�̎擾
	CManagerBlock* GetWallRoadBlock001(int nNumber) { return m_pWallRoadBlock001[nNumber]; }      //�ǌ����p�u���b�N001�̎擾
	CManagerBlock* GetSmallBlock (int nNumber) { return m_pSmallBlock[nNumber]; }                 //�������u���b�N�̎擾
	CManagerBlock* GetSmallBlock001 (int nNumber) { return m_pSmallBlock001[nNumber]; }           //�������u���b�N001�̎擾
	CManagerBlock* GetUpBlock (int nNumber) { return m_pUpWallBlock[nNumber]; }                   //��ǃu���b�N�̎擾
	CManagerBlock* GetWoodenBoard (int nNumber) { return m_pWoodenBoard[nNumber]; }               //�؂̔Q�̎擾
	CManagerBlock* GetFinalBlock () { return m_pFinalBlosk; }                                     //�{�X�펞�̒n�ʂ̎擾
	CManagerBlock* GetFinalCeiling() { return m_pFinalCeiling; }                                  //�{�X�펞�̓V��̎擾
	CManagerBlock* GetSpeceBattleShip(int nNumber) { return m_pSpeceBattleShip000[nNumber]; }     //���̃X�e�[�W�֍s���p�̃I�u�W�F�N�g�̎擾
																							      
	CDebrisX* GetDebrisX(int nNumber) { return m_pDebrisX[nNumber]; }                             //���I�̎擾

	//�X�e�[�W�ɔz�u����p�̃I�u�W�F�N�g�̃C���X�^���X���擾
	CStageObj* GetTelephonPole(int nNumber) { return m_pTelephonPole[nNumber]; }                  //�d���̎擾
	CStageObj* GetSurveillanceCameraUp(int nNUmber) { return m_pSurveillanceCameraUp[nNUmber]; }  //�J�����̏㕔���̎擾
	CStageObj* GetShop() { return m_pShop; }                                                      //�X�̎擾

	//�p�[�e�B�N���̎擾
	CParticles001* GetPraticles001(int nNumber) { return m_pPraticles001[nNumber]; }              //�~��̃p�[�e�B�N���̎擾

	//�G�t�F�N�g�̎擾
	CEffect* GetEffect() { return m_pEffect; }                                                    //�v���C���[�̒e�ɍs���G�t�F�N�g�̎擾
	CManagerEffect* GetExplosion() { return m_pExplosion; }                                       //�����G�t�F�N�g�̎擾
	CManagerEffect* GetExplosion001() { return m_pExplosion001; }                                 //�����G�t�F�N�g001�̎擾
	CManagerEffect* GetThander() { return m_pThander; }                                           //���G�t�F�N�g�̎擾
	CManagerEffect* GetFire() { return m_pFire; }                                                 //���G�t�F�N�g�̎擾
	CManagerEffect* GetDebris() { return m_pDebris; }                                             //�ꖇ�G�̔j�ЃG�t�F�N�g�̎擾
	CManagerEffect* GetPillarOfFire() { return m_pPillarOfFire; }                                 //����̉��̃G�t�F�N�g�̎擾
	CSpecialAttack* GetSpecialAttack() { return m_pSepecialAttack; }                              //�K�E�Z�̃G�t�F�N�g�̎擾
	CManagerBossEffect* GetBossSpecialAttack() { return m_pBossSpecialAttack; }                   //�{�X�̕K�E�Z�̃G�t�F�N�g�̎擾
	CManagerBossEffect* GetImpact() { return m_pImpact; }                                         //�Ռ��g�G�t�F�N�g�̎擾

	//�G�n�̎擾
	CManagerEnemy* GetEnemy000() { return m_pEnemy000; }                                              //�ʏ�G�̎擾
	CManagerEnemy* GetEnemy001(int nNumber) { return m_pEnemy001[nNumber]; }                          //�ʏ�G001�̎擾
	CManagerEnemy* GetEnemy002(int nNumber) { return m_pEnemy002[nNumber]; }                          //�ʏ�G001�̎擾
	CManagerEnemyInMotion* GetEnemyInMotion(int nNumber) { return m_pEnemyInMotion000[nNumber]; }     //���[�V�����t���̓G�̎擾
	CManagerEnemyInMotion* GetEnemyInMotion001(int nNumber) { return m_pEnemyInMotion001[nNumber]; }  //���[�V�����t���̓G001�̎擾
	CBoss* GetBoss() { return m_pBoss; }                                                              //�{�X�̎擾

	//2D�̃C���X�^���X
	CShopScreen* GetShopScreen() { return m_pShopScreen; }            //SHOP���̔w�i�̏����擾
	CManagerGage* GetPlayerHPGage() { return m_pPlayerHPGage; }       //�v���C���[��HP�Q�[�W�̎擾
	CBossHPGage* GetBossHPGage() { return m_pBossHPGage; }            //�{�X��HP�Q�[�W�̎擾
	CManagerScore* GetGameScore() { return m_pGameScore; }            //�Q�[�����̃X�R�A�̎擾

	//�RD�̎擾
	CFuelGage* GetFuelGage() {return m_pFuelGage; }                   //�R���Q�[�W�̎擾
																	  
	//����������擾����p�̊֐�									     
	int& GetFieldBlockCount() {return  m_nNumFiledBlock; }            //���p�̃u���b�N�̍������
	int& GetGoUpBlockCount() {return  m_nNumGoUpBlock; }              //�オ��p�̃u���b�N�̍������
	int& GetRoadBlockCount() {return  m_nRoadBlock; }                 //���p�u���b�N�̍������
	int& GetWallRoadBlockCount() {return  m_nWallRoadBlock; }         //�ǌ����p�u���b�N�̍������
	int& GetWallRoadBlock001Count() {return  m_nWallRoadBlock001; }   //�ǌ����p�u���b�N001�̍������
	int& GetSmallBlockCount() {return  m_nSmallBlock; }               //�������u���b�N�̍������
	int& GetSmallBlock001Count() {return  m_nSmallBlock001; }         //�������u���b�N�̍������
	int& GetUpWallBlockCount() {return  m_nUpWallBlock; }             //�オ��p�̃u���b�N�̍������
	int& GetWoodenBoardCount() { return m_nWoodenBoard; }             //�؂̔Q�̍������
	int& GetEnemy001Count() { return m_nEnemy001; }                   //�G�̍������
	int& GetEnemy002Count() { return m_nEnemy001; }                   //�G�̍������
	int& GetMotionInEnemyCount() { return m_nEnemyInMotion; }         //���[�V�����t���̓G�̐�����
	int& GetMotionInEnemy001Count() { return m_nEnemyInMotion001; }   //���[�V�����t���̓G001�̐�����

	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_ENEMYINMOTION = 10;  //���[�V�����t���̓G�̍ő吔
	constexpr static int MAX_OBJECT_DATA = 20;    //�I�u�W�F�N�g�̍ő吔
	constexpr static int MAX_STAGEOBJECT = 20;    //�X�e�[�W�ɒu���p�̔z��̍ő吔
	constexpr static int MAX_BREAKHOUSE = 10;     //�X�e�[�W�ɒu���p�̔z��̍ő吔
	constexpr static int MAX_RUBBLE = 40;         //���I�̍ő吔
	constexpr static int MAX_ENEMY = 25;          //�G�̍ő吔
	constexpr static int MAX_SHIP = 2;           //�X�y�[�X�V�b�v�̍ő吔

	//�C�����C���W�J
	/*inline void CreateFuelGage()
	{
		m_pFuelGage = CFuelGage::Create();
	}*/

private:
	//�u���b�N�̃C���X�^���X�𐶐�
	CManagerBlock* m_pFieldBlock[MAX_OBJECT_DATA];       //�n�ʗp�u���b�N�̃C���X�^���X
	CManagerBlock* m_pGoUpBlock[MAX_OBJECT_DATA];        //�オ�邽�߂̃u���b�N�̃C���X�^���X
	CManagerBlock* m_pRoadBlock[MAX_OBJECT_DATA];        //���p�u���b�N�̃C���X�^���X
	CManagerBlock* m_pWallRoadBlock[MAX_OBJECT_DATA];    //�ǌ����p�̃u���b�N�̃C���X�^���X
	CManagerBlock* m_pWallRoadBlock001[MAX_OBJECT_DATA]; //�ǌ����p�u���b�N�̃C���X�^���X
	CManagerBlock* m_pSmallBlock[MAX_OBJECT_DATA];       //�������u���b�N�̃C���X�^���X
	CManagerBlock* m_pSmallBlock001[MAX_OBJECT_DATA];    //�������u���b�N001�̃C���X�^���X
	CManagerBlock* m_pUpWallBlock[MAX_OBJECT_DATA];      //��ǂ̃u���b�N�̃C���X�^���X
	CManagerBlock* m_pWoodenBoard[MAX_RUBBLE];           //�؂̔Q�̃C���X�^���X
	CManagerBlock*m_pFinalBlosk;                         //�{�X�펞�̑���̃C���X�^���X
	CManagerBlock*m_pFinalCeiling;                       //�{�X�펞�̓V��̃C���X�^���X

	CManagerBlock* m_pSpeceBattleShip000[MAX_SHIP];      //���̃X�e�[�W�֍s���I�u�W�F�N�g�̃C���X�^���X

	//�G�̃C���X�^���X
	CManagerEnemy* m_pEnemy000;                                      //�ʏ�G�̃C���X�^���X
	CManagerEnemy* m_pEnemy001[MAX_ENEMY];                           //�ʏ�G001�̃C���X�^���X
	CManagerEnemy* m_pEnemy002[MAX_ENEMY];                           //�ʏ�G002�̃C���X�^���X

	CManagerEnemyInMotion* m_pEnemyInMotion000[MAX_ENEMYINMOTION];   //���[�V�����t���̓G�̃C���X�^���X
	CManagerEnemyInMotion* m_pEnemyInMotion001[MAX_ENEMYINMOTION];   //���[�V�����t���̓G001�̃C���X�^���X
	CBoss* m_pBoss;                                                  //�{�X�̃C���X�^���X

	//���o�p�̃I�u�W�F�N�g�̃C���X�^���X
	CDebrisX* m_pDebrisX[MAX_OBJECT_DATA];             //X�t�@�C���^�̔j�ЃI�u�W�F�N�g

	//�p�[�e�B�N���̃C���X�^���X�𐶐�
	CParticles001* m_pPraticles001[MAX_OBJECT_DATA];   //�p�[�e�B�N���̉~

	//�X�e�[�W�I�u�W�F�N�g�̃C���X�^���X
	CStageObj* m_pTelephonPole[MAX_STAGEOBJECT];           //�d��
	CStageObj* m_pSurveillanceCameraUp[MAX_STAGEOBJECT];   //�Ď��J�����̏�̕���
	CStageObj* m_pSurveillanceCameraDown[MAX_STAGEOBJECT]; //�Ď��J�����̉��̕���
	CStageObj* m_pShop;                                    //�X
	CStageObj* m_pBreakHouse[MAX_BREAKHOUSE];              //��ꂽ��

	//�G�t�F�N�g�̃C���X�^���X
	CEffect* m_pEffect;                          //�e�ɂ��G�t�F�N�g�̃C���X�^���X
	CManagerEffect* m_pExplosion;                //�����G�t�F�N�g�̃C���X�^���X
	CManagerEffect* m_pThander;                  //���G�t�F�N�g�̃C���X�^���X
	CManagerEffect* m_pFire;                     //���G�t�F�N�g�̃C���X�^���X
	CManagerEffect* m_pExplosion001;             //�����P�G�t�F�N�g�̃C���X�^���X
	CManagerEffect* m_pDebris;                   //�j�ЃG�t�F�N�g
	CManagerEffect* m_pPillarOfFire;             //����̉��G�t�F�N�g
	CSpecialAttack* m_pSepecialAttack;           //�K�E�Z�̃G�t�F�N�g
	CManagerBossEffect* m_pImpact;               //�Ռ��g�G�t�F�N�g�̃C���X�^���X
	CManagerBossEffect* m_pBossSpecialAttack;    //�{�X�̕K�E�Z�G�t�F�N�g�̃C���X�^���X


	//2D�̃C���X�^���X
	CShopScreen* m_pShopScreen;      //�V���b�v���̔w�i�X�N���[����UI
	CManagerGage* m_pPlayerHPGage;   //�v���C���[��HP�Q�[�W
	CBossHPGage* m_pBossHPGage;      //�v���C���[��HP�Q�[�W
	CManagerScore* m_pGameScore;

	//�RD�̃C���X�^���X
	CFuelGage* m_pFuelGage;

	//���ꂽ����ۊǂ���ϐ�
	int m_nNumFiledBlock;      //�n�ʗp�̃u���b�N�̐�
	int m_nNumGoUpBlock;       //�オ��p�̃u���b�N�̐�
	int m_nRoadBlock;          //���p�̃u���b�N�̐�
	int m_nWallRoadBlock;      //�ǌ����p�̃u���b�N�̐�
	int m_nWallRoadBlock001;   //�ǌ����p�̃u���b�N001�̐�
	int m_nSmallBlock;         //�������u���b�N�̐�
	int m_nSmallBlock001;      //�������u���b�N001�̐�
	int m_nUpWallBlock;        //��̕ǂ̃u���b�N�̐�
	int m_nEnemy001;           //�G�̐�
	int m_nEnemy002;           //�G�̐�
	int m_nEnemyInMotion;      //���[�V�����t���̓G�̐�
	int m_nEnemyInMotion001;   //���[�V�����t���̓G001�̐�
	int m_nWoodenBoard;        //�؂̔Q�̐�
	int m_nBreakHouse;         //��ꂽ�Ƃ̐�
	int m_nShip;               //�X�y�[�X�V�b�v�̐�
};

#endif
