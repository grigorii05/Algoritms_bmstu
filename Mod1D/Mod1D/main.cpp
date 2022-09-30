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
    unordered_map<string, vector<string>> vertexes; // ����� ������ � �� �������
public:
    unordered_map<string, bool> ISvisited;

    void build(const vector<pair<string, string>>& Ribs) // Ribs - ������������ � main
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
            if (Ribs[i].first != Ribs[i + 1].first)// ���� ��������� ������� ���������� �� �������, ������ ��� ������� �������
                // ������� ��������� � Neib
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
        for (auto& vertex : Que) { // �������������� ������� � �������
            for (auto& Neib : vertexes[vertex]) { // ��������� ������ �� ��������� ������
                bool repeatVisited = false;
                bool repeatQue = false;
                if (ISvisited.find(Neib)->second == true) // ���� ��� �������, �� ��������� ������� � ����� �������
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
    vector<pair<string, string>> ribs; // ����� 
    pair<string, string> rib; // ����� ��� ���������� � ������ ribs

    int i = 0; // ��� ����� for, ������� ����
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

    string v1, v2; // �������, ������� ��������� ����� 1�� ������
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
                if (v1 != v2) // �������, ����������� �� ����� ���� �� ���������
                {
                    rib = make_pair(v1, v2);
                    ribs.push_back(rib);
                    rib = make_pair(v2, v1);
                    ribs.push_back(rib);
                }
            }
            else
            {
                if (v1 != v2)// �������, ����������� �� ����� ���� �� ���������
                {
                    rib = make_pair(v1, v2);
                    ribs.push_back(rib);
                }
            }
        }
    } 

    GRAPH graph;
    sort(ribs.begin(), ribs.end()); // ��������� ����� ��� ����, ����� ����� ���� ����� ������ ��� ������ �������
   
    graph.build(ribs);

    vector<string> visited;
    unordered_set<string>SetQue; // �������� �������
    SetQue.insert(start_ver);
    if (search_type == "b") // ����� � ������
    {
        graph.Breadth(visited, SetQue);
    }
    //-------------------------------------------------------------------
    if (search_type == "d") // ����� � �������
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