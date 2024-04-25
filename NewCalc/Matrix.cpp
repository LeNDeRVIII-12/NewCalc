#include "Matrix.h"
#include <stdexcept>
#include <sstream>

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), values(rows, std::vector<double>(cols, 0)) {}
Matrix::Matrix(const std::vector<std::vector<double>>& values) : values(values)
{
	rows = values.size();
	cols = 0;
	for (const auto& row : values)
		cols = std::max(cols, static_cast<int>(row.size()));
}

MathObject* Matrix::add(const MathObject* other) const
{
	const Matrix* otherMatrix = dynamic_cast<const Matrix*>(other);
	if (otherMatrix && rows == otherMatrix->rows && cols == otherMatrix->cols)
	{
		std::vector<std::vector<double>> newValues(rows, std::vector<double>(cols));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				newValues[i][j] = values[i][j] + otherMatrix->values[i][j];
			}
		}
		return new Matrix(newValues);
	}
	else
		return nullptr;
}

MathObject* Matrix::substract(const MathObject* other) const
{
	const Matrix* otherMatrix = dynamic_cast<const Matrix*>(other);
	if (otherMatrix && rows == otherMatrix->rows && cols == otherMatrix->cols)
	{
		std::vector<std::vector<double>> newValues(rows, std::vector<double>(cols));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				newValues[i][j] = values[i][j] - otherMatrix->values[i][j];
			}
		}
		return new Matrix(newValues);
	}
	else
		return nullptr;
}

MathObject* Matrix::multiply(const MathObject* other) const
{
	const Matrix* otherMatrix = dynamic_cast<const Matrix*>(other);
	if (otherMatrix && cols == otherMatrix->rows)
	{
		std::vector<std::vector<double>> newValues(rows, std::vector<double>(otherMatrix->cols, 0));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < otherMatrix->cols; j++)
			{
				for (int k = 0; k < cols; k++)
				{
					newValues[i][j] += values[i][k] * otherMatrix->values[k][j];
				}
			}
		}
		return new Matrix(newValues);
	}
	else
		return nullptr;
}

MathObject* Matrix::divide(const MathObject* other) const
{
	return nullptr;
}

MathObject* Matrix::power(const MathObject* other) const
{
	const Matrix* otherMatrix = dynamic_cast<const Matrix*>(other);
	if (otherMatrix && otherMatrix->rows == 1 && otherMatrix->cols == 1)
	{
		int exponent = static_cast<int>(otherMatrix->getValue(0, 0));
		if (rows != cols)
			return nullptr;
		Matrix* result = new Matrix(*this);
		Matrix* temp = new Matrix(*this);
		for (int i = 1; i < exponent; i++)
			*result = *dynamic_cast<Matrix*>(result->multiply(temp));

		delete temp;
		return result;
	}
	else
		return nullptr;
}

int Matrix::getRows() const
{
	return rows;
}

int Matrix::getCols() const
{
	return cols;
}

double Matrix::getValue(int row, int col) const
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		throw std::out_of_range("Неверный индекс");
	return values[row][col];
}

void Matrix::setValue(int row, int col, double value)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		throw std::out_of_range("Неверный индекс");
	values[row][col] = value;
}

std::string Matrix::toString() const {
	std::ostringstream out;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			out << values[i][j];
			if (j < cols - 1) out << ", ";
		}
		if (i < rows - 1)
			out << "; ";
	}
	return out.str();
}