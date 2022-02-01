#pragma once
#include "Node.h"
#include "vector"

class Notework_manager
{
private:

	std::vector<Node*> NodeArr;
public:

	void Tick();

	void PostTick();

	void PreTick();
};