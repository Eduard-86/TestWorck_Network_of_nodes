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
	������� ������ ����� � ���� ����� Int � ��� ��������
		����� ���� ����� ��� ����� �����������
		����� ������� �� ����� �����������

	��� ������� ����������� ��� ��������

	������ ��� 2 ��������� ������ ������ ���� �������
		��� ������ ������ �������� int 
 
 */

/*
	����� �������� ����� ���� � ���������
	���� ����� ��������� ���� �� �������� ������� �� ����� ��������
		����������� ������� ������� ������� � ������

	����� ����
		�������� ���� ���� �����
			��������� � ���� ����� ���� �� ���������� � ���� ����
			"������ ����� � ���� �������� ������� ����� ���� �� �� ����������� ��� ���������"
		�������� ����� ������� � ���� ���� �������� ���� �������

	��������� �������� - ��������, ����
		��� �������� �� ���� ��������� ������� ���� ��������� � ��������� �� �����
		���� ��������� ���������� � ����� ��������
		� ����� ��� ������ ������� 

	��������� �������� �� ���������� ���� �� ����� ��������� ��������� �������������
 
 */

/*
	30.11
	todo ������ �������� � �������� ���� ����
		������� ������ �� �������
		������� ������ �� �������� 
  
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
		���� ����� ���� �������� � ������� �������� �� ������ ����
	 */
	
	// ��� ���������
	vector<pair<Node* ,function<void(int, Node*)>>> MulticastDelegate;
	
	//vector<function<void(int, Node*)>> MulticastDelegate1;

	// �������� ������ � ������� ����
	// std::placeholders::_1 ������ ��������� ��� ����������� ���������� 
	function<void(int, Node*)> FooEnd1 =
		bind(&Node::EventCall, this, std::placeholders::_1, std::placeholders::_2);

	// ��������
	// � ������ ���� ��������� �� �� ���� �������� ������ ����
	// ��������� ��� ���� ����������, ���� �������� bool - ��� ����� ��� ������ �� ��������
		// int - ��� �������� ������� ��� ����������, ���� ������� �� �������� � ����� ����
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

	// ������� ������� �� ���� �� ���� ��������
	void UnSubscribe();

	Node * CreateAndSubscribeNewNode();

	void Inaction();

#pragma endregion

private:
	
	// ������ ����� ���������� ����� �� ��� ���� ����� ����������� ��������
	// �� ����� �������� �������� ���������� ���������� 
	void Subscribe(Node* NodePtr, function<void(int, Node*)>);

	// ������� ��� �������� 
	void EventSum(int value, Node* callnode)
	{
		// ������� ������� � ����
		pair<bool, int> sub = MySubscription.at(callnode);

		if (sub.first)
		{
			int valuesum = (MySubscription.at(callnode).second += value);

			cout << "����������� - " << callnode
				<< " ���������� - " << this
				<< " ����� ���� ���������� ����� �� ����� ����������� - "
				<< valuesum << endl;
		}
		else
		{
			// TODO ������ ��� ���������� ���������� ! 
			cout << "������ � ���� ����� �� ����� �������� � ������ � ������� �� ������ ����!" << endl;
			cout << "����� ���� : " << this << " ����� � ���� ����� �� ������)" << endl;

		}
	}
	void EventCall(int value, Node* callnode)
	{
		// ������� ������� � ����
		pair<bool, int> sub = MySubscription.at(callnode);

		if (!sub.first)
		{
			int valuecall = (MySubscription.at(callnode).second += 1);

			cout << "����������� - " << callnode
				<< " ���������� - " << this
				<< " ����� ���� ������ �� ����� ����������� - "
				<< valuecall << endl;
		}
		else
		{
			// TODO ������ ��� ���������� ���������� ! 
			cout << "������ � ���� ����� �� ����� �������� � ������ � ������� �� ������ ����!" << endl;
			cout << "����� ���� : " << this << " ����� � ���� ����� �� ������)" << endl;

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
