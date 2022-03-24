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

	int callEvet, subscribeOnNode, unSubscribe, creatandSub, inaction;

	int start_size;

public:

	Notework_manager()
	{
		std::cout << "=== Конструктор менаджера сети ===" << std::endl;
		std::cout << "* Введите начальное число нод" << std::endl;

		std::cin >> start_size;

		if(start_size <= 1)
		{
			std::cout << "Число нод должно превышать 1 !" << std::endl;
			exit(0);
		}
		
		std::cout << "* Распределите 100 проценты между пятью ивентами" << std::endl;
		std::cout << "  важно чтобы сумма распределённых процентов была равна 100" << std::endl;

		std::cout << "\t * Вызов Ивента - " ;
		std::cin >> callEvet;

		//std::cout << std::endl;
		std::cout << "\t * Подписка на ноду - ";
		std::cin >> subscribeOnNode;

		//std::cout << std::endl;
		std::cout << "\t * Отписка от ноды - ";
		std::cin >> unSubscribe;

		//std::cout << std::endl;
		std::cout << "\t * Создание и подписка на ноду - ";
		std::cin >> creatandSub;

		//std::cout << std::endl;
		std::cout << "\t * Пропуск действия на итерации - ";
		std::cin >> inaction;

		std::cout << std::endl;
		
		if(100 != callEvet + subscribeOnNode + unSubscribe + creatandSub + inaction)
		{
			std::cout << "Ты НЕ справился не молодца" << std::endl;
			exit(0);
		}
		else
		{
			std::cout << "Ты справился МОЛОДЦА!" << std::endl;
		}

		
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < start_size; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// Блок подписки предыдущего элемента на нынешний
 
			pair<bool, function<void(int, Node*)>> RandoFu = NodeArr[i - 1]->RandomEvern();

			temp->Subscribe(NodeArr[i - 1], RandoFu.second);

			NodeArr[i - 1]->MySubscription.emplace(temp, std::make_pair(RandoFu.first, 0));
		}

	}

	Notework_manager(int size_val)
	{
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < size_val; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// Блок подписки предыдущего элемента на нынешний

			pair<bool, function<void(int, Node*)>> RandoFu = NodeArr[i - 1]->RandomEvern();

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

		std::cout << "--Поиск елементов без подписки--" << std::endl;
		
		for (int i = NodeArr.size() - 1; i > -1; --i)
		{
			if(NodeArr[i]->IsAlone())
			{
				std::cout << "\tНайден и убит елемент без подписки - " << NodeArr[i] << std::endl;
				NodeArr.erase(NodeArr.begin() + i);
			}
		}


		std::cout << "--Этап вызова эвентов--" << std::endl;
		
		for (int i = 0; i < NodeArr.size(); ++i)
		{
			// сделай метод чтоб рандомно выбрать евент

			int RandIndex = rand() % 5;

			switch (RandIndex)
			{
				case 0:
				{
					std::cout << "\tНода - " << NodeArr[i] << " отрабатывает подписки" << std::endl;
					NodeArr[i]->CallEvent();
					break;
				}
				case 1:
				{
					std::cout << "\tНода - " << NodeArr[i] << " подписывается на рандомную ноду" << std::endl;
					NodeArr[i]->SubscribeOnNode();
					break;
				}
				case 2:
				{
					std::cout << "\tНода - " << NodeArr[i] << " отписывается от своей подписки" << std::endl;
					NodeArr[i]->UnSubscribe();
					break;
				}
				case 3:
				{
					std::cout << "\tНода - " << NodeArr[i] << " создаёт и подписывается на ноду" << std::endl;
					NewNodeArr.push_back(NodeArr[i]->CreateAndSubscribeNewNode());
					break;
				}
				case 4:
				{
					std::cout << "\tНода - " << NodeArr[i] << " пропускает итерацию" << std::endl;
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