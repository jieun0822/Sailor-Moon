#pragma once
#include "gameNode.h"
class progressBar:public gameNode
{
private:
public:
	progressBar();
	~progressBar();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();
};

