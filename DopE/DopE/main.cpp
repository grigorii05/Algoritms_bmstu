#include <iostream>
#include <string>

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

bool NumberOk(std::string& str) // функция, проверяющая корректность написания числа после команды
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

class Heap
{
	std::pair<int, std::string>* heap;
	int size;
	int HeapSize;

	void heapify(int i)
	{
		int leftChild;
		int rightChild;
		int largestChild;

		for (; ; )
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			largestChild = i;

			if (leftChild < HeapSize && heap[leftChild].first > heap[largestChild].first)
			{
				largestChild = leftChild;
			}

			if (rightChild < HeapSize && heap[rightChild].first > heap[largestChild].first)
			{
				largestChild = rightChild;
			}

			if (largestChild == i)
			{
				break;
			}

			std::swap(heap[i], heap[largestChild]);
			i = largestChild;
		}
	}
public:
	Heap()
	{
		size = 0; // Основной размер
		heap = nullptr;
		HeapSize = 0; // Текущий размер
	}

	~Heap()
	{
		delete[] heap;
	}

	void Set_size(const int& n)
	{
		size = n;
		heap = new std::pair<int, std::string>[size];
	}

	void Push(std::string& data) {
		int i = HeapSize;
		heap[i].first = HeapSize;
		heap[i].second = data;
		int parentOFlastElement = (i - 1) / 2;
		while (parentOFlastElement >= 0 && i > 0) {
			if (heap[i].first > heap[parentOFlastElement].first) {
				std::swap(heap[i], heap[parentOFlastElement]);
			}
			i = parentOFlastElement;
			parentOFlastElement = (i - 1) / 2;
		}
		HeapSize++;
	}
	std::string Pop()
	{
		std::string poped;
		poped = heap[0].second;
		heap[0].first = heap[HeapSize - 1].first;
		heap[0].second = heap[HeapSize - 1].second;
		HeapSize--;
		heapify(0);
		return(poped);
	}
	void Print()
	{
		if (HeapSize != 0) 
		{
			for (int i = 0; i < HeapSize; ++i)
			{
				int j = HeapSize - 1;
				while (heap[j].first != i)
				{
					j = j - 1;
				}
				std::cout << heap[j].second << ' ';
			}
			std::cout << std::endl;
		}
		else {
			std::cout << "empty" << std::endl;
		}
	}
};

class Stack
{
	int size;
	int count;
	Heap heap;
public:
	Stack(Heap& h)
	{
		heap = h;
		size = 0;
		count = 0;
	}

	void Set_size(const int &s)
	{
		size = s;
		heap.Set_size(size);
	}

	bool Insert(std::string& data)
	{
		if (count < size)
		{
			++count;
			heap.Push(data);
			return false;
		}
		else {
			return true;
		}
	}

	bool Del()
	{
		if (count > 0)
		{
			std::cout << heap.Pop() << std::endl;
			--count;
			return false;
		}
		else 
		{
			return true;
		}
	}

	void Print()
	{
		heap.Print();
	}
};

int main()
{
	std::string command;
	std::string NumOfComm;
	Heap heap;
	Stack stack(heap);
	while (getline(std::cin, command))
	{
		if (ReadComm(command) == "set_size")
		{
			NumOfComm = GetNum(command);
			if (NumberOk(NumOfComm))
			{
				stack.Set_size(stoi(NumOfComm));
				break;
			}
			else
			{
				std::cout << "error" << std::endl;
			}
		}
		else
		{
			if (!command.empty())
			{
				std::cout << "error" << std::endl;
			}
		}
	}

	while (getline(std::cin, command))
	{
		if (ReadComm(command) == "push")
		{
			NumOfComm = GetNum(command);
			if (NumberOk(NumOfComm))
			{
				if (stack.Insert(NumOfComm))
				{
					std::cout << "overflow" << std::endl;
				}
			}
			else
			{
				std::cout << "error" << std::endl;
			}
		}

		if (ReadComm(command) == "pop")
		{
			if (GetNum(command) != " ")
			{
				std::cout << "error" << std::endl;
			}
			else
			{
				if (stack.Del())
				{
					std::cout << "underflow" << std::endl;
				}
			}
		}

		if (ReadComm(command) == "print")
		{
			if (GetNum(command) != " ")
			{
				std::cout << "error" << std::endl;
			}
			else {
				stack.Print();
			}
		}

		if (ReadComm(command) != "print" && ReadComm(command) != "push" && ReadComm(command) != "pop" &&
			!command.empty())
		{
			std::cout << "error" << std::endl;
		}
	}
	return 0;
}