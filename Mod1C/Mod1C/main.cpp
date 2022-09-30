#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string ReadComm(string& command) // функци€, считывающа€ команду строки
{
	string temp; // вспомогательна€ строка
	int i = 0;
	while ((command[i] != ' ' && command[i] != '\0') && i < command.length())
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
		if (str[i] == ' ')
		{
			return false;
		}
	}
	return true;
}


int main(int argc, char* argv[])
{
	string command;
	string NumOfComm = "0";
	//vector<string> Mass; // ћассив, который будет реализован в виде стека	

	ifstream finput(argv[1]);
	ofstream foutput;
	foutput.open(argv[2]);
	while (getline(finput, command))
	{
		if (ReadComm(command) == "set_size")
		{
			NumOfComm = GetNum(command);
			if (NumberOk(NumOfComm))
			{
				//Mass.resize(stoi(NumOfComm));// выдел€ем место под массив
				break;
			}
			else
			{
				foutput << "error" << endl;
			}
		}
		else
		{
			if (!command.empty())
			{
				foutput << "error" << endl;
			}
		}
	}

	int size = stoi(NumOfComm);
	string* mass = new string[size];

	int head = 0; // номер €чейки головы
	int tail = 0; // номер €чейки хвоста
	bool is_empty = true; // проверка массива на пустоту
	while (getline(finput, command))
	{
		if (ReadComm(command) == "push")
		{
			NumOfComm = GetNum(command);
			if (NumberOk(NumOfComm))
			{
				if ( is_empty == false && ((tail == size - 1 && head == 0)
					|| tail + 1 == head))
				{
					foutput << "overflow" << endl;
				}
				else
				{
					if (is_empty)
					{
						mass[tail] = GetNum(command);
						is_empty = false;
					}
					else
					{
						if (tail == size-1)
						{
							tail = 0;
							mass[tail] = GetNum(command);
							is_empty = false;
						}
						else
						{
							tail++;
							mass[tail] = GetNum(command);
							is_empty = false;
						}
					}
				}
			}
			else
			{
				foutput << "error" << endl;
			}
		}

		if (ReadComm(command) == "pop")
		{
			if (GetNum(command) != " ")
			{
				foutput << "error" << endl;
			}
			else
			{
					if (is_empty == true)
					{
						foutput << "underflow" << endl;
					}
					else
					{
						if (head == size - 1) // голова находитс€ на краю справа
						{
							foutput << mass[head] << endl;
							if (head == tail)
							{
								is_empty = true;
							}
							else
							{
								head = 0;
							}
						}
						else
						{
							foutput << mass[head] << endl;
							if (head == tail)
							{
								is_empty = true;
							}
							else
							{
								head++;
							}
						}
					}
			}
		}

		if (ReadComm(command) == "print")
		{
			if (GetNum(command) != " ")
			{
				foutput << "error" << endl;
			}
			else
			{
				if (!is_empty)
				{
					int i = head;
					while (i != tail)
					{
						foutput << mass[i] << " ";
						i++;
						if (i == size) i = 0;
					}
					foutput << mass[tail] << endl;
				}
				else
				{
					foutput << "empty" << endl;
				}
			}
		}

		if (ReadComm(command) != "print" && ReadComm(command) != "push" && ReadComm(command) != "pop" &&
			!command.empty())
		{
			foutput << "error" << endl;
		}
	}
	finput.close();
	foutput.close();
	return 0;
}