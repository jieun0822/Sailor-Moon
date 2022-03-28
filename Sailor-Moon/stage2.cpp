#include "framework.h"
#include "stage2.h"

stage2::stage2()
{
}

stage2::~stage2()
{
}



HRESULT stage2::init()
{

	IMAGE->addImage("스테이지2배경화면", "images/BG3.bmp", WINSIZEX * 5, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("카메라", "images/카메라.bmp", WINSIZEX / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGE->addImage("스테이지2미니맵", "images/BG3_mini.bmp", WINSIZEX * 2 / 10, WINSIZEY / 10, 50, 50, true, RGB(255, 0, 255));

	//IMAGE->addImage("퀘스트창배경", "images/background/yellow_background.bmp", 256,192, 150, 200, true, RGB(255, 0, 255));
	IMAGE->addImage("퀘스트창배경", "images/background/blue_background.bmp", 150, 200, 150, 200, true, RGB(255, 0, 255));
	IMAGE->addImage("인벤토리배경", "images/background/blue_moon.bmp", 200, 250, 200, 250, true, RGB(255, 0, 255));

	//플레이어
	_player = IMAGE->addFrameImage("세일러문", "images/character1_walk.bmp", 503 * 2, 210 * 2, 11, 2, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("캐릭터1_점프", "images/character1_jump.bmp", 808 * 2, 286 * 2, 11, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_공격1", "images/character1_attack1.bmp", 520 * 2, 188 * 2, 4, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_공격2", "images/character1_attack2.bmp", 480 * 2, 210 * 2, 4, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_공격3", "images/character1_attack3.bmp", 450 * 2, 258 * 2, 5, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_공격4", "images/character1_attack4.bmp", 400 * 2, 271 * 2, 5, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_공격5", "images/character1_attack5.bmp", 410 * 2, 271 * 2, 6, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_기본", "images/character1_idle.bmp", 112 * 2, 105 * 2, 2, 1, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_기본2", "images/character1_idle_left.bmp", 57 * 2, 107 * 2, 1, 1, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("캐릭터1_데미지1", "images/character1_damage1.bmp", 600 * 2, 214 * 2, 6, 2, true, RGB(255, 255, 255));

	//불렛
	Bullet2 bullet1;
	bullet1._image = IMAGE->addFrameImage("총알1", "images/bullet/bullet.bmp", 360 * 2, 36 * 2, 10, 1, true, RGB(255, 0, 255));
	bullet1._index = 0;
	bullet1._count = 0;
	bullet1._x = WINSIZEX / 2;
	bullet1._y = WINSIZEY / 2;
	bullet1._rc = RectMakeCenter(bullet1._x, bullet1._y, bullet1._image->getWidth(), bullet1._image->getHeight());
	bullet1._existence = false;
	bullet1._collision = false;
	bullet1.isLeft = false;

	Bullet2 bullet2;
	bullet2._image = IMAGE->addFrameImage("총알2", "images/bullet2/bullet.bmp", 1062, 244, 6, 2, true, RGB(255, 255, 255));
	bullet2._index = 0;
	bullet2._count = 0;
	bullet2._x = WINSIZEX / 2;
	bullet2._y = WINSIZEY / 2;
	bullet2._rc = RectMakeCenter(bullet2._x, bullet2._y, bullet2._image->getWidth(), bullet2._image->getHeight());
	bullet2._existence = false;
	bullet2._collision = false;
	bullet2.isLeft = false;

	Bullet2 bullet3;
	bullet3._image = IMAGE->addFrameImage("총알3", "images/bullet3/bullet.bmp", 560, 84, 7, 2, true, RGB(255, 255, 255));
	bullet3._index = 0;
	bullet3._count = 0;
	bullet3._x = WINSIZEX / 2;
	bullet3._y = WINSIZEY / 2;
	bullet3._rc = RectMakeCenter(bullet2._x, bullet2._y, bullet2._image->getWidth(), bullet2._image->getHeight());
	bullet3._existence = false;
	bullet3._collision = false;
	bullet3.isLeft = false;


	for (size_t i = 0; i < BULLET1_MAX; i++)
	{
		_vBullet1.push_back(bullet1);
		_vBullet2.push_back(bullet2);
		_vBullet3.push_back(bullet3);
	}

	//플레이어 상태
	IMAGE->addFrameImage("캐릭터상태창_노멀", "images/sm_normal.bmp", 34 * 2 + 20, 34 * 2 + 20, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("캐릭터상태창_데미지", "images/sm_damage.bmp", 34 * 2 + 20, 34 * 2 + 20, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("캐릭터상태창_승리", "images/sm_victory.bmp", 34 * 2 + 20, 34 * 2 + 20, 1, 1, true, RGB(255, 0, 255));


	_player->setX(WINSIZEX / 2);
	_player->setY(WINSIZEY / 2);

	player1_x = WINSIZEX / 2;
	player1_y = WINSIZEY / 2;

	pet_x = player1_x - 20;
	pet_y = player1_y + 150;

	currentState = State2::IDLE_RIGHT;
	prevState = State2::WALK_RIGHT;

	m_index = 0;
	m_count = 0;
	m_camera = 0;
	isPlayerDie = false;

	_playerState = IMAGE->findImage("캐릭터상태창_노멀");
	IMAGE->addImage("HP", "images/HP.bmp", 32 * 2, 14 * 2, true, RGB(255, 0, 255));
	IMAGE->addImage("MP", "images/MP.bmp", 32 * 2, 14 * 2, true, RGB(255, 0, 255));

	playerHP_Front = RectMakeCenter(280, 77, 200, 30);
	playerHP_Back = RectMakeCenter(280, 77, 200, 30);

	playerMP_Front = RectMakeCenter(280, 120, 200, 30);
	playerMP_Back = RectMakeCenter(280, 120, 200, 30);

	IMAGE->addImage("EXP", "images/EXP.bmp", 42 * 2, 14 * 2, true, RGB(255, 0, 255));
	expFront = RectMakeCenter(580 - 195, 700, 0, 30);
	expBack = RectMakeCenter(580, 700, 390, 30);

	p_red = 0;
	p_green = 255;

	//몬스터
	/*IMAGE->addFrameImage("Bret_Walk_Right", "images/Bret Butler/BretButler_Walk_Right.bmp", 1000 * 2, 200 * 2, 5, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("Bret_Walk_Left", "images/Bret Butler/BretButler_Walk_Left.bmp", 1000 * 2, 200 * 2, 5, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("Bret_Damage_Right", "images/Bret Butler/BretButler_Damage_Right.bmp", 800 * 2, 200 * 2, 4, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("Bret_Damage_Left", "images/Bret Butler/BretButler_Damage_Left.bmp", 800 * 2, 200 * 2, 4, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("Bret_Attack_Right", "images/Bret Butler/BretButler_Attack_Right.bmp", 1200 * 2, 200 * 2, 6, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("Bret_Attack_Left", "images/Bret Butler/BretButler_Attack_Left.bmp", 1200 * 2, 200 * 2, 6, 1, true, RGB(252, 0, 252));

	IMAGE->addFrameImage("BretAttack_Right", "images/Bret Butler/bb/right.bmp", 1800 * 2, 177 * 2, 6, 1, true, RGB(252, 0, 252));
	IMAGE->addFrameImage("BretAttack_Left", "images/Bret Butler/bb/left.bmp", 1800 * 2, 177 * 2, 6, 1, true, RGB(252, 0, 252));
	*/
	
	IMAGE->addFrameImage("Garoben_Walk", "images/monster2/walk.bmp", 642 * 2, 260 * 2, 7, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("Garoben_Attack", "images/monster2/attack.bmp", 536 * 2, 298 * 2, 4, 2, true, RGB(255, 255, 255));
	IMAGE->addFrameImage("Garoben_Damage", "images/monster2/damage.bmp", 121 * 2, 202 * 2, 1, 2, true, RGB(255, 255, 255));

	//몬스터 상태
	IMAGE->addFrameImage("Garoben_icon", "images/monster2/icon.bmp", 18 * 2, 18 * 2, 1, 1, true, RGB(255, 0, 255));

	_monsterState = IMAGE->findImage("Bret_Butler");

	monster_index = 0;
	monster_count = 0;
	monster_isLeft = true;

	_monster = IMAGE->findImage("Garoben_Walk");
	monster_x = WINSIZEX + 100;
	monster_y = WINSIZEY / 2;
	monsterState = monster2_State::WALK;
	monster_collision = false;
	isMonsterDie = false;

	m_gaugeFront = RectMakeCenter(1000, 400, 20, 200);
	m_gaugeBack = RectMakeCenter(1000, 400, 20, 200);

	m_red = 0;
	m_green = 255;

	//점수
	playerScore = 500;

	zero = IMAGE->addFrameImage("0", "images/number/zero.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	one = IMAGE->addFrameImage("1", "images/number/one.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	two = IMAGE->addFrameImage("2", "images/number/two.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	three = IMAGE->addFrameImage("3", "images/number/three.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	four = IMAGE->addFrameImage("4", "images/number/four.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	five = IMAGE->addFrameImage("5", "images/number/five.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	six = IMAGE->addFrameImage("6", "images/number/six.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	seven = IMAGE->addFrameImage("7", "images/number/seven.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	eight = IMAGE->addFrameImage("8", "images/number/eight.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));
	nine = IMAGE->addFrameImage("9", "images/number/nine.bmp", WINSIZEX + 100, WINSIZEY / 2, 13 * 3, 20 * 3, 1, 1, true, RGB(255, 0, 255));

	//_score100 = RectMakeCenter(820, 100, one->getFrameWidth(), one->getFrameHeight());
	//_score10 = RectMakeCenter(820 + 25, 100, one->getFrameWidth(), one->getFrameHeight());
	//_score1 = RectMakeCenter(820 + 25 * 2, 100, one->getFrameWidth(), one->getFrameHeight());

	IMAGE->addImage("Lv", "images/Lv.bmp", 21 * 3, 12 * 3, true, RGB(255, 0, 255));
	level = 1;
	levelRC = RectMakeCenter(110, 687, 13 * 3, 20 * 3);

	//_TIME = IMAGE->addImage("TIME", "images/etc/TIME.bmp", 98+10,20+10, true, RGB(184, 248, 168));
	_time10 = RectMakeCenter(WINSIZEX / 2 + 30, 20 + 10, 13 * 3, 20 * 3);
	_time1 = RectMakeCenter(WINSIZEX / 2 + 30 + 40, 20 + 10, 13 * 3, 20 * 3);

	//프레임
	//_FRAME = IMAGE->addImage("FRAME", "images/etc/Frame.bmp", 140+5, 21+10, true, RGB(184, 248, 168));
	//_frame10 = RectMakeCenter(180, WINSIZEY- 70, 13 * 3, 20 * 3);
	//_frame1 = RectMakeCenter(210, WINSIZEY - 70, 13 * 3, 20 * 3);

	//이름
	S = IMAGE->addFrameImage("S", "images/S.bmp", WINSIZEX + 100, WINSIZEY / 2, 17 * 3, 14 * 3, 1, 1, true, RGB(255, 0, 255));
	M = IMAGE->addFrameImage("M", "images/M.bmp", WINSIZEX + 100, WINSIZEY / 2, 17 * 3, 14 * 3, 1, 1, true, RGB(255, 0, 255));
	o = IMAGE->addFrameImage("o", "images/o.bmp", WINSIZEX + 100, WINSIZEY / 2, 17 * 3, 14 * 3, 1, 1, true, RGB(255, 0, 255));
	n = IMAGE->addFrameImage("n", "images/n.bmp", WINSIZEX + 100, WINSIZEY / 2, 17 * 3, 14 * 3, 1, 1, true, RGB(255, 0, 255));
	dot = IMAGE->addFrameImage("dot", "images/dot.bmp", WINSIZEX + 100, WINSIZEY / 2, 8 * 3, 8 * 3, 1, 1, true, RGB(255, 0, 255));

	//드롭아이템
	dropItem1 = IMAGE->addFrameImage("item1", "images/item1.bmp", WINSIZEX + 100, WINSIZEY / 2, 16 * 3, 28 * 3, 1, 1, true, RGB(255, 0, 255));
	item_existence = false;
	itemCollision = false;
	prevItemCollision = itemCollision;

	//이펙트
	_effect1 = IMAGE->addFrameImage("effect1", "images/effect/effect.bmp", WINSIZEX + 100, WINSIZEY / 2, 670 * 3, 67 * 3, 10, 1, true, RGB(255, 0, 255));
	effect1_index = 0;
	effect1_frameCount = 0;

	_effect2 = IMAGE->addFrameImage("effect2", "images/damage/damage.bmp", WINSIZEX + 100, WINSIZEY / 2, 1680 * 3, 92 * 3, 12, 1, true, RGB(0, 128, 0));
	effect2_index = 0;

	//_effect2 = IMAGE->addFrameImage("effect2", "images/effect/effect.bmp", WINSIZEX + 100, WINSIZEY / 2, 670 * 3, 67 * 3, 10, 1, true, RGB(255, 0, 255));
	//effect2_index = 0;

	//인벤토리
	inven1 = RectMakeCenter(WINSIZEX / 2 + 300 - 20, 50, 50, 50);
	inven2 = RectMakeCenter(WINSIZEX / 2 + 360 - 20, 50, 50, 50);
	inven3 = RectMakeCenter(WINSIZEX / 2 + 420 - 20, 50, 50, 50);
	inven4 = RectMakeCenter(WINSIZEX / 2 + 480 - 20, 50, 50, 50);

	//IMAGE->addImage("Green_Gel","images/store/green.bmp",25 + 20,34 + 20,true,RGB(127,127,127));
	//IMAGE->addImage("Lemon_Gel", "images/store/yellow.bmp", 25 + 20, 34 + 20, true, RGB(127, 127, 127));
	//IMAGE->addImage("Oberol_Gold", "images/store/G.bmp", 25 + 20, 34 + 20, true, RGB(127, 127, 127));
	//IMAGE->addImage("Life_Bottle", "images/store/blue.bmp", 25 + 20, 34 + 20, true, RGB(127, 127, 127));

	IMAGE->addImage("Green_Gel", "images/itemList/Green_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Green_Gel_icon", "images/itemList/Green_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Elixir", "images/itemList/Elixir.bmp", 226, 62, true, RGB(48, 120, 128));
	IMAGE->addImage("Elixir_icon", "images/itemList/Elixir_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Lemon_Gel", "images/itemList/Lemon_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Lemon_Gel_icon", "images/itemList/Lemon_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Life_Bottle", "images/itemList/Life_Bottle.bmp", 233, 65, true, RGB(48, 120, 128));
	IMAGE->addImage("Life_Bottle_icon", "images/itemList/Life_Bottle_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Melange_Gel", "images/itemList/Melange_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Melange_Gel_icon", "images/itemList/Melange_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Miracle_Gel", "images/itemList/Miracle_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Miracle_Gel_icon", "images/itemList/Miracle_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Oberol_Gold", "images/itemList/Oberol_Gold.bmp", 233, 65, true, RGB(48, 120, 128));
	IMAGE->addImage("Oberol_Gold_icon", "images/itemList/Oberol_Gold_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Orange_Gel", "images/itemList/Orange_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Orange_Gel_icon", "images/itemList/Orange_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));
	IMAGE->addImage("Pine_Gel", "images/itemList/Pine_Gel.bmp", 233, 54, true, RGB(48, 120, 128));
	IMAGE->addImage("Pine_Gel_icon", "images/itemList/Pine_Gel_icon.bmp", 33, 35, true, RGB(48, 120, 128));



	//int id_increase = 0;//id 넘버를 증가시키기 위한 변수. 

	/*for (size_t i = 0; i < 4; i++)
	{
		Item item;
		item.id = ++id_increase;
		item.number = 0;
		item.pos = 0;
		item.empty = true;
		item.selected = false;

		_vItem.push_back(item);
	}*/

	Item2 item1;
	item1.id = 1;
	item1.number = 0;
	item1.pos = 0;
	item1.empty = true;
	item1.selected = false;

	Item2 item2;
	item2.id = 2;
	item2.number = 0;
	item2.pos = 0;
	item2.empty = true;
	item2.selected = false;

	Item2 item3;
	item3.id = 3;
	item3.number = 0;
	item3.pos = 0;
	item3.empty = true;
	item3.selected = false;

	Item2 item4;
	item4.id = 4;
	item4.number = 0;
	item4.pos = 0;
	item4.empty = true;
	item4.selected = false;

	_vItem.push_back(item1);
	_vItem.push_back(item2);
	_vItem.push_back(item3);
	_vItem.push_back(item4);

	for (size_t i = 0; i < 9; i++)
	{
		Item2 _item;
		_item.id = i + 1;
		_item.number = 0;
		_item.pos = 0;
		_item.empty = true;
		_item.selected = false;

		_vInventory.push_back(_item);
	}

	//인벤토리 윈도우.
	//inventoryWindow_RC = RectMakeCenter(700, 265, 200, 250);
	inventoryDisable = true;

	//스킬키
	IMAGE->addImage("c_skill", "images/bullet3/icon.bmp", 50, 50, true, RGB(127, 127, 127));
	IMAGE->addImage("v_skill", "images/bullet/icon.bmp", 50, 50, true, RGB(127, 127, 127));
	IMAGE->addImage("a_skill", "images/bullet2/icon.bmp", 50, 50, true, RGB(127, 127, 127));
	skill_c = RectMakeCenter(900, 700, 50, 50);
	skill_v = RectMakeCenter(960, 700, 50, 50);
	skill_a = RectMakeCenter(1020, 700, 50, 50);

	miniMapDisable = true;
	questWindowDisable = false;

	//펫
	_pet = IMAGE->addFrameImage("pet", "images/pet/pet.bmp", 216 * 2, 88 * 2, 4, 2, true, RGB(255, 255, 255));
	IMAGE->addImage("pet_icon", "images/pet/pet_icon.bmp", 50, 50, true, RGB(255, 255, 255));
	pet_existence = false;
	pet_count = 0;
	pet_index = 0;
	cashShopDisable = true;

	revive = false;

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
	//플레이어 조작.
	if (!isPlayerDie)
	{
		if (InputManager->isStayKeyDown(VK_LEFT) && player1_x - _player->getFrameWidth() / 2 > 0 && currentState != State2::JUMP)
		{
			currentState = State2::WALK_LEFT;
			_player = IMAGE->findImage("세일러문");
			prevState = currentState;

			if (player1_x >= WINSIZEX / 2)
			{
				player1_x -= 5;

				if (pet_existence) pet_x = player1_x + 20;
			}
			else if (m_camera < 0)
			{
				m_camera += 5;

				if (item_existence == true) item_x += 5;

			}
			else {
				player1_x -= 5;

				if (pet_existence) pet_x = player1_x + 20;
			}
		}
		else if (InputManager->isStayKeyDown(VK_RIGHT) && player1_x + _player->getFrameWidth() / 2 < WINSIZEX && currentState != State2::JUMP)
		{
			currentState = State2::WALK_RIGHT;
			_player = IMAGE->findImage("세일러문");
			prevState = currentState;

			if (player1_x <= WINSIZEX / 2)
			{
				player1_x += 5;

				if (pet_existence) pet_x = player1_x - 20;
			}
			else if (m_camera > -WINSIZEX)
			{
				m_camera -= 5;
				if (item_existence == true) item_x -= 5;

			}
			else {
				player1_x += 5;

				if (pet_existence) pet_x = player1_x - 20;
			}
		}
		if (InputManager->isOnceKeyUp(VK_LEFT) && currentState != State2::JUMP) currentState = State2::IDLE_LEFT;
		if (InputManager->isOnceKeyUp(VK_RIGHT) && currentState != State2::JUMP) currentState = State2::IDLE_RIGHT;

		if (InputManager->isOnceKeyDown(VK_UP))
		{
			currentState = State2::JUMP;
			_player = IMAGE->findImage("캐릭터1_점프");

			if (prevState == State2::WALK_RIGHT ||
				prevState == State2::IDLE_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT ||
				prevState == State2::IDLE_LEFT) m_index = 11;
		}

		else if (InputManager->isOnceKeyDown('Z') && currentState != State2::JUMP)//캐릭터1_공격1.
		{
			currentState = State2::ATTACK1;
			_player = IMAGE->findImage("캐릭터1_공격1");

			if (prevState == State2::WALK_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT) m_index = 4;
		}

		else if (InputManager->isOnceKeyDown('X') && currentState != State2::JUMP)//캐릭터1_공격2.
		{
			currentState = State2::ATTACK2;
			_player = IMAGE->findImage("캐릭터1_공격2");

			if (prevState == State2::WALK_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT) m_index = 4;
		}

		else if (InputManager->isOnceKeyDown('C') && currentState != State2::JUMP
			&& (playerMP_Front.left + 10 <= playerMP_Back.right))//캐릭터1_공격3.
		{
			currentState = State2::ATTACK3;
			_player = IMAGE->findImage("캐릭터1_공격3");

			if (prevState == State2::WALK_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT) m_index = 5;

			playerMP_Front.left += 10;
			if (playerMP_Front.left >= playerMP_Back.right) playerMP_Front.left = playerMP_Back.right;
		}

		else if (InputManager->isOnceKeyDown('V') && currentState != State2::JUMP
			&& (playerMP_Front.left + 20 <= playerMP_Back.right))//캐릭터1_공격4.
		{
			currentState = State2::ATTACK4;
			_player = IMAGE->findImage("캐릭터1_공격4");

			if (prevState == State2::WALK_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT) m_index = 5;

			playerMP_Front.left += 20;
			if (playerMP_Front.left >= playerMP_Back.right) playerMP_Front.left = playerMP_Back.right;
		}

		else if (InputManager->isOnceKeyDown('A') && currentState != State2::JUMP
			&& (playerMP_Front.left + 50 <= playerMP_Back.right))//캐릭터1_공격5.
		{
			currentState = State2::ATTACK5;
			_player = IMAGE->findImage("캐릭터1_공격5");

			if (prevState == State2::WALK_RIGHT) m_index = 0;
			else if (prevState == State2::WALK_LEFT) m_index = 6;

			playerMP_Front.left += 50;
			if (playerMP_Front.left >= playerMP_Back.right) playerMP_Front.left = playerMP_Back.right;
		}
	}

	//몬스터 충돌 시간.
	if (!monster_collision) startTime = TIME->getWorldTime();

	//총알 
	_viBullet1 = _vBullet1.begin();
	for (_viBullet1; _viBullet1 != _vBullet1.end(); ++_viBullet1)
	{
		if (!(*_viBullet1)._existence)//불렛1
		{
			(*_viBullet1)._x = player1_x;
			(*_viBullet1)._y = player1_y;
		}
	}

	//불렛1
	_viBullet1 = _vBullet1.begin();
	for (_viBullet1; _viBullet1 != _vBullet1.end(); ++_viBullet1)
	{

		if ((*_viBullet1)._existence)
		{
			(*_viBullet1)._y = player1_y;

			if ((*_viBullet1).isLeft) (*_viBullet1)._x -= 5;
			else (*_viBullet1)._x += 5;

			if ((*_viBullet1)._x > WINSIZEX || (*_viBullet1)._x < 0)(*_viBullet1)._existence = false;

			(*_viBullet1)._rc = RectMakeCenter((*_viBullet1)._x, (*_viBullet1)._y, (*_viBullet1)._image->getWidth(), (*_viBullet1)._image->getHeight());

			//불렛 충돌.
			if ((*_viBullet1).isLeft)//플레이어가 왼쪽을 바라보며 공격.
			{
				if ((*_viBullet1)._x - 200 < monster_x && monster_x < player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet1)._collision = true;
					effect2_index = 0;

					monster_collision = true;

					(*_viBullet1)._existence = false;
					m_gaugeFront.top += 20;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}
			else//플레이어가 오른쪽을 바라보며 공격.
			{
				if ((*_viBullet1)._x - 50 > monster_x && monster_x > player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet1)._collision = true;
					effect2_index = 0;

					monster_collision = true;

					(*_viBullet1)._existence = false;
					m_gaugeFront.top += 20;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}

		}
	}

	//불렛2

	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if (!(*_viBullet2)._existence)//불렛2
		{
			if ((*_viBullet2).isLeft) (*_viBullet2)._x = player1_x;
			(*_viBullet2)._y = player1_y;
		}
	}

	_viBullet2 = _vBullet2.begin();
	for (_viBullet2; _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{

		if ((*_viBullet2)._existence)
		{
			(*_viBullet2)._y = player1_y;

			if ((*_viBullet2).isLeft) (*_viBullet2)._x -= 5;
			else (*_viBullet2)._x += 5;

			if ((*_viBullet2)._x > WINSIZEX || (*_viBullet2)._x < 0)(*_viBullet2)._existence = false; //영역밖 false.

			(*_viBullet2)._rc = RectMakeCenter((*_viBullet2)._x, (*_viBullet2)._y, (*_viBullet2)._image->getWidth(), (*_viBullet2)._image->getHeight());


			//불렛 충돌.
			if ((*_viBullet2).isLeft)//플레이어가 왼쪽을 바라보며 공격.
			{
				if ((*_viBullet2)._x - 160 < monster_x && monster_x < player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet2)._collision = true;
					monster_collision = true;
					effect2_index = 0;

					(*_viBullet2)._existence = false;
					m_gaugeFront.top += 100;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}
			else//플레이어가 오른쪽을 바라보며 공격.
			{
				if ((*_viBullet2)._x > monster_x && monster_x > player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet2)._collision = true;
					monster_collision = true;
					effect2_index = 0;

					(*_viBullet2)._existence = false;
					m_gaugeFront.top += 100;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}
		}
	}

	//불렛3

	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end(); ++_viBullet3)
	{
		if (!(*_viBullet3)._existence)//불렛2
		{
			if ((*_viBullet3).isLeft) (*_viBullet3)._x = player1_x;
			(*_viBullet3)._y = player1_y;
		}
	}

	_viBullet3 = _vBullet3.begin();
	for (_viBullet3; _viBullet3 != _vBullet3.end(); ++_viBullet3)
	{

		if ((*_viBullet3)._existence)
		{
			(*_viBullet3)._y = player1_y;

			if ((*_viBullet3).isLeft) (*_viBullet3)._x -= 5;
			else (*_viBullet3)._x += 5;

			if ((*_viBullet3)._x > WINSIZEX || (*_viBullet3)._x < 0)(*_viBullet3)._existence = false; //영역밖 false.

			(*_viBullet3)._rc = RectMakeCenter((*_viBullet3)._x, (*_viBullet3)._y, (*_viBullet3)._image->getWidth(), (*_viBullet3)._image->getHeight());


			//불렛 충돌.
			if ((*_viBullet3).isLeft)//플레이어가 왼쪽을 바라보며 공격.
			{
				if ((*_viBullet3)._x - 190 < monster_x && monster_x < player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet3)._collision = true;
					monster_collision = true;
					effect2_index = 0;

					(*_viBullet3)._existence = false;
					m_gaugeFront.top += 20;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}
			else//플레이어가 오른쪽을 바라보며 공격.
			{
				if ((*_viBullet3)._x - 50 > monster_x && monster_x > player1_x)
				{
					monsterState = monster2_State::DAMAGE;
					(*_viBullet3)._collision = true;
					monster_collision = true;
					effect2_index = 0;

					(*_viBullet3)._existence = false;
					m_gaugeFront.top += 20;
					expFront.right += 10;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;
					}
				}
			}
		}
	}

	if (monster_collision) endTime = TIME->getWorldTime();

	if (endTime - startTime > 0.5)
	{
		monster_collision = false;
		monsterState = monster2_State::WALK;
	}


	//몬스터 조작.
	if (isPlayerDie)monsterState = monster2_State::WALK;

	if (!isMonsterDie && !isPlayerDie)
	{
		static int monster_term = 0;
		monster_term++;

		if (monster_term > 5)
		{
			if (monster_isLeft)
			{
				_monster = IMAGE->findImage("Garoben_Walk");
				//_monster->setFrameY(1);
				if (monster_x - _monster->getFrameWidth() / 2 > -150) monster_x -= 10;
				else monster_isLeft = false;
			}
			else
			{
				_monster = IMAGE->findImage("Garoben_Walk");
				//_monster->setFrameY(0);
				if (monster_x + _monster->getFrameWidth() / 2 < WINSIZEX - 100) monster_x += 10;
				else monster_isLeft = true;
			}
			monster_term = 0;
		}

		//몬스터 게이지.
		static int count = 0;
		count++;

		if (count > 10)
		{
			RECT temp;
			//플레이어 공격에 맞았을때.
			if ((currentState == State2::ATTACK1 || currentState == State2::ATTACK2) && IntersectRect(&temp, &_playerRC, &_monsterRC))
			{
				if (monsterState != monster2_State::DAMAGE)
				{
					m_gaugeFront.top += 30;
					playerScore += 20;
					if (m_gaugeFront.top >= m_gaugeFront.bottom)
					{
						m_gaugeFront.top = m_gaugeBack.bottom;
						isMonsterDie = true;//몬스터가 죽음.
					}
					expFront.right += 100;
					if (expFront.right >= expBack.right)
					{
						//expFront.right = expBack.right;
						level++;
						expFront.right = expBack.left;

					}
				}
				monsterState = monster2_State::DAMAGE;
				effect1_index++;
			}
			else if (IntersectRect(&temp, &_playerRC, &_monsterRC))
				monsterState = monster2_State::ATTACK;
			else if (monster_collision) monsterState = monster2_State::DAMAGE;
			else monsterState = monster2_State::WALK;
			count = 0;
		}
	}

	if (isMonsterDie)
	{
		monster_x = WINSIZEX + 100;

	}

	//프레임 관리

	//몬스터.
	switch (monsterState)
	{
	case monster2_State::WALK:
		monster_count++;
		

		if (monster_isLeft)
		{
			_monster->setFrameY(1);

			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index--;

				if (monster_index < 0)
				{
					monster_index = 6;
				}
				_monster->setFrameX(monster_index);
			}
			break;
		}
		else
		{
			_monster->setFrameY(0);

			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index++;

				if (monster_index >= 7)
				{
					monster_index = 0;
				}
				_monster->setFrameX(monster_index);
			}
			break;
		}

	case monster2_State::DAMAGE:
		monster_count++;
		

		if (player1_x - 100 < monster_x)//플레이어가 왼쪽에서 공격
		{
			_monster->setFrameY(1);

			monster_isLeft = true;
			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index--;

				if (monster_index < 0)
				{
					//	monster_index = 3;
				}
				_monster->setFrameX(0);
				//_monster->setFrameX(monster_index);
			}
			break;
		}
		else
		{
			_monster->setFrameY(0);

			monster_isLeft = false;
			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index++;

				if (monster_index >= 4)
				{
					//monster_index = 0;
				}
				_monster->setFrameX(0);
				//_monster->setFrameX(monster_index);
			}
			break;
		}
	case monster2_State::ATTACK:
		monster_count++;
		

		if (player1_x - 100 < monster_x)//플레이어가 왼쪽에 있음.
		{
			_monster->setFrameY(1);
			//monster_isLeft = true;
			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index--;

				if (monster_index == 1)
				{
					if (currentState == State2::JUMP)
					{
						player1_x = WINSIZEX / 2;
						player1_y = WINSIZEY / 2;
					}

					if (currentState != State2::DAMAGE1)
					{
						playerHP_Front.left += 20;
						if (playerHP_Front.left >= playerHP_Front.right)
						{
							playerHP_Front.left = playerHP_Back.right;
							isPlayerDie = true;
							player1_x = 0;
						}
					}
					currentState = State2::DAMAGE1;
				}

				if (monster_index < 0)
				{
					monster_index = 3;
				}
				_monster->setFrameX(monster_index);
			}
			break;

		}
		else if (player1_x - 100 > monster_x)
		{
			_monster->setFrameY(0);
			//monster_isLeft = false;
			if (monster_count % 7 == 0)
			{
				monster_count = 0;
				monster_index++;

				if (monster_index == 4)
				{
					if (currentState == State2::JUMP)
					{
						player1_x = WINSIZEX / 2;
						player1_y = WINSIZEY / 2;
					}

					if (currentState != State2::DAMAGE1)
					{
						playerHP_Front.left += 20;
						if (playerHP_Front.left >= playerHP_Front.right)
						{
							playerHP_Front.left = playerHP_Back.right;
							isPlayerDie = true;
						}
					}
					currentState = State2::DAMAGE1;
				}

				if (monster_index >= 4)
				{
					monster_index = 0;
				}
				_monster->setFrameX(monster_index);
			}
			break;
		}
	}

	//플레이어 프레임.
	switch (currentState)
	{
	case State2::IDLE_LEFT:
		_player = IMAGE->findImage("캐릭터1_기본");
		_player->setFrameY(0);
		_player->setFrameX(1);
		break;

	case State2::IDLE_RIGHT:
		_player = IMAGE->findImage("캐릭터1_기본");
		_player->setFrameY(0);
		_player->setFrameX(0);
		break;

	case State2::WALK_LEFT:
		_player = IMAGE->findImage("세일러문");

		m_count++;
		_player->setFrameY(1);

		if (m_count % 5 == 0)
		{
			m_count = 0;
			m_index--;
			if (m_index < _player->getMaxFrameY())
			{
				m_index = 10;
			}
			_player->setFrameX(m_index);
		}
		break;

	case State2::WALK_RIGHT:
		_player = IMAGE->findImage("세일러문");

		m_count++;
		_player->setFrameY(0);

		if (m_count % 5 == 0)
		{
			m_count = 0;
			m_index++;

			if (m_index >= _player->getMaxFrameX())
			{
				m_index = 0;
			}
			_player->setFrameX(m_index);
		}
		break;

	case State2::JUMP:

		m_count++;
		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 5 == 0)
			{
				m_count = 0;

				m_index++;

				if (m_index >= 0 && m_index < 5)player1_y -= 50;
				else if (m_index >= 5 && m_index < 9)player1_y += 50;

				if (m_index > 11) currentState = State2::IDLE_RIGHT;
				else _player->setFrameX(m_index);

			}
		}

		else
		{
			_player->setFrameY(1);

			if (m_count % 5 == 0)
			{
				m_count = 0;

				m_index--;

				if (m_index <= 10 && m_index > 5)player1_y -= 50;
				else if (m_index <= 5 && m_index >= 1)player1_y += 50;

				if (m_index < 0)
				{
					currentState = State2::IDLE_LEFT;
				}
				else _player->setFrameX(m_index);

			}
		}
		break;

	case State2::ATTACK1:                                 //캐릭터 공격.

		m_count++;

		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index++;
				if (m_index >= 4)
				{
					m_index = 0;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(m_index);
			}
		}
		else
		{
			_player->setFrameY(1);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index--;
				if (m_index < 0)
				{
					m_index = 3;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(m_index);
			}
		}
		break;

	case State2::ATTACK2:
		m_count++;
		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index++;
				if (m_index >= 4)
				{
					m_index = 3;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(m_index);
			}
		}
		else
		{
			_player->setFrameY(1);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index--;
				if (m_index <= 0)
				{
					m_index = 0;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(m_index);
			}
		}
		break;

	case State2::ATTACK3:
		m_count++;
		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index++;

				if (m_index == 5)
				{
					for (_viBullet3 = _vBullet3.begin(); _viBullet3 != _vBullet3.end(); ++_viBullet3)
					{
						if (!(*_viBullet3)._existence)
						{
							(*_viBullet3)._existence = true;
							(*_viBullet3)._collision = false;
							(*_viBullet3).isLeft = false;
							(*_viBullet3)._x = player1_x + 50;
							break;
						}
					}
				}

				if (m_index >= 5)
				{
					m_index = 4;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(m_index);
			}
		}
		else
		{
			_player->setFrameY(1);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index--;
				if (m_index == 0)
				{
					for (_viBullet3 = _vBullet3.begin(); _viBullet3 != _vBullet3.end(); ++_viBullet3)
					{
						if (!(*_viBullet3)._existence)
						{
							(*_viBullet3)._existence = true;
							(*_viBullet3)._collision = false;
							(*_viBullet3).isLeft = true;
							(*_viBullet3)._x = player1_x - 50;
							break;
						}
					}
				}
				if (m_index <= 0)
				{
					m_index = 0;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(m_index);
			}
		}
		break;

	case State2::ATTACK4:
		m_count++;
		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 7 == 0)
			{
				m_count = 0;
				m_index++;

				if (m_index == 4)
				{
					for (_viBullet1 = _vBullet1.begin(); _viBullet1 != _vBullet1.end(); ++_viBullet1)
					{
						if (!(*_viBullet1)._existence)
						{
							(*_viBullet1)._existence = true;
							(*_viBullet1)._collision = false;
							(*_viBullet1).isLeft = false;
							break;
						}
					}
				}

				if (m_index >= 5)
				{
					m_index = 4;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(m_index);
			}
		}
		else
		{
			_player->setFrameY(1);

			if (m_count % 7 == 0)
			{
				m_count = 0;

				m_index--;

				if (m_index == 1)
				{
					for (_viBullet1 = _vBullet1.begin(); _viBullet1 != _vBullet1.end(); ++_viBullet1)
					{
						if (!(*_viBullet1)._existence)
						{
							(*_viBullet1)._existence = true;
							(*_viBullet1)._collision = false;
							(*_viBullet1).isLeft = true;
							break;
						}
					}
				}

				if (m_index <= 0)
				{
					m_index = 0;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(m_index);
			}
		}
		break;

	case State2::ATTACK5:
		m_count++;
		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 8 == 0)
			{
				m_count = 0;

				m_index++;
				if (m_index == 4)
				{
					for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); ++_viBullet2)
					{
						if (!(*_viBullet2)._existence)
						{
							(*_viBullet2)._existence = true;
							(*_viBullet2)._collision = false;
							(*_viBullet2).isLeft = false;
							(*_viBullet2)._x = player1_x + 50;
							break;
						}
					}
				}

				if (m_index >= 6)
				{
					m_index = 0;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(m_index);
			}
		}
		else//왼쪽을 바라볼때.
		{
			_player->setFrameY(1);

			if (m_count % 8 == 0)
			{
				m_count = 0;

				m_index--;
				if (m_index == 1)
				{
					for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); ++_viBullet2)
					{
						if (!(*_viBullet2)._existence)
						{
							(*_viBullet2)._existence = true;
							(*_viBullet2)._collision = false;
							(*_viBullet2).isLeft = true;
							(*_viBullet2)._x = player1_x - 120;
							break;
						}
					}
				}
				if (m_index <= 0)
				{
					m_index = 5;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(m_index);
			}
		}
		break;

	case State2::DAMAGE1:

		m_count++;

		if (prevState == State2::WALK_RIGHT)
		{
			_player->setFrameY(0);

			if (m_count % 5 == 0)
			{
				m_count = 0;

				m_index++;
				if (m_index >= 6)
				{
					m_index = 0;
					currentState = State2::IDLE_RIGHT;
				}
				_player->setFrameX(2);
				if (monsterState != monster2_State::ATTACK)currentState = State2::IDLE_RIGHT;
			}
		}
		else
		{
			_player->setFrameY(1);

			if (m_count % 5 == 0)
			{
				m_count = 0;

				m_index--;
				if (m_index < 0)
				{
					m_index = 5;
					currentState = State2::IDLE_LEFT;
				}
				_player->setFrameX(3);
				if (monsterState != monster2_State::ATTACK)currentState = State2::IDLE_LEFT;
			}
		}
		break;
	}

	//펫 프레임.
	if (pet_existence)
	{
		switch (currentState)
		{
		case State2::WALK_RIGHT:
			pet_count++;
			_pet->setFrameY(0);


			if (pet_count % 7 == 0)
			{
				pet_count = 0;
				pet_index++;

				if (pet_index > 3)
				{
					pet_index = 0;
				}
				_pet->setFrameX(pet_index);
			}
			break;

		case State2::WALK_LEFT:
			pet_count++;
			_pet->setFrameY(1);

			if (pet_count % 7 == 0)
			{
				pet_count = 0;
				pet_index++;

				if (pet_index >= 5)
				{
					pet_index = 0;
				}
				_pet->setFrameX(pet_index);
			}
			break;
		}
	}



	//캐릭터_데미지1.
	if (currentState == State2::DAMAGE1)
	{
		currentState = State2::DAMAGE1;
		_player = IMAGE->findImage("캐릭터1_데미지1");

		if (prevState == State2::WALK_RIGHT) m_index = 0;
		else if (prevState == State2::WALK_LEFT) m_index = 4;
	}

	//불렛
	for (_viBullet1 = _vBullet1.begin(); _viBullet1 != _vBullet1.end(); ++_viBullet1)//불렛1
	{
		(*_viBullet1)._count++;
		(*_viBullet1)._image->setFrameY(0);

		if ((*_viBullet1)._count % 7 == 0)
		{
			(*_viBullet1)._count = 0;
			(*_viBullet1)._index++;

			if ((*_viBullet1)._index >= 10)
			{
				(*_viBullet1)._index = 0;
			}
			(*_viBullet1)._image->setFrameX((*_viBullet1)._index);
		}
	}

	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); ++_viBullet2)//불렛2
	{
		(*_viBullet2)._count++;
		if ((*_viBullet2).isLeft)
		{
			//(*_viBullet2)._image->setFrameY(1);

			if ((*_viBullet2)._count % 7 == 0)
			{
				(*_viBullet2)._count = 0;
				(*_viBullet2)._index--;

				if ((*_viBullet2)._index < 0)
				{
					(*_viBullet2)._index = 5;
				}
				(*_viBullet2)._image->setFrameX((*_viBullet2)._index);
			}
		}
		else
		{
			//(*_viBullet2)._image->setFrameY(1);

			if ((*_viBullet2)._count % 7 == 0)
			{
				(*_viBullet2)._count = 0;
				(*_viBullet2)._index++;

				if ((*_viBullet2)._index >= 6)
				{
					(*_viBullet2)._index = 0;
				}
				(*_viBullet2)._image->setFrameX((*_viBullet2)._index);
			}
		}
	}

	for (_viBullet3 = _vBullet3.begin(); _viBullet3 != _vBullet3.end(); ++_viBullet3)//불렛3
	{
		(*_viBullet3)._count++;
		if ((*_viBullet3).isLeft)
		{
			//(*_viBullet2)._image->setFrameY(1);

			if ((*_viBullet3)._count % 7 == 0)
			{
				(*_viBullet3)._count = 0;
				(*_viBullet3)._index--;

				if ((*_viBullet3)._index < 0)
				{
					(*_viBullet3)._index = 6;
				}
				(*_viBullet3)._image->setFrameX((*_viBullet3)._index);
			}
		}
		else
		{
			//(*_viBullet2)._image->setFrameY(1);

			if ((*_viBullet3)._count % 7 == 0)
			{
				(*_viBullet3)._count = 0;
				(*_viBullet3)._index++;

				if ((*_viBullet3)._index >= 7)
				{
					(*_viBullet3)._index = 0;
				}
				(*_viBullet3)._image->setFrameX((*_viBullet3)._index);
			}
		}
	}

	//이펙트

	for (_viBullet1 = _vBullet1.begin(); _viBullet1 != _vBullet1.end(); ++_viBullet1)
	{
		if ((*_viBullet1)._collision) effect2_index++;
		if (effect2_index >= 12) (*_viBullet1)._collision = false;
	}

	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); ++_viBullet2)
	{
		if ((*_viBullet2)._collision) effect2_index++;
		if (effect2_index >= 12) (*_viBullet2)._collision = false;
	}

	for (_viBullet3 = _vBullet3.begin(); _viBullet3 != _vBullet3.end(); ++_viBullet3)
	{
		if ((*_viBullet3)._collision) effect2_index++;
		if (effect2_index >= 12) (*_viBullet3)._collision = false;
	}

	_effect1->setFrameY(0);
	if (effect1_index >= 10) effect1_index = 0;
	_effect1->setFrameX(effect1_index);

	_effect2->setFrameY(0);
	if (effect2_index < 12) _effect2->setFrameX(effect2_index);


	//캐릭터 상태창.
	_playerState->setFrameX(0);
	_playerState->setFrameY(0);
	//몬스터 상태창.
	_monsterState->setFrameX(0);
	_monsterState->setFrameY(0);


	//영역확인.
	_playerRC = RectMakeCenter(player1_x + _player->getFrameWidth() / 2, player1_y + _player->getHeight() / 2
		, _player->getFrameWidth(), _player->getHeight());
	_monsterRC = RectMakeCenter(monster_x + _monster->getFrameWidth() / 2, monster_y + _monster->getHeight() / 2,
		_monster->getFrameWidth() - 100, _monster->getHeight());

	//드롭아이템
	if (item_existence == false && itemCollision == false && !isMonsterDie)
		item_x = monster_x + 150;


	if (item_existence && item_x > player1_x && item_x - player1_x - 60 < 2) //드롭아이템이 오른쪽.
	{
		itemCollision = true;
		//item_x = monster_x + 150;
	}
	else if (item_existence && item_x <= player1_x && player1_x - item_x < 2)
	{
		itemCollision = true;
		//item_x = monster_x + 150;
	}

	if (itemCollision && !prevItemCollision)//드롭아이템 먹음.
	{
		playerScore += 100;
		prevItemCollision = itemCollision;
		item_x = 0;
	}

	_itemRC = RectMakeCenter(item_x, monster_y + 140 + dropItem1->getHeight() / 2, dropItem1->getWidth(), dropItem1->getHeight());

	//인벤토리 구현.
	ItemUpdate();

	//아이템 먹기

	if (InputManager->isOnceKeyDown('1'))
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).pos == 1)
			{
				if ((*_viInventory).id == 1)
				{
					playerHP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 2)
				{
					playerHP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 3)
				{
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 4)
				{
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 5)
				{
					playerHP_Front.left -= 50;
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 6)
				{
					playerHP_Front.left -= 100;
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 7)
				{
					playerHP_Front.left = playerHP_Back.left;
				}
				else if ((*_viInventory).id == 8)
				{
					playerHP_Front.left = playerHP_Back.left;
					playerMP_Front.left = playerMP_Back.left;
				}
				else if ((*_viInventory).id == 9)
				{
					revive = true;
				}
				(*_viInventory).number -= 1;
				break;
			}
		}
	}

	if (InputManager->isOnceKeyDown('2'))
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).pos == 2)
			{
				if ((*_viInventory).id == 1)
				{
					playerHP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 2)
				{
					playerHP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 3)
				{
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 4)
				{
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 5)
				{
					playerHP_Front.left -= 50;
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 6)
				{
					playerHP_Front.left -= 100;
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 7)
				{
					playerHP_Front.left = playerHP_Back.left;
				}
				else if ((*_viInventory).id == 8)
				{
					playerHP_Front.left = playerHP_Back.left;
					playerMP_Front.left = playerMP_Back.left;
				}
				else if ((*_viInventory).id == 9)
				{
					revive = true;
				}
				(*_viInventory).number -= 1;
				break;
			}
		}
	}


	if (InputManager->isOnceKeyDown('3'))
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).pos == 3)
			{
				if ((*_viInventory).id == 1)
				{
					playerHP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 2)
				{
					playerHP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 3)
				{
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 4)
				{
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 5)
				{
					playerHP_Front.left -= 50;
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 6)
				{
					playerHP_Front.left -= 100;
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 7)
				{
					playerHP_Front.left = playerHP_Back.left;
				}
				else if ((*_viInventory).id == 8)
				{
					playerHP_Front.left = playerHP_Back.left;
					playerMP_Front.left = playerMP_Back.left;
				}
				else if ((*_viInventory).id == 9)
				{
					revive = true;
				}
				(*_viInventory).number -= 1;
				break;
			}
		}
	}


	if (InputManager->isOnceKeyDown('4'))
	{
		for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
		{
			if ((*_viInventory).pos == 4)
			{
				if ((*_viInventory).id == 1)
				{
					playerHP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 2)
				{
					playerHP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 3)
				{
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 4)
				{
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 5)
				{
					playerHP_Front.left -= 50;
					playerMP_Front.left -= 50;
				}
				else if ((*_viInventory).id == 6)
				{
					playerHP_Front.left -= 100;
					playerMP_Front.left -= 100;
				}
				else if ((*_viInventory).id == 7)
				{
					playerHP_Front.left = playerHP_Back.left;
				}
				else if ((*_viInventory).id == 8)
				{
					playerHP_Front.left = playerHP_Back.left;
					playerMP_Front.left = playerMP_Back.left;
				}
				else if ((*_viInventory).id == 9)
				{
					revive = true;
				}
				(*_viInventory).number -= 1;
				break;
			}
		}
	}


	if (playerHP_Front.left < playerHP_Back.left)playerHP_Front.left = playerHP_Back.left;
	if (playerMP_Front.left < playerMP_Back.left)playerMP_Front.left = playerMP_Back.left;

	if (revive)//부활
	{
		playerHP_Front.left = playerHP_Back.left;
		playerMP_Front.left = playerMP_Back.left;

		isPlayerDie = false;
		revive = false;
	}

	//아이템창
	if (InputManager->isOnceKeyUp('I'))	inventoryDisable = !inventoryDisable;

	//미니맵
	if (InputManager->isOnceKeyUp('W'))	miniMapDisable = !miniMapDisable;

	//퀘스트창
	if (InputManager->isOnceKeyUp('E'))	questWindowDisable = !questWindowDisable;

	//캐시샵
	if (InputManager->isOnceKeyUp('R'))	cashShopDisable = !cashShopDisable;

}

void stage2::render()
{
	HPEN hpen;
	HPEN hpenOld;
	//IMAGE->render("배경화면", getMemDC(), m_camera, 0);
	//IMAGE->loopRender("배경화면", getMemDC(), &RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY), loopX, loopY);
	IMAGE->render("스테이지2배경화면", getMemDC(), m_camera, 0);

	//Rectangle(getMemDC(), _playerRC.left, _playerRC.top, _playerRC.right, _playerRC.bottom);
	//Rectangle(getMemDC(), _monsterRC.left, _monsterRC.top, _monsterRC.right, _monsterRC.bottom);

	//Rectangle(getMemDC(), _playerRC.left, _playerRC.top, _playerRC.right, _playerRC.bottom);
	//Rectangle(getMemDC(), _itemRC.left, _itemRC.top, _itemRC.right, _itemRC.bottom);

	//Rectangle(getMemDC(), _bullet1RC.left, _bullet1RC.top, _bullet1RC.right, _bullet1RC.bottom);
	//Rectangle(getMemDC(), _monsterRC.left, _monsterRC.top, _monsterRC.right, _monsterRC.bottom);
	if (!isMonsterDie)
	{
		switch (monsterState)
		{
		case monster2_State::WALK:
			if (monster_isLeft) IMAGE->frameRender("Garoben_Walk", getMemDC(), monster_x, monster_y - 50, _monster->getFrameX(), _monster->getFrameY());
			else IMAGE->frameRender("Garoben_Walk", getMemDC(), monster_x, monster_y - 50, _monster->getFrameX(), _monster->getFrameY());
			break;
		case monster2_State::DAMAGE:
			if (monster_isLeft) IMAGE->frameRender("Garoben_Damage", getMemDC(), monster_x, monster_y +30, _monster->getFrameX(), _monster->getFrameY());
			else IMAGE->frameRender("Garoben_Damage", getMemDC(), monster_x, monster_y +30, _monster->getFrameX(), _monster->getFrameY());

			IMAGE->frameRender("effect1", getMemDC(), monster_x + 40, monster_y + 50, _effect1->getFrameX() * 3, _effect1->getFrameY() * 3);
			break;
		case monster2_State::ATTACK:
			//if (player1_x - 100 < monster_x) IMAGE->frameRender("Bret_Attack_Left", getMemDC(), monster_x, monster_y - 100, _monster->getFrameX(), _monster->getFrameY());
			//else IMAGE->frameRender("Bret_Attack_Right", getMemDC(), monster_x, monster_y - 100, _monster->getFrameX(), _monster->getFrameY());

			if (player1_x - 100 < monster_x) IMAGE->frameRender("Garoben_Attack", getMemDC(), monster_x, monster_y - 80, _monster->getFrameX(), _monster->getFrameY());
			else IMAGE->frameRender("Garoben_Attack", getMemDC(), monster_x, monster_y - 80, _monster->getFrameX(), _monster->getFrameY());
			break;
		}
	}


	if (!isPlayerDie)
	{
		switch (currentState)
		{
		case State2::IDLE_LEFT:
			IMAGE->frameRender("캐릭터1_기본", getMemDC(), player1_x, player1_y, _player->getFrameX(), _player->getFrameY());

			break;
		case State2::IDLE_RIGHT:
			IMAGE->frameRender("캐릭터1_기본", getMemDC(), player1_x, player1_y, _player->getFrameX(), _player->getFrameY());

			break;
		case State2::ATTACK1:
			IMAGE->frameRender("캐릭터1_공격1", getMemDC(), player1_x, player1_y - 30, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::ATTACK2:
			IMAGE->frameRender("캐릭터1_공격2", getMemDC(), player1_x, player1_y, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::ATTACK3:
			IMAGE->frameRender("캐릭터1_공격3", getMemDC(), player1_x, player1_y - 50, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::ATTACK4:
			IMAGE->frameRender("캐릭터1_공격4", getMemDC(), player1_x, player1_y - 50, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::ATTACK5:
			IMAGE->frameRender("캐릭터1_공격5", getMemDC(), player1_x, player1_y - 50, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::JUMP:
			IMAGE->frameRender("캐릭터1_점프", getMemDC(), player1_x - 25, player1_y - 68, _player->getFrameX(), _player->getFrameY());
			break;
		case State2::WALK_LEFT:
		case State2::WALK_RIGHT:
			IMAGE->frameRender("세일러문", getMemDC(), player1_x, player1_y, _player->getFrameX(), _player->getFrameY());

			break;
		case State2::DAMAGE1:
			IMAGE->frameRender("캐릭터1_데미지1", getMemDC(), player1_x, player1_y, _player->getFrameX(), _player->getFrameY());
			break;
		}

		if (pet_existence)
			IMAGE->frameRender("pet", getMemDC(), pet_x, pet_y, _pet->getFrameX(), _pet->getFrameY());
	}

	//총알
	for (_viBullet1 = _vBullet1.begin(); _viBullet1 != _vBullet1.end(); ++_viBullet1) //총알1.
	{
		if ((*_viBullet1)._existence)
			IMAGE->frameRender("총알1", getMemDC(), (*_viBullet1)._x, (*_viBullet1)._y, (*_viBullet1)._image->getFrameX(), (*_viBullet1)._image->getFrameY());
		if ((*_viBullet1)._collision)
			IMAGE->frameRender("effect2", getMemDC(), monster_x, monster_y, _effect2->getFrameX(), _effect2->getFrameY());
	}
	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); ++_viBullet2) //총알2.
	{
		if ((*_viBullet2)._existence)
		{
			if ((*_viBullet2).isLeft)
			{
				(*_viBullet2)._image->setFrameY(1);
				IMAGE->frameRender("총알2", getMemDC(), (*_viBullet2)._x, (*_viBullet2)._y, (*_viBullet2)._image->getFrameX(), (*_viBullet2)._image->getFrameY());
			}
			else
			{
				(*_viBullet2)._image->setFrameY(0);
				IMAGE->frameRender("총알2", getMemDC(), (*_viBullet2)._x, (*_viBullet2)._y, (*_viBullet2)._image->getFrameX(), (*_viBullet2)._image->getFrameY());
			}
		}

		if ((*_viBullet2)._collision)
			IMAGE->frameRender("effect2", getMemDC(), monster_x, monster_y, _effect2->getFrameX(), _effect2->getFrameY());
	}

	for (_viBullet3 = _vBullet3.begin(); _viBullet3 != _vBullet3.end(); ++_viBullet3) //총알3.
	{
		if ((*_viBullet3)._existence)
		{
			if ((*_viBullet3).isLeft)
			{
				(*_viBullet3)._image->setFrameY(0);
				IMAGE->frameRender("총알3", getMemDC(), (*_viBullet3)._x, (*_viBullet3)._y + 50, (*_viBullet3)._image->getFrameX(), (*_viBullet3)._image->getFrameY());
			}
			else
			{
				(*_viBullet3)._image->setFrameY(1);
				IMAGE->frameRender("총알3", getMemDC(), (*_viBullet3)._x, (*_viBullet3)._y + 50, (*_viBullet3)._image->getFrameX(), (*_viBullet3)._image->getFrameY());

			}
		}

		if ((*_viBullet3)._collision)
			IMAGE->frameRender("effect2", getMemDC(), monster_x, monster_y, _effect2->getFrameX(), _effect2->getFrameY());
	}

	//플레이어 게이지
	//HP
	IMAGE->render("HP", getMemDC(), 110, 60);

	Rectangle(getMemDC(), playerHP_Back.left, playerHP_Back.top, playerHP_Back.right, playerHP_Back.bottom);

	HBRUSH brush = CreateSolidBrush(RGB(p_red, p_green, 0));
	Rectangle(getMemDC(), playerHP_Front.left, playerHP_Front.top, playerHP_Front.right, playerHP_Front.bottom);
	FillRect(getMemDC(), &playerHP_Front, brush);
	DeleteObject(brush);

	//MP
	IMAGE->render("MP", getMemDC(), 110, 100);

	Rectangle(getMemDC(), playerMP_Back.left, playerMP_Back.top, playerMP_Back.right, playerMP_Back.bottom);


	brush = CreateSolidBrush(RGB(0, 0, 255));
	Rectangle(getMemDC(), playerMP_Front.left, playerMP_Front.top, playerMP_Front.right, playerMP_Front.bottom);
	FillRect(getMemDC(), &playerMP_Front, brush);
	DeleteObject(brush);

	gaugeDraw();


	//EXP
	IMAGE->render("EXP", getMemDC(), 280, 685);


	//Lv
	IMAGE->render("Lv", getMemDC(), 20, levelRC.top + 13);
	//Rectangle(getMemDC(), levelRC.left, levelRC.top, levelRC.right, levelRC.bottom);

	Rectangle(getMemDC(), expBack.left, expBack.top, expBack.right, expBack.bottom);
	levelRender();


	brush = CreateSolidBrush(RGB(255, 255, 102));
	Rectangle(getMemDC(), expFront.left, expFront.top, expFront.right, expFront.bottom);
	FillRect(getMemDC(), &expFront, brush);
	DeleteObject(brush);


	//player_gaugeBack->render(getMemDC(),"gauge2", 100,100);

	//몬스터 게이지
	//m_gaugeFront = RectMakeCenter(WINSIZEX / 2 + 300, 100, 200, 20);
	//m_gaugeBack = RectMakeCenter(WINSIZEX / 2 + 300, 100, 200, 20);
	if (/*monsterState == monsterState::DAMAGE && */ !isMonsterDie)
	{
		IMAGE->frameRender("Garoben_icon", getMemDC(), m_gaugeBack.left - 45, m_gaugeBack.top - 8, _monsterState->getFrameX(), _monsterState->getFrameY());

		hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 선 스타일, 굵기, 색상 
		hpenOld = (HPEN)::SelectObject(getMemDC(), (HGDIOBJ)hpen); // 펜 선택 

		Rectangle(getMemDC(), m_gaugeBack.left, m_gaugeBack.top, m_gaugeBack.right, m_gaugeBack.bottom);

		hpen = (HPEN)::SelectObject(getMemDC(), hpenOld); // 기존의 펜 다시 선택 
		::DeleteObject(hpen); // 생성한 펜 삭제
		//m_gaugeBack = RectMake ( monster_x+100, m_gaugeBack.top, 20, m_gaugeBack.top - m_gaugeBack.bottom);
		//Rectangle(getMemDC(), m_gaugeBack.left, m_gaugeBack.top, m_gaugeBack.right, m_gaugeBack.bottom);

		brush = CreateSolidBrush(RGB(m_red, m_green, 0));
		Rectangle(getMemDC(), m_gaugeFront.left, m_gaugeFront.top, m_gaugeFront.right, m_gaugeFront.bottom);
		//m_gaugeFront = RectMake(monster_x+100, m_gaugeFront.top, 20,m_gaugeFront.top - m_gaugeFront.bottom);
		//Rectangle(getMemDC(), m_gaugeFront.left, m_gaugeBack.top, m_gaugeFront.right, m_gaugeBack.bottom);
		FillRect(getMemDC(), &m_gaugeFront, brush);
		DeleteObject(brush);
	}



	//캐릭터 상태창
	if (currentState == State2::DAMAGE1 || isPlayerDie) IMAGE->frameRender("캐릭터상태창_데미지", getMemDC(), 10, 10, _playerState->getFrameX(), _playerState->getFrameY());
	else if (isMonsterDie) IMAGE->frameRender("캐릭터상태창_승리", getMemDC(), 10, 10, _playerState->getFrameX(), _playerState->getFrameY());
	else IMAGE->frameRender("캐릭터상태창_노멀", getMemDC(), 10, 10, _playerState->getFrameX(), _playerState->getFrameY());

	//프레임

	//Rectangle(getMemDC(), _frame10.left, _frame10.top, _frame10.right, _frame10.bottom);
	//Rectangle(getMemDC(), _frame1.left, _frame1.top, _frame1.right, _frame1.bottom);
	frameRender();

	//이름
	IMAGE->frameRender("S", getMemDC(), 100, 10);
	IMAGE->frameRender("dot", getMemDC(), 140, 30);
	IMAGE->frameRender("M", getMemDC(), 160, 10);
	IMAGE->frameRender("o", getMemDC(), 200, 14);
	IMAGE->frameRender("o", getMemDC(), 230, 14);
	IMAGE->frameRender("n", getMemDC(), 270, 9);

	//타임
	IMAGE->render("TIME", getMemDC(), WINSIZEX / 2 - 100, 20);
	//Rectangle(getMemDC(), _time10.left, _time10.top, _time10.right, _time10.bottom);
	//Rectangle(getMemDC(), _time1.left, _time1.top, _time1.right, _time1.bottom);

	timeRender();

	//드롭아이템
	if (isMonsterDie && !itemCollision)
	{
		item_existence = true;
		IMAGE->frameRender("item1", getMemDC(), item_x, monster_y + 140);
	}
	else item_existence = false;

	scoreRender();


	//인벤토리
	TCHAR str[100];

	HFONT font, oldfont;
	//AddFontResource("images/font/OdBestFreind.ttf");
	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);



	Rectangle(getMemDC(), inven1.left, inven1.top, inven1.right, inven1.bottom);
	wsprintf(str, "1");
	TextOut(getMemDC(), inven1.left + 5, inven1.top + 2, str, lstrlen(str));

	Rectangle(getMemDC(), inven2.left, inven2.top, inven2.right, inven2.bottom);
	wsprintf(str, "2");
	TextOut(getMemDC(), inven2.left + 5, inven2.top + 2, str, lstrlen(str));

	Rectangle(getMemDC(), inven3.left, inven3.top, inven3.right, inven3.bottom);
	wsprintf(str, "3");
	TextOut(getMemDC(), inven3.left + 5, inven3.top + 2, str, lstrlen(str));

	Rectangle(getMemDC(), inven4.left, inven4.top, inven4.right, inven4.bottom);
	wsprintf(str, "4");
	TextOut(getMemDC(), inven4.left + 5, inven4.top + 2, str, lstrlen(str));



	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		if ((*_viInventory).pos == 1 /* && !(*_viItem).empty*/)
		{
			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), inven1.right - 25, inven1.bottom - 18, str, lstrlen(str));
		}

		if ((*_viInventory).pos == 2 /* && !(*_viItem).empty */)
		{
			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), inven2.right - 25, inven2.bottom - 18, str, lstrlen(str));
		}

		if ((*_viInventory).pos == 3 /*&& !(*_viItem).empty*/)
		{
			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), inven3.right - 25, inven3.bottom - 18, str, lstrlen(str));
		}

		if ((*_viInventory).pos == 4/* && !(*_viItem).empty*/)
		{
			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), inven4.right - 25, inven4.bottom - 18, str, lstrlen(str));
		}
	}

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);


	/*for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		TCHAR str[100];

		if ((*_viInventory).id == 1)
		{
			wsprintf(str, "id : %d %number : %d", (*_viInventory).id, (*_viInventory).number);
			TextOut(getMemDC(), 400, 400, str, lstrlen(str));
		}

		if ((*_viInventory).id == 2)
		{
			wsprintf(str, "id : %d %number : %d", (*_viInventory).id, (*_viInventory).number);
			TextOut(getMemDC(), 400, 440, str, lstrlen(str));
		}

		if ((*_viInventory).id == 3)
		{
			wsprintf(str, "id : %d %number : %d", (*_viInventory).id, (*_viInventory).number);
			TextOut(getMemDC(), 400, 480, str, lstrlen(str));
		}

		if ((*_viInventory).id == 4)
		{
			wsprintf(str, "id : %d %number : %d", (*_viInventory).id, (*_viInventory).number);
			TextOut(getMemDC(), 400, 520, str, lstrlen(str));
		}

		if ((*_viInventory).id == 5)
		{
			wsprintf(str, "id : %d %number : %d", (*_viInventory).id, (*_viInventory).number);
			TextOut(getMemDC(), 400, 560, str, lstrlen(str));
		}
	}
	*/


	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		int interval_x = 9;
		if ((*_viInventory).pos == 1)
		{
			if ((*_viInventory).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 8) IMAGE->render("Elixir_icon", getMemDC(), inven1.left + interval_x, inven1.top);
			else if ((*_viInventory).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), inven1.left + interval_x, inven1.top);
		}

		else if ((*_viInventory).pos == 2)
		{
			if ((*_viInventory).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 8) IMAGE->render("Elixir_icon", getMemDC(), inven2.left + interval_x, inven2.top);
			else if ((*_viInventory).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), inven2.left + interval_x, inven2.top);
		}

		else if ((*_viInventory).pos == 3)
		{
			if ((*_viInventory).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 8) IMAGE->render("Elixir_icon", getMemDC(), inven3.left + interval_x, inven3.top);
			else if ((*_viInventory).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), inven3.left + interval_x, inven3.top);
		}

		else if ((*_viInventory).pos == 4)
		{
			if ((*_viInventory).id == 1) IMAGE->render("Green_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 2) IMAGE->render("Lemon_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 3) IMAGE->render("Orange_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 4) IMAGE->render("Pine_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 5) IMAGE->render("Melange_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 6) IMAGE->render("Miracle_Gel_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 7) IMAGE->render("Oberol_Gold_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 8) IMAGE->render("Elixir_icon", getMemDC(), inven4.left + interval_x, inven4.top);
			else if ((*_viInventory).id == 9) IMAGE->render("Life_Bottle_icon", getMemDC(), inven4.left + interval_x, inven4.top);
		}
	}

	//스킬키

	hpen = CreatePen(PS_SOLID, 7, RGB(0, 0, 0)); // 선 스타일, 굵기, 색상 
	hpenOld = (HPEN)::SelectObject(getMemDC(), (HGDIOBJ)hpen); // 펜 선택 

	Rectangle(getMemDC(), skill_a.left, skill_a.top, skill_a.right, skill_a.bottom);
	Rectangle(getMemDC(), skill_c.left, skill_c.top, skill_c.right, skill_c.bottom);
	Rectangle(getMemDC(), skill_v.left, skill_v.top, skill_v.right, skill_v.bottom);

	hpen = (HPEN)::SelectObject(getMemDC(), hpenOld); // 기존의 펜 다시 선택 
	::DeleteObject(hpen); // 생성한 펜 삭제

	IMAGE->render("c_skill", getMemDC(), skill_c.left, skill_c.top);
	wsprintf(str, "c");
	TextOut(getMemDC(), skill_c.left, skill_c.top, str, lstrlen(str));

	IMAGE->render("v_skill", getMemDC(), skill_v.left, skill_v.top);
	wsprintf(str, "v");
	TextOut(getMemDC(), skill_v.left, skill_v.top, str, lstrlen(str));

	IMAGE->render("a_skill", getMemDC(), skill_a.left, skill_a.top);
	wsprintf(str, "a");
	TextOut(getMemDC(), skill_a.left, skill_a.top, str, lstrlen(str));


	if (!inventoryDisable) inventoryWindow();

	if (!miniMapDisable) miniMap();

	if (!questWindowDisable)questWindow();

	if (!cashShopDisable)cashShop();

	//RECT temp = RectMakeCenter(100, 100, 100, 100);
	//Rectangle(getMemDC(), temp.left, temp.top, temp.right, temp.bottom);

	//TCHAR str[100];
	//wsprintf(str, "isMonsterDie : %d, itemCollision : %d", isMonsterDie, itemCollision);
	//TextOut(getMemDC(), 100, 100, str, lstrlen(str));



	//Rectangle(getMemDC(), mini_rc.left, mini_rc.top, mini_rc.right, mini_rc.bottom);

	//IMAGE->render("카메라", getMemDC(), 100 - m_camera / 10, 50);
}

void stage2::gaugeDraw()
{
	if (playerHP_Front.right - playerHP_Front.left > 200)
	{
		p_red = 0;
		p_green = 255;
	}
	if (playerHP_Front.right - playerHP_Front.left <= 200)
	{
		p_red = 200;
		p_green = 255;
	}
	if (playerHP_Front.right - playerHP_Front.left <= 80)
	{
		p_red = 255;
		p_green = 0;
	}

	if (m_gaugeFront.bottom - m_gaugeFront.top <= 200)
	{
		m_red = 200;
	}
	if (m_gaugeFront.bottom - m_gaugeFront.top <= 80)
	{
		m_red = 255;
		m_green = 0;
	}
}

void stage2::scoreRender()
{
	//RECT scoreRender_RC = RectMake(850, 640, 220, 30);
	//Rectangle(getMemDC(), scoreRender_RC.left, scoreRender_RC.top, scoreRender_RC.right, scoreRender_RC.bottom);

	float startTime = 0;
	float endTime = 0;
	//몬스터가 죽었을 때.
	static float startTime2 = 0;
	static bool prevDie = false;
	//아이템을 먹었을 때.
	static float startTime3 = 0;
	static bool prevItem = false;

	static bool isGetCoin = false;

	if (monsterState == monster2_State::DAMAGE && !isMonsterDie)
	{
		startTime = TIME->getWorldTime();
		isGetCoin = true;
	}
	else if (isMonsterDie && !prevDie)
	{
		startTime2 = TIME->getWorldTime();
		isGetCoin = true;
		prevDie = true;
	}
	else if (itemCollision && !prevItem)
	{
		startTime3 = TIME->getWorldTime();
		isGetCoin = true;
		prevItem = true;
	}
	else
	{
		endTime = TIME->getWorldTime();
	}

	//TCHAR str[100];
	//_stprintf_s(str, "startTime2 : %f", startTime2);
	//TextOut(getMemDC(), 100, 100, str, lstrlen(str));

	//endTime2 = TIME->getWorldTime();

	HFONT font, oldfont;

	font = CreateFont(25, 0, 0, 0, FW_LIGHT, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	if ((endTime - startTime < 2 && isGetCoin) || (endTime - startTime2 < 0.5f && isGetCoin))
	{
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TCHAR str[100];
		wsprintf(str, "20 코인을 획득하였습니다.");
		TextOut(getMemDC(), 875, 640, str, lstrlen(str));
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	}
	else if (endTime - startTime3 < 0.5f && isGetCoin)
	{
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TCHAR str[100];
		wsprintf(str, "100 코인을 획득하였습니다.");
		TextOut(getMemDC(), 875, 640, str, lstrlen(str));
		SetTextColor(getMemDC(), RGB(0, 0, 0));
	}
	else isGetCoin = false;

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	/*
	HFONT font, oldfont;

	font = CreateFont(25, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "THEHappyfruit");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(255, 102, 204));
	RECT scoreRender_RC = RectMake(870, 80, 120, 30);
	Rectangle(getMemDC(), scoreRender_RC.left, scoreRender_RC.top, scoreRender_RC.right, scoreRender_RC.bottom);
	FillRect(getMemDC(), &scoreRender_RC, brush);
	DeleteObject(brush);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TCHAR str[100];
	wsprintf(str, "COIN : %d", getScore());
	TextOut(getMemDC(), scoreRender_RC.left, scoreRender_RC.top, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
	*/

	//float score100 = playerScore / 100;
	//float score10 = (playerScore % 100) / 10;
	//float score1 = (playerScore % 100) % 10;

	/*
	HDC hdc = getMemDC();

	if (score100 == 0)IMAGE->render("0", hdc, _score100.left, _score100.top);
	else if (score100 == 1)IMAGE->render("1", hdc, _score100.left, _score100.top);
	else if (score100 == 2)IMAGE->render("2", hdc, _score100.left, _score100.top);
	else if (score100 == 3)IMAGE->render("3", hdc, _score100.left, _score100.top);
	else if (score100 == 4)IMAGE->render("4", hdc, _score100.left, _score100.top);
	else if (score100 == 5)IMAGE->render("5", hdc, _score100.left, _score100.top);
	else if (score100 == 6)IMAGE->render("6", hdc, _score100.left, _score100.top);
	else if (score100 == 7)IMAGE->render("7", hdc, _score100.left, _score100.top);
	else if (score100 == 8)IMAGE->render("8", hdc, _score100.left, _score100.top);
	else if (score100 == 9)IMAGE->render("9", hdc, _score100.left, _score100.top);

	if (score10 == 0)IMAGE->render("0", hdc, _score10.left, _score10.top);
	else if (score10 == 1)IMAGE->render("1", hdc, _score10.left, _score10.top);
	else if (score10 == 2)IMAGE->render("2", hdc, _score10.left, _score10.top);
	else if (score10 == 3)IMAGE->render("3", hdc, _score10.left, _score10.top);
	else if (score10 == 4)IMAGE->render("4", hdc, _score10.left, _score10.top);
	else if (score10 == 5)IMAGE->render("5", hdc, _score10.left, _score10.top);
	else if (score10 == 6)IMAGE->render("6", hdc, _score10.left, _score10.top);
	else if (score10 == 7)IMAGE->render("7", hdc, _score10.left, _score10.top);
	else if (score10 == 8)IMAGE->render("8", hdc, _score10.left, _score10.top);
	else if (score10 == 9)IMAGE->render("9", hdc, _score10.left, _score10.top);

	if (score1 == 0)IMAGE->render("0", hdc, _score1.left, _score1.top);
	else if (score1 == 1)IMAGE->render("1", hdc, _score1.left, _score1.top);
	else if (score1 == 2)IMAGE->render("2", hdc, _score1.left, _score1.top);
	else if (score1 == 3)IMAGE->render("3", hdc, _score1.left, _score1.top);
	else if (score1 == 4)IMAGE->render("4", hdc, _score1.left, _score1.top);
	else if (score1 == 5)IMAGE->render("5", hdc, _score1.left, _score1.top);
	else if (score1 == 6)IMAGE->render("6", hdc, _score1.left, _score1.top);
	else if (score1 == 7)IMAGE->render("7", hdc, _score1.left, _score1.top);
	else if (score1 == 8)IMAGE->render("8", hdc, _score1.left, _score1.top);
	else if (score1 == 9)IMAGE->render("9", hdc, _score1.left, _score1.top);
	*/
}


void stage2::timeRender()
{
	HFONT font, oldfont;

	font = CreateFont(50, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "THEHappyfruit");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	SetTextColor(getMemDC(), RGB(0, 0, 0)); // 검은그림자.
	TCHAR str[100];
	wsprintf(str, "TIME");
	TextOut(getMemDC(), 428, 8, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SetTextColor(getMemDC(), RGB(153, 204, 255));
	wsprintf(str, "TIME");
	TextOut(getMemDC(), 431, 5, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	int time;
	time = TIME->getWorldTime();

	int time10 = (120 - time) / 10;
	int time1 = (120 - time) % 10;

	HDC hdc = getMemDC();


	if (time10 == 0)IMAGE->render("0", hdc, _time10.left, _time10.top);
	else if (time10 == 1)IMAGE->render("1", hdc, _time10.left, _time10.top);
	else if (time10 == 2)IMAGE->render("2", hdc, _time10.left, _time10.top);
	else if (time10 == 3)IMAGE->render("3", hdc, _time10.left, _time10.top);
	else if (time10 == 4)IMAGE->render("4", hdc, _time10.left, _time10.top);
	else if (time10 == 5)IMAGE->render("5", hdc, _time10.left, _time10.top);
	else if (time10 == 6)IMAGE->render("6", hdc, _time10.left, _time10.top);
	else if (time10 == 7)IMAGE->render("7", hdc, _time10.left, _time10.top);
	else if (time10 == 8)IMAGE->render("8", hdc, _time10.left, _time10.top);
	else if (time10 == 9)IMAGE->render("9", hdc, _time10.left, _time10.top);

	if (time1 == 0)IMAGE->render("0", hdc, _time1.left, _time1.top);
	else if (time1 == 1)IMAGE->render("1", hdc, _time1.left, _time1.top);
	else if (time1 == 2)IMAGE->render("2", hdc, _time1.left, _time1.top);
	else if (time1 == 3)IMAGE->render("3", hdc, _time1.left, _time1.top);
	else if (time1 == 4)IMAGE->render("4", hdc, _time1.left, _time1.top);
	else if (time1 == 5)IMAGE->render("5", hdc, _time1.left, _time1.top);
	else if (time1 == 6)IMAGE->render("6", hdc, _time1.left, _time1.top);
	else if (time1 == 7)IMAGE->render("7", hdc, _time1.left, _time1.top);
	else if (time1 == 8)IMAGE->render("8", hdc, _time1.left, _time1.top);
	else if (time1 == 9)IMAGE->render("9", hdc, _time1.left, _time1.top);
}

void stage2::frameRender()
{
	int frame;
	frame = TIME->getFrameRate();

	int frame10 = frame / 10;
	int frame1 = frame % 10;

	HFONT font, oldfont;

	font = CreateFont(15, 0, 0, 0, FW_LIGHT, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "THEHappyfruit");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	RECT frameRender_RC = RectMake(WINSIZEX - 80, 0, 100, 50);
	//Rectangle(getMemDC(), frameRender_RC.left, frameRender_RC.top, frameRender_RC.right, frameRender_RC.bottom);

	SetBkMode(getMemDC(), OPAQUE);
	SetTextColor(getMemDC(), RGB(153, 153, 153));

	TCHAR str[100];
	wsprintf(str, "FRAME : %d", frame);
	TextOut(getMemDC(), frameRender_RC.left, frameRender_RC.top, str, lstrlen(str));

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SetBkMode(getMemDC(), TRANSPARENT);
	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
	//HDC hdc = getMemDC();

	/*
	if (frame10 == 0)IMAGE->render("0", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 1)IMAGE->render("1", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 2)IMAGE->render("2", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 3)IMAGE->render("3", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 4)IMAGE->render("4", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 5)IMAGE->render("5", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 6)IMAGE->render("6", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 7)IMAGE->render("7", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 8)IMAGE->render("8", hdc, _frame10.left, _frame10.top);
	else if (frame10 == 9)IMAGE->render("9", hdc, _frame10.left, _frame10.top);

	if (frame1 == 0)IMAGE->render("0", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 1)IMAGE->render("1", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 2)IMAGE->render("2", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 3)IMAGE->render("3", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 4)IMAGE->render("4", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 5)IMAGE->render("5", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 6)IMAGE->render("6", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 7)IMAGE->render("7", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 8)IMAGE->render("8", hdc, _frame1.left, _frame1.top);
	else if (frame1 == 9)IMAGE->render("9", hdc, _frame1.left, _frame1.top);
	*/
}

void stage2::levelRender()
{
	HDC hdc = getMemDC();


	if (level == 0)IMAGE->render("0", hdc, levelRC.left, levelRC.top);
	else if (level == 1)IMAGE->render("1", hdc, levelRC.left, levelRC.top);
	else if (level == 2)IMAGE->render("2", hdc, levelRC.left, levelRC.top);
	else if (level == 3)IMAGE->render("3", hdc, levelRC.left, levelRC.top);
	else if (level == 4)IMAGE->render("4", hdc, levelRC.left, levelRC.top);
	else if (level == 5)IMAGE->render("5", hdc, levelRC.left, levelRC.top);
	else if (level == 6)IMAGE->render("6", hdc, levelRC.left, levelRC.top);
	else if (level == 7)IMAGE->render("7", hdc, levelRC.left, levelRC.top);
	else if (level == 8)IMAGE->render("8", hdc, levelRC.left, levelRC.top);
	else if (level == 9)IMAGE->render("9", hdc, levelRC.left, levelRC.top);
}

/*void minimap::getBuyItem(int item1, int item2, int item3, int item4)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).id == 1)	(*_viItem).number = item1;
		else if ((*_viItem).id == 2) (*_viItem).number = item2;
		else if ((*_viItem).id == 3) (*_viItem).number = item3;
		else if ((*_viItem).id == 4) (*_viItem).number = item4;
	}
}*/

void stage2::GetBuyItem(int id)
{
	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		if ((*_viInventory).id == id) (*_viInventory).number++;
	}
}

/*void minimap::itemUpdate()
{
	static bool pos1_empty = true;
	static bool pos2_empty = true;
	static bool pos3_empty = true;
	static bool pos4_empty = true;

	int pos1 = 1;
	int pos2 = 2;
	int pos3 = 3;
	int pos4 = 4;

	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).number == 0)//비어있으면.
		{
			(*_viItem).empty = true;


			if ((*_viItem).pos == pos1) pos1_empty = true;
			if ((*_viItem).pos == pos2) pos2_empty = true;
			if ((*_viItem).pos == pos3) pos3_empty = true;
			if ((*_viItem).pos == pos4) pos4_empty = true;

			(*_viItem).pos = 0;
		}

		else if((*_viItem).pos == 0)
		{
			(*_viItem).empty = false;

			if (pos1_empty) { (*_viItem).pos = 1;  pos1_empty = false; }
			else if (pos2_empty) { (*_viItem).pos = 2; pos2_empty = false; }
			else if (pos3_empty) { (*_viItem).pos = 3; pos3_empty = false; }
			else if (pos4_empty) { (*_viItem).pos = 4; pos4_empty = false; }
		}


		//앞으로 당기기.
		if (pos1_empty && !pos2_empty && (*_viItem).pos == pos2)
		{
			(*_viItem).pos = 1;
			pos1_empty = false;
			pos2_empty = true;
		}
		if (pos2_empty && !pos3_empty && (*_viItem).pos == pos3)
		{
			(*_viItem).pos = 2;
			pos2_empty = false;
			pos3_empty = true;
		}
		if (pos3_empty && !pos4_empty && (*_viItem).pos == pos4)
		{
			(*_viItem).pos = 3;
			pos3_empty = false;
			pos4_empty = true;
		}
	}
}*/

void stage2::ItemUpdate()
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

	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		if ((*_viInventory).pos == 1 && (*_viInventory).number > 0)pos1_empty = false;
		else if ((*_viInventory).pos == 2 && (*_viInventory).number > 0)pos2_empty = false;
		else if ((*_viInventory).pos == 3 && (*_viInventory).number > 0)pos3_empty = false;
		else if ((*_viInventory).pos == 4 && (*_viInventory).number > 0)pos4_empty = false;
		else if ((*_viInventory).pos == 5 && (*_viInventory).number > 0)pos5_empty = false;
		else if ((*_viInventory).pos == 6 && (*_viInventory).number > 0)pos6_empty = false;
		else if ((*_viInventory).pos == 7 && (*_viInventory).number > 0)pos7_empty = false;
		else if ((*_viInventory).pos == 8 && (*_viInventory).number > 0)pos8_empty = false;
		else if ((*_viInventory).pos == 9 && (*_viInventory).number > 0)pos9_empty = false;
	}

	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		if ((*_viInventory).number == 0)//비어있으면.
		{
			(*_viInventory).empty = true;


			if ((*_viInventory).pos == pos1) pos1_empty = true;
			else if ((*_viInventory).pos == pos2) pos2_empty = true;
			else if ((*_viInventory).pos == pos3) pos3_empty = true;
			else if ((*_viInventory).pos == pos4) pos4_empty = true;
			else if ((*_viInventory).pos == pos5) pos5_empty = true;
			else if ((*_viInventory).pos == pos6) pos6_empty = true;
			else if ((*_viInventory).pos == pos7) pos7_empty = true;
			else if ((*_viInventory).pos == pos8) pos8_empty = true;
			else if ((*_viInventory).pos == pos9) pos9_empty = true;

			(*_viInventory).pos = 0;
		}

		else if ((*_viInventory).pos == 0)
		{
			(*_viInventory).empty = false;

			if (pos1_empty) { (*_viInventory).pos = 1;  pos1_empty = false; }
			else if (pos2_empty) { (*_viInventory).pos = 2; pos2_empty = false; }
			else if (pos3_empty) { (*_viInventory).pos = 3; pos3_empty = false; }
			else if (pos4_empty) { (*_viInventory).pos = 4; pos4_empty = false; }
			else if (pos5_empty) { (*_viInventory).pos = 5; pos5_empty = false; }
			else if (pos6_empty) { (*_viInventory).pos = 6; pos6_empty = false; }
			else if (pos7_empty) { (*_viInventory).pos = 7; pos7_empty = false; }
			else if (pos8_empty) { (*_viInventory).pos = 8; pos8_empty = false; }
			else if (pos9_empty) { (*_viInventory).pos = 9; pos9_empty = false; }
		}


		//앞으로 당기기.
		if (pos1_empty && !pos2_empty && (*_viInventory).pos == pos2)
		{
			(*_viInventory).pos = 1;
			pos1_empty = false;
			pos2_empty = true;
		}
		if (pos2_empty && !pos3_empty && (*_viInventory).pos == pos3)
		{
			(*_viInventory).pos = 2;
			pos2_empty = false;
			pos3_empty = true;
		}
		if (pos3_empty && !pos4_empty && (*_viInventory).pos == pos4)
		{
			(*_viInventory).pos = 3;
			pos3_empty = false;
			pos4_empty = true;
		}
		if (pos4_empty && !pos5_empty && (*_viInventory).pos == pos5)
		{
			(*_viInventory).pos = 4;
			pos4_empty = false;
			pos5_empty = true;
		}
		if (pos5_empty && !pos6_empty && (*_viInventory).pos == pos6)
		{
			(*_viInventory).pos = 5;
			pos5_empty = false;
			pos6_empty = true;
		}
		if (pos6_empty && !pos7_empty && (*_viInventory).pos == pos7)
		{
			(*_viInventory).pos = 6;
			pos6_empty = false;
			pos7_empty = true;
		}
		if (pos7_empty && !pos8_empty && (*_viInventory).pos == pos8)
		{
			(*_viInventory).pos = 7;
			pos7_empty = false;
			pos8_empty = true;
		}
		if (pos8_empty && !pos9_empty && (*_viInventory).pos == pos9)
		{
			(*_viInventory).pos = 8;
			pos8_empty = false;
			pos9_empty = true;
		}
	}
}

void stage2::inventoryWindow()
{
	TCHAR str[100];
	//inventoryWindow_RC = RectMakeCenter(700, 265, 200, 250);
	//Rectangle(getMemDC(), inventoryWindow_RC.left, inventoryWindow_RC.top, inventoryWindow_RC.right, inventoryWindow_RC.bottom);	

	POINT mouse = m_ptMouse;



	/*bool m_bLDown = false;
	POINT m_ptOld;
	int temp_x;
	int temp_y;

	int x = inventoryWindow_RC.left;
	int y = inventoryWindow_RC.top;
	if (InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		int x1, y1;

		if (PtInRect(&inventoryWindow_RC, mouse))
		{
			x1 = mouse.x;
			y1 = mouse.y;



			temp_x = x1 - x; //사각형 시작부분의 x좌표와 마우스가 클릭된 좌표의 차를 저장함
			temp_y = y1 - y; //사각형 시작부분의 y좌표와 마우스가 클릭된 좌표의 차를 저장함

			m_bLDown = true;
		}
	}
	else if ((InputManager->isOnceKeyUp(VK_LBUTTON)))
	{
		m_bLDown = false;

	}

	if (mouseMove)
	{
		if (m_bLDown)
		{
			POINT ptNew = mouse;
			x = ptNew.x- temp_x;
			y = ptNew.y- temp_y;

		}
	}*/

	Rectangle(getMemDC(), Menu_RC.left, Menu_RC.top, Menu_RC.right, Menu_RC.bottom);

	IMAGE->render("인벤토리배경", getMemDC(), Menu_RC.left, Menu_RC.top);

	//RECT iwName_RC = RectMakeCenter(700, 150, 200, 30);
	RECT iwName_RC = RectMake(Menu_RC.left, Menu_RC.top, 200, 30);
	Rectangle(getMemDC(), iwName_RC.left, iwName_RC.top, iwName_RC.right, iwName_RC.bottom);

	HFONT font, oldfont;

	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "인벤토리");
	TextOut(getMemDC(), iwName_RC.left + 5, iwName_RC.top + 5, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(255, 0, 0));
	RECT iwClose_RC = RectMake(Menu_RC.left + 170, Menu_RC.top, 30, 30);
	Rectangle(getMemDC(), iwClose_RC.left, iwClose_RC.top, iwClose_RC.right, iwClose_RC.bottom);
	FillRect(getMemDC(), &iwClose_RC, brush);
	DeleteObject(brush);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	wsprintf(str, "X");
	TextOut(getMemDC(), iwClose_RC.left + 10, iwClose_RC.top + 7, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	RectangleMake(getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
	RectangleMake(getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);

	bool LB_KeepDown = false;
	if (InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&iwClose_RC, mouse)) inventoryDisable = !inventoryDisable;

		LB_KeepDown = false;
	}
	else if (InputManager->isStayKeyDown(VK_LBUTTON))
	{

		if (PtInRect(&invenPos1_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos1_RC.left, invenPos1_RC.top, invenPos1_RC.right, invenPos1_RC.bottom);
		}
		else if (PtInRect(&invenPos2_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos2_RC.left, invenPos2_RC.top, invenPos2_RC.right, invenPos2_RC.bottom);
		}
		else if (PtInRect(&invenPos3_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos3_RC.left, invenPos3_RC.top, invenPos3_RC.right, invenPos3_RC.bottom);
		}
		else if (PtInRect(&invenPos4_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos4_RC.left, invenPos4_RC.top, invenPos4_RC.right, invenPos4_RC.bottom);
		}
		else if (PtInRect(&invenPos5_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos5_RC.left, invenPos5_RC.top, invenPos5_RC.right, invenPos5_RC.bottom);
		}
		else if (PtInRect(&invenPos6_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos6_RC.left, invenPos6_RC.top, invenPos6_RC.right, invenPos6_RC.bottom);
		}
		else if (PtInRect(&invenPos7_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos7_RC.left, invenPos7_RC.top, invenPos7_RC.right, invenPos7_RC.bottom);
		}
		else if (PtInRect(&invenPos8_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos8_RC.left, invenPos8_RC.top, invenPos8_RC.right, invenPos8_RC.bottom);
		}
		else if (PtInRect(&invenPos9_RC, mouse))
		{
			LB_KeepDown = true;
			Rectangle(getMemDC(), invenPos9_RC.left, invenPos9_RC.top, invenPos9_RC.right, invenPos9_RC.bottom);
		}
	}
	else LB_KeepDown = false;

	if (InputManager->isOnceKeyUp(VK_LBUTTON))
	{
		//단축키 변경.
		RECT temp;
		if (IntersectRect(&temp, &inven1, &invenPos2_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 2) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 2;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}

		}
		else if (IntersectRect(&temp, &inven1, &invenPos3_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 3) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 3;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos4_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 4) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 4;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos5_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 5) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 5;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos6_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 6) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 6;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos7_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 7) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 7;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos8_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 8) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 8;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven1, &invenPos9_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 1) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 9) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 9;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 1;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos1_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 1) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 1;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos3_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 3) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 3;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos4_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 4) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 4;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos5_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 5) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 5;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos6_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 6) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 6;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos7_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 7) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 7;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos8_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 8) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 8;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven2, &invenPos9_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 2) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 9) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 9;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 2;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos1_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 1) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 1;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos2_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 2) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 2;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos4_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 4) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 4;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos5_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 5) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 5;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos6_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 6) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 6;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos7_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 7) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 7;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos8_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 8) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 8;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven3, &invenPos9_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 3) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 9) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 9;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 3;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos1_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 1) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 1;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos2_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 2) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 2;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos3_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 3) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 3;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos5_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 5) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 5;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos6_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 6) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 6;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos7_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 7) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 7;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos8_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 8) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 8;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		else if (IntersectRect(&temp, &inven4, &invenPos9_RC))
		{
			int sour;
			int dest;
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).pos == 4) sour = (*_viInventory).id;
				if ((*_viInventory).pos == 9) dest = (*_viInventory).id;
			}
			for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
			{
				if ((*_viInventory).id == sour) (*_viInventory).pos = 9;
				if ((*_viInventory).id == dest) (*_viInventory).pos = 4;
			}
		}
		invenPos1_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
		invenPos2_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 35, 50, 50);
		invenPos3_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
		invenPos4_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
		invenPos5_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
		invenPos6_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
		invenPos7_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
		invenPos8_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
		invenPos9_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);
	}


	RECT iwCoin_RC = RectMake(Menu_RC.left, Menu_RC.bottom - 30, 200, 30);
	Rectangle(getMemDC(), iwCoin_RC.left, iwCoin_RC.top, iwCoin_RC.right, iwCoin_RC.bottom);

	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "COIN :   %d", getScore());
	TextOut(getMemDC(), iwCoin_RC.left + 10, iwCoin_RC.top + 4, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);


	/*Rectangle(getMemDC(), invenPos1_RC.left, invenPos1_RC.top, invenPos1_RC.right, invenPos1_RC.bottom);
	Rectangle(getMemDC(), invenPos2_RC.left, invenPos2_RC.top, invenPos2_RC.right, invenPos2_RC.bottom);
	Rectangle(getMemDC(), invenPos3_RC.left, invenPos3_RC.top, invenPos3_RC.right, invenPos3_RC.bottom);
	Rectangle(getMemDC(), invenPos4_RC.left, invenPos4_RC.top, invenPos4_RC.right, invenPos4_RC.bottom);
	Rectangle(getMemDC(), invenPos5_RC.left, invenPos5_RC.top, invenPos5_RC.right, invenPos5_RC.bottom);
	Rectangle(getMemDC(), invenPos6_RC.left, invenPos6_RC.top, invenPos6_RC.right, invenPos6_RC.bottom);
	Rectangle(getMemDC(), invenPos7_RC.left, invenPos7_RC.top, invenPos7_RC.right, invenPos7_RC.bottom);
	Rectangle(getMemDC(), invenPos8_RC.left, invenPos8_RC.top, invenPos8_RC.right, invenPos8_RC.bottom);
	Rectangle(getMemDC(), invenPos9_RC.left, invenPos9_RC.top, invenPos9_RC.right, invenPos9_RC.bottom);*/



	/*
	RECT iwItemList1_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 35, 50, 50);
	RECT iwItemList2_RC = RectMake(Menu_RC.left +70, Menu_RC.top + 35, 50, 50);
	RECT iwItemList3_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 35, 50, 50);
	RECT iwItemList4_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 95, 50, 50);
	RECT iwItemList5_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 95, 50, 50);
	RECT iwItemList6_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 95, 50, 50);
	RECT iwItemList7_RC = RectMake(Menu_RC.left + 10, Menu_RC.top + 155, 50, 50);
	RECT iwItemList8_RC = RectMake(Menu_RC.left + 70, Menu_RC.top + 155, 50, 50);
	RECT iwItemList9_RC = RectMake(Menu_RC.left + 130, Menu_RC.top + 155, 50, 50);
	/*
	Rectangle(getMemDC(), iwItemList1_RC.left, iwItemList1_RC.top, iwItemList1_RC.right, iwItemList1_RC.bottom);
	Rectangle(getMemDC(), iwItemList2_RC.left, iwItemList2_RC.top, iwItemList2_RC.right, iwItemList2_RC.bottom);
	Rectangle(getMemDC(), iwItemList3_RC.left, iwItemList3_RC.top, iwItemList3_RC.right, iwItemList3_RC.bottom);
	Rectangle(getMemDC(), iwItemList4_RC.left, iwItemList4_RC.top, iwItemList4_RC.right, iwItemList4_RC.bottom);
	Rectangle(getMemDC(), iwItemList5_RC.left, iwItemList5_RC.top, iwItemList5_RC.right, iwItemList5_RC.bottom);
	Rectangle(getMemDC(), iwItemList6_RC.left, iwItemList6_RC.top, iwItemList6_RC.right, iwItemList6_RC.bottom);
	Rectangle(getMemDC(), iwItemList7_RC.left, iwItemList7_RC.top, iwItemList7_RC.right, iwItemList7_RC.bottom);
	Rectangle(getMemDC(), iwItemList8_RC.left, iwItemList8_RC.top, iwItemList8_RC.right, iwItemList8_RC.bottom);
	Rectangle(getMemDC(), iwItemList9_RC.left, iwItemList9_RC.top, iwItemList9_RC.right, iwItemList9_RC.bottom);
	*/




	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	for (_viInventory = _vInventory.begin(); _viInventory != _vInventory.end(); ++_viInventory)
	{
		if ((*_viInventory).pos == 1)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos1_RC.left, invenPos1_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 35);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 10 + 25, Menu_RC.top + 35 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 2)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos2_RC.left, invenPos2_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 35);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 70 + 25, Menu_RC.top + 35 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 3)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos3_RC.left, invenPos3_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 35);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 130 + 25, Menu_RC.top + 35 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 4)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos4_RC.left, invenPos4_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 95);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 10 + 25, Menu_RC.top + 95 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 5)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos5_RC.left, invenPos5_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 95);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 70 + 25, Menu_RC.top + 95 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 6)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos6_RC.left, invenPos6_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 95);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 130 + 25, Menu_RC.top + 95 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 7)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos7_RC.left, invenPos7_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 10, Menu_RC.top + 155);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 10 + 25, Menu_RC.top + 155 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 8)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos8_RC.left, invenPos8_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 70, Menu_RC.top + 155);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 70 + 25, Menu_RC.top + 155 + 30, str, lstrlen(str));
		}

		else if ((*_viInventory).pos == 9)
		{
			if ((*_viInventory).id == 1)
			{
				if (LB_KeepDown)IMAGE->render("Green_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Green_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 2)
			{
				if (LB_KeepDown)IMAGE->render("Lemon_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Lemon_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 3)
			{
				if (LB_KeepDown) IMAGE->render("Orange_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Orange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 4)
			{
				if (LB_KeepDown)IMAGE->render("Pine_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Pine_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 5)
			{
				if (LB_KeepDown)IMAGE->render("Melange_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Melange_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 6)
			{
				if (LB_KeepDown)IMAGE->render("Miracle_Gel_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Miracle_Gel_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 7)
			{
				if (LB_KeepDown)IMAGE->render("Oberol_Gold_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Oberol_Gold_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 8)
			{
				if (LB_KeepDown)IMAGE->render("Elixir_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Elixir_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}
			else if ((*_viInventory).id == 9)
			{
				if (LB_KeepDown)IMAGE->render("Life_Bottle_icon", getMemDC(), invenPos9_RC.left, invenPos9_RC.top);
				IMAGE->render("Life_Bottle_icon", getMemDC(), Menu_RC.left + 130, Menu_RC.top + 155);
			}

			wsprintf(str, "%d개", (*_viInventory).number);
			TextOut(getMemDC(), Menu_RC.left + 130 + 25, Menu_RC.top + 155 + 30, str, lstrlen(str));
		}
	}

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
}

void stage2::miniMap()
{
	miniPlayer_RC = RectMakeCenter(420 + player1_x / 10 - m_camera / 10, 60 + player1_y / 10, 10, 10);
	IMAGE->render("스테이지2미니맵", getMemDC(), 420, 60);
	Rectangle(getMemDC(), miniPlayer_RC.left, miniPlayer_RC.top, miniPlayer_RC.right, miniPlayer_RC.bottom);

}

void stage2::cashShop()
{
	RECT cashShopWindow_RC = RectMake(300, 100, 200, 250);
	Rectangle(getMemDC(), cashShopWindow_RC.left, cashShopWindow_RC.top, cashShopWindow_RC.right, cashShopWindow_RC.bottom);

	RECT cashShopName_RC = RectMake(cashShopWindow_RC.left, cashShopWindow_RC.top, 200, 30);
	Rectangle(getMemDC(), cashShopName_RC.left, cashShopName_RC.top, cashShopName_RC.right, cashShopName_RC.bottom);

	TCHAR str[100];
	//취소
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(255, 0, 0));
	RECT cashShopClose_RC = RectMake(cashShopWindow_RC.right - 30, cashShopWindow_RC.top, 30, 30);
	Rectangle(getMemDC(), cashShopClose_RC.left, cashShopClose_RC.top, cashShopClose_RC.right, cashShopClose_RC.bottom);
	FillRect(getMemDC(), &cashShopClose_RC, brush);
	DeleteObject(brush);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	wsprintf(str, "X");
	TextOut(getMemDC(), cashShopClose_RC.left + 10, cashShopClose_RC.top + 9, str, lstrlen(str));
	SetTextColor(getMemDC(), RGB(0, 0, 0));



	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldfont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);


	wsprintf(str, "캐시샵");
	TextOut(getMemDC(), cashShopName_RC.left + 5, cashShopName_RC.top + 5, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);


	RECT petIcon_RC = RectMake(cashShopWindow_RC.left + 10, cashShopWindow_RC.top + 60, 50, 50);
	Rectangle(getMemDC(), petIcon_RC.left, petIcon_RC.top, petIcon_RC.right, petIcon_RC.bottom);

	IMAGE->render("pet_icon", getMemDC(), petIcon_RC.left, petIcon_RC.top);

	RECT petDescrip_RC = RectMake(petIcon_RC.right + 10, petIcon_RC.top, 120, 50);
	Rectangle(getMemDC(), petDescrip_RC.left, petDescrip_RC.top, petDescrip_RC.right, petDescrip_RC.bottom);

	brush = CreateSolidBrush(RGB(255, 153, 255));
	RECT buyButton = RectMake(petDescrip_RC.left + 62, petDescrip_RC.bottom + 7, 55, 20);
	Rectangle(getMemDC(), buyButton.left, buyButton.top, buyButton.right, buyButton.bottom);
	FillRect(getMemDC(), &buyButton, brush);
	DeleteObject(brush);

	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "종류");
	TextOut(getMemDC(), petIcon_RC.left + 15, petIcon_RC.top - 25, str, lstrlen(str));
	wsprintf(str, "설명");
	TextOut(getMemDC(), petDescrip_RC.left + 44, petDescrip_RC.top - 25, str, lstrlen(str));

	wsprintf(str, "귀여운 아기 고양이");
	TextOut(getMemDC(), petDescrip_RC.left + 5, petDescrip_RC.top + 17, str, lstrlen(str));

	wsprintf(str, "귀여운 아기 고양이");
	TextOut(getMemDC(), petDescrip_RC.left + 5, petDescrip_RC.top + 17, str, lstrlen(str));

	wsprintf(str, "구매하기");
	TextOut(getMemDC(), buyButton.left + 3, buyButton.top + 3, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

	if (InputManager->isOnceKeyUp(VK_LBUTTON))
	{
		POINT mouse = m_ptMouse;
		if (PtInRect(&cashShopClose_RC, mouse))	cashShopDisable = !cashShopDisable;

		if (PtInRect(&buyButton, mouse)) pet_existence = true;
	}


}

void stage2::questWindow()
{
	RECT questWindow_RC = RectMake(10, 200, 150, 200);
	//Rectangle(getMemDC(), questWindow_RC.left, questWindow_RC.top, questWindow_RC.right, questWindow_RC.bottom);

	IMAGE->alphaRender("퀘스트창배경", getMemDC(), 10, 200, 170);

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldfont;
	AddFontResource("images/font/THEHappyfruit.ttf");
	AddFontResource("images/font/OdBestFreind.ttf");


	font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);


	TCHAR str[100];
	wsprintf(str, "퀘스트");
	TextOut(getMemDC(), questWindow_RC.left + 40, questWindow_RC.top + 10, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);
	//RemoveFontResource("images/font/THEHappyfruit.ttf");

	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "OdBestFreind");
	oldfont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "Garoben 처치");
	TextOut(getMemDC(), questWindow_RC.left + 10, questWindow_RC.top + 60, str, lstrlen(str));
	wsprintf(str, "(%d / 1)", isMonsterDie);
	TextOut(getMemDC(), questWindow_RC.left + 10, questWindow_RC.top + 80, str, lstrlen(str));

	int clear = 0;
	if (level == 3) clear = 1;
	wsprintf(str, "레벨 3 달성하기");
	TextOut(getMemDC(), questWindow_RC.left + 10, questWindow_RC.top + 120, str, lstrlen(str));
	wsprintf(str, "(%d / 1)", clear);
	TextOut(getMemDC(), questWindow_RC.left + 10, questWindow_RC.top + 140, str, lstrlen(str));

	SelectObject(getMemDC(), oldfont);
	DeleteObject(font);

}
