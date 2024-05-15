// JsonParser.cpp
#include "JsonParser.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "ComplexNumber.h"
#include "Matrix.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

JsonParser::JsonParser(const std::string& jsonStr) {
	data = nlohmann::json::parse(jsonStr);
}

std::string JsonParser::getCalculatorType() const {
	return data["calculatorType"];
}

std::string JsonParser::getExpression() const {
	return data["expression"];
}

std::unordered_map<std::string, MathObject*> JsonParser::getVariables() const {
	std::unordered_map<std::string, MathObject*> variables;
	parseVariables(variables);
	return variables;
}

void JsonParser::parseVariables(std::unordered_map<std::string, MathObject*>& variables) const {
	nlohmann::json variablesJson = data["variables"];
	for (auto it = variablesJson.begin(); it != variablesJson.end(); ++it) {
		std::string variable = it.key();
		nlohmann::json valueJson = it.value();
		std::string type = getCalculatorType();
		MathObject* value = createMathObject(type, valueJson);
		if (value) {
			variables[variable] = value;
		}
	}
}

MathObject* JsonParser::createMathObject(const std::string& type, const nlohmann::json& value) const {
	MathObject* obj = nullptr;
	if (type == "real") {
		if (value.is_number_float()) {
			obj = new RealNumber(value.get<double>());
		}
		else {
			std::cerr << "Неверный формат вещественного числа" << std::endl;
		}
	}
	else if (type == "fraction") {
		if (value.is_string()) {
			try {
				int numerator, denominator;
				char slash;
				std::istringstream iss(value.get<std::string>());
				iss >> numerator >> slash >> denominator;
				if (!iss || slash != '/') {
					throw std::invalid_argument("Неверный формат дробного числа");
				}
				obj = new Fraction(numerator, denominator);
			}
			catch (const std::exception& e) {
				std::cerr << "Ошибка при создании дробного числа: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Неверный формат дробного числа" << std::endl;
		}
	}
	else if (type == "complex") {
		if (value.is_array() && value.size() == 2) {
			try {
				double real = value[0].get<double>();
				double imaginary = value[1].get<double>();
				obj = new ComplexNumber(real, imaginary);
			}
			catch (const std::exception& e) {
				std::cerr << "Ошибка при создании комплексного числа: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Неверный формат комплексного числа" << std::endl;
		}
	}

	else if (type == "matrix") {
		if (value.is_string()) {
			try {
				std::istringstream iss(value.get<std::string>());
				std::vector<std::vector<double>> matrixValues;
				std::vector<double> row;
				std::string token;
				while (std::getline(iss, token, ';')) {
					std::istringstream rowStream(token);
					row.clear();
					double val;
					while (rowStream >> val) {
						row.push_back(val);
						if (!rowStream.eof()) {
							rowStream.clear();
							rowStream.ignore();
						}
					}
					matrixValues.push_back(row);
				}
				obj = new Matrix(matrixValues);
			}
			catch (const std::exception& e) {
				std::cerr << "Ошибка при создании матрицы: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Неверный формат матрицы" << std::endl;
		}
	}
	return obj;
}