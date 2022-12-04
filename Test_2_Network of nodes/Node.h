#pragma once
#include <functional>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#include <ctime>
#include <stdlib.h>

//using namespace std;

/*
	Событие должно нести в себе число Int и доп операцию
	Сумма всех чисел это этого отправителя
	Число событий от этого отправителя

	Тип события назначается при подписке

	то есть это 2 отдельных метода нашего узла которые
	при вызове примут значение int

*/

/*
	Давай прогоним весь цикл и подытожим
	Узлы могут выполнить одни из действий которые мы знаем рандомно
	вероятность каждого события задаётся вручную

	Этапы сети
	Основной этап всех узлов
	Созданные в этом этапе узлы не участвуют в этом тике
	"то есть когда у ноды выпадает создать новую ноду то мы откладываем это действие"
	Удаление узлов которые в этом тике потеряли всех соседей

	Структура действий - делегаты, мапа
	При подписке на ноду подпичкик передаёт свой указатель и указатель на метод
	нода сохраняет подписчика и метод отдельно
	и когда она создаёт событие

	программа работает до вырождения либо до явной остановки программы пользователем
 
 */

	/** Образец
	* @brief Вставка элемента в список после указаного
	* @param node  Вставляемый элемент
	* @param after Элемент, после которого будет произведена вставка. Если равен nullptr, то
	*				вставка будет произведена в начало списка
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
protected:
	/**
	 * @brief Ноды подписанные на меня.
	 *		Контейнер хранящий пары в массиве:
	 *			Указатель на подписавшуюся ноду
	 *			Делегат переданный этой нодой
	*/ // мб стоит хранить не пару а только делигат, но это не точно
	vector<pair<Node* ,function<void(int, Node*)>>> MulticastDelegate;

	// Хранения делегата произволдиться с помащью бинд
	/*
		std::placeholders::_1 данный синтаксис для определения параметров 
		function<void(int, Node*)> FooEnd1 =
			bind(&Node::EventCall, this, std::placeholders::_1, std::placeholders::_2);
	*/

	/**
	 * @brief Ноды на которые подписан данная ноду, передачей делегата.
	 * В мапе хранится следующая информация
	 *		// bool - это какой тип метода мы передали
	 *		// int - это значения которое нас интересует, инфа которую мы получали с этого узла
	*/
	map<Node*, pair<bool, int>> MySubscription;

	friend class Notework_manager;
	
public: 

	Node(Node* NodePtr, function<void(int, Node*)> Del);

	Node() {};

	~Node() {};
 
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

protected:
	
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
