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
  stack<char> opearatorsStack;
  map<char, int> significance;  //= {{'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}};
  significance.insert(pair<char, int>('*', 3));
  significance.insert(pair<char, int>('/', 3));
  significance.insert(pair<char, int>('+', 2));
  significance.insert(pair<char, int>('-', 2));
  significance.insert(pair<char, int>('(', 1));
  char topToken;
  string postfixString = "";
  for (int i = 0; i < size; i++) {
    if (infix[i][0] >= '0' && infix[i][0] <= '9') {
      postfixString += infix[i];
      postfixString += " ";
    } else if (infix[i][0] == '(') {
      opearatorsStack.push(infix[i][0]);
    } else if (infix[i][0] == ')') {
      topToken = opearatorsStack.top();
      opearatorsStack.pop();
      while (topToken != '(') {
        postfixString += topToken;
        postfixString += " ";
        topToken = opearatorsStack.top();
        opearatorsStack.pop();
      }
    } else {
      while (!opearatorsStack.empty() 
        && significance[opearatorsStack.top()] >= significance[infix[i][0]]) {
        postfixString += opearatorsStack.top();
        postfixString += " ";
        opearatorsStack.pop();
      }
      opearatorsStack.push(infix[i][0]);
    }
  }
  while (!opearatorsStack.empty()) {
    postfixString += opearatorsStack.top();
    postfixString += " ";
    opearatorsStack.pop();
  }
  return postfixString;
}

// Вычислить результат выполнения выражения со строковыми оператором и двумя
// операндами
double RPN::doMath(string sign, string firstStringOperand, string secondStringOperand) {
  double firstOperand = firstStringOperand.c_str().ToDouble();
  double secondOperand = secondStringOperand.c_str().ToDouble();
  if (sign[0] == '*')
    return firstOperand * secondOperand;
  else if (sign[0] == '/')
    return firstOperand / secondOperand;
  else if (sign[0] == '+')
    return firstOperand + secondOperand;
  else
    return firstOperand - secondOperand;
}

// Убрать пробелы в строке
string RPN::removeSpaces(string str) {
  string* newString = new string[size];
  for (int i = 0; str.find_first_of(" ") > 0; i++) {
    int pos = str.find_first_of(" ");
    newString[i] = str.substr(0, pos);
    if (str.length() > 2)
      str.erase(0, pos + 1);
    else
      str.erase(0, pos);
  }
  return *newString;
}

// Вычислить результат из постфиксной формы
double RPN::postfixEval(string* postfixExpr) {
  stack<string> operandStack;
  double result;
  for (int i = 0; i < (*postfixExpr).length(); i++) {
    if (postfixExpr[i][0] >= '0' && postfixExpr[i][0] <= '9') {
      operandStack.push(postfixExpr[i]);
    } else {
      string secondOperand = operandStack.top();
      operandStack.pop();
      string firstOperand = operandStack.top();
      operandStack.pop();
      result = doMath(postfixExpr[i], firstOperand, secondOperand);
      AnsiString aResult = AnsiString(result);
      operandStack.push(aResult.c_str());
    }
  }
  return result;
}
