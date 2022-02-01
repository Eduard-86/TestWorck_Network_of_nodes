#pragma once
#include "Node.h"
#include "math.h"

Node::Node(Node* NodePtr, function<void(int, Node*)> Del)
{
	this->Subscribe(NodePtr, Del);

	//function<void(Node&, int)> Del = &Node::EventSum;

	//node.Subscribe(Del);
}

Node::~Node()
{
	delete(&MySubscription);
	delete(&FooEnd1);
}

void Node::SubscribeOnNode()
{
	//find the node
	/*
		���� ���� ���������� �� ����� ���� 
		������ ����� ���������� ������, ����� ����� ���������� ������ ������
			� ����������

		��������� �� ����� ������ �� ������ ������, ������� �� ����� ���������� ��������
			����� 2 ���� ���������� ���� �� ����� ��� ���� ���� ���������� ��� ��� ������ 

	
		������ ���� �� ����� ���� ��������� - �������� 
	 */

	
	int my = MySubscription.size();
	int del = MulticastDelegate.size();
	int indexsusa = rand() % my + del;

	Node* newsub = nullptr;

	// todo ��� ����������� �� �� �����, ���������
	/*
	MySubscription.emplace(NewNode, std::make_pair(i, 0));
	*/

	if (indexsusa < my && my != 0)
	{
		map<Node*, pair<bool, int>>::iterator iter = MySubscription.begin();

		// ����������� �������� �� ������ ����� ��������
		int indexmysub = indexsusa == my ? indexsusa - 1 : indexsusa;
		std::advance(iter, indexmysub);

		//todo ��� ����� ������ ����� ������ ������ �������
		// neighbor

		int mysub_nei = iter->first->MySubscription.size();
		int del_nei = iter->first->MulticastDelegate.size();
		int indexsusa_nei = rand() % mysub_nei + del_nei;

		if(indexsusa_nei < mysub_nei && mysub_nei != 0)
		{
			map<Node*, pair<bool, int>>::iterator iter_nei = iter->first->MySubscription.begin();
			
			int indexmysub_nei = indexsusa_nei == mysub_nei ? indexsusa_nei - 1 : indexsusa_nei;
			std::advance(iter_nei, indexmysub_nei);

			newsub = iter_nei->first;
		}
		else if(del_nei != 0)
		{
			int tempindex_nei = del_nei > mysub_nei ? del_nei - mysub_nei : mysub_nei - del_nei;
			
			int inxdel = indexsusa_nei == tempindex_nei ? tempindex_nei - 1 : tempindex_nei;

			// todo �� �� ����������� ����� ���������� ������������ ������ ???
			newsub = iter->first->MulticastDelegate[inxdel].first;
		}
		else
		{
			return;
		}
	}
	else if(del != 0)
	{
		int tempindex = del > my ? del - my : my - del;

		int inxdel = indexsusa == tempindex ? tempindex - 1 : tempindex;

		Node* delNode = MulticastDelegate[inxdel].first;

		int mysub_nei = delNode->MySubscription.size();
		int del_nei = delNode->MulticastDelegate.size();
		int indexsusa_nei = rand() % mysub_nei + del_nei;

		if(indexsusa_nei < mysub_nei && mysub_nei != 0)
		{
			map<Node*, pair<bool, int>>::iterator iter_nei = delNode->MySubscription.begin();

			int indexmysub_nei = indexsusa_nei == mysub_nei ? indexsusa_nei - 1 : indexsusa_nei;
			std::advance(iter_nei, indexmysub_nei);

			newsub = iter_nei->first;
		}
		else if (del_nei != 0)
		{
			int tempindex_nei = del_nei > mysub_nei ? del_nei - mysub_nei : mysub_nei - del_nei;

			int inxdel = indexsusa_nei == tempindex_nei ? tempindex_nei - 1 : tempindex_nei;
			
			// todo �� �� ����������� ����� ���������� ������������ ������ ???
			newsub = delNode->MulticastDelegate[inxdel].first;
		}
		else
		{
			return;
		}

		if(MulticastDelegate[inxdel].first != this)
		{
			// todo ������, ������� �����
			// ���� ������ ��� �� ��� ���� �������� � ����
			bool keymyneighbor = false;
			for (int i = 0; MulticastDelegate.size() > i; ++i)
			{
				if (MulticastDelegate[i].first == MulticastDelegate[inxdel].first)
					keymyneighbor = true;

			}
			if (MySubscription.find(MulticastDelegate[inxdel].first) == MySubscription.end())
				keymyneighbor = true;

			if (keymyneighbor)
				return;


			// ��� �������� ������� !!!

			pair<bool, function<void(int, Node*)>> RandoFu = RandomEvern();

			
			MulticastDelegate[inxdel].first->MulticastDelegate[my].first->Subscribe(this, RandoFu.second);

			MySubscription.emplace(MulticastDelegate[inxdel].first->MulticastDelegate[my].first, std::make_pair(RandoFu.first, 0));

			return;
		}
	}

	if (newsub != this)
	{
		// todo ������, ������� �����
		// ���� ������ ��� �� ��� ���� �������� � ����
		for (int i = 0; MulticastDelegate.size() > i; ++i)
		{
			if (MulticastDelegate[i].first == newsub)
			{
				// todo ����� ���������� ���� ��������� �� �������� 
				return;
			}
		}

		if (MySubscription.find(newsub) != MySubscription.end())
		{
			// todo ����� ���������� ���� ��������� �� �������� 
			return;
		}

		// ��� �������� ������� !!!

		pair<bool, function<void(int, Node*)>> RandoFu = RandomEvern();


		newsub->Subscribe(this, RandoFu.second);

		MySubscription.emplace(newsub, std::make_pair(RandoFu.first, 0));

		// todo ����� ���������� ���� ��������� �� �������� 
		return;
	}

}

void Node::Subscribe(Node* NodePtr, function<void(int, Node*)> Del)
{
	
	MulticastDelegate.push_back(std::make_pair(NodePtr, Del));
}

void Node::UnSubscribe()
{
	int my = MySubscription.size();
	int del = MulticastDelegate.size();
	int indexsusa = rand() % my + del;


	if (indexsusa <= my)
	{
		// ����������� �������� �� ������ ����� ��������
		int indexmysub = indexsusa == my ? indexsusa - 1 : indexsusa;

		map<Node*, pair<bool, int>>::iterator iter = MySubscription.begin();
		std::advance(iter, indexmysub);


		iter->first->UnSubscribeOnMe(this);

	}
	else
	{
		int inxdel = indexsusa == del ? indexsusa - my - 1 : indexsusa - my;

		if (MulticastDelegate[inxdel].first != this)
		{
			return;
		}
	}

	
	//toDO ��������
	// �������� ���� �� ����������� ��������
	map<Node*, pair<bool, int>>::iterator iter = MySubscription.begin();
	
	// ��� ������� ������, ��� ����� 
	for (; iter != MySubscription.end(); ++iter)
	{

	}

	iter->first->UnSubscribeOnMe(this);
	
	MySubscription.erase(iter->first);
}

void Node::UnSubscribeOnMe(Node* node)
{
	vector<pair<Node*, function<void(int, Node*)>>>::iterator endit = MulticastDelegate.end();
	
	for(vector<pair<Node*, function<void(int, Node*)>>>::iterator itdel = MulticastDelegate.begin();
		itdel > endit; itdel++)
	{
		if(itdel->first == node)
		{
			MulticastDelegate.erase(itdel);
			break;
		}
	}
}

void Node::CreateAndSubscribeNewNode()
{
	//bool EventKey = (bool)rand() % 2;

	pair<bool, function<void(int, Node*)>> RandoFu = RandomEvern();

	Node* NewNode = new Node(this, RandoFu.second);

	MySubscription.emplace(NewNode, std::make_pair(RandoFu.first, 0));
	
}


pair<bool,function<void(int, Node*)>> Node::RandomEvern()
{
	bool EventKey = (bool)rand() % 2;
	function<void(int, Node*)> FooEnd;

	// ������ 0 ����� 1 
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
