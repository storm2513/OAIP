//---------------------------------------------------------------------------

#ifndef RPNH
#define RPNH
#include <iostream>
#include <stack>
#include <map>
using namespace std;

// RPN - Reverse Polish Notation
class RPN {
 public:
  RPN(string* s, int _size);
  string infixToPostfix();
  double doMath(string op, string _op1, string _op2);
  string removeSpaces(string str);
  double postfixEval(string* postfixExpr);
  string* infix;
  string postfix;
  double result;
  int size;
};
//---------------------------------------------------------------------------
#endif
