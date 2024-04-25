#pragma once
#include "MathObject.h"

class Fraction : public MathObject
{
public:
	Fraction(int numerator, int denominator);

	MathObject* add(const MathObject* other) const override;
	MathObject* substract(const MathObject* other) const override;
	MathObject* multiply(const MathObject* other) const override;
	MathObject* divide(const MathObject* other) const override;
	MathObject* power(const MathObject* other) const override;
	std::string toString() const override;

private:
	int numerator;
	int denominator;

	static int gcd(int a, int b);
	void simplify();
};