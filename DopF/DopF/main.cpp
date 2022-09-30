#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

void setMass(std::string& str, std::vector<std::string>& mass)
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
            mass.push_back(el);
            el = "";
        }
    }
}

bool NextGEN(std::vector<std::string>& mass,const std::vector<std::string>& begin)
{
    int j = mass.size() - 2;
    while (j != -1 && mass[j] >= mass[j + 1]) j--;
    if (j == -1)
    {
        for (int i = 0; i < int(mass.size() / 2); i++)
        {
            std::swap(mass[i], mass[mass.size() - 1 - i]);
        }
        if (mass == begin) return false; // больше перестановок нет
        else return true;
    }
    int k = mass.size() - 1;
    while (mass[j] >= mass[k]) k--;
    swap(mass[j], mass[k]);
    int l = j + 1, r = mass.size() - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
        swap(mass[l++], mass[r--]);
    if (mass == begin)
        return false; // больше перестановок нет
    return true;
}

void PRINT(std::vector<std::string>& mass)  // вывод перестановки
{
    for (int i = 0; i < mass.size() - 1; i++)
        std::cout << mass[i] << " ";
    std::cout << mass[mass.size() - 1] << std::endl;
}

int main()
{
    std::string str;
    getline(std::cin, str);
    std::vector<std::string> M;
    setMass(str, M);
    PRINT(M);
    std::vector<std::string> begin = M;
    while (NextGEN(M,begin))
        PRINT(M);
    return 0;
}