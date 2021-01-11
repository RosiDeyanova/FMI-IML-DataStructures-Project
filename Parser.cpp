#include "Parser.h"

Parser::Parser()
{
	lastCommandOpenning = false;

}

bool Parser::read(const string& filename)
{
	ifstream fin(filename);
	if (!fin)
	{
		return false;
	}
	while (fin)
	{
		char c;
		fin.get(c);
		if (fin)
		{
			input += c;
		}
	}
	fin.close();
	return true;
}

bool Parser::write(const string& filename) const
{
	ofstream fout(filename);
	if (!fout)
	{
		return false;
	}
		
	if (!(fout << numbers.top()))
	{
		return false;
	}
	fout.close();
	return true;
}

void Parser::calculate(const string& temp)
{
    int CounterForClosingCommands = 0;
    int counterForAttrubutes = 0;
    int startingIndexForAttributes = 0;
    string attribute;
    int attributeINT;
    string commandTop = commands.top();
    bool needsToBreak = false;
    int counterDigits = 1;
    int k = 0;
    string singleNum;
    int arrayCount = 0;



    for (size_t i = 0; i < commandTop.size(); i++)
    {
        if (commandTop[i] == '"')
        {
            startingIndexForAttributes = i + 1;
            while (commandTop[i + 1] != '"')
            {
                counterForAttrubutes++;
                i++;
                needsToBreak = true;
            }

            attribute = commandTop.substr(startingIndexForAttributes, counterForAttrubutes);
            commands.top() = commandTop.substr(0, commands.top().size() - 3 - counterForAttrubutes);

            if (needsToBreak == true)
            {
                break;
            }
        }
    }


    if (temp == commands.top())
    {
        string lenght = numbers.top();
        int spaceCount = 0;
        for (size_t i = 0; i < lenght.length(); i++)
        {
            if (lenght[i] == ' ')
            {
                spaceCount++;
            }
        }
        vector<int>numbersArray(spaceCount + 1);
        string num = numbers.top();

        while (!num.empty())
        {
            if (num[k] != ' ' && num[k + 1] != ' ' && num[k + 1] != '/0')
            {
                counterDigits++; 
            }
            singleNum = num.substr(k, counterDigits);
            numbersArray[arrayCount] = stoi(singleNum);
            num.erase(k, counterDigits + 1);
            arrayCount++;
            counterDigits = 1;

        }
        string result;

        if (temp == "AGG-SUM")
        {
            int sum = 0;
            for (size_t i = 0; i < numbersArray.size(); i++)
            {
                sum += numbersArray[i];
            }

            result = to_string(sum);
            numbers.pop();

            if (numbers.empty())
            {
                numbers.push(result);
            }
            numbers.top() += " " + result;
            commands.pop();
        }
        else if (temp == "AGG-PRO")
        {
            int pro = 1;
            for (size_t i = 0; i < numbersArray.size(); i++)
            {
                pro *= numbersArray[i];
            }

            result = to_string(pro);
            numbers.pop();

            if (numbers.empty())
            {
                numbers.push(result);
            }
            numbers.top() += " " + result;
            commands.pop();
        }
        else if (temp == "AGG-AVG")
        {
            int count = 0;
            int sum = 0;
            for (size_t i = 0; i < numbersArray.size(); i++)
            {
                sum += numbersArray[i];
                count++;
            }

            result = to_string((sum / count));
            numbers.pop();

            if (numbers.empty())
            {
                numbers.push(result);
            }
            numbers.top() += " " + result;
            commands.pop();
        }
        else if (temp == "AGG-FST")
        {
            result = to_string(numbersArray[0]);
            numbers.pop();

            if (numbers.empty())
            {
                numbers.push(result);
            }
            numbers.top() += " " + result;
            commands.pop();
        }
        else if (temp == "SRT-DST")
        {
            if (numbersArray.size() > 1)
            {
                for (size_t i = 0; i < numbersArray.size(); i++)
                {
                    for (size_t j = i + 1; j < numbersArray.size(); j++)
                    {
                        if (numbersArray[i] == numbersArray[j])
                        {
                            numbersArray.erase(numbersArray.begin() + j);
                        }
                    }
                }
            }
        }
        else if (temp == "MAP-INC")
        {
            attributeINT = stoi(attribute);
            for (size_t i = 0; i < numbersArray.size(); i++)
            {
                numbersArray[i] += attributeINT;
                result += to_string(numbersArray[i]) + ' ';
            }
            result.erase(result.size() - 1);

            numbers.pop();


            if (numbers.empty())
            {
                numbers.push(result);
            }
            else { numbers.top() += " " + result; }
            commands.pop();
        }
        else if (temp == "SRT-ORD")
        {
            if (attribute == "ASC")
            {
                sort(numbersArray.begin(), numbersArray.end());
            }
            for (size_t i = 0; i < numbersArray.size(); i++)
            {

                result += to_string(numbersArray[i]) + ' ';
            }
            result.erase(result.size() - 1);

            numbers.pop();


            if (numbers.empty())
            {
                numbers.push(result);
            }
            numbers.top() += " " + result;
            commands.pop();
        }

        else
         {
            //print out "Wrong tag format"
         }
        lastCommandOpenning = false;
    }
  
}

void Parser::lexer()
{

    int counterForFindingCommands = 0;
    int counterForFindingNumbers = 0;
    int CounterForClosingCommands = 0;
    unsigned inputSize = input.length();


    for (size_t i = 0; i < inputSize - 1; i++)
    {
        string temp;
        string num;
        int startIndex = 0;
        startIndex = i + 1;

        if (input[i] == '<' && input[i + 1] != '/')  //finds the open tags and adds them to a stack
        {
            while (input[i + 1] != '>')
            {
                counterForFindingCommands++; i++;
            }
            temp = input.substr(startIndex, counterForFindingCommands);
            commands.push(temp);
            counterForFindingCommands = 0;
            lastCommandOpenning = true;
        }

        else if (input[i] == '>' && input[i + 1] != '<') // gets the numbers and puts the in a stack
        {
            while (input[i + 1] != '>' && input[i + 1] != '<')
            {
                counterForFindingNumbers++; i++;
            }

            temp = input.substr(startIndex, counterForFindingNumbers);

            if (lastCommandOpenning)
            {
                numbers.push(temp);
            }
            else {
                if (numbers.empty()) {
                    numbers.push(temp);
                }
                else {
                    numbers.top() += " " + temp;
                }
            }

            counterForFindingNumbers = 0;
        }
        else if (input[i] == '<' && input[i + 1] == '/') //checking if the tags are written correctly and what are they
        {

            int k = 0;
            int arrayCount = 0;
            int counterDigits = 1;
            string num;
            string singleNum;

            while (input[i + 1] != '>')
            {
                CounterForClosingCommands++; i++;
            }
            temp = input.substr(startIndex + 1, CounterForClosingCommands - 1);
        }
    }
}
