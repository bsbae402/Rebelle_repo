#pragma once

#include "mg\gsm\state\GameStateMachine.h"

class RebelleStateMachine : public GameStateMachine
{
public:
	RebelleStateMachine() {}
	~RebelleStateMachine() {}
	void update();
};