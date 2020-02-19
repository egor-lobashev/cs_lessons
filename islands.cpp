#include <vector>
#include <iostream>
#include <fstream>
#include <string>


std::vector<std::vector<int>> read_map(std::string filename, int &N, int &M)
{
	std::ifstream file;
	file.open(filename);
	file >> N >> M;
	std::vector<std::vector<int>> output(N, std::vector<int>(M));

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			file >> output[i][j];
		}
	}
	file.close();
	return output;
}

const std::vector<std::vector<int>> neighbours = {{0,1}, {1,0}, {0,-1}, {-1,0}};

void dump_island(std::vector<std::vector<int>>& map, int N, int M, int x, int y)
{
	map[x][y] = 0;
	for (int i = 0; i < 4; i++)
	{
		int x1 = x + neighbours[i][0];
		int y1 = y + neighbours[i][1];
		if ((x1 < 0) or (x1 >= N) or (y1 < 0) or (y1 >= M))
			continue;

		if (map[x1][y1] == 1)
		{
			dump_island(map, N, M, x1, y1);
		}
	}
}
	
int count_islands(std::vector<std::vector<int>>& map, int N, int M)
{
	int islands_number = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 1)
			{
				islands_number += 1;
				dump_island(map, N, M, i, j);
			}
		}
	}
	return islands_number;
}

int main()
{
	int N, M;
	std::vector<std::vector<int>> map = read_map("input", N, M);
	std::cout << count_islands(map, N, M) << std::endl;
	return 0;
}
