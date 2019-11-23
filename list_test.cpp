#include "List.h"
#include <stdio.h>

int main()
{
	List list;

	//list.push_front(49);
	//list.push_front(27);
	//list.push_back(98);
	//list.pop_back();
	list.insert(65, 0);
	//printf("%d\n", list.pop(1));

	list.remove(65);
	list.print();

	return 0;
}
