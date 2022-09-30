#include <iostream>
#include <unordered_map>
#include <string>
#include <math.h>
#include<vector>

class MinHeap
{
    std::unordered_map<int64_t, int> HeapMap;
    std::vector<std::pair<int64_t, std::string>> HeapVec;

    void Heapify(const int& i)
    {
        int l = 2 * i + 1; int r = 2 * i + 2;
        int min;
        if (l <= HeapVec.size() - 1)
        {
            if (HeapVec[l].first < HeapVec[i].first) min = l;
            else  min = i;
        }
        else
        {
            min = i;
        }
        if (r <= HeapVec.size() - 1)
        {
            if (HeapVec[r].first < HeapVec[min].first) min = r;
        }
        if (min != i)
        {
            HeapMap.find(HeapVec[min].first)->second = i;
            HeapMap.find(HeapVec[i].first)->second = min;
            std::swap(HeapVec[i], HeapVec[min]);
            Heapify(min);
        }
        else
        {
            if (i < HeapVec.size() && i > 0)
            {
                int iparent = floor((i - 1) / 2);
                if (HeapVec[i].first < HeapVec[iparent].first)
                {
                    HeapMap.find(HeapVec[iparent].first)->second = i;
                    HeapMap.find(HeapVec[i].first)->second = iparent;
                    std::swap(HeapVec[i], HeapVec[iparent]);
                    Heapify(iparent);
                }
            }
        }
    }

public:
 
    std::vector<std::pair<int64_t, std::string>> setHeap()
    {
        return HeapVec;
    }

    void Insert(int64_t& K, std::string& V) {
        if (HeapVec.size() == 0)
        {
            HeapMap[K] = HeapVec.size();
            HeapVec.emplace_back(K, V);
            return;
        }
        int i = HeapVec.size();
        HeapVec.emplace_back(K, V);
        int iparent = floor((i - 1) / 2);
        while (i > 0 && HeapVec[iparent].first > K)
        {
            HeapMap[HeapVec[iparent].first] = i;
            std::swap(HeapVec[i], HeapVec[iparent]);
            i = iparent;
            iparent = floor((iparent - 1) / 2);
        }
        HeapMap[HeapVec[i].first] = i;
    }

    bool Remove(const int64_t& key)
    {
        if (HeapVec.size() == 0)
        {
            return true;
        }
        else
        {
            if (HeapMap.find(key) != HeapMap.end())
            {
                int index = HeapMap.find(key)->second;
                if (index == HeapVec.size() - 1)
                {
                    HeapVec.pop_back();
                    HeapMap.erase(HeapMap.find(key));
                }
                else
                {
                    HeapMap.find(HeapVec[index].first)->second = HeapVec.size() - 1;
                    HeapMap.find(HeapVec[HeapVec.size() - 1].first)->second = index;
                    std::swap(HeapVec[index], HeapVec[HeapVec.size() - 1]);
                    HeapVec.pop_back();
                    HeapMap.erase(HeapMap.find(key));
                    Heapify(index);
                }
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    std::string _Minimum() {
        if (HeapVec.size() != 0)
        {
            return std::to_string(HeapVec[0].first) + " 0 " + HeapVec[0].second;
        }
        else
        {
            return "error";
        }
    }

    std::string _Maximum() {
        if (HeapVec.size() != 0)
        {
            if (HeapVec.size() == 1)
            {
                return std::to_string(HeapVec[0].first) + " 0 " + HeapVec[0].second;
            }
            int ParentOfLastVer = floor((HeapVec.size() - 1 - 1) / 2);
            std::pair<int64_t, std::string> MAX = HeapVec[HeapVec.size() - 1];
            int indexMAX = HeapVec.size() - 1;
            for (int i = HeapVec.size() - 1; i > ParentOfLastVer; i--)
            {
                if (HeapVec[i].first > MAX.first)
                {
                    MAX = HeapVec[i];
                    indexMAX = i;
                }
            }
            return std::to_string(MAX.first) + " " + std::to_string(indexMAX) + " " + MAX.second ;
        }
        else
        {
            return "error" ;
        }
    }

    bool _Search_SET(int64_t& key, std::string& V) {
        if (HeapMap.find(key) == HeapMap.end())
        {
            return true;
        }
        else
        {
            HeapVec[HeapMap.find(key)->second].second = V;
            return false;
        }
    }

    std::string _Search(const int64_t& key) {
        std::unordered_map<int64_t, int>::iterator it  = HeapMap.find(key);
        if (it == HeapMap.end())
        {
            return "0";
        }
        else
        {
            return "1 " + std::to_string(it->second ) + " " + HeapVec[it->second].second;
        }
    }

    std::string extract()
    {
        if (HeapVec.size() == 1)
        {
            std::string output = std::to_string(HeapVec[0].first) + " " + HeapVec[0].second;
            HeapVec.pop_back();
            HeapMap.erase(HeapMap.find(HeapVec[0].first));
            return output;
        }
        else
        {
            if (HeapVec.size() == 0)
            {
                return "error"; // -выход из функции т.к.ошибка
            }
            std::string output = std::to_string(HeapVec[0].first) + " " + HeapVec[0].second;
            HeapMap.find(HeapVec[0].first)->second = HeapVec.size() - 1;
            HeapMap.find(HeapVec[HeapVec.size() - 1].first)->second = 0;
            std::swap(HeapVec[0], HeapVec[HeapVec.size() - 1]);
            HeapMap.erase(HeapMap.find(HeapVec[HeapVec.size() - 1].first));
            HeapVec.pop_back();
            Heapify(0);
            return output;
        }
    }

    void print(int& index, int& level)
    {
        bool is_end = false;
        for (int lev = 0; lev < level; index++, lev++)
        {
            if (index < HeapVec.size())
            {
                std::cout << "[" + std::to_string(HeapVec[index].first) + " " + HeapVec[index].second + " " + std::to_string(HeapVec[floor((index - 1) / 2)].first) + "]";
            }
            else
            {
                std::cout << "_";
                is_end = true;
            }
            if (lev != level - 1)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << std::endl;
            }
        }
        if (index > HeapVec.size() - 1) return;

        level = 2 * level;
        print(index, level);
    }

    bool is_notRepeat(int64_t& K, std::string& V)
    {
        if (HeapMap.find(K) != HeapMap.end()) return false;
        else return true;
    }
};

int main()
{
    std::string str;
    MinHeap heap;
    int64_t Kint;
    std::string K = "";
    std::string V = "";
    while (getline(std::cin, str))
    {
        if (!str.empty())
        {
            if (str.substr(0, 3) == "add")
            {
                int i = 4;
                V = "";
                K = "";
                while (str[i] != ' ')
                {
                    K += str[i];
                    i++;
                }
                i++;
                while (str[i] != '\0')
                {
                    V += str[i];
                    i++;
                }
                Kint = stoll(K);
                if (heap.is_notRepeat(Kint, V))
                {
                    heap.Insert(Kint, V);
                }
                else
                {
                    std::cout << "error" << std::endl;
                }
            }

            if (str.substr(0, 3) == "set")
            {
                int i = 4;
                K = "";
                V = "";
                while (str[i] != ' ')
                {
                    K += str[i];
                    i++;
                }
                i++;
                while (str[i] != '\0')
                {
                    V += str[i];
                    i++;
                }
                Kint = stoll(K);
                if (heap._Search_SET(Kint, V))
                {
                    std::cout << "error" << std::endl;
                }
            }

            if (str.substr(0, 3) == "min")
            {
                std::cout << heap._Minimum() << std::endl;
            }

            if (str.substr(0, 3) == "max")
            {
                std::cout << heap._Maximum() << std::endl;
            }

            if (str.substr(0, 6) == "search")
            {
                std::cout << heap._Search(std::stoll(str.data() + 6)) << std::endl;
            }

            if (str.substr(0, 6) == "delete")
            {
                if(heap.Remove(std::stoll(str.data() + 6)))
                    std::cout << "error" << std::endl;
            }

            if (str.substr(0, 5) == "print")
            {
                if (heap.setHeap().size() != 0)
                {
                    std::cout << "[" + std::to_string(heap.setHeap()[0].first) + " " << heap.setHeap()[0].second + "]" << std::endl;
                    if (heap.setHeap().size() > 1)
                    {
                        int level = 2;
                        int index = 1;
                        heap.print(index, level);
                    }
                }
                else
                {
                    std::cout << "_" << std::endl;
                }
            }

            if (str.substr(0, 7) == "extract")
            {
                std::cout << heap.extract() << std::endl;
            }

            if (str.substr(0, 3) != "add" && str.substr(0, 3) != "set" && str.substr(0, 3) != "min" &&
                str.substr(0, 3) != "max" && str.substr(0, 6) != "search" && str.substr(0, 6) != "delete" && str.substr(0, 5) != "print"
                && str.substr(0, 7) != "extract")
            {
                std::cout << "error" << std::endl;
            }
        }
    }
    return 0;
}