#include <iostream>
#include <vector>
#include <string>

bool IS_OK(std::string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

int greatest_common_divisor(const int& a, const int& b) {
	if (a == 0 && b == 0) return 0;
	if (a == 0) return b;
	if (b == 0) return a;
	if (a % b == 0)
		return b;
	if (b % a == 0)
		return a;
	if (a > b)
		return greatest_common_divisor(a % b, b);
	return greatest_common_divisor(a, b % a);
}

int HODofALL(const std::vector<std::pair<int, int>>& pairs,const int& W)
{
	int res = greatest_common_divisor(W, pairs[0].first);
	for (int i = 1; i < pairs.size(); i++)
		res = greatest_common_divisor(res, pairs[i].first);
	return res;
}

class Bag
{
	int W;
	int maxweightofelements;
	int NOD;
	std::vector<std::pair<int, int>> pairs;
	std::vector<std::vector<int>> A;
	std::vector<int> ans;
public:
	Bag(std::vector<std::pair<int, int>>& p)
	{
		pairs = p;
	}

	Bag(int& WfrMain,int& MaxweightofElements,int& Nod, std::vector<std::pair<int, int>>& p)
	{
		W = WfrMain;
		maxweightofelements = MaxweightofElements;
		NOD = Nod;
		pairs = p;
	}

	std::string If_W_is_null()
	{
		if (pairs.size() == 0)
		{
			return "0 0";
		}
		int cost = 0;
		std::vector<int> nums;
		std::string to_print = "";
		for (int i = 0; i < pairs.size(); i++)
		{
			if (pairs[i].first == 0)
			{
				cost += pairs[i].second;
				nums.push_back(i + 1);
			}
		}
		to_print = "0 " + std::to_string(cost) + '\n';
		for (auto& n : nums)
		{
			to_print += (std::to_string(n) + '\n');
		}
		return to_print;
	}

	void setA()
	{
		A.resize(pairs.size() + 1);
		for (int i = 0; i < pairs.size() + 1; i++)
		{
			if (maxweightofelements >= W)
				A[i].resize(maxweightofelements / NOD + 1, 0);
			else A[i].resize(W / NOD + 1, 0);
		}

		for (int k = 1; k < pairs.size() + 1; k++)
		{
			for (int s = 0; s < A[k].size(); s++)
			{
				if (s >= pairs[k - 1].first / NOD)
				{
					A[k][s] = std::max(A[k - 1][s], (A[k - 1][s - (pairs[k - 1].first) / NOD] +
						pairs[k - 1].second));
				}
				else
				{
					A[k][s] = A[k - 1][s];
				}
			}
		}
	}

	void findAns(const int& k, const int& s)
	{
		if (A[k][s] == 0) return;
		if (A[k - 1][s] == A[k][s])
		{
			findAns(k - 1, s);
		}
		else
		{
			findAns(k - 1, s - pairs[k - 1].first / NOD);
			ans.push_back(k - 1);
		}
	}

	void PrintAns()
	{
		int cost = 0;
		int weight = 0;
		for (int i = 0; i < ans.size(); i++)
		{
			weight += pairs[ans[i]].first;
			cost += pairs[ans[i]].second;
		}
		std::cout << weight << " " << cost << std::endl;
		for (int i = 0; i < ans.size(); i++)
		{
			std::cout << ans[i] + 1 << std::endl;
		}
	}
};


int main()
{
	std::string str = "";
	int W = 0;
	while (getline(std::cin, str))
	{
		if (!str.empty())
		{
			bool is_ok = true;
			for (int i = 0; i < str.size(); i++)
			{
				if (!isdigit(str[i]) || str[i] == ' ')
				{
					std::cout << "error" << std::endl;
					is_ok = false;
				}
			}
			if (is_ok)
			{
				W = stoi(str);
				break;
			}
		}
	}

	std::string wi , ci;
	std::vector<std::pair<int,int>> pairs;
	int maxweightofelements = 0;
	while (getline(std::cin, str))
	{
		if (!str.empty())
		{
			wi = "";
			ci = "";
			int i = 0;
			while (str[i] != ' ')
			{
				wi += str[i];
				i++;
			}
			i++;
			while (str[i] != '\0')
			{
				ci += str[i];
				i++;
			}

			if (IS_OK(wi) && IS_OK(ci))
			{
				std::pair <int, int> p;
				p = std::make_pair(stoi(wi), stoi(ci));
				pairs.push_back(p);
				if (maxweightofelements < stoi(wi)) maxweightofelements = stoi(wi);
			}
			else
			{
				std::cout << "error" << std::endl;
			}
		}
	}

	if (W == 0)
	{
		Bag bag(pairs);
		std::cout << bag.If_W_is_null() << std::endl;
		return 0;
	}

	// Генерируем А(N,W)
	int NOD = HODofALL(pairs, W);
	
	Bag bag(W, maxweightofelements, NOD, pairs);

	bag.setA();

	int k = pairs.size();
	int s = W / NOD;

	bag.findAns(k, s);

	bag.PrintAns();
	return 0;
}