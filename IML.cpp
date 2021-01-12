#include <iostream>
#include <fstream> 
#include <string>
#include "Parser.h"
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int main()
{
 /*  string input = "<MAP-INC \"-3\">4 12 55</MAP-INC>" ;*/
   string input_file;
   string output_file;
  /* cout << "The name of the input file:\n";
   cin >> input_file;
   cout << "The name of the output file:\n";
   cin >> output_file;*/

   Parser p;
   p.read("input.txt");
   p.lexer();
   p.write("output.txt");




    
}

