#include <iostream>
#include <string>
#include <map>
#include <vector>

void getMass(std::string& str, std::map<std::string, int>& mass)
{
    std::string el = "";
    for(int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            el += str[i];
        }
        if (str[i] == ' ' || str[i + 1] == '\0')
        {
            if (mass[el] == 0)
            {
                mass[el] = 1;
            }
            else
            {
                mass[el] = mass[el] + 1;
            }
            el = "";
        }
    }
}

std::string find(std::map<std::string, int>& mass)
{
    std::string finded;
    int max = mass.begin()->second;
    for (auto it = mass.begin(); it != mass.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
        }
    }

    for (auto it = mass.begin(); it != mass.end(); it++)
    {
        if (it->second == max)
        {
            finded = it->first;
            break;
        }
    }
    return finded;
}

int main()
{
    std::string str;
    std::map<std::string, int> mass;
    getline(std::cin, str);
    getMass(str, mass);
    std::cout << find(mass) << std::endl;
    return 0;
}