#pragma once
#include"gameNode.h"
#include"enemyManager.h"
#include"minimap.h"
#include"stage2.h"
enum class Menu
{
	store,
	play
};

struct buyItem
{
	int id;
	int number;
	int pos;
	bool empty;
	TCHAR *name;
};

struct itemList
{
	int id;
	int number;
	int pos;
	RECT rc;
};

class mainGame : public gameNode
{
private:
	enemyManager* _enemyManager;
	minimap* m_minimap;
	stage2* _stage2;

	RECT rc;

	Menu menu;

	image* _image;

	//상점
	int item1;
	int item2;
	int item3;
	int item4;

	//내가 산 아이템
	vector<buyItem> _vBuyItem;
	vector<buyItem>::iterator _viBuyItem;

	//아이템 리스트
	vector<itemList> _vItemList;
	vector<itemList>::iterator _viItemList;


	RECT buyItem1_RC;
	RECT buyItem2_RC;
	RECT buyItem3_RC;
	RECT buyItem4_RC;
	RECT buyItem5_RC;
	RECT buyItem6_RC;
	RECT buyItem7_RC;
	RECT buyItem8_RC;
	RECT buyItem9_RC;

	//RECT score100_RC;
	//RECT score10_RC;
	//RECT score1_RC;

	//4개 아이템 리스트만 display
	RECT listBox1;
	RECT listBox2;
	RECT listBox3;
	RECT listBox4;

	//bool scrollUp_limit;
	bool scrollDown_limit;

	RECT ItemList_window;
	RECT scrollBar_outline;
	RECT scrollBar;

	//RECT myItem_window;
	//RECT myScrollBar_outline;
	//RECT myScrollBar;
	//bool myScrollDown_limit;
	int player_level;
	int coin;
	bool isPetexist;
	int currentEXP;
	int currentHP;
	int currentMP;
	


public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void storeNameRender();
	void buyItemRender();
	void coinRender();
	void buyItemUpdate();
	void itemSelect();
	void scrollRender();
	void Final();
};

