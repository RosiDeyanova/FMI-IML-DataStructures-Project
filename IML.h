#pragma once
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include<algorithm>
#include <stack>
using namespace std;


void DoStuff(string input) {

   

    stack<string>commands;
    stack<string>numbers;
    int counterForFindingCommands = 0;
    int counterForFindingNumbers = 0;
    int CounterForClosingCommands = 0;

    for (size_t i = 0; i < input.length()-1; i++)
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
        }
      
        else if (input[i] == '>' && input[i + 1] != '<') // gets the numbers and puts the in a stack
        {  
            while (input[i + 1] != '>' && input[i + 1] != '<')
            {
                counterForFindingNumbers++; i++;
            }

            temp = input.substr(startIndex, counterForFindingNumbers);
            numbers.push(temp);
            counterForFindingNumbers = 0;

        }
        else if (input[i]=='<' && input [i+1]=='/') //checking if the tags are written correctly and what are they
        {
           while (input[i+1]!='>')
            {
                CounterForClosingCommands++; i++;
            }
           temp = input.substr(startIndex, CounterForClosingCommands);
           CounterForClosingCommands = 0;

           if (temp==commands.top())
           {

           }
           else
           {
               //print out "Wrong tag format"
           }
        }



    }



};

