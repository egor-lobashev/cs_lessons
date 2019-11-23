#include <stdio.h>

class Node
{
public:
	int* value;
	Node* next;

	Node()
	{
		next = nullptr;
		value = nullptr;
	}

	~Node()
	{
		delete value;
	}
};


class List
{
private:
	Node* find_by_index(int index)
	{
		Node* current_node = head;
		for (int i=0; i<index; ++i)
		{
			current_node = current_node->next;
		}	
		return current_node;
	}
public:
	Node* head;

	List()
	{
		head = nullptr;
	}

	~List()
	{
		Node* current_node = head;
		while (current_node != nullptr)
		{
			current_node = current_node->next;
			delete current_node;
		}
	}

	void push_front(int value)
	{
		Node* first = new Node;
		int* first_value = new int;
		*first_value = value;

		first->value = first_value;
		first->next = head;

		head = first;
	}

	int pop_front()
	{
		int pop_value = *head->value;
		Node* new_head = head->next;
		delete head;
		head = new_head;
		return pop_value;
	}

	void insert(int value, int index)
	{
		if (index == 0)
		{
			push_front(value);
		} else {
			Node* previous_node = find_by_index(index-1);

			Node* new_node = new Node;
			int* new_value = new int;
			*new_value = value;

			new_node->value = new_value;
			new_node->next = previous_node->next;

			previous_node->next = new_node;
		}
	}

	int pop(int index)
	{
		if (index == 0)
		{
			return pop_front();
		} else {
			Node* previous_node = find_by_index(index-1);

			int pop_value = *previous_node->next->value;
			Node* replacing_node = previous_node->next->next;
			delete previous_node->next;
			previous_node->next = replacing_node;
			return pop_value;
		}
	}

	void push_back(int value)
	{
		Node** current_node = &head;
		while (*current_node != nullptr)
		{
			current_node = &(*current_node)->next;
		}

		Node* last = new Node;
		int* last_value = new int;
		*last_value = value;

		last->value = last_value;
		last->next = nullptr;

		*current_node = last;
	}

	int pop_back()  // FIXME
	{
		Node* previous_node;
		if (head == nullptr)
		{
			return 0;
		}
		if (head->next == nullptr)
		{
			previous_node = nullptr;
		} else {
			Node* current_node = head;
			while (current_node->next->next != nullptr)
			{
				current_node = current_node->next;
			}
			previous_node = current_node;
		}

		int pop_value = *previous_node->next->value;
		delete previous_node->next;
		previous_node->next = nullptr;
		return pop_value;
	}

	void print()
	{
		Node* current_node = head;
		while (current_node != nullptr)
		{
			printf("%d ", *current_node->value);
			current_node = current_node->next;
		}
		printf("\n");
	}

	int find(int value)
	{
		Node* current_node = head;
		int position = 0;
		bool found_value = false;
		while (current_node != nullptr)
		{
			if (*current_node->value == value)
			{
				found_value = true;
				break;
			}
			current_node = current_node->next;
			position++;
		}
		return (found_value ? position : -1);
	}

	void remove(int value)
	{
		if (head == nullptr)
			return;
		if (*head->value == value)
		{
			pop_front();
			return;
		}
		if (head->next == nullptr)
		{
			return;
		}

		Node* current_node = head;
		bool found_value = false;

		while (current_node->next != nullptr)
		{
			if (*current_node->next->value == value)
			{
				found_value = true;
				break;
			}
			current_node = current_node->next;
		}

		if (found_value)
		{
			Node* replacing_node = current_node->next->next;
			delete current_node->next;
			current_node->next = replacing_node;
		}
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
