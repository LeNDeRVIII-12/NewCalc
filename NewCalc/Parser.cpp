#include "Parser.h"
#include <cctype>
#include <stack>
#include <stdexcept>

Parser::Parser(const std::string& expression) : expression(expression) {}

bool Parser::parse()
{
	tokenize();
	toPostfixNotation();
	return !postfixNotation.empty();
}

const std::vector<std::string>& Parser::getTokens() const
{
	return tokens;
}

const std::vector<std::string>& Parser::getPostfixNotation() const
{
	return postfixNotation;
}

bool Parser::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Parser::getPrecedence(char op) const
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	return 0;
}

void Parser::tokenize()
{
	tokens.clear();
	std::string currentToken;

	for (char c : expression)
	{
		if (isspace(c))
			continue;
		else if (isdigit(c) || c == '.')
			currentToken += c;
		else if (isalpha(c))
			currentToken += c;
		else if (isOperator(c))
		{
			if (!currentToken.empty())
			{
				tokens.push_back(currentToken);
				currentToken.clear();
			}
			tokens.push_back(std::string(1, c));
		}
		else if (c == '(' || c == ')')
		{
			if (!currentToken.empty())
			{
				tokens.push_back(currentToken);
				currentToken.clear();
			}
			tokens.push_back(std::string(1, c));
		}
		else
			throw std::exception("Неизвестный символ");
	}

	if (!currentToken.empty())
		tokens.push_back(currentToken);
}

void Parser::toPostfixNotation()
{
	postfixNotation.clear();
	std::stack<char> operatorStack;

	for (const std::string& token : tokens)
	{
		if (isdigit(token[0]) || isalpha(token[0]))
			postfixNotation.push_back(token);
		else if (isOperator(token[0]))
		{
			char op = token[0];
			while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(op))
			{
				postfixNotation.push_back(std::string(1, operatorStack.top()));
				operatorStack.pop();
			}
			operatorStack.push(op);
		}
		else if (token[0] == '(')
			operatorStack.push('(');
		else if (token[0] == ')')
		{
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				postfixNotation.push_back(std::string(1, operatorStack.top()));
				operatorStack.pop();
			}
			if (!operatorStack.empty() && operatorStack.top() == '(')
				operatorStack.pop();
		}
	}

	while (!operatorStack.empty())
	{
		postfixNotation.push_back(std::string(1, operatorStack.top()));
		operatorStack.pop();
	}
}