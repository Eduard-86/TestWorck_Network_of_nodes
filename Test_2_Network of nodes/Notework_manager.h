#pragma once
#include "Node.h"
#include "vector"

using std::vector;

class Notework_manager
{
	
	
	/*
	 *�������� 
		����� ����� ������� �����
		����� ����� 2 �������  � ��������� ������ � � �������
		����� �������������� ��������� ������ ���� ���
			��� �������� ����� �������� ������
	 */
private:

	std::vector<Node*> NodeArr;
	std::vector<Node*> NewNodeArr;

	int callEvet, subscribeOnNode, unSubscribe, creatandSub, inaction;

	int start_size;

public:

	Notework_manager()
	{
		std::cout << "=== ����������� ��������� ���� ===" << std::endl;
		std::cout << "* ������� ��������� ����� ���" << std::endl;

		std::cin >> start_size;

		if(start_size <= 1)
		{
			std::cout << "����� ��� ������ ��������� 1 !" << std::endl;
			exit(0);
		}
		
		std::cout << "* ������������ 100 �������� ����� ����� ��������" << std::endl;
		std::cout << "  ����� ����� ����� ������������� ��������� ���� ����� 100" << std::endl;

		std::cout << "\t * ����� ������ - " ;
		std::cin >> callEvet;

		//std::cout << std::endl;
		std::cout << "\t * �������� �� ���� - ";
		std::cin >> subscribeOnNode;

		//std::cout << std::endl;
		std::cout << "\t * ������� �� ���� - ";
		std::cin >> unSubscribe;

		//std::cout << std::endl;
		std::cout << "\t * �������� � �������� �� ���� - ";
		std::cin >> creatandSub;

		//std::cout << std::endl;
		std::cout << "\t * ������� �������� �� �������� - ";
		std::cin >> inaction;

		std::cout << std::endl;
		
		if(100 != callEvet + subscribeOnNode + unSubscribe + creatandSub + inaction)
		{
			std::cout << "�� �� ��������� �� �������" << std::endl;
			exit(0);
		}
		else
		{
			std::cout << "�� ��������� �������!" << std::endl;
		}

		
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < start_size; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// ���� �������� ����������� �������� �� ��������
 
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

			// ���� �������� ����������� �������� �� ��������

			pair<bool, function<void(int, Node*)>> RandoFu = NodeArr[i - 1]->RandomEvern();

			temp->Subscribe(NodeArr[i - 1], RandoFu.second);

			NodeArr[i - 1]->MySubscription.emplace(temp, std::make_pair(RandoFu.first, 0));
		}
	}
	
	void Tick()
	{
		/*
			������ ���������� �� ���� ��������� � �������� �� �� ������� ��������

			����� ���������� �� ������� NodeArr � ���������� � ������� �������� �����

			� ����� ������ ����� ��������� ��������� ���������� � ��������
		 */

		std::cout << "--����� ��������� ��� ��������--" << std::endl;
		
		for (int i = NodeArr.size() - 1; i > -1; --i)
		{
			if(NodeArr[i]->IsAlone())
			{
				std::cout << "\t������ � ���� ������� ��� �������� - " << NodeArr[i] << std::endl;
				NodeArr.erase(NodeArr.begin() + i);
			}
		}


		std::cout << "--���� ������ �������--" << std::endl;
		
		for (int i = 0; i < NodeArr.size(); ++i)
		{
			// ������ ����� ���� �������� ������� �����

			int RandIndex = rand() % 5;

			switch (RandIndex)
			{
				case 0:
				{
					std::cout << "\t���� - " << NodeArr[i] << " ������������ ��������" << std::endl;
					NodeArr[i]->CallEvent();
					break;
				}
				case 1:
				{
					std::cout << "\t���� - " << NodeArr[i] << " ������������� �� ��������� ����" << std::endl;
					NodeArr[i]->SubscribeOnNode();
					break;
				}
				case 2:
				{
					std::cout << "\t���� - " << NodeArr[i] << " ������������ �� ����� ��������" << std::endl;
					NodeArr[i]->UnSubscribe();
					break;
				}
				case 3:
				{
					std::cout << "\t���� - " << NodeArr[i] << " ������ � ������������� �� ����" << std::endl;
					NewNodeArr.push_back(NodeArr[i]->CreateAndSubscribeNewNode());
					break;
				}
				case 4:
				{
					std::cout << "\t���� - " << NodeArr[i] << " ���������� ��������" << std::endl;
					NodeArr[i]->Inaction();
					break;
				}
				default :
				{
					cout << "�� ��� ����� ����� ?" << endl <<
						"��� ��� ����� ��� � ��������� ������ ������ �������� 4 ???\n";
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