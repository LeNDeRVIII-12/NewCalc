#pragma once
#include "MathObject.h"
#include <vector>

class Matrix : public MathObject
{
public:
	Matrix(int rows, int cols);
	Matrix(const std::vector<std::vector<double>>& values);

	MathObject* add(const MathObject* other) const override;
	MathObject* substract(const MathObject* other) const override;
	MathObject* multiply(const MathObject* other) const override;
	MathObject* divide(const MathObject* other) const override;
	MathObject* power(const MathObject* other) const override;
	std::string toString() const override;

	int getRows() const;
	int getCols() const;
	double getValue(int row, int col) const;
	void setValue(int row, int col, double value);

private:
	std::vector<std::vector<double>> values;
	int rows;
	int cols;
};