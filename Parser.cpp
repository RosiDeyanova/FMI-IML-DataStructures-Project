#include "Parser.h"

Parser::Parser()
{
	lastCommandOpenning = false;
	isThereError = 0;

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
	case 1:cout << "Syntax error \nTry different input"; exit(0); break;
	case 2:cout << "No letters allowed between the tags \nTry different input"; exit(0); break;
	case 3: cout << "Number incorrect \nTry different input"; exit(0); break;
	case 4:cout << "Not enough numbers for the tag \nTry different input"; exit(0); break;
	case 5:break;
	case 6:cout << "Incorrect attribute \nTry different input"; exit(0); break;
	default: return true;
		break;
	}
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
int countDigits(std::string line)
{
	int count = 0;
	for (char i : line) {


		if (i !=' ') {
			count++;
		}
		else {
			break;
		}
	}
	return count;
}
string applyCommand(vector<int>numbersArray, string temp, string attribute, int attributeINT, string result, int isThereError)
{
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
		for (size_t i = 0; i < attribute.size(); i++)
		{
			if (attribute[i] == '-')
			{
				continue;
				if (!(attribute[i] >= '0' && (attribute[i] <= '9')))
				{
					errorCheck(6);
				}
			}
			else
			{

				if (!(attribute[i] >= '0' && (attribute[i] <= '9')))
				{
					errorCheck(6);
				}
			}

		}
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
		if (attribute[i] == '-')
		{
			continue;
			if (!(attribute[i] >= '0' && (attribute[i] <= '9')))
			{
				errorCheck(6);
			}
		}
		else
		{

			if (!(attribute[i] >= '0' && (attribute[i] <= '9')))
			{
				errorCheck(6);
			}
		}

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
		{
			errorCheck(6);
		}
		for (size_t i = 0; i < numbersArraySize; i++)
		{

			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "SRT-SLC")
	{
		attributeINT = stoi(attribute);
		/*if (attributeINT > numbersArray.size())
		{
			cout << "Invalit attribute";
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
				
			}
		
		}
		for (size_t i = 0; i < singleNumSize; i++)
		{
			if (singleNum[i]=='-')
			{
				continue;
				if (!(singleNum[i] >= '0' && (singleNum[i] <= '9')))
				{
					isThereError = 2;
					errorCheck(2);
				}
			}
			else
			{

				if (!(singleNum[i] >= '0' && (singleNum[i] <= '9')))
				{
					isThereError = 2;
					errorCheck(2);
				}
			}
		    
		}
		numbersArray[arrayCount] = stoi(singleNum);
		num.erase(0, counterDigits + 1);
		arrayCount++;
		counterDigits = 1;


	}
	return numbersArray;
}
void Parser::calculate(const string& temp)
	{
		int CounterForClosingCommands = 0;
		int counterForAttrubutes = 0;
		int startingIndexForAttributes = 0;
		string attribute;
		int attributeINT=0;
		string commandTop = commands.top();
		bool needsToBreak = false;
		int counterDigits = 1;
		int k = 0;
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
			vector<int>numbersArray = addNumsToVector(numbers, counterDigits, singleNum, arrayCount, isThereError);

			bool isThereFalseTag = false;
			vector<string>tags{"MAP-INC","MAP-MLT","AGG-SUM","AGG-PRO","AGG-AVG","AGG-FST","AGG-LST","SRT-REV","SRT-ORD","SRT-SLC", "SRT-DST"};
			
			if (!(std::count(tags.begin(), tags.end(), temp)))
			{
				isThereError = 1;
				errorCheck(isThereError);
			}
		
			if ((temp == "AGG-SUM" || temp == "AGG-PRO" || temp == "AGG-AVG") && numbersArray.size()<2)
			{
				isThereError = 4;
				errorCheck(isThereError);
			}
			string result;
			result = applyCommand(numbersArray, temp, attribute, attributeINT, result, isThereError);

		
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
		else
		{
			isThereError = 1;
			errorCheck(isThereError);
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
			while (input[i + 1] != '>' && input[i + 1] != '<' && input[i+1]!='\0')
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
				else if ((!numbers.empty()) && startIndex+counterForFindingNumbers!=inputSize) //проверява дали стекът е празен и числата не са изцяло извън командите
				{
					numbers.top() += " " + temp;
				}
			}
			//if (startIndex+counterForFindingNumbers==input.size()) //??? ako w kraq na inputa ima random 4isla
			//{
			//	numbers.pop();
			//}

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
			calculate(temp);
		}
	}

}