#include <vector>
#include <iostream>


std::vector<int> sort_sqares(std::vector<int>& task)
{
	int N = task.size();
	std::vector<int> plus, minus;
	for (int i = 0; i < N; i++)
	{
		int current_value = task[i];
		if (current_value > 0)
			plus.push_back(current_value*current_value);
		else
			minus.push_back(current_value*current_value);
	}

	int plus_position = 0, minus_position = minus.size() - 1;
	int value_plus, value_minus;
	int actual_inf = plus.back() + minus[0];
	std::vector<int> answer(N);

	for (int i = 0; i < N; i++)
	{
		value_plus = (plus_position >= 0 ? plus[plus_position] : actual_inf);
		value_minus = (minus_position >= 0 ? minus[minus_position] : actual_inf);
		if (value_plus < value_minus)
		{
			answer[i] = value_plus;
			plus_position++;
		} else {
			answer[i] = value_minus;
			minus_position--;
		}
	}
	return answer;
}

int main()
{
	std::vector<int> one = {-3, -1, 0, 2, 5, 6, 7, 9};
	std::vector<int> two = sort_sqares(one);
	for (int i = 0; i < two.size(); i++)
		std::cout << two[i] << ' ';
	std::cout << std::endl;
	return 0;
}
