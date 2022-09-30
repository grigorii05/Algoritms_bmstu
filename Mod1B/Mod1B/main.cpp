#include <iostream>
#include <string>

using namespace std;

string ReadComm(string& command) // функци€, считывающа€ команду строки
{
	string temp; // вспомогательна€ строка
	int i = 0;
	while ( (command[i] != ' ' && command[i] != '\0')  && i < command.length() )
	{
		temp += command[i];
		++i;
	}
	return temp;
}


string GetNum(string& command) // функци€, возращающа€ строку, сто€щую после команды
{
	int i = 0;
	string temp;// вспомогательна€ строка
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

bool NumberOk(string& str) // функци€, провер€юща€ корректность написани€ числа после команды
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ' )
		{
			return false;
		}
	}
	return true;
}

int main()
{
	string command;
	string NumOfComm = "0";
	while (getline(cin, command))
	{
		if (ReadComm(command) == "set_size")
		{
			NumOfComm = GetNum(command);
			if (NumberOk(NumOfComm))
			{
				break;
			}
			else
			{
				cout << "error" << endl;
			}
		}
		else
		{
			if (!command.empty())
			{
				cout << "error" << endl;
			}
		}
	}
	int size = 0;
	int count = -1;
	size = stoi(NumOfComm);
	string* mass =  new string[size];

	while (getline(cin, command)) 
	{
				if (ReadComm(command) == "push")
				{
					NumOfComm = GetNum(command);
					if (NumberOk(NumOfComm))
					{
						if (count != size - 1)
						{
							count++;
							mass[count] = GetNum(command);
						}
						else
						{
							cout << "overflow" << endl;
						}
					}
					else
					{
						cout << "error" << endl;
					}
				}

				if (ReadComm(command) == "pop")
				{
					if (GetNum(command) != " ")
					{
						cout << "error" << endl;
					}
					else
					{
						if (count != -1)
						{
							cout << mass[count] << endl;
							count--;
						}
						else
						{
							cout << "underflow" << endl;
						}
					}
				}

				if (ReadComm(command) == "print")
				{
					if (GetNum(command) != " ")
					{
						cout << "error" << endl;
					}
					else
					{
						if (count != -1)
						{
							for (int i = 0; i < count; ++i)
							{
								cout << mass[i] << " ";
							}
							cout << mass[count] << endl;
						}
						else
						{
							cout << "empty" << endl;
						}
					}
				}

				if (ReadComm(command) != "print" && ReadComm(command) != "push" && ReadComm(command) != "pop" &&
					!command.empty() )
				{
					cout << "error" << endl;
				}
	}
	delete[] mass;
	return 0;
}