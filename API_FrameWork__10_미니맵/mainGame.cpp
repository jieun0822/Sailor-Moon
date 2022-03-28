#include"framework.h"
#include "mainGame.h"

mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);

	

	enemyManager* _enemyManager;


	
	m_minimap = new minimap;
	m_minimap->init();

	_stage2 = new stage2;
	_stage2->init();

	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	menu = Menu::play;

	//_image = IMAGE->addImage("store", "images/store1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_image = IMAGE->addImage("store", "images/store/store9.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGE->addImage("BG", "images/etc/5.bmp", WINSIZEX/2, WINSIZEY/2, true, RGB(255, 0, 255));
	IMAGE->addImage("night", "images/etc/3.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGE->addImage("scene1", "images/final/1.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	//IMAGE->addImage("scene1", "images/final/1.bmp", 206, 190, true, RGB(0, 255, 0));
	IMAGE->addImage("scene2", "images/final/2.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene3", "images/final/3.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene4", "images/final/4.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene5", "images/final/5.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene6", "images/final/6.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene7", "images/final/7.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene8", "images/final/8.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene9", "images/final/9.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene10", "images/final/10.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene11", "images/final/11.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene12", "images/final/12.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene13", "images/final/13.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene14", "images/final/14.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene15", "images/final/15.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene17", "images/final/17.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene18", "images/final/18.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene19", "images/final/19.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene20", "images/final/20.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));
	IMAGE->addImage("scene21", "images/final/21.bmp", WINSIZEX / 2, WINSIZEY / 2, true, RGB(0, 255, 0));

	//인벤토리
	

	int item1;
	int item2;
	int item3;
	int item4;

	for (size_t i = 0; i < 9; i++)
	{
		buyItem _buyItem;
		_buyItem.id = i+1;
		_buyItem.number = 0;
		_buyItem.pos = 0;
		_buyItem.empty = true;

	

		if (_buyItem.id == 1)_buyItem.name = TEXT("Green Gel");
		else if (_buyItem.id == 2)_buyItem.name = TEXT("Lemon Gel");
		else if (_buyItem.id == 3)_buyItem.name = TEXT("Orange Gel");
		else if (_buyItem.id == 4)_buyItem.name = TEXT("Pine Gel");
		else if (_buyItem.id == 5)_buyItem.name = TEXT("Melange Gel");
		else if (_buyItem.id == 6)_buyItem.name = TEXT("Miracle Gel");
		else if (_buyItem.id == 7)_buyItem.name = TEXT("Oberol Gold");
		else if (_buyItem.id == 8)_buyItem.name = TEXT("Eilxir");
		else if (_buyItem.id == 9)_buyItem.name = TEXT("Life Bottle");

		_vBuyItem.push_back(_buyItem);
	}
	

	buyItem1_RC = RectMakeCenter(630, 230, 30, 30);
	buyItem2_RC = RectMakeCenter(630, 270, 30, 30);
	buyItem3_RC = RectMakeCenter(630, 310, 30, 30);
	buyItem4_RC = RectMakeCenter(630, 350, 30, 30);
	buyItem5_RC = RectMakeCenter(630, 390, 30, 30);
	buyItem6_RC = RectMakeCenter(630, 430, 30, 30);
	buyItem7_RC = RectMakeCenter(630, 470, 30, 30);
	buyItem8_RC = RectMakeCenter(630, 510, 30, 30);
	buyItem9_RC = RectMakeCenter(630, 550, 30, 30);

	//myScrollBar_outline = RectMakeCenter(820, 300, 30, 150);
	///myScrollBar = RectMakeCenter(820, 260, 25, 40);

	//int idIncrement = 0;
	for (size_t i = 0; i < 9; i++)
	{
		itemList _itemList;
		_itemList.id = i+1;
		_itemList.number = 0;
		_itemList.pos = i+1;
		_vItemList.push_back(_itemList);
	}


	//코인
	/*
	IMAGE->addImage("coin", "images/store/coin.bmp", 45 * 2, 19 * 2, true, RGB(184, 248, 168));
	IMAGE->addImage("zero", "images/store/0.bmp", 14*3, 16*3, true, RGB(184, 248, 168));
	IMAGE->addImage("one", "images/store/1.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("two", "images/store/2.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("three", "images/store/3.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("four", "images/store/4.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("five", "images/store/5.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("six", "images/store/6.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("seven", "images/store/7.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("eight", "images/store/8.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	IMAGE->addImage("nine", "images/store/9.bmp", 14 * 3, 16 * 3, true, RGB(184, 248, 168));
	*/
	//score100_RC = RectMakeCenter(710, 190, IMAGE->findImage("0")->getWidth(), IMAGE->findImage("0")->getHeight());
	//score10_RC = RectMakeCenter(710 +40, 190, IMAGE->findImage("0")->getWidth(), IMAGE->findImage("0")->getHeight());
	//score1_RC = RectMakeCenter(710 +80, 190, IMAGE->findImage("0")->getWidth(), IMAGE->findImage("0")->getHeight());

	listBox1 = RectMakeCenter(348, 205, 270, 90);
	listBox2 = RectMakeCenter(348, 318, 270, 90);
	listBox3 = RectMakeCenter(348, 435, 270, 90);
	listBox4 = RectMakeCenter(348, 549, 270, 90);

	ItemList_window = RectMakeCenter(370, 385, 350, 480);
	//myItem_window = RectMakeCenter(710, 300, 250, 300);


	scrollBar_outline = RectMakeCenter(520,340,30,370);
	scrollBar = RectMakeCenter(520,230,27,100);

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(m_minimap);
	SAFE_DELETE(_stage2);
}

void mainGame::update()
{

	gameNode::update();
	static bool isStage2 = false;
	
	if (menu == Menu::play && InputManager->isOnceKeyDown('Q'))
		menu = Menu::store;
	
	else if (menu == Menu::store && InputManager->isOnceKeyDown('Q'))
	{
		menu = Menu::play;

		
	}
	else if (menu == Menu::store)
	{
		itemSelect();
		buyItemUpdate();
	}
	else if(menu == Menu::play)
	{
		
		if (TIME->getWorldTime() <= 60)
		{
			m_minimap->update();
			player_level = m_minimap->getLevel();
			coin = m_minimap->getScore();
			currentEXP = m_minimap->getEXP();
			currentHP = m_minimap->getHP();
			currentMP = m_minimap->getMP();
			isPetexist = m_minimap->getPet();

			for (size_t i = 0; i < 9; i++) //play하면서 변화 받아옴.
			{
				for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
				{
					if ((*_viBuyItem).id == i + 1)
					{
						(*_viBuyItem).number = m_minimap->getItem(i + 1);
						
						
					}
				}
			}
		}
		else if (TIME->getWorldTime() <= 120)
		{
			if (!isStage2)
			{
				_stage2->setLevel(player_level);
				_stage2->setScore(coin);
				_stage2->setEXP(currentEXP);
				_stage2->setHP(currentHP);
				_stage2->setMP(currentMP);
				_stage2->setPet(isPetexist);


				for (size_t i = 0; i < 9; i++) //play하면서 변화 받아옴.
				{
					for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
					{
						_stage2->setItem((*_viBuyItem).id, (*_viBuyItem).number, (*_viBuyItem).pos, (*_viBuyItem).empty, false);
						
					}
				}
				isStage2 = true;
			}


			_stage2->update();

			for (size_t i = 0; i < 9; i++) //play하면서 변화 받아옴.
			{
				for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
				{
					if ((*_viBuyItem).id == i + 1) (*_viBuyItem).number = _stage2->getItem(i + 1);
				}
			}
		}
	}
	

	
	
}
void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	
	//설명서 페이지
	
	if (menu == Menu::store)
	{
		IMAGE->render("store", getMemDC());


		storeNameRender();
		coinRender();
		buyItemRender();

		itemSelect();
		scrollRender();
	}
	else
	{
		if (TIME->getWorldTime() <= 60)	m_minimap->render();
		else if (TIME->getWorldTime() <= 120) _stage2->render();
		else Final();
	}
	
	
	//==============================================
	//TIME->render(getMemDC());
	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


void mainGame::storeNameRender()
{
	RECT storeName_RC = RectMake(420, 60, 200, 70);
	//Rectangle(getMemDC(), storeName_RC.left, storeName_RC.top, storeName_RC.right, storeName_RC.bottom);


	HFONT font, oldfont;
	
	font = CreateFont(80, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "THEHappyfruit");
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	
	TCHAR str[100];

	SetTextColor(getMemDC(), RGB(255, 255, 255));//하얀 그림자.
	wsprintf(str, "STORE");
	TextOut(getMemDC(), storeName_RC.left +8, storeName_RC.top + 8, str, lstrlen(str));

	SetTextColor(getMemDC(), RGB(000, 102, 153));
	wsprintf(str, "STORE");
	TextOut(getMemDC(), storeName_RC.left+5, storeName_RC.top+5, str, lstrlen(str));
	
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
}

void mainGame::buyItemRender()
{
	TCHAR str[100];

	HFONT font, oldfont;

	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	
	for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
	{
		if ((*_viBuyItem).pos == 1)
		{
		//	Rectangle(getMemDC(), buyItem1_RC.left, buyItem1_RC.top, buyItem1_RC.right, buyItem1_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem1_RC.left, buyItem1_RC.top);

			
			TextOut(getMemDC(), buyItem1_RC.right + 7, buyItem1_RC.top + (buyItem1_RC.bottom - buyItem1_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem1_RC.right + 120, buyItem1_RC.top + (buyItem1_RC.bottom - buyItem1_RC.top) / 2, str, lstrlen(str));

		}

		else if ((*_viBuyItem).pos == 2)
		{
		//	Rectangle(getMemDC(), buyItem2_RC.left, buyItem2_RC.top, buyItem2_RC.right, buyItem2_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem2_RC.left, buyItem2_RC.top);

			TextOut(getMemDC(), buyItem2_RC.right + 7, buyItem2_RC.top + (buyItem2_RC.bottom - buyItem2_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem2_RC.right + 120, buyItem2_RC.top + (buyItem2_RC.bottom - buyItem2_RC.top) / 2, str, lstrlen(str));
		}

		else if ((*_viBuyItem).pos == 3)
		{
		//	Rectangle(getMemDC(), buyItem3_RC.left, buyItem3_RC.top, buyItem3_RC.right, buyItem3_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem3_RC.left, buyItem3_RC.top);

			TextOut(getMemDC(), buyItem3_RC.right + 7, buyItem3_RC.top + (buyItem3_RC.bottom - buyItem3_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem3_RC.right + 120, buyItem3_RC.top + (buyItem3_RC.bottom - buyItem3_RC.top) / 2, str, lstrlen(str));
		}

		else if ((*_viBuyItem).pos == 4)
		{
		//	Rectangle(getMemDC(), buyItem4_RC.left, buyItem4_RC.top, buyItem4_RC.right, buyItem4_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem4_RC.left, buyItem4_RC.top);

			TextOut(getMemDC(), buyItem4_RC.right + 7, buyItem4_RC.top + (buyItem4_RC.bottom - buyItem4_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem4_RC.right + 120, buyItem4_RC.top + (buyItem4_RC.bottom - buyItem4_RC.top) / 2, str, lstrlen(str));
		}

		else if ((*_viBuyItem).pos == 5)
		{
		//	Rectangle(getMemDC(), buyItem5_RC.left, buyItem5_RC.top, buyItem5_RC.right, buyItem5_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem5_RC.left, buyItem5_RC.top);

			TextOut(getMemDC(), buyItem5_RC.right + 7, buyItem5_RC.top + (buyItem5_RC.bottom - buyItem5_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem5_RC.right + 120, buyItem5_RC.top + (buyItem5_RC.bottom - buyItem5_RC.top) / 2, str, lstrlen(str));

		}

		else if ((*_viBuyItem).pos == 6)
		{
		//	Rectangle(getMemDC(), buyItem6_RC.left, buyItem6_RC.top, buyItem6_RC.right, buyItem6_RC.bottom);

			if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);
			else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem6_RC.left, buyItem6_RC.top);

			TextOut(getMemDC(), buyItem6_RC.right + 7, buyItem6_RC.top + (buyItem6_RC.bottom - buyItem6_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
			wsprintf(str, "%d개", (*_viBuyItem).number);
			TextOut(getMemDC(), buyItem6_RC.right + 120, buyItem6_RC.top + (buyItem6_RC.bottom - buyItem6_RC.top) / 2, str, lstrlen(str));

		}

		else if ((*_viBuyItem).pos == 7)
		{
		//Rectangle(getMemDC(), buyItem7_RC.left, buyItem7_RC.top, buyItem7_RC.right, buyItem7_RC.bottom);

		if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);
		else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem7_RC.left, buyItem7_RC.top);

		TextOut(getMemDC(), buyItem7_RC.right + 7, buyItem7_RC.top + (buyItem7_RC.bottom - buyItem7_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
		wsprintf(str, "%d개", (*_viBuyItem).number);
		TextOut(getMemDC(), buyItem7_RC.right + 120, buyItem7_RC.top + (buyItem7_RC.bottom - buyItem7_RC.top) / 2, str, lstrlen(str));
		}

		else if ((*_viBuyItem).pos == 8)
		{
		//Rectangle(getMemDC(), buyItem8_RC.left, buyItem8_RC.top, buyItem8_RC.right, buyItem8_RC.bottom);

		if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);
		else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem8_RC.left, buyItem8_RC.top);

		TextOut(getMemDC(), buyItem8_RC.right + 7, buyItem8_RC.top + (buyItem8_RC.bottom - buyItem8_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
		wsprintf(str, "%d개", (*_viBuyItem).number);
		TextOut(getMemDC(), buyItem8_RC.right + 120, buyItem8_RC.top + (buyItem8_RC.bottom - buyItem8_RC.top) / 2, str, lstrlen(str));
		}

		else if ((*_viBuyItem).pos == 9)
		{
		//Rectangle(getMemDC(), buyItem9_RC.left, buyItem9_RC.top, buyItem9_RC.right, buyItem9_RC.bottom);

		if ((*_viBuyItem).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 8) IMAGE->render("Elixir_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);
		else if ((*_viBuyItem).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), buyItem9_RC.left, buyItem9_RC.top);

		TextOut(getMemDC(), buyItem9_RC.right + 7, buyItem9_RC.top + (buyItem9_RC.bottom - buyItem9_RC.top) / 2, (*_viBuyItem).name, lstrlen((*_viBuyItem).name));
		wsprintf(str, "%d개", (*_viBuyItem).number);
		TextOut(getMemDC(), buyItem9_RC.right + 120, buyItem9_RC.top + (buyItem9_RC.bottom - buyItem9_RC.top) / 2, str, lstrlen(str));
		}
	}

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
	
}

void mainGame::coinRender()
{
	//IMAGE->render("coin", getMemDC(),600,170);

	RECT coinDisplay = RectMake(600, 180, 200, 30);
	//Rectangle(getMemDC(), coinDisplay.left, coinDisplay.top, coinDisplay.right, coinDisplay.bottom);
	int score;

	if (TIME->getWorldTime() <= 60)
	{
		score = m_minimap->getScore();
	}
	else if (TIME->getWorldTime() <= 120)
	{
		score = _stage2->getScore();
	}
	HFONT font, oldfont;
	font = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	
	TCHAR str[100];
	wsprintf(str, "COIN : %d", score);
	TextOut(getMemDC(), coinDisplay.left + 20, coinDisplay.top + 5, str, lstrlen(str));

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
	
	float score100 = score / 100;
	float score10 = (score % 100) / 10;
	float score1 = (score % 100) % 10;

	HDC hdc = getMemDC();

	//Rectangle(hdc, score100_RC.left, score100_RC.top, score100_RC.right, score100_RC.bottom);
	//Rectangle(hdc, score10_RC.left, score10_RC.top, score10_RC.right, score10_RC.bottom);
	//Rectangle(hdc, score1_RC.left, score1_RC.top, score1_RC.right, score1_RC.bottom);

	/*
	if (score100 == 0)IMAGE->render("zero", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 1)IMAGE->render("one", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 2)IMAGE->render("two", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 3)IMAGE->render("three", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 4)IMAGE->render("four", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 5)IMAGE->render("five", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 6)IMAGE->render("six", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 7)IMAGE->render("seven", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 8)IMAGE->render("eight", hdc, score100_RC.left, score100_RC.top);
	else if (score100 == 9)IMAGE->render("nine", hdc, score100_RC.left, score100_RC.top);

	if (score10 == 0)IMAGE->render("zero", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 1)IMAGE->render("one", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 2)IMAGE->render("two", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 3)IMAGE->render("three", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 4)IMAGE->render("four", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 5)IMAGE->render("five", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 6)IMAGE->render("six", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 7)IMAGE->render("seven", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 8)IMAGE->render("eight", hdc, score10_RC.left, score10_RC.top);
	else if (score10 == 9)IMAGE->render("nine", hdc, score10_RC.left, score10_RC.top);

	if (score1 == 0)IMAGE->render("zero", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 1)IMAGE->render("one", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 2)IMAGE->render("two", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 3)IMAGE->render("three", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 4)IMAGE->render("four", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 5)IMAGE->render("five", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 6)IMAGE->render("six", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 7)IMAGE->render("seven", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 8)IMAGE->render("eight", hdc, score1_RC.left, score1_RC.top);
	else if (score1 == 9)IMAGE->render("nine", hdc, score1_RC.left, score1_RC.top);
	*/
}

void mainGame::buyItemUpdate()
{
	static bool pos1_empty = true;
	static bool pos2_empty = true;
	static bool pos3_empty = true;
	static bool pos4_empty = true;
	static bool pos5_empty = true;
	static bool pos6_empty = true;
	static bool pos7_empty = true;
	static bool pos8_empty = true;
	static bool pos9_empty = true;

	int pos1 = 1;
	int pos2 = 2;
	int pos3 = 3;
	int pos4 = 4;
	int pos5 = 5;
	int pos6 = 6;
	int pos7 = 7;
	int pos8 = 8;
	int pos9 = 9;

	
	for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
	{
		if ((*_viBuyItem).number == 0)//비어있으면.
		{
			(*_viBuyItem).empty = true;


			if ((*_viBuyItem).pos == pos1) pos1_empty = true;
			if ((*_viBuyItem).pos == pos2) pos2_empty = true;
			if ((*_viBuyItem).pos == pos3) pos3_empty = true;
			if ((*_viBuyItem).pos == pos4) pos4_empty = true;
			if ((*_viBuyItem).pos == pos5) pos5_empty = true;
			if ((*_viBuyItem).pos == pos6) pos6_empty = true;
			if ((*_viBuyItem).pos == pos7) pos7_empty = true;
			if ((*_viBuyItem).pos == pos8) pos8_empty = true;
			if ((*_viBuyItem).pos == pos9) pos9_empty = true;

			(*_viBuyItem).pos = 0;
		}

		else if ((*_viBuyItem).pos == 0 && (*_viBuyItem).empty)
		{
			(*_viBuyItem).empty = false;

			if (pos1_empty) { (*_viBuyItem).pos = 1;  pos1_empty = false; }
			else if (pos2_empty) { (*_viBuyItem).pos = 2; pos2_empty = false; }
			else if (pos3_empty) { (*_viBuyItem).pos = 3; pos3_empty = false; }
			else if (pos4_empty) { (*_viBuyItem).pos = 4; pos4_empty = false; }
			else if (pos5_empty) { (*_viBuyItem).pos = 5; pos5_empty = false; }
			else if (pos6_empty) { (*_viBuyItem).pos = 6; pos6_empty = false; }
			else if (pos7_empty) { (*_viBuyItem).pos = 7; pos7_empty = false; }
			else if (pos8_empty) { (*_viBuyItem).pos = 8; pos8_empty = false; }
			else if (pos9_empty) { (*_viBuyItem).pos = 9; pos9_empty = false; }
		}


		//앞으로 당기기.
		if (pos1_empty && !pos2_empty && (*_viBuyItem).pos == pos2)
		{
			(*_viBuyItem).pos = 1;
			pos1_empty = false;
			pos2_empty = true;
		}
		if (pos2_empty && !pos3_empty && (*_viBuyItem).pos == pos3)
		{
			(*_viBuyItem).pos = 2;
			pos2_empty = false;
			pos3_empty = true;
		}
		if (pos3_empty && !pos4_empty && (*_viBuyItem).pos == pos4)
		{
			(*_viBuyItem).pos = 3;
			pos3_empty = false;
			pos4_empty = true;
		}
		if (pos4_empty && !pos5_empty && (*_viBuyItem).pos == pos5)
		{
			(*_viBuyItem).pos = 4;
			pos4_empty = false;
			pos5_empty = true;
		}
		if (pos5_empty && !pos6_empty && (*_viBuyItem).pos == pos6)
		{
			(*_viBuyItem).pos = 5;
			pos5_empty = false;
			pos6_empty = true;
		}
		if (pos6_empty && !pos7_empty && (*_viBuyItem).pos == pos7)
		{
			(*_viBuyItem).pos = 6;
			pos6_empty = false;
			pos7_empty = true;
		}
		if (pos7_empty && !pos8_empty && (*_viBuyItem).pos == pos8)
		{
			(*_viBuyItem).pos = 7;
			pos7_empty = false;
			pos8_empty = true;
		}
		if (pos8_empty && !pos9_empty && (*_viBuyItem).pos == pos9)
		{
			(*_viBuyItem).pos = 8;
			pos8_empty = false;
			pos9_empty = true;
		}
	}

	

}

void mainGame::itemSelect()
{
	

	POINT mouse = m_ptMouse;
	TCHAR str[100];
	


	if (InputManager->isOnceKeyDown(VK_LBUTTON))//아이템 선택
	{
		if (PtInRect(&listBox1, mouse))
		{
			for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
			{
				if ((*_viItemList).pos == 1)
				{
					for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
					{
						if ((*_viItemList).id == (*_viBuyItem).id)
						{
							++(*_viBuyItem).number;
						}
					}
					if (TIME->getWorldTime() <= 60)
					{
						m_minimap->GetBuyItem((*_viItemList).id);
						m_minimap->setScore(m_minimap->getScore() - 10);
					}
					else if (TIME->getWorldTime() <= 120)
					{
						_stage2->GetBuyItem((*_viItemList).id);
						_stage2->setScore(_stage2->getScore() - 10);
					}
				}
			}
		}
		else if (PtInRect(&listBox2, mouse))
		{
			for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
			{
				if ((*_viItemList).pos == 2)
				{
					for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
					{
						if ((*_viItemList).id == (*_viBuyItem).id) ++(*_viBuyItem).number;
					}
					if (TIME->getWorldTime() <= 60)
					{
						m_minimap->GetBuyItem((*_viItemList).id);
						m_minimap->setScore(m_minimap->getScore() - 10);
					}
					else if (TIME->getWorldTime() <= 120)
					{
						_stage2->GetBuyItem((*_viItemList).id);
						_stage2->setScore(_stage2->getScore() - 10);
					}
				}
			}
		}
		else if (PtInRect(&listBox3, mouse))
		{
			for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
			{
				if ((*_viItemList).pos == 3)
				{
					for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
					{
						if ((*_viItemList).id == (*_viBuyItem).id) ++(*_viBuyItem).number;
					}
					if (TIME->getWorldTime() <= 60)
					{
						m_minimap->GetBuyItem((*_viItemList).id);
						m_minimap->setScore(m_minimap->getScore() - 10);
					}
					else if (TIME->getWorldTime() <= 120)
					{
						_stage2->GetBuyItem((*_viItemList).id);
						_stage2->setScore(_stage2->getScore() - 10);
					}
				}
			}
		}
		else if (PtInRect(&listBox4, mouse))
		{
			for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
			{
				if ((*_viItemList).pos == 4)
				{
					for (_viBuyItem = _vBuyItem.begin(); _viBuyItem != _vBuyItem.end(); ++_viBuyItem)
					{
						if ((*_viItemList).id == (*_viBuyItem).id) ++(*_viBuyItem).number;
					}
					if (TIME->getWorldTime() <= 60)
					{
						m_minimap->GetBuyItem((*_viItemList).id);
						m_minimap->setScore(m_minimap->getScore() - 10);
					}
					else if (TIME->getWorldTime() <= 120)
					{
						_stage2->GetBuyItem((*_viItemList).id);
						_stage2->setScore(_stage2->getScore() - 10);
					}
				}
			}
		}
	}

	//아이템 리스트 스크롤.
	if (zDelta > 0 && PtInRect(&ItemList_window, mouse)) // scroll up
	{
		for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
		{
			if ((*_viItemList).id == 1 && (*_viItemList).pos == 1)break;


			(*_viItemList).pos++;
			//if ((*_viItemList).id == 5 && (*_viItemList).pos == 1) scrollDown_limit = false;
			//if ((*_viItemList).pos == 5) (*_viItemList).pos = 5;

		}
	}
	else if (zDelta < 0 && PtInRect(&ItemList_window, mouse))
	{
		for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
		{
			if ((*_viItemList).id == 1 && (*_viItemList).pos == -4)
			{
				//scrollDown_limit = true;
				break;
			}
			else if (scrollDown_limit)
			{
				if ((*_viItemList).id == 1) (*_viItemList).pos == -4;
				if ((*_viItemList).id == 2) (*_viItemList).pos == -3;
				if ((*_viItemList).id == 3) (*_viItemList).pos == -2;
				if ((*_viItemList).id == 4) (*_viItemList).pos == -1;

				break;
			}
			else (*_viItemList).pos--;
			//if ((*_viItemList).pos == 0) (*_viItemList).pos = 0;
		}
	}

	
	

	

	for (_viItemList = _vItemList.begin(); _viItemList != _vItemList.end(); ++_viItemList)
	{
		

		int interval_x = 20;
		int interval_y = 20;
		if ((*_viItemList).pos == 1)
		{
			if ((*_viItemList).id == 1)	IMAGE->render("Green_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top+ interval_y);
			else if ((*_viItemList).id == 2)IMAGE->render("Orange_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 3)IMAGE->render("Lemon_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 4)IMAGE->render("Pine_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 5)IMAGE->render("Melange_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 6)IMAGE->render("Miracle_Gel", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 7)IMAGE->render("Oberol_Gold", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 8)IMAGE->render("Elixir", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
			else if ((*_viItemList).id == 9)IMAGE->render("Life_Bottle", getMemDC(), listBox1.left + interval_x, listBox1.top + interval_y);
		}
		if ((*_viItemList).pos == 2)
		{
			if ((*_viItemList).id == 1)	IMAGE->render("Green_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 2)IMAGE->render("Orange_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 3)IMAGE->render("Lemon_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 4)IMAGE->render("Pine_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 5)IMAGE->render("Melange_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 6)IMAGE->render("Miracle_Gel", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 7)IMAGE->render("Oberol_Gold", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 8)IMAGE->render("Elixir", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
			else if ((*_viItemList).id == 9)IMAGE->render("Life_Bottle", getMemDC(), listBox2.left + interval_x, listBox2.top + interval_y);
		}
		if ((*_viItemList).pos == 3)
		{
			if ((*_viItemList).id == 1)	IMAGE->render("Green_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 2)IMAGE->render("Orange_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 3)IMAGE->render("Lemon_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 4)IMAGE->render("Pine_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 5)IMAGE->render("Melange_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 6)IMAGE->render("Miracle_Gel", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 7)IMAGE->render("Oberol_Gold", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 8)IMAGE->render("Elixir", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
			else if ((*_viItemList).id == 9)IMAGE->render("Life_Bottle", getMemDC(), listBox3.left + interval_x, listBox3.top + interval_y);
		}
		if ((*_viItemList).pos == 4)
		{
			if ((*_viItemList).id == 1)	IMAGE->render("Green_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 2)IMAGE->render("Orange_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 3)IMAGE->render("Lemon_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 4)IMAGE->render("Pine_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 5)IMAGE->render("Melange_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 6)IMAGE->render("Miracle_Gel", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 7)IMAGE->render("Oberol_Gold", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 8)IMAGE->render("Elixir", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
			else if ((*_viItemList).id == 9)IMAGE->render("Life_Bottle", getMemDC(), listBox4.left + interval_x, listBox4.top + interval_y);
		}
	}
}

void mainGame::scrollRender()//스크롤 바 렌더.
{
	Rectangle(getMemDC(), scrollBar_outline.left, scrollBar_outline.top, scrollBar_outline.right, scrollBar_outline.bottom);
	Rectangle(getMemDC(), scrollBar.left, scrollBar.top, scrollBar.right, scrollBar.bottom);
	
	POINT mouse = m_ptMouse;

	
	int distance = 70;

	if ( zDelta > 0 && PtInRect(&ItemList_window,mouse)) //scroll up
	{
		if (scrollBar.top - distance >= scrollBar_outline.top)
		{
			scrollBar.top -= distance;
			scrollBar.bottom -= distance;
		}
	}
	else if (zDelta < 0 && PtInRect(&ItemList_window, mouse))
	{
		if (scrollBar.bottom + distance <= scrollBar_outline.bottom)
		{
			scrollBar.top += distance;
			scrollBar.bottom += distance;
		}
	}
}


void mainGame::Final()
{

	//IMAGE->render("store", getMemDC(), 0, 0);

	static int count = 0;

	count++;
	
	int term = 40;

	
	IMAGE->render("night", getMemDC(), 0, 0);
	IMAGE->render("BG", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);

	HFONT font, oldfont;

	font = CreateFont(100, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "THEHappyfruit");
	oldfont = (HFONT)SelectObject(getMemDC(), font);
	
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255)); 
	TCHAR str[100];
	wsprintf(str, "END");
	TextOut(getMemDC(), 450, 570, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SetTextColor(getMemDC(), RGB(153, 204, 255));
	wsprintf(str, "END");
	TextOut(getMemDC(), 450 + 5, 570 + 5, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);


	
	if (count < 110) IMAGE->render("scene4", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 140) IMAGE->render("scene5", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 200) IMAGE->render("scene6", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 230) IMAGE->render("scene7", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 250) IMAGE->render("scene8", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 260) IMAGE->render("scene9", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 270) IMAGE->render("scene10", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 280) IMAGE->render("scene11", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 290) IMAGE->render("scene12", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 310) IMAGE->render("scene13", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 400) IMAGE->render("scene14", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	//else if (count < term * 15) IMAGE->render("scene15", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	//else if (count < term * 16) IMAGE->render("scene16", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count <420) IMAGE->render("scene17", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 430) IMAGE->render("scene18", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 440) IMAGE->render("scene19", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else if (count < 600) IMAGE->render("scene20", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	else  IMAGE->render("scene21", getMemDC(), WINSIZEX / 2 / 2, WINSIZEY / 2 / 2);
	
	
}

