#include <thread>
#include <fstream>
#include <iostream>
#include <vector>

void sort(std::vector<int*> data)
{
    // std::cout << data.size() << " ";

    if (data.size() == 1)
        return;

    std::vector<int*> data_1, data_2;
    int i;
    for (i = 0; i < data.size()/2; i++)
    {
        data_1.push_back(data[i]);
    }
    for (; i < data.size(); i++)
    {
        data_2.push_back(data[i]);
    }

    std::thread sort_1(sort, data_1);
    std::thread sort_2(sort, data_2);
    
    sort_1.join();
    sort_2.join();

    i = 0;
    int j = 0;
    std::vector<int> new_data;
    while (i+j < data.size())
    {
        if (i == data_1.size())
        {
            new_data.push_back(*data_2[j]);
            j++;
            continue;
        }
        if (j == data_2.size())
        {
            new_data.push_back(*data_1[i]);
            i++;
            continue;
        }

        if (*data_1[i] <= *data_2[j])
        {
            new_data.push_back(*data_1[i]);
            i++;
        }
        else
        {
            new_data.push_back(*data_2[j]);
            j++;
        }
    }

    for (i=0; i<data.size(); i++)
    {
        *data[i] = new_data[i];
    }
}

int main()
{
    std::ifstream file;
    file.open("input");

    int N;
    file >> N;

    int* values = new int[N];
    std::vector<int*> data;

    for (int i = 0; i < N; i++)
    {
        file >> values[i];
        data.push_back(&values[i]);
    }

    file.close();

    std::thread sort_1(sort, data);
    sort_1.join();

    for (int i = 0; i < N; i++)
    {
        std::cout << values[i] << ' ';
    }
    std::cout << std::endl;

    delete [] values;
    return 0;
}