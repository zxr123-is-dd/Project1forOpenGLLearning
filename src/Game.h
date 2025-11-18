#pragma once

#include "Camera.h"

class Game {
public:
	Game(const int &screenWidth, const int &screenHeight, const std::string &windowName);
	~Game();

	void mainProcess();

private:
	void initialize();
	void destory();
};