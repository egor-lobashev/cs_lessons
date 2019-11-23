#include <stdio.h>

class Node
{
public:
	int* value;
	Node* next;
};


class List
{
public:
	Node* head = nullptr;

	~List()
	{
		Node* current_node;
		while (current_node != nullptr)
		{
			delete current_node->value;
			current_node = current_node->next;
		}
	}

	void push_front(int value)
	{
		int* first = new int;
		*first = value;
		head->value = first;
	}

	int& operator[](int index)
	{
		Node* current_node = head;
		for (int i=0; i<index; ++i)
		{
			current_node = current_node->next;
		}
		return *current_node->value;
	}
};
