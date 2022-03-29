#pragma once
#include "Node.h"

int Node::indexnode = 0;

Node::Node(Node* NodePtr, function<void(int, Node*)> Del)
{
	this->Subscribe(NodePtr, Del);

}

Node::~Node()
{
	delete(&MySubscription);
	delete(&FooEnd1);
}

#pragma region Events

void Node::CallEvent()
{
	for(int i = 0; i < MulticastDelegate.size(); ++i)
	{
		MulticastDelegate[i].second(rand() % 100, this);
	}
}

void Node::SubscribeOnNode()
{
	//find the node
	/*
		Блок кода отвечающий за поиск ноды 
		сперва возмём рандомного соседа, после возмём рандомного соседа соседа
			и подпишимся

		Подписать мы можем только на соседа соседа, поэтому не может возникнуть ситуации
			когда 2 ноды подписанны друг на друга ибо если одна подписанна они уже соседи 

	
		Чекаем один ли унего лишь подписчик - подписка 
	 */
	
	int my = MySubscription.size();
	int del = MulticastDelegate.size();

	// осталась ли нода без связей на данный момент 
	if (my && del)
	{
		return;
	}
	
	int indexsusa = rand() % (my + del);

	Node* newsub = nullptr;

	// todo чёт кампилятору не по нраву, разберись
	/*
	MySubscription.emplace(NewNode, std::make_pair(i, 0));
	*/

	if (indexsusa < my && my != 0)
	{
		map<Node*, pair<bool, int>>::iterator iter = MySubscription.begin();

		// переместить итератор на нужное число индексов
		int indexmysub = indexsusa == my ? indexsusa - 1 : indexsusa;
		std::advance(iter, indexmysub);

		int mysub_nei = iter->first->MySubscription.size();
		int del_nei = iter->first->MulticastDelegate.size();
		int indexsusa_nei = rand() % (mysub_nei + del_nei);

		if(indexsusa_nei < mysub_nei && mysub_nei != 0)
		{
			map<Node*, pair<bool, int>>::iterator iter_nei = iter->first->MySubscription.begin();
			
			int indexmysub_nei = indexsusa_nei == mysub_nei ? indexsusa_nei - 1 : indexsusa_nei;
			std::advance(iter_nei, indexmysub_nei);

			newsub = iter_nei->first;
		}
		else if(del_nei != 0)
		{
			int inxdel = indexsusa_nei - mysub_nei;

			// todo всё ли подтерается когда удолдяется динамический объект ???
			newsub = iter->first->MulticastDelegate[inxdel].first;
		}
		else
		{
			// этот ретурнт тут на всякий
			// todo и вообще воткни сюда исключение 
			return;
		}
	}
	else if(del != 0)
	{
		int inxdel = indexsusa - my;

		Node* delNode = MulticastDelegate[inxdel].first;

		int mysub_nei = delNode->MySubscription.size();
		int del_nei = delNode->MulticastDelegate.size();
		int indexsusa_nei = rand() % (mysub_nei + del_nei);

		if(indexsusa_nei < mysub_nei && mysub_nei != 0)
		{
			map<Node*, pair<bool, int>>::iterator iter_nei = delNode->MySubscription.begin();

			int indexmysub_nei = indexsusa_nei == mysub_nei ? indexsusa_nei - 1 : indexsusa_nei;
			std::advance(iter_nei, indexmysub_nei);

			newsub = iter_nei->first;
		}
		else if (del_nei != 0)
		{
			int inxdel = indexsusa_nei - mysub_nei;
			
			// todo всё ли подтерается когда удолдяется динамический объект ???
			newsub = delNode->MulticastDelegate[inxdel].first;
		}
		else
		{
			// этот ретурнт тут на всякий
			// todo и вообще воткни сюда исключение
			return;
		}
	}

	if (newsub != this)
	{
		// todo дерьмо, поправь потом
		// Блок поиска нет ли уже этой подписки у меня
		for (int i = 0; MulticastDelegate.size() > i; ++i)
		{
			if (MulticastDelegate[i].first == newsub)
			{
				std::cout << "\t\tПодписка не произошла, была получена нода которая уже в подписках" << std::endl;
				return;
			}
		}

		if (MySubscription.find(newsub) != MySubscription.end())
		{
			std::cout << "\t\tПодписка не произошла, была получена нода которая уже в подписках" << std::endl;
			return;
		}

		// Ура подписка удолась !!!

		pair<bool, function<void(int, Node*)>> RandoFu = RandomEvern();


		newsub->Subscribe(this, RandoFu.second);

		MySubscription.emplace(newsub, std::make_pair(RandoFu.first, 0));

		std::cout << "\t\tПодписка успешна, адрес ноду на которую произошла подписка - " << newsub << std::endl;
		
		return;
	}
	else
	{
		std::cout << "\t\tПодписка не произошла, при попытке подписаться нода получила ссылку на себя" << std::endl;
		return;
	}
}

void Node::UnSubscribe()
{
	int mysub = MySubscription.size();
	if(!mysub)
	{
		cout << "\t\tУ ноды - " << this << " нет подписок" << endl;
		return;
	}
	
	int indexunsub = rand() % mysub;
	
	map<Node*, pair<bool, int>>::iterator iter = MySubscription.begin();
	std::advance(iter, indexunsub);

	iter->first->UnSubscribeOnMe(this);
	
	//MySubscription.erase(iter->first);
	MySubscription.erase(iter);
}

Node* Node::CreateAndSubscribeNewNode()
{
	pair<bool, function<void(int, Node*)>> RandoFu = RandomEvern();

	Node* NewNode = new Node(this, RandoFu.second);

	MySubscription.emplace(NewNode, std::make_pair(RandoFu.first, 0));

	return NewNode;
	
}

void Node::Inaction()
{
	// Тут должно быть сообщеие об инактиве и всё, покачто
}

#pragma endregion

void Node::Subscribe(Node* NodePtr, function<void(int, Node*)> Del)
{

	MulticastDelegate.push_back(std::make_pair(NodePtr, Del));
}


void Node::EventSum(int value, Node* callnode)
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


void Node::EventCall(int value, Node* callnode)
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


void Node::UnSubscribeOnMe(Node* node)
{
	vector<pair<Node*, function<void(int, Node*)>>>::iterator endit = MulticastDelegate.end();

	for (vector<pair<Node*, function<void(int, Node*)>>>::iterator itdel = MulticastDelegate.begin();
		itdel != endit; itdel++)
	{
		if (itdel->first == node)
		{
			MulticastDelegate.erase(itdel);
			return;
		}
	}
	// если до сюда дошли значит отписки не случилось и чтото пошло не по плану
	// todo можно въебать исключение 
}

pair<bool, function<void(int, Node*)>> Node::RandomEvern()
{
	int EventKey = rand() % 2;
	function<void(int, Node*)> FooEnd;
	
	// Вызовы 0 Сумма 1 
	if (EventKey)
	{
		FooEnd = bind(&Node::EventSum, this, std::placeholders::_1, std::placeholders::_2);
	}
	else
	{
		FooEnd = bind(&Node::EventCall, this, std::placeholders::_1, std::placeholders::_2);
	}

	return std::make_pair(EventKey, FooEnd);
}