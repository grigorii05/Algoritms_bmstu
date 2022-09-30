#include <iostream>
#include <string>
#include <vector>

class Bin
{
    std::vector<int64_t> mass;
public:
    int getSize()
    {
        return mass.size();
    }

    void setMass(std::string& str)
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
                int64_t i = stoll(el);
                mass.push_back(i);
                el = "";
            }
        }
    }

    int find(const int64_t Num,  const int& begin, const int& end)
    {
        if (begin > end) return -1;
        if (begin == 0 && end == 0)
        {
            if (mass[0] == Num) return 0;
            else return -1;
        }
        int i = (begin + end) / 2;
        if (mass[i] == Num)
        {
            while (mass[i] == Num)
            {
                i = i - 1;
                if (i == -1) break;
            }
            return (i + 1);
        }
        if (end - begin == 1)
        {
            if (mass[begin] == Num) return begin;
            if (mass[end] == Num) return end;
            return -1;
        }
        if (mass[i] < Num)
        {
            find(Num, i + 1, end);
        }
        else
        {
            find(Num, begin, i - 1);
        }
    }
};

int main()
{
    std::string str;
    Bin bin;
    while (getline(std::cin, str))
    {
        if (str.substr(0, 6) == "search") std::cout << -1 << std::endl;
        else if (!str.empty()) break;
    }
    bin.setMass(str);
    
    std::string Num = "";
    int64_t n;
    while (getline(std::cin, str))
    {
        if (!str.empty())
        {
            Num = str.substr(7, str.size() - 7);
            n = stoll(Num);
            int s = bin.getSize() - 1;
            std::cout << bin.find(n, 0, s) << std::endl;
            Num = "";
        }
    }
    return 0;
}