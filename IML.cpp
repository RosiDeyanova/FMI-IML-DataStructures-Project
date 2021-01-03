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
   string inputGetCommands = "<SRT-DST><SRT-SLC \"3\">57 18 9<MAP-INC \"-3\">4 2 2</MAP-INC>5</SRT-SLC></SRT-DST>" ;
   string input = inputGetCommands;
  


   FindOpenTags(inputGetCommands);

   int counter = 0;
   string temp;
   int startIndex=0;
   stack<string>numbers;
   for (size_t i = 0; i < input.length()-1; i++)
   {
       if (input[i] == '>' && input[i + 1] != '<') // gets the numbers and puts the in a stack
       {
           startIndex = i+1;

           while (input[i + 1] != '>' && input[i + 1] != '<')
           {
               counter++; i++;
           }

           temp = input.substr(startIndex, counter);           
           numbers.push(temp);
           counter = 0;
          

       }
       else if (input[i]=='<' && input [i+1]=='/')
       {
           string lastCom;
       }
	   
   }




    
}

