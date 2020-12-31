#include <iostream>
#include <fstream> 
#include <string>
#include "IML.h"
#include <vector>
#include<algorithm>
#include <stack>
using namespace std;

int main()
{
    //string str = "102:330:3133:76531:451:000:12:44412";
    //std::replace(str.begin(), str.end(), ':', ' ');  // replace ':' by ' '

    //vector<int> array;
    //stringstream ss(string);
    //int temp;
    //while (ss >> temp)
    //    array.push_back(temp);

    string input = "<SRT-DST><SRT-SLC \"3\">57 18 9<MAP-INC \"-3\">4 2 2</MAP-INC>5</SRT-SLC></SRT-DST>" ;
    
    stack<string>commands;
    stack<string>numbers;
    char command;
    
   
   
    
    int counter = 0;
    int removeFromCounter = 0;
    bool isCounterResetNeeded = true;

    for (size_t i = 0; i < input.capacity(); i++)
    {
        string temp;
        int startIndex = 0;
        if (isCounterResetNeeded)
        {
            counter = 0;
        }
      


        if (input[i]=='<' && input[i+1]!='/')
        {
            startIndex = i;
           
            while (input[i+1]!='>')
            {
                counter++; i++;
            }

            temp = input.substr(startIndex+1, counter-removeFromCounter);
            input.erase(0, counter+1);
            i = -1;

            commands.push(temp);
            if (input[0]=='>')
            {
                input.erase(input.begin());
                isCounterResetNeeded = true;
            }
           
        }
        else 
        {
            counter++;
            removeFromCounter++;
            isCounterResetNeeded = false;
        }

        

    }

    
}

