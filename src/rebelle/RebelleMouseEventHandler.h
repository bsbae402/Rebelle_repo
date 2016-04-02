#pragma once

#include "mg\game\Game.h"
#include "mg\input\MouseEventHandler.h"

class RebelleMouseEventHandler : public MouseEventHandler
{
public:
	RebelleMouseEventHandler() {}
	~RebelleMouseEventHandler() {}
	void handleMousePressEvent(int mouseX, int mouseY);
	void handleMouseMoveEvent(int mouseX, int mouseY);
};