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

public:

	Notework_manager(int start_size)
	{
		Node* temptr = new Node();

		NodeArr.push_back(temptr);

		for (int i = 1; i < start_size; ++i)
		{

			Node* temp = new Node();

			NodeArr.push_back(temp);

			// ���� �������� ����������� �������� �� ��������

			// todo ��� ����� � ������ � ��������� �������� 
			pair<bool, function<void(int, Node*)>> RandoFu = temp->RandomEvern();

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

		for (int i = NodeArr.size() - 1; i > -1; --i)
		{
			if(NodeArr[i]->IsAlone())
			{
				NodeArr.erase(NodeArr.begin() + i);
			}
		}
		
		for (int i = 0; i < NodeArr.size(); ++i)
		{
			// ������ ����� ���� �������� ������� �����

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