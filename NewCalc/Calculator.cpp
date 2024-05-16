#include "Calculator.h"
#include <stack>
#include <iostream>

Calculator::Calculator(const std::vector<std::string>& postfixNotation) : postfixNotation(postfixNotation) {}

void Calculator::setVariable(const std::string& variable, MathObject* value)
{
	variables[variable] = value;
}

MathObject* Calculator::evaluate()
{
	if (postfixNotation.empty()) {
		throw std::invalid_argument("Постфиксная нотация пуста");
	}
	std::stack<MathObject*> stack;

	for (const std::string& token : postfixNotation)
	{
		if (isOperator(token))
		{
			MathObject* b = stack.top();
			stack.pop();
			MathObject* a = stack.top();
			stack.pop();

			MathObject* result = performOperation(token, a, b);
			if (result)
				stack.push(result);
			else
				return nullptr;
		}
		else
		{
			MathObject* value = variables[token];
			if (value)
				stack.push(value);
			else
				return nullptr;
		}
	}

	if (stack.size() == 1)
		return stack.top();
	else
		return nullptr;
}

bool Calculator::isOperator(const std::string& token) const
{
	return token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^');
}

MathObject* Calculator::performOperation(const std::string& op, MathObject* a, MathObject* b) const
{
	char opChar = op[0];
	switch (opChar) 
	{
	case '+':
		return a->add(b);
	case '-':
		return a->substract(b);
	case '*':
		return a->multiply(b);
	case '/':
		return a->divide(b);
	case '^':
		return a->power(b);
	default:
		return nullptr;
	}
}