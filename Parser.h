#pragma once
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include<algorithm>
#include <stack>
using namespace std;

class Parser {
private:
    stack<string>commands;
    stack<string>numbers;
    bool lastCommandOpenning;
    string input;
    void calculate(string& temp);

public:
    Parser();
    bool read(const string& filename);
    bool write(const string& filename) const;
    void lexer();


};


