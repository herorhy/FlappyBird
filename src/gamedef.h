#ifndef SG_GAMEDEF_H_
#define SG_GAMEDEF_H_

#include <cstdint>
#include<SDL_mouse.h>
//#define Init_WIDTH 1280 //��Ϸ���ڳ�ʼ���
//#define Init_HEIGHT 960	//��Ϸ���ڳ�ʼ�߶�
constexpr double kPi = 3.14159265358979323846264338327950288;

/*#define Init_WIDTH 1280 //��Ϸ���ڳ�ʼ���
#define Init_HEIGHT 960	//��Ϸ���ڳ�ʼ�߶�
// size definition
constexpr int kWinWidth = 1280, kWinHeight = 960;
constexpr int kAreaWidth = 1280, kAreaHeight = 960;*/

#define Init_WIDTH 800 //��Ϸ���ڳ�ʼ���
#define Init_HEIGHT 1200	//��Ϸ���ڳ�ʼ�߶�
// size definition
constexpr int kWinWidth = 800, kWinHeight = 1200;
constexpr int kAreaWidth = 800, kAreaHeight = 1200;
// data saving definition
constexpr const char* kDataPath = "data/game.data";
constexpr int kRankMaxSize = 10;

// data definition
constexpr int kInitHP = 5;//��ʼ����ֵ
constexpr int kInitFuel = 100;//��ʼ����
constexpr int kInitScore = 0;//��ʼ����
constexpr int kInitHighScore = 0;//��ʼ��߷�
constexpr int kInitEnemyCount = 20;//��ʼ�л���Ŀ
constexpr int kSupplyFuel = 20;//����������

// score definition
constexpr int kScoreEnemy = 7;//ɱ���л��ӷ�
constexpr int kScoreHP = 3;//�Ե�Ѫ���ӷ�
constexpr int kScoreFuel = 2;//�Ե��Ͱ��ӷ�

// enemy definition
constexpr int kEnemyHP = 2;//�л�Ѫ��
constexpr int kEnemySpeed = 4;//�л��ٶ�
constexpr int kEnemyBulletSpeed = 1;//�л��ӵ��ٶ�
constexpr int kEnemyShootInterval = 800;//�л��ӵ�������

// player definition
////���ķɻ���ʼλ��
//constexpr int kPlayerInitX = 440;//�ɻ���ʼλ��
//constexpr int kPlayerInitY = 810;//�ɻ���ʼλ��
constexpr int kPlayerInitX = 125;//�ɻ���ʼλ��
constexpr int kPlayerInitY = 525;//�ɻ���ʼλ��
constexpr int kPlayerHiSpeed = 5;//�ɻ�����ٶ�
constexpr int kPlayerLoSpeed = 2;//�ɻ�����ٶ�
constexpr int kPlayerBulletSpeed = 7;//�ɻ��ӵ��ٶ�
constexpr int kPlayerShootInterval = 500;//�ӵ�������
constexpr int kPlayerBlinkInterval = 100;//�����˸���
constexpr int kPlayerInvisibleTimeout = 1510;//���ɼ�ʱ��

// interval definition
constexpr int kIntervalEnemyGen = 1400;//�л����ּ��
constexpr int kIntervalSupGenBase = 10000;//�������ֵĻ������
constexpr int kIntervalSupGenMax = 10000;//�������ֵ�����
constexpr int kIntervalFuelDec = 500;//�����½��ٶ�

// other
constexpr int kSupplySpeed = 7;//����������ٶ�

// key definition

constexpr uint64_t kKey_A = uint64_t(1) << 0;   // 
constexpr uint64_t kKey_B = uint64_t(1) << 1;   // 
constexpr uint64_t kKey_C = uint64_t(1) << 2;   // 
constexpr uint64_t kKey_D = uint64_t(1) << 3;   // 
constexpr uint64_t kKey_E = uint64_t(1) << 4;   // 
constexpr uint64_t kKey_F = uint64_t(1) << 5;   // 
constexpr uint64_t kKey_G = uint64_t(1) << 6;   // 
constexpr uint64_t kKey_H = uint64_t(1) << 7;   // 
constexpr uint64_t kKey_I = uint64_t(1) << 8;   // 
constexpr uint64_t kKey_J = uint64_t(1) << 9;   // 
constexpr uint64_t kKey_K = uint64_t(1) << 10;   // 
constexpr uint64_t kKey_L = uint64_t(1) << 11;   // 
constexpr uint64_t kKey_M = uint64_t(1) << 12;   // 
constexpr uint64_t kKey_N = uint64_t(1) << 13;   // 
constexpr uint64_t kKey_O = uint64_t(1) << 14;   // 
constexpr uint64_t kKey_P = uint64_t(1) << 15;   // 
constexpr uint64_t kKey_Q = uint64_t(1) << 16;   // 
constexpr uint64_t kKey_R = uint64_t(1) << 17;   // 
constexpr uint64_t kKey_S = uint64_t(1) << 18;   // 
constexpr uint64_t kKey_T = uint64_t(1) << 19;   // 
constexpr uint64_t kKey_U = uint64_t(1) << 20;   // 
constexpr uint64_t kKey_V = uint64_t(1) << 21;   // 
constexpr uint64_t kKey_W = uint64_t(1) << 22;   // 
constexpr uint64_t kKey_X = uint64_t(1) << 23;  // 
constexpr uint64_t kKey_Y = uint64_t(1) << 24; // 
constexpr uint64_t kKey_Z = uint64_t(1) << 25;

constexpr uint64_t kKey_Up = uint64_t(1) << 26;	//
constexpr uint64_t kKey_Down = uint64_t(1) << 27;
constexpr uint64_t kKey_Left = uint64_t(1) << 28;
constexpr uint64_t kKey_Right = uint64_t(1) << 29;

constexpr uint64_t kKey_0 = uint64_t(1) << 30;
constexpr uint64_t kKey_1 = uint64_t(1) << 31;
constexpr uint64_t kKey_2 = uint64_t(1) << 32;
constexpr uint64_t kKey_3 = uint64_t(1) << 33;
constexpr uint64_t kKey_4 = uint64_t(1) << 34;
constexpr uint64_t kKey_5 = uint64_t(1) << 35;
constexpr uint64_t kKey_6 = uint64_t(1) << 36;
constexpr uint64_t kKey_7 = uint64_t(1) << 37;
constexpr uint64_t kKey_8 = uint64_t(1) << 38;
constexpr uint64_t kKey_9 = uint64_t(1) << 39;

constexpr uint64_t kKey_F1 = uint64_t(1) << 40;
constexpr uint64_t kKey_F2 = uint64_t(1) << 41;
constexpr uint64_t kKey_F3 = uint64_t(1) << 42;
constexpr uint64_t kKey_F4 = uint64_t(1) << 43;
constexpr uint64_t kKey_F5 = uint64_t(1) << 44;
constexpr uint64_t kKey_F6 = uint64_t(1) << 45;
constexpr uint64_t kKey_F7 = uint64_t(1) << 46;
constexpr uint64_t kKey_F8 = uint64_t(1) << 47;
constexpr uint64_t kKey_F9 = uint64_t(1) << 48;
constexpr uint64_t kKey_F10 = uint64_t(1) << 49;
constexpr uint64_t kKey_F11 = uint64_t(1) << 50;
constexpr uint64_t kKey_F12 = uint64_t(1) << 51;

constexpr uint64_t kKey_Enter = uint64_t(1) << 52;   //
constexpr uint64_t kKey_Shift = uint64_t(1) << 53;   //
constexpr uint64_t kKey_Esc = uint64_t(1) << 54;   //
constexpr uint64_t kKey_Ctrl = uint64_t(1) << 55;	//
constexpr uint64_t kKey_Tab = uint64_t(1) << 56;	//
constexpr uint64_t kKey_Space = uint64_t(1) << 57;	//


using KeyStatus = uint64_t;//����״̬

//mouse key definition

constexpr uint8_t kMouse_Left = SDL_BUTTON_LMASK;
constexpr uint8_t kMouse_Right = SDL_BUTTON_RMASK;
constexpr uint8_t kMouse_Middle = SDL_BUTTON_MMASK;
constexpr uint8_t kMouse_4 = SDL_BUTTON_X1MASK;
constexpr uint8_t kMouse_5 = SDL_BUTTON_X2MASK;

struct MouseStatus
{
	uint32_t Status;
	int x;
	int y;
};

#endif // SG_GAMEDEF_H_
