#include <iostream>
#include <string>
#include <vector>

std::string to_binary_string(int n)
{
    if (n == 0) return "0";
    std::string result = "";
    do
    {
        if(n % 2 == 1) result = result + "1";
        else result = result + "0";
        n = n / 2;
    } while (n > 0);
    return result; // порядок чтения бинарного кода справа-> налево,
    //но в данной задаче это не имеет значения, так как нас итересует только вес(кол-во 1ц или 0)
    // и длина бинарного кода
}

int sumof0(const std::string& str)
{
    int s = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '0') s++;
    }
    return s;
}

void findsteps(std::vector<std::string>& step, int& NUM)
{
    if (NUM == 0) return;
    if (NUM % 2 == 0)
    {
        step.emplace_back("dbl");
        NUM = NUM / 2;
    }
    if (NUM % 2 != 0)
    {
        if (NUM == 1)
        {
            step.emplace_back("inc");
            NUM = NUM - 1;
        }
        if (NUM == 3)
        {
            step.emplace_back("inc");
            NUM = NUM - 1;
        }
        else
        {
            if (NUM == 0) return;
            int plus1 = sumof0(to_binary_string(NUM + 1)); // чем больше нулей, тем больше можно беспрерывно делить на 2
            int minus1 = sumof0(to_binary_string(NUM - 1));

            if (plus1 > minus1)
            {
                NUM = NUM + 1;
                step.emplace_back("dec");
            }

            if (plus1 < minus1)
            {
                NUM = NUM - 1;
                step.emplace_back("inc");
            }

            if (plus1 == minus1)
            {
                int sizep1 = to_binary_string(NUM + 1).size(); // выбираем с число с меньшим разрядом - оно ближе к 0
                int sizem1 = to_binary_string(NUM - 1).size();
                if (sizep1 > sizem1)
                {
                    NUM = NUM - 1;
                    step.emplace_back("inc");
                }
                else
                {
                    NUM = NUM + 1;
                    step.emplace_back("dec");
                }
            }
        }
    }
    findsteps(step, NUM);
}

int main()
{
    int NUM;
    std::string N;
    getline(std::cin, N);

    NUM = stoi(N);
    std::vector<std::string> step;
    
    findsteps(step, NUM);

    for (int i = step.size() - 1; i >-1 ; i--)
    {
        std::cout << step[i] << std::endl;
    }
	return 0;
}