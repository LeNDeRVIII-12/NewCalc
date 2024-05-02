#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "Parser.h"
#include "Calculator.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "ComplexNumber.h"
#include "Matrix.h"

int main()
{
	system("chcp 1251 > null");
	std::cout << "Выберите тип калькулятора:" << std::endl;
	std::cout << "1. Вещественные числа" << std::endl;
	std::cout << "2. Простые дроби" << std::endl;
	std::cout << "3. Комплексные числа" << std::endl;
	std::cout << "4. Матрицы" << std::endl;
	std::cout << "Введите нормер: ";

	int choice;
	std::cin >> choice;

	std::cout << "Введите выражение: ";
	std::string expression;
	std::cin.ignore();
	std::getline(std::cin, expression);

	Parser parser(expression);
	if (!parser.parse())
	{
		std::cout << "Ошибка при разборе выражения" << std::endl;
		return 1;
	}

	Calculator calculator(parser.getPostfixNotation());

	std::unordered_map<std::string, MathObject*> variables;
	std::cout << "Введите значения переменных (формат: x=значение):" << std::endl;
	std::string input;
	while (std::getline(std::cin, input))
	{
		if (input.empty())
			break;
		size_t equalPos = input.find('=');
		if (equalPos == std::string::npos)
		{
			std::cout << "Неверный формат ввода" << std::endl;
			continue;
		}
		std::string variable = input.substr(0, equalPos);
		std::string valueStr = input.substr(equalPos + 1);
		MathObject* value = nullptr;
		switch (choice)
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
					throw std::invalid_argument("Неверный формат простой дроби");
				
				value = new Fraction(numerator, denominator);
			}
			catch (const std::exception& e) 
			{
				std::cerr << "Ошибка при парсинге простой дроби: " << e.what() << std::endl;
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
						throw std::invalid_argument("Неверный формат комплексного числа");
				}
				else if (iss.peek() == 'i' || iss.peek() == 'I')
				{
					imaginary = 1;
					iss.ignore();
				}
				else
					imaginary = 0;

				if (iss.fail()) 
					throw std::invalid_argument("Неверный формат комплексного числа");
				
				value = new ComplexNumber(real, imaginary);
			}
			catch (const std::exception& e) 
			{
				std::cerr << "Ошибка при парсинге комплексного числа: " << e.what() << std::endl;
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
				std::cerr << "Ошибка при парсинге матрицы: " << e.what() << std::endl;
			}
			break;
		default:
			std::cout << "Неверный ввод!" << std::endl;
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
		std::cout << "Результат: " << result->toString() << std::endl;
		delete result;
	}
	else
		std::cout << "Ошибка при вычислении выражения" << std::endl;

	for (const auto& pair : variables)
		delete pair.second;

	return 0;
}