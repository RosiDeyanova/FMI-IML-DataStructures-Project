#pragma once
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include<algorithm>
#include <stack>
using namespace std;

void ReadFromConsole();
void FindOpenTags(string inputCommands) {

    //finds the open tags and adds them to a stack

    stack<string>commands;
    char command;
    int counter1 = 0;
    int removeFromCounter = 0;
    bool isCounterResetNeeded = true;

    for (size_t i = 0; i < inputCommands.length()-1; i++)
    {
        string temp;
        int startIndex = 0;
        if (isCounterResetNeeded)
        {
            counter1 = 0;
        }



        if (inputCommands[i] == '<' && inputCommands[i + 1] != '/')
        {
            startIndex = i;

            while (inputCommands[i + 1] != '>')
            {
                counter1++; i++;
            }

            temp = inputCommands.substr(startIndex + 1, counter1 - removeFromCounter);
            inputCommands.erase(0, counter1 + 1);
            i = -1;
            commands.push(temp);
            if (inputCommands[0] == '>')
            {
                inputCommands.erase(inputCommands.begin());
                isCounterResetNeeded = true;
            }

        }
        else
        {
            counter1++;
            removeFromCounter++;
            isCounterResetNeeded = false;
        }



    }



};
