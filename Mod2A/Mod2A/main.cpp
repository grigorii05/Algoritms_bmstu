#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstring>

const unsigned long long Mer = 2147483647; //число Мерсенна

std::string ReadComm(std::string& command) // функция, считывающая команду строки
{
	std::string temp; // вспомогательная строка
	int i = 0;
	while ((command[i] != ' ' && command[i] != '\0') && i < command.length())
	{
		temp += command[i];
		++i;
	}
	return temp;
}


std::string GetNum(std::string& command) // функция, возращающая строку, стоящую после команды
{
	int i = 0;
	std::string temp;// вспомогательная строка
	while (command[i] != ' ' && i < command.length()) // саму команду пропускаем
	{
		++i;
	}
	if (command[i] == '\0') { return " "; } // если после команды нет ничего, возвращаем пробел
	++i;
	while (command[i] != '\0' && i < command.size()) // считываем число
	{
		temp += command[i];
		++i;
	}

	return temp;
}

bool NumberOk(const std::string& str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (!isdigit(str[i]) && str[i] != '.')
		{
			return false;
		}
	}
	return true;
}

int p(const int& i) // находим простое число определённой позиции
{
	int simple = 2;
	int j = 1;
	bool is_simple = true;
	while (j != i)
	{
		is_simple = true;
		simple++;
		for (int x = 2; x <= simple - 1; x++)
		{
			if (simple % x == 0)
			{
				is_simple = false;
				break;
			}
		}
		if (is_simple)
		{
			j++;
		}
	}
	return simple;
}

class BMass
{
	std::vector<bool> BitMass;
public:
	void setSize(const int& s)
	{
		BitMass.resize(s, 0);
	}

	void add(const int& i)
	{
		BitMass[i] = 1;
	}

	bool operator[](int& i)
	{
		return BitMass[i];
	}

	void print(std::ostream* stream) {
		std::string result(BitMass.size(), '0');
		for (size_t i = 0; i < BitMass.size(); ++i)
			if (BitMass[i])
				result[i] = '1';

		(*stream) << result;
	}
};

class Bloom
{
	int k;
	int size;
	BMass BitMass;
public:

	int Hash(const int& i, unsigned long long int& key, const int& size_of_set) // хэш-функция
	{
		int pos = (((((unsigned long long int)i) % Mer) * (key % Mer) % Mer
			+ (p(i) % Mer)) % Mer) % size_of_set;
		return pos;
	}

	void setk(const int& K)
	{
		k = K;
	}

	void setSize(const int& K)
	{
		BitMass.setSize(K);
		size = K;
	}

	void add(const std::string& NumOfComm)
	{
		unsigned long long key = stoull(NumOfComm);
		for (int i = 0; i < k; i++)
		{
			BitMass.add(Hash(i + 1, key, size));
		}
	}

	void search(const std::string& NumOfComm)
	{
		unsigned long long key = stoull(NumOfComm);
		bool is_searched = true;
		for (int i = 0; i < k; i++)
		{
			int h = Hash(i + 1, key, size);
			if (BitMass[h] == 0)
			{
				is_searched = false;
				break;
			}
		}
		std::cout << is_searched << std::endl;
	}

	void print()
	{
		BitMass.print(&std::cout);
	}
};

int main(int argc, char* argv[])
{
	std::string str; // строка, которую считываем
	std::string nstr = "";
	std::string Pstr = "";
	Bloom BlFiltr;
	BMass BitMass;
	while (getline(std::cin, str))
	{
		if (!str.empty())
		{
			if (ReadComm(str) == "set")
			{
				int i = 4;
				while (str[i] != ' ')
				{
					nstr += str[i]; // число n
					i++;
				}
				if (nstr != "0" && NumberOk(nstr))
				{
					i++;
					while (str[i] != '\0')
					{
						Pstr += str[i]; // число P
						i++;
					}
					if (stod(Pstr) < 1 && stod(Pstr) > 0 && NumberOk(Pstr))
					{
						int n;
						double P; // переводим стоку в числа
						double m;
						double k;
						n = stoi(nstr);
						P = stod(Pstr);
						nstr.clear();
						Pstr.clear();
						m = -n * log2(P) / log(2);
						k = -log2(P);
						double fractpart; // остаток
						double mint; // целая часть
						double kint;
						fractpart = modf(m, &mint);
						if (fractpart >= 0.5)
						{
							mint = mint + 1;
						}
						fractpart = modf(k, &kint);
						if (fractpart >= 0.5)
						{
							kint = kint + 1;
						}
						if (kint > 0 && mint > 0)
						{
							std::cout << static_cast<int>(mint) << " " << static_cast<int>(kint) << std::endl;
							BlFiltr.setk(static_cast<int>(kint)); // добавляем кол-во хэш функциий
							//BlFiltr.getMass(static_cast<int>(mint)); // инициализация двоичного массива
							BlFiltr.setSize(static_cast<int>(mint));
							break;
						}
						else
						{
							std::cout << "error" << std::endl;
						}
					}
					else
					{
						std::cout << "error" << std::endl;
					}
				}
				else
				{
					std::cout << "error" << std::endl;
				}
			}
			else
			{
				std::cout << "error" << std::endl;
			}
		}
	}
	
	while (getline(std::cin, str))
	{
		if (ReadComm(str) == "add")
		{
			BlFiltr.add(GetNum(str));
		}

		if (ReadComm(str) == "search")
		{
			BlFiltr.search(GetNum(str));
		}

		if (ReadComm(str) == "print")
		{
			if (GetNum(str) != " ")
			{
				std::cout << "error" << std::endl;
			}
			else
			{
				BlFiltr.print();
				std::cout << std::endl;
			}
		}

		if (ReadComm(str) != "print" && ReadComm(str) != "add" && ReadComm(str) != "search" &&
			!str.empty())
		{
			std::cout << "error" << std::endl;
		}
	}
	return 0;
}