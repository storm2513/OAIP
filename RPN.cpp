//---------------------------------------------------------------------------

#pragma hdrstop

#include "RPN.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

RPN::RPN(string* s, int _size) {
  size = _size;
  infix = s;
  postfix = infixToPostfix();
  string str = removeSpaces(postfix);
  result = postfixEval(&str);
}

// Перевод из инфиксной формы в постфиксную
string RPN::infixToPostfix() {
  stack<char> opStack;
  map<char, int> prec;  //= {{'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}};
  prec.insert(pair<char, int>('*', 3));
  prec.insert(pair<char, int>('/', 3));
  prec.insert(pair<char, int>('+', 2));
  prec.insert(pair<char, int>('-', 2));
  prec.insert(pair<char, int>('(', 1));
  char topToken;
  string postfixList = "";
  for (int i = 0; i < size; i++) {
    if (infix[i][0] >= '0' && infix[i][0] <= '9') {
      postfixList += infix[i];
      postfixList += " ";
    } else if (infix[i][0] == '(') {
      opStack.push(infix[i][0]);
    } else if (infix[i][0] == ')') {
      topToken = opStack.top();
      opStack.pop();
      while (topToken != '(') {
        postfixList += topToken;
        postfixList += " ";
        topToken = opStack.top();
        opStack.pop();
      }
    } else {
      while (!opStack.empty() && prec[opStack.top()] >= prec[infix[i][0]]) {
        postfixList += opStack.top();
        postfixList += " ";
        opStack.pop();
      }
      opStack.push(infix[i][0]);
    }
  }
  while (!opStack.empty()) {
    postfixList += opStack.top();
    postfixList += " ";
    opStack.pop();
  }
  return postfixList;
}

// Вычислить результат выполнения выражения со строковыми оператором и двумя
// операндами
double RPN::doMath(string op, string _op1, string _op2) {
  AnsiString opas1 = _op1.c_str();
  AnsiString opas2 = _op2.c_str();
  double op1 = opas1.ToDouble();
  double op2 = opas2.ToDouble();
  if (op[0] == '*')
    return op1 * op2;
  else if (op[0] == '/')
    return op1 / op2;
  else if (op[0] == '+')
    return op1 + op2;
  else
    return op1 - op2;
}

// Убрать пробелы в строке
string RPN::removeSpaces(string str) {
  string* ar = new string[size];
  for (int i = 0; str.find_first_of(" ") > 0; i++) {
    int pos = str.find_first_of(" ");
    ar[i] = str.substr(0, pos);
    if (str.length() > 2)
      str.erase(0, pos + 1);
    else
      str.erase(0, pos);
  }
  string s = *ar;
  return s;
}

// Вычислить результат из постфиксной формы
double RPN::postfixEval(string* postfixExpr) {
  stack<string> operandStack;
  double result;
  for (int i = 0; i < (*postfixExpr).length(); i++) {
    if (postfixExpr[i][0] >= '0' && postfixExpr[i][0] <= '9') {
      operandStack.push(postfixExpr[i]);
    } else {
      string operand2 = operandStack.top();
      operandStack.pop();
      string operand1 = operandStack.top();
      operandStack.pop();
      result = doMath(postfixExpr[i], operand1, operand2);
      AnsiString aResult = AnsiString(result);
      operandStack.push(aResult.c_str());
    }
  }
  return result;
}
