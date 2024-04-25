#pragma once
#include <string>
#include <vector>


class Parser
{
public:
	Parser(const std::string& expression);

	bool parse();
	const std::vector<std::string>& getTokens() const;
	const std::vector<std::string>& getPostfixNotation() const;

private:
	std::string expression;
	std::vector<std::string> tokens;
	std::vector<std::string> postfixNotation;

	bool isOperator(char c) const;
	int getPrecedence(char op) const;
	void tokenize();
	void toPostfixNotation();
};