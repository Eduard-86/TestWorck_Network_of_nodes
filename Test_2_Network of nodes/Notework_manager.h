#pragma once
#include "Node.h"
#include "vector"

using std::vector;

class Notework_manager
{
	
	
	/*
	 *Менеджер 
		будет знать обовсех нодах
		будет иметь 2 массива  с основными нодами и с свежими
		будет самостоятельно запускать ивенты всех нод
			сам рандомно будет вызывать ивенты
	 */
private:

	std::vector<Node*> NodeArr;
	std::vector<Node*> NewNodeArr;

public:

	Notework_manager(int start_size)
	{
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < start_size; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// Блок подписки предыдущего элемента на нынешний

			// todo тут косяк с биндом и передачей делегата 
			pair<bool, function<void(int, Node*)>> RandoFu = temp->RandomEvern();

			temp->Subscribe(NodeArr[i - 1], RandoFu.second);

			NodeArr[i - 1]->MySubscription.emplace(temp, std::make_pair(RandoFu.first, 0));
		}

	}

	void Tick()
	{
		/*
			Сперва пробежимяс по всем элиментам и проверим их на наличие подписок

			После пробежимся по массиву NodeArr и отработаем у каждого элемента ивент

			в конце массив свеже созданных элементов переместим в основной
		 */

		for (int i = NodeArr.size() - 1; i > -1; --i)
		{
			if(NodeArr[i]->IsAlone())
			{
				NodeArr.erase(NodeArr.begin() + i);
			}
		}
		
		for (int i = 0; i < NodeArr.size(); ++i)
		{
			// сделай метод чтоб рандомно выбрать евент

			int RandIndex = rand() % 5;

			switch (RandIndex)
			{
				case 0:
				{
					NodeArr[i]->CallEvent();
					break;
				}
				case 1:
				{
					NodeArr[i]->SubscribeOnNode();
					break;
				}
				case 2:
				{
					NodeArr[i]->UnSubscribe();
					break;
				}
				case 3:
				{
					NewNodeArr.push_back(NodeArr[i]->CreateAndSubscribeNewNode());
					break;
				}
				case 4:
				{
					NodeArr[i]->Inaction();
					break;
				}
				default :
				{
					cout << "Ты что дурак блять ?" << endl <<
						"Как так вышло что в менаджере индекс эвента привысил 4 ???\n";
					return;
					break;
				}
			}
		}

		for (int i = 0; i < NewNodeArr.size(); ++i)
		{
			NodeArr.push_back(NewNodeArr[i]);
		}
		NewNodeArr.clear();
	}
};