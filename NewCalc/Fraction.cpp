#include "Fraction.h"
#include <cmath>
#include <numeric>
#include <string>

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) 
{
	simplify();
}

MathObject* Fraction::add(const MathObject* other) const
{
	const Fraction* otherFraction = dynamic_cast<const Fraction*>(other);
	if (otherFraction)
	{
		int newNumerator = numerator * otherFraction->denominator + otherFraction->numerator * denominator;
		int newDenominator = denominator * otherFraction->denominator;
		Fraction* result = new Fraction(newNumerator, newDenominator);
		result->simplify();
		return result;
	}
	else
		return nullptr;
}

MathObject* Fraction::substract(const MathObject* other) const
{
	const Fraction* otherFraction = dynamic_cast<const Fraction*>(other);
	if (otherFraction)
	{
		int newNumerator = numerator * otherFraction->denominator - otherFraction->numerator * denominator;
		int newDenominator = denominator * otherFraction->denominator;
		Fraction* result = new Fraction(newNumerator, newDenominator);
		result->simplify();
		return result;
	}
	else
		return nullptr;
}

MathObject* Fraction::multiply(const MathObject* other) const
{
	const Fraction* otherFraction = dynamic_cast<const Fraction*>(other);
	if (otherFraction)
	{
		int newNumerator = numerator * otherFraction->numerator;
		int newDenominator = denominator * otherFraction->denominator;
		Fraction* result = new Fraction(newNumerator, newDenominator);
		result->simplify();
		return result;
	}
	else
		return nullptr;
}

MathObject* Fraction::divide(const MathObject* other) const
{
	const Fraction* otherFraction = dynamic_cast<const Fraction*>(other);
	if (otherFraction)
	{
		if (otherFraction - numerator == 0)
			return nullptr;

		int newNumerator = numerator * otherFraction->denominator;
		int newDenominator = denominator * otherFraction->numerator;
		Fraction* result = new Fraction(newNumerator, newDenominator);
		result->simplify();
		return result;
	}
	else
		return nullptr;
}

MathObject* Fraction::power(const MathObject* other) const
{
	const Fraction* otherFraction = dynamic_cast<const Fraction*>(other);
	if (otherFraction && otherFraction->denominator == 1)
	{
		int exponent = otherFraction->numerator;
		int newNumerator = std::pow(numerator, exponent);
		int newDenominator = std::pow(denominator, exponent);
		Fraction* result = new Fraction(newNumerator, newDenominator);
		result->simplify();
		return result;
	}
	else
		return nullptr;
}

int Fraction::gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void Fraction::simplify()
{
	int divisor = gcd(std::abs(numerator), std::abs(denominator));
	numerator /= divisor;
	denominator /= divisor;
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
}

std::string Fraction::toString() const 
{
	return std::to_string(numerator) + "/" + std::to_string(denominator);
}