#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "MathObject.h"

class Calculator
{
public:
	Calculator(const std::vector<std::string>& postfixNotation);

	void setVariable(const std::string& variable, MathObject* value);
	MathObject* evaluate();

private:
	std::vector<std::string> postfixNotation;
	std::unordered_map<std::string, MathObject*> variables;

	bool isOperator(const std::string& token) const;
	MathObject* performOperation(const std::string& op, MathObject* a, MathObject* b) const;
};