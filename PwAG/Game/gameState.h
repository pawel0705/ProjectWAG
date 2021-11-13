#pragma once

#include "programState.h"
#include "src/Game Objects/maze.h"
#include "./stateMachine.h"
#include "gameAssets.h"

class GameState : public ProgramState
{
private:
	Maze* maze;
	GameReference gameReference;

public:
	GameState(GameReference gameReference);
	~GameState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard keyboard, Mouse mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime) override;
};
