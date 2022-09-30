#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class GRAPH
{
    unordered_map<string, vector<string>> vertexes; // набор вершин и их соседей
public:
    unordered_map<string, bool> ISvisited;

    void build(const vector<pair<string, string>>& Ribs) // Ribs - отсортирован в main
    {
        vector<string> Neib;
        for (int i = 0; i < Ribs.size(); i++)
        {
            Neib.push_back(Ribs[i].second);
            if (ISvisited.find(Ribs[i].first) == ISvisited.end()) ISvisited.insert({ Ribs[i].first, false });
            if (ISvisited.find(Ribs[i].second) == ISvisited.end()) ISvisited.insert({ Ribs[i].second, false });
            if (i == Ribs.size() - 1)
            {
                vertexes.insert({ Ribs[i].first, Neib });
                //vertexes[Ribs[i].first] = Neib;
                break;
            }
            if (Ribs[i].first != Ribs[i + 1].first)// если следующая вершина отличается от текущей, значит все сосседи текущей
                // вершины добавлены в Neib
            {
                vertexes.insert({ Ribs[i].first, Neib });
                //vertexes[Ribs[i].first] = Neib;
                Neib.clear();
            }
        }
    }
    void Breadth(vector<string>& visited, unordered_set<string>& Que)
    {
        if (Que.empty()) return;
        for (auto& vertex : Que)
        {
            visited.push_back(vertex);
            ISvisited.find(vertex)->second = true;
        }
        //vector<string> NewQue;
        unordered_set<string> QueVisited;
        for (auto& vertex : Que) { // просматривваем вершины в очереди
            for (auto& Neib : vertexes[vertex]) { // извдекаем соседа из очередных вершин
                bool repeatVisited = false;
                bool repeatQue = false;
                if (ISvisited.find(Neib)->second == true) // если нет повтора, то добавляем вершину в новую очередь
                {
                    repeatVisited = true;
                }
                if (QueVisited.find(Neib) != QueVisited.end())
                {
                    repeatQue = true;
                }
                if (repeatVisited == false && repeatQue == false)
                {
                    //NewQue.push_back(Neib);
                    QueVisited.insert(Neib);
                }
            }
        }
        Breadth(visited, QueVisited);
    }

    void Depth(vector<string>& visited, const string& current_vertex)
    {
        for (auto& Neib : vertexes[current_vertex])
        {
            if (ISvisited.find(Neib)->second == false)
            {
                visited.push_back(Neib);
                ISvisited.find(Neib)->second = true;
                Depth(visited, Neib);
            }
        }
    }
};

int main(int argc, char* argv[])
{
    string str;
    string gr_type;
    string search_type;
    string start_ver;
    vector<pair<string, string>> ribs; // ребра 
    pair<string, string> rib; // ребро для добавления в массив ribs

    int i = 0; // для цикла for, который ниже
    while (getline(cin, str))
    {
        if (!str.empty())
        {
            if (str[0] == 'u' || str[0] == 'd')
            {
                gr_type = str[0];
                for (i = 2; str[i] != ' '; i++)
                {
                    start_ver += str[i];
                }
                search_type = str[i + 1];
                break;
            }
        }
    }

    string v1, v2; // вершины, которые считываем после 1ой строки
    while(getline(cin, str))
    {
        if (!str.empty())
        {
            v1 = "";
            v2 = "";
            for (i = 0; str[i] != ' '; i++)
            {
                v1 += str[i];
            }

            for (i = i + 1; str[i] != '\0'; i++)
            {
                v2 += str[i];
            }

            if (gr_type == "u")
            {
                if (v1 != v2) // вершины, указывающие на самих себя не добавляем
                {
                    rib = make_pair(v1, v2);
                    ribs.push_back(rib);
                    rib = make_pair(v2, v1);
                    ribs.push_back(rib);
                }
            }
            else
            {
                if (v1 != v2)// вершины, указывающие на самих себя не добавляем
                {
                    rib = make_pair(v1, v2);
                    ribs.push_back(rib);
                }
            }
        }
    } 

    GRAPH graph;
    sort(ribs.begin(), ribs.end()); // сортируем ребра для того, чтобы легче было найти соедей для каждой вершины
   
    graph.build(ribs);

    vector<string> visited;
    unordered_set<string>SetQue; // соседние вершины
    SetQue.insert(start_ver);
    if (search_type == "b") // ПОИСК В ШИРИНУ
    {
        graph.Breadth(visited, SetQue);
    }
    //-------------------------------------------------------------------
    if (search_type == "d") // ПОИСК В ГЛУБИНУ
    {
        visited.push_back(start_ver);
        graph.ISvisited.find(start_ver)->second = true;
        graph.Depth(visited, start_ver);
    }
    for (auto& i : visited)
    {
        cout << i << endl;
    }
    return 0;
}