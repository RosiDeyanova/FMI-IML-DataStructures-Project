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
	case 1:cout << "Syntax error \nTry different input"; exit(0); break;
	case 2:cout << "No letters allowed between the tags \nTry different input"; exit(0); break;
	case 3: cout << "Number incorrect \nTry different input"; exit(0); break;
	case 4:cout << "Not enough numbers for the tag \nTry different input"; exit(0); break;
	case 5:cout << "Can't be passed a double as an atribute in SRT-SLC tag \nTry different input"; exit(0); break;
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
	if (!commands.empty())
	{
		errorCheck(1);

	}
	string result;
	string toPrint = numbers.top();
	int toPrintSize = toPrint.size();
	for (size_t i = 0; i < toPrintSize; i++)
	{
		if (toPrint[i]=='.')
		{
			bool flag = false;
			i++;
			string afterDot;
			while (i<toPrintSize && toPrint[i]!=' ')
			{

				if (toPrint[i]!='0')
				{
					flag = true;
				}
				afterDot += toPrint[i];
				i++;
				

			}
			if (flag==true)
			{
				int counterLastNum=0;
				unsigned afterDotSize = afterDot.size();
				for (size_t i = afterDotSize-1; i >0; i--)
				{
					if (afterDot[i]!='0') 
					{
						break;
					}
					counterLastNum++;
					
				}
				afterDot = afterDot.substr(0, afterDotSize-counterLastNum);
				result +="." +afterDot;
				
			}
			result += " ";
			
		}
		else
		{
			result += toPrint[i];
		}
	}

	if (!(fout << result))
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


		if (i != ' ') {
			count++;
		}
		else {
			break;
		}
	}
	return count;
}
string applyCommand(vector<double>numbersArray, string temp, string attribute, int attributeINT, string result)
{
	

	int numbersArraySize = numbersArray.size();
	if (temp == "AGG-SUM")
	{
		double sum = 0;
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			sum += numbersArray[i];
		}

		result = to_string(sum);

	}
	else if (temp == "AGG-PRO")
	{
		double pro = 1;
		for (size_t i = 0; i < numbersArraySize; i++)
		{
			pro *= numbersArray[i];
		}

		result = to_string(pro);

	}
	else if (temp == "AGG-AVG")
	{
		int count = 0;
		double sum = 0;
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
					
				}
				if (dublicate == true)
				{
					numbersArray.erase(numbersArray.begin() + j, numbersArray.begin() + j + 1);
					--size;
					dublicate = false;
				}
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
		double attributeDouble;
		int attributeSize = attribute.size();
		if (!(attribute[0] == '-' || (attribute[0] >= '0' && (attribute[0] <= '9')) || attribute[attributeSize - 1] == '.'))
		{
			errorCheck(6);
		}
		for (size_t i = 1; i < attributeSize; i++)
		{
			if (attribute[i] != '.' && (!((attribute[i] >= '0') && (attribute[i] <= '9'))))
			{
				errorCheck(6);
			}


		}
		attributeDouble = stod(attribute);
		if (attributeDouble == -0)
		{
			attributeDouble = 0;

		}

		for (size_t i = 0; i < numbersArraySize; i++)
		{
			numbersArray[i] += attributeDouble;
			result += to_string(numbersArray[i]) + ' ';
		}
		result.erase(result.size() - 1);

	}
	else if (temp == "MAP-MLT")
	{
	double attributeDouble;
	int attributeSize = attribute.size();
	if (!(attribute[0] == '-' || (attribute[0] >= '0' && (attribute[0] <= '9')) || attribute[attributeSize - 1] == '.'))
	{
		errorCheck(6);
	}
	for (size_t i = 1; i < attributeSize; i++)
	{
		if (attribute[i] != '.' && (!((attribute[i] >= '0') && (attribute[i] <= '9'))))
		{
			errorCheck(6);
		}


	}
	attributeDouble = stod(attribute);
	if (attributeDouble == -0)
	{
		attributeDouble = 0;

	}

	for (size_t i = 0; i < numbersArraySize; i++)
	{
		numbersArray[i] *= attributeDouble;
		if (numbersArray[i]==-0)
		{
			numbersArray[i] = 0;

		}
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
		for (size_t i = 0; i < attribute.size(); i++)
		{
			if (attribute[i] == '.')
			{
				errorCheck(5);
			}
		}
		attributeINT = stoi(attribute);

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
vector<double> addNumsToVector(stack <string>numbers, int counterDigits, string singleNum, int arrayCount) {

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
	vector<double>numbersArray(spaceCount + 1);
	string num = numbers.top();

	while (!num.empty())
	{

		counterDigits = countDigits(num);
		singleNum = num.substr(0, counterDigits);
		int singleNumSize = singleNum.size();
		if (singleNumSize > 1)
		{
			if (singleNum[0] == '0'&& singleNum[1]!='.')//015
			{
				
				errorCheck(3);

			}

		}
		size_t i = 0;
		if (singleNum[i] == '-') // проверява легитимността на число ако или ако не е отрицателно(дробно)
		{
			i++;
		}
		while (i < singleNumSize)
		{
			if (!(singleNum[i] >= '0' && (singleNum[i] <= '9') || (singleNum[i] == '.')))
			{
				errorCheck(2);

			}
			i++;
		}


		numbersArray[arrayCount] = stod(singleNum);
		num.erase(0, counterDigits + 1);
		arrayCount++;
		counterDigits = 1;


	}
	return numbersArray;
}
void Parser::calculate(string& temp)
{
	int CounterForClosingCommands = 0;
	int counterForAttrubutes = 0;
	int startingIndexForAttributes = 0;
	string attribute;
	int attributeINT = 0;
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
			if (counterForAttrubutes==0)
			{
				errorCheck(1);
			}
			attribute = commandTop.substr(startingIndexForAttributes, counterForAttrubutes);
			commands.top() = commandTop.substr(0, commands.top().size() - 3 - counterForAttrubutes);

			if (needsToBreak == true)
			{
				break;
			}
		}
		else
		{
			if (commandTop=="SRT-SLC"||commandTop=="SRT-ORD"||commandTop=="MAP-INC"|| commandTop=="MAP-MLT")
			{
				errorCheck(1);
			}
		}
	}


	if (temp == commands.top())
	{
		if (numbers.top()==""&&numbers.size()==commands.size())
		{
			numbers.pop();
			commands.pop();
			lastCommandOpenning = false;
			return;
			
		}
		vector<double>numbersArray = addNumsToVector(numbers, counterDigits, singleNum, arrayCount);

		bool isThereFalseTag = false;
		vector<string>tags{ "MAP-INC","MAP-MLT","AGG-SUM","AGG-PRO","AGG-AVG","AGG-FST","AGG-LST","SRT-REV","SRT-ORD","SRT-SLC", "SRT-DST" };

		if (!(std::count(tags.begin(), tags.end(), temp)))
		{
			
			errorCheck(1);
		}

		if ((temp == "AGG-SUM" || temp == "AGG-PRO" || temp == "AGG-AVG") && numbersArray.size() < 2)
		{
			
			errorCheck(4);
		}
		string result;
		result = applyCommand(numbersArray, temp, attribute, attributeINT, result);


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
	
		errorCheck(1);
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
				if (input[i + 1] == '<'|| (i + 1) == input.size()) //<MAP-MLT "-0"<15</MAP-MLT> or <MAP-MLT "1" 
				{
					errorCheck(1);
				}
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
			while (input[i + 1] != '>' && input[i + 1] != '<' && input[i + 1] != '\0')
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
				else if ((!numbers.empty()) && startIndex + counterForFindingNumbers != inputSize) //проверява дали стекът е празен и числата не са изцяло извън командите
				{
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
			calculate(temp);


		}
	
	
		
	}

}