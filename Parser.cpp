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
bool errorCheck(int isThereError) {
	switch (isThereError)
	{
	case 1:
	case 2:
	case 3: cout << "Wrong written number"; return false;
	case 4:
	case 5:
	case 6:
	default: return true;
		break;
	}


}
bool Parser::write(const string& filename) const
{
	if (errorCheck)
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
	}
	
	
	return true;
}
int countDigits(string line)
{
	int count = 0;
	for (char i : line) {


		if ((i >= '0' && i <= '9') || i == '-') {
			count++;
		}
		else {
			break;
		}
	}
	return count;
}
string applyCommand(vector<int>numbersArray, string temp, string attribute, int attributeINT, string result,int isThereError) {

	int numbersArraySize = numbersArray.size();
	if (temp == "AGG-SUM")
	{
		int sum = 0;
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			sum += numbersArray[i];
		}

		result = to_string(sum);

	}
	else if (temp == "AGG-PRO")
	{
		int pro = 1;
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			pro *= numbersArray[i];
		}

		result = to_string(pro);

	}
	else if (temp == "AGG-AVG")
	{
		int count = 0;
		int sum = 0;
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			sum += numbersArray[i];
			count++;
		}

		result = to_string((sum / count));

	}
	else if (temp == "AGG-FST")
	{
		result = to_string(numbersArray[0]);

	}
	else if (temp == "AGG-LST")
	{
		numbersArraySize = numbersArray.size();
		result = to_string(numbersArray[numbersArraySize - 1]);

	}
	else if (temp == "SRT-REV")
	{
		reverse(numbersArray.begin(), numbersArray.end());
		numbersArraySize = numbersArray.size();
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "SRT-DST")
	{

		unsigned size = numbersArraySize;
		for (size_t i = 0; i < size - 1; i++)
		{

			bool dublicate = false;
			int j = i + 1;
			for (; j < size; j++)
			{
				if (numbersArray[i] == numbersArray[j])
				{
					dublicate = true;
					break;
				}
			}
			if (dublicate == true)
			{
				numbersArray.erase(numbersArray.begin() + j, numbersArray.begin() + j + 1);
				--size;
			}
		}
		numbersArraySize = numbersArray.size();
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);
	}
	else if (temp == "MAP-INC")
	{
		/*for (size_t i = 0; i < attribute.size(); i++)
		{
			if (!(attribute[i]>=0 && attribute[i]<=9)||(attribute[0]=='-'))
			{
				isThereError = 6;
				errorCheck(isThereError);
				return;
			}
		}*/
		attributeINT = stoi(attribute);

		for (size_t i = 0; i < numbersArraySize; i++)
		{
			numbersArray[i] += attributeINT;
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "MAP-MLT")
	{
	for (size_t i = 0; i < attribute.size(); i++)
	{
		/*if (!(attribute[i] >= 0 && attribute[i] <= 9) || (attribute[0] == '-'))
		{
			isThereError = 6;
			errorCheck(isThereError);
			return;
		}*/
	}
		attributeINT = stoi(attribute);
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			numbersArray[i] *= attributeINT;
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "SRT-ORD")
	{
		if (attribute == "ASC")
		{
			sort(numbersArray.begin(), numbersArray.end());
		}
		else if (attribute == "DSC")
		{
			sort(numbersArray.begin(), numbersArray.end(), greater<int>());
		}
		else
	/*	{
			isThereError = 6;
			errorCheck(isThereError);
			return;
		}*/
		for (size_t i = 0; i < numbersArraySize; i++)
		{

			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "SRT-SLC")
	{
	/*for (size_t i = 0; i < attribute.size(); i++)
	{
		if (!(attribute[i] >= 0 && attribute[i] <= 9))
		{
			isThereError = 6;
			errorCheck(isThereError);
			return;
		}
	}*/
		attributeINT = stoi(attribute);
	/*	if (attributeINT > numbersArray.size())
		{
			isThereError = 6;
			errorCheck(isThereError);
			return;
		}*/
		numbersArray.erase(numbersArray.begin(), numbersArray.begin() + attributeINT);
		int numbersArrayS = numbersArray.size();
		for (size_t i = 0; i < numbersArrayS; i++)
		{
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);
	}

	return result;
}
vector<int> addNumsToVector(stack <string>numbers, int counterDigits, string singleNum, int arrayCount, int isThereError) {
	string lenght = numbers.top();
	int lenghtLenght = lenght.length();
	int spaceCount = 0;
	for (size_t i = 0; i < lenghtLenght; i++)
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

		counterDigits = countDigits(num);
		singleNum = num.substr(0, counterDigits);
		int singleNumSize = singleNum.size();
		if (singleNumSize > 0)
		{
			if (singleNum[0] == '0')
			{
				isThereError = 3;
				errorCheck(isThereError);
				abort();
			}
		}
		for (size_t i = 0; i < singleNumSize; i++)
		{
		   /* if (!((singleNum[i]>='0') && (singleNum[i]<='9') || (singleNum[0]=='-')))
		    {
				isThereError = 2;
				errorCheck(isThereError);
		        return;
		    }*/
		}
		numbersArray[arrayCount] = stoi(singleNum);
		num.erase(0, counterDigits + 1);
		arrayCount++;
		counterDigits = 1;


	}
	return numbersArray;
}
void Parser::calculate(const string& temp,int isThereError)
{
	int CounterForClosingCommands = 0;
	int counterForAttrubutes = 0;
	int startingIndexForAttributes = 0;
	string attribute;
	int attributeINT = 0;
	string commandTop = commands.top();
	bool needsToBreak = false;
	int counterDigits = 1;
	string singleNum;
	int arrayCount = 0;
	int commandSize = commandTop.size();



	for (size_t i = 0; i < commandSize; i++)
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
		vector<string>commandsForChecking{"MAP-INC","MAP-MLT","AGG-SUM","AGG-PRO","AGG-AVG","AGG-FST","AGG-LST","SRT-REV","SRT-ORD","SRT-SLC","SRT-DST"}; 
		for (size_t i = 0; i < commandsForChecking.size(); i++)
		{
			if (temp != commandsForChecking[i])
			{
				isThereError = 1;
				errorCheck(isThereError);
				return;
			}
			
		}

		 if ((temp == "AGG-SUM") || (temp == "AGG-PRO") || (temp == "AGG-AVG") && addNumsToVector(numbers, counterDigits, singleNum, arrayCount,isThereError).size() < 2)
		{
			 isThereError = 4;
			 errorCheck(isThereError);
			 return;
		}

		string result;
		result = applyCommand(addNumsToVector(numbers, counterDigits, singleNum, arrayCount,isThereError), temp, attribute, attributeINT, result,isThereError);
		numbers.pop();
		if (numbers.empty())
		{
			numbers.push(result);
		}
		else if (numbers.top() == "")
		{
			numbers.top() = result;
		}
		else if (numbers.top() != result)
		{
			numbers.top() += " " + result;
		}

		commands.pop();
		lastCommandOpenning = false;
	}

}
void Parser::lexer()
{

	int counterForFindingCommands = 0;
	int counterForFindingNumbers = 0;
	int CounterForClosingCommands = 0;
	unsigned inputSize = input.length();
	string temp;
	string num;
	bool IslastTagOpen = false;
	int isThereError = 0;

	for (size_t i = 0; i < inputSize - 1; i++)
	{
		temp = "";
		num = "";
		int startIndex = 0;
		startIndex = i + 1;


		if (input[i] == '<' && input[i + 1] != '/')  //finds the open tags and adds them to a stack
		{
			IslastTagOpen = true;
			while (input[i + 1] != '>')
			{
				counterForFindingCommands++; i++;
			}
			temp = input.substr(startIndex, counterForFindingCommands);
			commands.push(temp);
			counterForFindingCommands = 0;
			lastCommandOpenning = true;
		}
		else if (input[i] == '>' && input[i + 1] == '<' && IslastTagOpen == true)
		{
			numbers.push("");
		}
		else if (input[i] == '>' && input[i + 1] != '<') // gets the numbers and puts the in a stack
		{
			IslastTagOpen = false;
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
			IslastTagOpen = false;
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
			CounterForClosingCommands = 0;
			calculate(temp,isThereError);
		}
	}

}
