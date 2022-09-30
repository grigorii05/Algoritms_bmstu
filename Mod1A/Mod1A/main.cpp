#include <iostream>
#include <string>

void getNum(std::string& str, int64_t& summ)
{
	std::string Num; // число в строке
	for (int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]) || (str[i] == '-' && isdigit(str[i + 1])) )
		{
			Num += str[i];
			if (str[i + 1] == '\0') summ += std::stoi(Num);
		}
		else
		{
			if (!Num.empty())
			{
				summ += std::stoi(Num);
				Num = "";
			}
		}
	}
}

int main()
{	std::string str; // считывем строку
    int64_t  summ = 0; // сумма чисел
	getline(std::cin, str);
	if (!str.empty()) getNum(str, summ);
	/*while (getline(std::cin, str))
	{
		if(!str.empty()) getNum(str,summ);
	}
	*/
	std::cout << summ << std::endl;
	return 0;
}