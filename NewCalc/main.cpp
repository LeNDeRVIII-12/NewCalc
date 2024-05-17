#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include "nlohmann/json.hpp"

#include "Parser.h"
#include "Calculator.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "ComplexNumber.h"
#include "Matrix.h"
#include "JsonParser.h"

int main()
{
	system("chcp 1251 > null");

	std::cout << "�������� ������ ����� ������:" << std::endl;
	std::cout << "1. ���� �������" << std::endl;
	std::cout << "2. ������ �� JSON �����" << std::endl;
	std::cout << "��� �����: ";

	int choice;
	std::cin >> choice;

	if (choice == 1)
	{
		std::cout << "������� ��� ������������:" << std::endl;
		std::cout << "1. ������������ �����" << std::endl;
		std::cout << "2. ������� �����" << std::endl;
		std::cout << "3. ����������� �����" << std::endl;
		std::cout << "4. �������" << std::endl;
		std::cout << "��� �����: ";

		int calculatorType;
		std::cin >> calculatorType;

		std::string expression;
		std::cout << "������� ���������: ";
		do
		{
			std::cin.ignore();
			std::getline(std::cin, expression);
			if (expression.size() == 0)
				std::cout << "��������� ������!" << std::endl;
		} while (expression.size() == 0);


		Parser parser(expression);
		if (!parser.parse())
		{
			std::cout << "������ ��� ������� ���������" << std::endl;
			return 1;
		}

		Calculator calculator(parser.getPostfixNotation());
		std::unordered_map<std::string, MathObject*> variables;

		std::cout << "������� ���������� (������: x=��������):" << std::endl;
		std::string input;
		while (std::getline(std::cin, input))
		{
			if (input.empty())
				break;

			size_t equalPos = input.find('=');
			if (equalPos == std::string::npos)
			{
				std::cout << "�������� ������ �����" << std::endl;
				continue;
			}

			std::string variable = input.substr(0, equalPos);
			std::string valueStr = input.substr(equalPos + 1);
			MathObject* value = nullptr;

			switch (calculatorType)
			{
			case 1:
				value = new RealNumber(std::stod(valueStr));
				break;
			case 2:
				try
				{
					int numerator, denominator;
					char slash;
					std::istringstream iss(valueStr);
					iss >> numerator >> slash >> denominator;
					if (!iss || slash != '/')
						throw std::invalid_argument("�������� ������ �������� �����");
					
					if (denominator == 0)
						throw std::invalid_argument("0 � �����������!");
					value = new Fraction(numerator, denominator);
				}
				catch (const std::exception& e)
				{
					std::cerr << "������ ��� �������� �������� �����: " << e.what() << std::endl;
				}
				break;
			case 3:
				try
				{
					double real, imaginary;
					std::istringstream iss(valueStr);
					iss >> real;
					if (iss.peek() == '+' || iss.peek() == '-')
					{
						char sign = iss.get();
						iss >> imaginary;

						if (iss.peek() == 'i' || iss.peek() == 'I')
							iss.ignore();
						else
							throw std::invalid_argument("�������� ������ ������������ �����");
					}
					else if (iss.peek() == 'i' || iss.peek() == 'I')
					{
						imaginary = 1;
						iss.ignore();
					}
					else
						imaginary = 0;

					if (iss.fail())
						throw std::invalid_argument("�������� ������ ������������ �����");

					value = new ComplexNumber(real, imaginary);
				}
				catch (const std::exception& e)
				{
					std::cerr << "������ ��� �������� ������������ �����: " << e.what() << std::endl;
				}
				break;
			case 4:
				try
				{
					std::istringstream iss(valueStr);
					std::vector<std::vector<double>> matrixValues;
					std::vector<double> row;
					std::string token;
					while (std::getline(iss, token, ';'))
					{
						std::istringstream rowStream(token);
						row.clear();
						double value;
						while (rowStream >> value)
						{
							row.push_back(value);
							if (!rowStream.eof())
							{
								rowStream.clear();
								rowStream.ignore();
							}
						}
						matrixValues.push_back(row);
					}
					value = new Matrix(matrixValues);
				}
				catch (const std::exception& e)
				{
					std::cerr << "������ ��� �������� �������: " << e.what() << std::endl;
				}
				break;
			default:
				std::cout << "�������� ��� ������������!" << std::endl;
				return 1;
			}

			if (value)
			{
				variables[variable] = value;
				calculator.setVariable(variable, value);
			}
		}

		MathObject* result = calculator.evaluate();
		if (result)
		{
			std::cout << "���������: " << result->toString() << std::endl;
			delete result;
		}
		else
			std::cout << "������ ��� ���������� ���������" << std::endl;


		for (const auto& pair : variables)
			delete pair.second;
	}
	else if (choice == 2)
	{
		std::cout << "������� ��� JSON �����: ";
		std::string fileName;
		std::cin >> fileName;

		std::ifstream file(fileName);
		if (!file.is_open())
		{
			std::cerr << "�� ������� ������� ����: " << fileName << std::endl;
			return 1;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string jsonStr = buffer.str();

		JsonParser jsonParser(jsonStr);
		std::string calculatorType = jsonParser.getCalculatorType();
		std::string expression = jsonParser.getExpression();
		std::unordered_map<std::string, MathObject*> variables = jsonParser.getVariables();

		Parser parser(expression);
		if (!parser.parse())
		{
			std::cout << "������ ��� ������� ���������" << std::endl;
			return 1;
		}

		Calculator calculator(parser.getPostfixNotation());
		for (const auto& pair : variables)
		{
			calculator.setVariable(pair.first, pair.second);
		}

		MathObject* result = calculator.evaluate();
		if (result)
		{
			std::cout << "���������: " << result->toString() << std::endl;
			delete result;
		}
		else
			std::cout << "������ ��� ���������� ���������" << std::endl;

		for (const auto& pair : variables)
			delete pair.second;
	}
	else
	{
		std::cout << "�������� �����" << std::endl;
		return 1;
	}

	return 0;
}