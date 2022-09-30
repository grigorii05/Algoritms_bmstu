#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
#include <algorithm>

struct Node
{
    // хранит слово текущего узла
    std::wstring word;

    // ссылки на другой узел в дереве
    std::unordered_map<int, Node*> childrens;
    // конструкторы

    Node(std::wstring& w, std::unordered_map<int, Node*>& c)
    {
        word = w;
        childrens = c;
    }

    Node(std::wstring& w) 
    {
        word = w;
    }
    ~Node()
    {
        for (auto it = childrens.begin(); it != childrens.end(); it++)
        {
            delete it->second;
        }
    }

    Node() {}
};

class BKtree
{
    Node* root;

public:

    BKtree()
    {
        root = nullptr;
    }
    ~BKtree()
    {
        delete root;
    }
    int Min(const int& a,const int& b,const int& c)
    {
        return std::min(a, std::min(b, c));
    }

    int leven(std::wstring& a, std::wstring& b)
    {

        int m = a.length();
        int n = b.length();

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        // заполнение матрицы с использованием dp-подхода

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int cost;
                if (a[i - 1] == b[j - 1])
                {
                    cost = 0;
                }
                else
                {
                    cost = 1;
                }
                dp[i][j] = std::min(dp[i - 1][j] + 1,
                    std::min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost));
                if (i > 1 && j > 1 && a[i - 1] == b[j - 2] && a[i - 2] == b[j - 1])
                {
                    dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost);
                }
            }
        }

        return dp[m][n];
    }


    // добавляет узел дерева в дерево
    void add(std::wstring& str)
    {
        Node* curr = new Node(str);
        if (root == nullptr)
        {
            // если это первый узел
            // затем делаем его корневым узлом
            root = curr;
            return;
        }

        Node* localroot = root;
        while (1)
        {
            if (curr->word == localroot->word)
            {
                delete curr;
                break;
            }
            int dist = leven(curr->word, localroot->word);
            if (localroot->childrens.find(dist) == localroot->childrens.end())
            {
                // добавляем узел curr к дереву
                localroot->childrens[dist] = curr;
                break;
            }
            else
            {
                auto it = localroot->childrens.find(dist);
                localroot = it->second;
            }
        }
    }

    std::vector<std::wstring> getSimilarWords(std::wstring& s)
    {
        std::vector<std::wstring > ret;

        if (root == nullptr) return ret;

        std::deque<Node*> canditates;
        canditates.push_back(root);

        while (!canditates.empty())
        {
            Node* nod = canditates.front();
            canditates.pop_front();
            int dist = leven(nod->word, s);
            if (dist == 0)
            {
                if (ret.empty()) ret.push_back(nod->word);
                else ret[0] = nod->word;
                return ret;
            }
            if (dist == 1) ret.push_back(nod->word);

            if (!nod->childrens.empty())
            {
                int lower = dist - 2;
                int upper = dist + 2;
                for (int i = lower; i <= upper; i++)
                {
                    if (nod->childrens.find(i) != nod->childrens.end())
                    {
                        auto it = nod->childrens.find(i);
                        canditates.push_back(it->second);
                    }
                }
            }
        }
        return ret;
    }
};


int main()
{
#ifdef _MSC_VER
    // Microsoft Visual C++
    setlocale(LC_ALL, ".866");
#else
    // GNU g++
    std::locale loc("");
    std::locale::global(loc);
#endif

	int size = 1;
	std::wcin >> size;
	std::wstring word;
	int i = 0;
    BKtree tree;

	while(i < size)
	{
		getline(std::wcin, word);
		if (!word.empty())
		{
            for (int j = 0; j < word.size(); j++)
            {
                if (int(word[j]) >= 65 && int(word[j]) <= 90)
                {
                    word[j] = word[j] + 32;
                }
                if (int(word[j]) >= 1040 && int(word[j]) <= 1071)// для русскоязычных слов
                {
                    word[j] = word[j] + 32;
                }
                if (int(word[j]) == 1025)
                {
                    word[j] = 1105;
                }
            }
            tree.add(word);
			i++;
		}
	}


	std::vector<std::wstring> findWords;
	while (getline(std::wcin, word))
	{
		if (!word.empty())
		{
            std::wstring forsearch = word;
            for (int j = 0; j < word.size(); j++)
            {
                if (int(forsearch[j]) >= 65 && int(forsearch[j]) <= 90)
                {
                    forsearch[j] = forsearch[j] + 32;
                }
                if (int(forsearch[j]) >= 1040 && int(forsearch[j]) <= 1071)// для русскоязычных слов
                {
                    forsearch[j] = forsearch[j] + 32;
                }
                if (int(forsearch[j]) == 1025)
                {
                    forsearch[j] = 1105;
                }
            }
            findWords = tree.getSimilarWords(forsearch);
            if (!findWords.empty())
            {
                if (findWords[0] == forsearch) {
                    std::wcout << word << " - ok" << std::endl;
                }
                else
                {
                    std::sort(findWords.begin(), findWords.end());
                    std::wcout << word << " -> ";
                    for (int i = 0; i < findWords.size() - 1; i++)
                    {
                        std::wcout << findWords[i] << ", ";
                    }
                    std::wcout << findWords[findWords.size() - 1] << std::endl;
                }
            }
            else
            {
                std::wcout << word << " -?" << std::endl;
            }
		}
	}
	return 0;
}