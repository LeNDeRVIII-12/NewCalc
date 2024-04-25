#include "ComplexNumber.h"
#include <string>
#include <cmath>

ComplexNumber::ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

MathObject* ComplexNumber::add(const MathObject* other) const
{
	const ComplexNumber* otherComplex = dynamic_cast<const ComplexNumber*>(other);
	if (otherComplex)
	{
		double newReal = real + otherComplex->real;
		double newImaginary = imaginary + otherComplex->imaginary;
		return new ComplexNumber(newReal, newImaginary);
	}
	else
		return nullptr;
}

MathObject* ComplexNumber::substract(const MathObject* other) const
{
	const ComplexNumber* otherComplex = dynamic_cast<const ComplexNumber*>(other);
	if (otherComplex)
	{
		double newReal = real - otherComplex->real;
		double newImaginary = imaginary - otherComplex->imaginary;
		return new ComplexNumber(newReal, newImaginary);
	}
	else
		return nullptr;
}

MathObject* ComplexNumber::multiply(const MathObject* other) const
{
	const ComplexNumber* otherComplex = dynamic_cast<const ComplexNumber*>(other);
	if (otherComplex)
	{
		double newReal = real * otherComplex->real - imaginary * otherComplex->imaginary;
		double newImaginary = real * otherComplex->imaginary + imaginary * otherComplex->real;
		return new ComplexNumber(newReal, newImaginary);
	}
	else
		return nullptr;
}

MathObject* ComplexNumber::divide(const MathObject* other) const
{
	const ComplexNumber* otherComplex = dynamic_cast<const ComplexNumber*>(other);
	if (otherComplex)
	{
		double denominator = otherComplex->real * otherComplex->real + otherComplex->imaginary * otherComplex->imaginary;
		if (denominator == 0)
			return nullptr;

		double newReal = (real * otherComplex->real + imaginary * otherComplex->imaginary) / denominator;
		double newImaginary = (imaginary * otherComplex->real - real * otherComplex->imaginary) / denominator;
		return new ComplexNumber(newReal, newImaginary);
	}
	else
		return nullptr;
}

MathObject* ComplexNumber::power(const MathObject* other) const
{
	const ComplexNumber* otherComplex = dynamic_cast<const ComplexNumber*>(other);
	if (otherComplex && otherComplex->imaginary == 0)
	{
		double base = std::sqrt(real * real + imaginary * imaginary);
		double angle = std::atan2(imaginary, real);
		double exponent = otherComplex->real;
		double newReal = std::pow(base, exponent) * std::cos(exponent * angle);
		double newImaginary = std::pow(base, exponent) * std::sin(exponent * angle);
		return new ComplexNumber(newReal, newImaginary);
	}
	else
		return nullptr;
}

std::string ComplexNumber::toString() const 
{
	std::string result = std::to_string(real);
	if (imaginary >= 0)
		result += "+";
	result += std::to_string(imaginary) + "i";
	return result;
}