#pragma once
#include "IController.h"

class IInputController : IController
{
public:
	IInputController();
	~IInputController();
	void UpdateGameObject(const GameObject & i_other) override;

};
