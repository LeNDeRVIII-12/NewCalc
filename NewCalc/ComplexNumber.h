#pragma once
#include "MathObject.h"

class ComplexNumber : public MathObject
{
public:
	ComplexNumber(double real, double imaginary);

	MathObject* add(const MathObject* other) const override;
	MathObject* substract(const MathObject* other) const override;
	MathObject* multiply(const MathObject* other) const override;
	MathObject* divide(const MathObject* other) const override;
	MathObject* power(const MathObject* other) const override;
	std::string toString() const override;

private:
	double real;
	double imaginary;
};