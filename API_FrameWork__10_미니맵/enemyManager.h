#pragma once
#include"gameNode.h"
#include"minion.h"

class rocket;
class enemyManager : public gameNode
{

private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	

private:
	vEnemy			_vMinion;
	viEnemy			_viMinion;

public:

	enemyManager();
	~enemyManager();


	HRESULT init();
	void release();
	void update();
	void render();


	void setMinion();



	vEnemy			getVMinion() { return _vMinion; }
	viEnemy			getViMinion() { return _viMinion; }

	void removeMinion(int arrNum);

	void collision();



};

