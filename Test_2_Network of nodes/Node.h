#pragma once
#include <functional>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#include <ctime>
#include <stdlib.h>
//#include "Notework_manager.h"

//using namespace std;

/*
	Событие должно нести в себе число Int и доп операцию
		Сумма всех чисел это этого отправителя
		Число событий от этого отправителя

	Тип события назначиется при подписке

	тоесть это 2 отдельных метода нашего узла которые
		при вызове примут значение int 
 
 */

/*
	Давай прогоним всень цикл и подитожем
	Узлы могут выполнить одни из действий которые мы знаем рандомно
		вероятность каждого события задаётся в ручную

	Этапы сети
		Основной этап всех узлов
			Созданные в этом этапе узлы не учавствуют в этом тике
			"тоесть когда у ноды выподает создать новую ноду то мы откладываем это действиет"
		Удаление узлов которые в этом тике потеряли всех соседей

	Структура действий - делегаты, мапа
		При подписке на ноду подпичкие передаёт свой указатель и указатель на метод
		нода сохраняет подписчика и метод отдельно
		и когда она создаёт событие 

	программа работает до выраждения либо до явной остановки программы пользователем
 
 */

/*
	30.11
	todo сделай мазафаку и подставь куда надо
		выборка одного из методов
		выборка одного из объектов 
  
 */


using std::vector; 
using std::map; 
using std::set;
using std::pair;
using std::function;
using std::bind;

using std::cout;
using std::endl;
 
class Node 
{
	/*
		Узел может быть подписан и хранить подписку от одного узла
	 */
	
	// мои подпищики
	vector<pair<Node* ,function<void(int, Node*)>>> MulticastDelegate;
	
	//vector<function<void(int, Node*)>> MulticastDelegate1;

	// Хранения метода с помащью бинд
	// std::placeholders::_1 данный синтаксис для определения параметров 
	function<void(int, Node*)> FooEnd1 =
		bind(&Node::EventCall, this, std::placeholders::_1, std::placeholders::_2);

	// подписки
	// В данной мапе храняться те на кого подписан данный узел
	// Указатель это хешь информация, пара значение bool - это какой тип метода мы передали
		// int - это значения которое нас интересует, инфа которую мы получали с этого узла
	map<Node*, pair<bool, int>> MySubscription;

	friend class Notework_manager;
	
public: 

	Node(Node* NodePtr, function<void(int, Node*)> Del);

	Node() {};

	~Node();
	
 	void Test();
 
#pragma region Events

	// call event on our subscribers 
	void CallEvent();
	
	// method subscribe on the node
	void SubscribeOnNode();

	// события отписки от того на кого подписан
	void UnSubscribe();

	Node * CreateAndSubscribeNewNode();

	void Inaction();

#pragma endregion

private:
	
	// данный метод вызавается когда на эту ноду будет происходить подписка
	// во время подписки вешается конкретный обработчик 
	void Subscribe(Node* NodePtr, function<void(int, Node*)>);

	// события для делегата 
	void EventSum(int value, Node* callnode)
	{
		// находим элемент в мапе
		pair<bool, int> sub = MySubscription.at(callnode);

		if (sub.first)
		{
			int valuesum = (MySubscription.at(callnode).second += value);

			cout << "Отправитель - " << callnode
				<< " получатель - " << this
				<< " Сумма всех получанных чисел от этого отправителя - "
				<< valuesum << endl;
		}
		else
		{
			// TODO сделай тут нормальное исключение ! 
			cout << "Ошибка у тебя пошли по пизде подписки а именно у функции не верный ключ!" << endl;
			cout << "Адрес ноды : " << this << " Делай с этой инфой чё хочешь)" << endl;

		}
	}
	void EventCall(int value, Node* callnode)
	{
		// находим элемент в мапе
		pair<bool, int> sub = MySubscription.at(callnode);

		if (!sub.first)
		{
			int valuecall = (MySubscription.at(callnode).second += 1);

			cout << "Отправитель - " << callnode
				<< " получатель - " << this
				<< " Сумма всех вызово от этого отправителя - "
				<< valuecall << endl;
		}
		else
		{
			// TODO сделай тут нормальное исключение ! 
			cout << "Ошибка у тебя пошли по пизде подписки а именно у функции не верный ключ!" << endl;
			cout << "Адрес ноды : " << this << " Делай с этой инфой чё хочешь)" << endl;

		}
	}
	
	void UnSubscribeOnMe(Node*);

	pair < bool, function<void(int, Node*)>> RandomEvern();

	bool IsAlone()
	{
		return MySubscription.empty() && MulticastDelegate.empty();
	}

	static int indexnode;
}; 



/*
void Node::Test()
{
	//Node no(bind(&Node::EventCall, this, std::placeholders::_1));
	
	//MulticastDelegate.emplace_back(&Node::EventCall);
	//MulticastDelegate.emplace_back(&Node::Test);
	
	//std::bind;
}*/
