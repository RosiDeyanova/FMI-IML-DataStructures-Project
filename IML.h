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
           
            int k = 0;
            int arrayCount=0;
            int counterDigits = 1;
            string num;
            string singleNum;

           while (input[i+1]!='>')
            {
                CounterForClosingCommands++; i++;
            }
           temp = input.substr(startIndex+1, CounterForClosingCommands-1);
           CounterForClosingCommands = 0;

           if (temp==commands.top())
           {
               string newstr;
               int numbersArray[/*sizeof(newstr)*/50];
               while (!numbers.empty())
               {
                   num = numbers.top();
                   numbers.pop();
                   newstr = num;
                   newstr.erase(remove(newstr.begin(), newstr.end(), ' '), newstr.end());
                   //int numbersArray[/*sizeof(newstr)*/50]; //makes an array that has as many elements as there are numbers
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

               }
               for (size_t i = 0; i < input.length(); i++)
               {
                   if (true)
                   {

                   }
               }
               string result;
               if (temp=="AGG-SUM")
               {
                   int sum = 0;
                   for (size_t i = 0; i <newstr.length() ; i++)
                   {
                       sum += numbersArray[i];
                   }
                   result = to_string(sum);
                   numbers.push(result);
               }
               

           }
           else
           {
               //print out "Wrong tag format"
           }
        }



    }



};

