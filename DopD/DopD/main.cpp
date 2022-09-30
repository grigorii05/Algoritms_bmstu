#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random>

void setMass(std::string& str, std::vector<int>& mass)
{
    std::string el = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            el += str[i];
        }
        if (str[i] == ' ' || str[i + 1] == '\0')
        {
            int i = stoi(el);
            mass.push_back(i);
            el = "";
        }
    }
}

std::pair<int,int> partition(std::vector<int>& mass, const int& l, const int& r)
{
    int v = mass[rand()%( (r - l + 1) ) + l];
    int i = l;
    int j = r;
    int midbegin = l; // начало опрных элементов
    bool is_changed = false;
    int count_repeatmid = 1; // кол-во опорных элементов
    while (i <= j)
    {
        while (mass[i] <= v)
        {
            if (mass[i] == v)
            {
                if (!is_changed)
                {
                    midbegin = i;
                    is_changed = true;
                }
                else count_repeatmid++; // при повторе увелиливввается кол-во опорных элементов
                if (i != r)
                    i++;
                else break;
            }
            if (mass[i] < v) // элемент, меньший опорных, помещаем слева от опорных элементов
            {
                std::swap(mass[i], mass[midbegin]);
                if (i != r)
                {
                    midbegin++;
                    i++;
                }
                else
                {
                    midbegin++;
                    break;
                }
            }
        }

        while (mass[j] > v)
            j--;
        if (i >= j)
            break;
        std::swap(mass[i], mass[j]);
        j--;
    }
    return std::make_pair(midbegin - 1, midbegin + count_repeatmid);
}

void quicksort(std::vector<int>& mass, const int& l, const int& r)
{
    if (l < r)
    {
        std::pair<int, int> q = partition(mass, l, r);
        quicksort(mass, l, q.first);
        quicksort(mass, q.second, r);
    }
}


int main()
{
    std::string str;
    std::vector<int> mass;
    getline(std::cin, str);
    setMass(str, mass);
    quicksort(mass, 0, mass.size() - 1);
    for (int i = 0; i < mass.size() - 1; i++)
    {
        std::cout << mass[i] << " ";
    }
    std::cout << mass[mass.size() - 1] << std::endl;
    return 0;
}