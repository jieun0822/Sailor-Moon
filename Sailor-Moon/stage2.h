#pragma once
#include"gameNode.h"


#define PLAYERSPEED 5
#define CAMERASPEED 5

#define BULLET1_MAX 10


enum class State2
{
	IDLE_LEFT,
	IDLE_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	ATTACK5,
	JUMP,
	DAMAGE1,
};
enum class monster2_State
{
	IDLE,
	WALK,
	ATTACK,
	DAMAGE
};



struct Bullet2
{
	image* _image;
	RECT _rc;
	int _index;
	int _count;
	int _x;
	int _y;
	bool _existence;
	bool _collision;
	bool isLeft;
};

struct Item2
{
	int id;
	int number;//갯수
	int pos;//위치
	bool empty;
	bool selected;
};


class stage2 :public gameNode
{

private:

	//////////플레이어
	image* _player;
	image* _playerState;

	int m_index;
	int m_count;
	int m_camera;

	RECT mini_rc;

	State2 currentState;
	State2 prevState;

	int player1_x;
	int player1_y;

	RECT _playerRC;
	bool isPlayerDie;

	//불렛

	//섬광불렛
	vector <Bullet2> _vBullet1;
	vector <Bullet2>::iterator _viBullet1;

	//하트불렛
	vector <Bullet2> _vBullet2;
	vector <Bullet2>::iterator _viBullet2;

	//파이어불렛
	vector <Bullet2> _vBullet3;
	vector <Bullet2>::iterator _viBullet3;


	//게이지
	RECT playerHP_Front;
	RECT playerHP_Back;

	RECT playerMP_Front;
	RECT playerMP_Back;

	int level;
	RECT levelRC;

	RECT expFront;
	RECT expBack;

	//int gaugeFront_x;
	//int gaugeFront_y;

	//image* player_gaugeFront;
	//image* player_gaugeBack;
	//RECT player_gaugeRC;

	//int currentGauge;
	//int MaxGauge;

	//int getGaugeFront_Left() { return playerHP_Front.left; }
	//void setGaugeFront_Left(int num) { playerHP_Front.left += num; }

	//색상
	int p_red;
	int p_green;

	////////////몬스터
	int monster_index;
	int monster_count;

	image* _monster;
	image* _monsterState;
	int monster_x;
	int monster_y;
	monster2_State monsterState;
	RECT _monsterRC;
	bool isMonsterDie;


	bool monster_isLeft;
	bool monster_collision;

	int startTime;
	int endTime;


	//게이지
	RECT m_gaugeFront;
	RECT m_gaugeBack;

	//색상
	int m_red;
	int m_green;

	//루프
	int loopX;
	int loopY;

	//점수
	int playerScore;

	image* zero;
	image* one;
	image* two;
	image* three;
	image* four;
	image* five;
	image* six;
	image* seven;
	image* eight;
	image* nine;

	//RECT _score100;
	//RECT _score10;
	//RECT _score1;

	//image* _TIME;
	RECT _time10;
	RECT _time1;

	//프레임
	//image* _FRAME;
	//RECT _frame10;
	//RECT _frame1;

	//이름
	image* S;
	image* M;
	image* o;
	image* n;
	image* dot;

	//드롭아이템
	image* dropItem1;
	int item_x;
	bool item_existence;
	RECT _itemRC;
	bool itemCollision;
	bool prevItemCollision;

	//이펙트
	image* _effect1;
	int effect1_index;
	int effect1_frameCount;

	image* _effect2;
	int effect2_index;

	//인벤토리 아이템
	vector<Item2> _vItem;
	vector<Item2>::iterator _viItem;

	vector<Item2> _vInventory;
	vector<Item2>::iterator _viInventory;

	RECT inven1;
	RECT inven2;
	RECT inven3;
	RECT inven4;

	//인벤토리 윈도우
	//RECT inventoryWindow_RC;
	bool inventoryDisable;


	//스킬키
	RECT skill_c;
	RECT skill_v;
	RECT skill_a;

	//미니맵
	RECT miniPlayer_RC;
	RECT miniMap_RC;
	bool miniMapDisable;

	bool questWindowDisable;

	//펫
	bool pet_existence;
	image* _pet;
	int pet_count;
	int pet_index;
	int pet_x;
	int pet_y;
	bool cashShopDisable;

	bool revive;

public:
	stage2();
	~stage2();
	HRESULT init();
	void release();
	void update();
	void render();


	void gaugeDraw();

	void scoreRender();
	void timeRender();
	void frameRender();
	void levelRender();


	int getScore() const { return playerScore; }
	void setScore(int score) { playerScore = score; }

	///////////////////인벤토리
	//void getBuyItem(int item1, int item2, int item3, int item4); //상점으로부터 데이터 가져옴.
	void GetBuyItem(int id);
	//void itemUpdate();
	void ItemUpdate();
	int getItem(int id)
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).id == id)
				return (*_viInventory).number;
		}
	}


	void inventoryWindow();
	void miniMap();
	void cashShop();
	void questWindow();

	void setLevel(int level) { this->level = level; }
	void setEXP(int n) { expFront.right = n; }
	void setHP(int n) { playerHP_Front.left = n; }
	void setMP(int n) { playerMP_Front.left = n; }
	void setPet(bool n) { pet_existence = n; }

	//int id;
	//int number;//갯수
	//int pos;//위치
	//bool empty;
	//bool selected;
	void setItem(int id, int number, int pos, bool empty, bool selected)
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).id == id)
			{
				(*_viInventory).number = number;
				(*_viInventory).pos = pos;
				(*_viInventory).empty = empty;
				(*_viInventory).selected = selected;
			}
		}
	}

};


