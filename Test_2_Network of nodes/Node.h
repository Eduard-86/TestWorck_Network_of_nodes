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
	void EventSum(int value, Node* callnode);
	
	void EventCall(int value, Node* callnode);
	
	void UnSubscribeOnMe(Node*);

	pair < bool, function<void(int, Node*)>> RandomEvern();

	bool IsAlone()
	{
		return MySubscription.empty() && MulticastDelegate.empty();
	}

	static int indexnode;
}; 
