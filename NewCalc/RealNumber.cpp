#include "RealNumber.h"
#include <cmath>
#include <string>
#include <iostream>

RealNumber::RealNumber(double value) : value(value) {}

MathObject* RealNumber::add(const MathObject* other) const
{
	const RealNumber* otherReal = dynamic_cast<const RealNumber*>(other);
	if (otherReal)
	{
		double result = value + otherReal->value;
		return new RealNumber(result);
	}
	else
		return nullptr;
}

MathObject* RealNumber::substract(const MathObject* other) const
{
	const RealNumber* otherReal = dynamic_cast<const RealNumber*>(other);
	if (otherReal)
	{
		double result = value - otherReal->value;
		return new RealNumber(result);
	}
	else
		return nullptr;
}

MathObject* RealNumber::multiply(const MathObject* other) const
{
	const RealNumber* otherReal = dynamic_cast<const RealNumber*>(other);
	if (otherReal)
	{
		double result = value * otherReal->value;
		return new RealNumber(result);
	}
	else
		return nullptr;
}

MathObject* RealNumber::divide(const MathObject* other) const
{
	const RealNumber* otherReal = dynamic_cast<const RealNumber*>(other);
	if (otherReal)
	{
		double result = value / otherReal->value;
		if (otherReal->value == 0)
		{
			std::cout << "Деление на 0!" << std::endl;
			return nullptr;
		}
		return new RealNumber(result);
	}
	else
		return nullptr;
}

MathObject* RealNumber::power(const MathObject* other) const
{
	const RealNumber* otherReal = dynamic_cast<const RealNumber*>(other);
	if (otherReal)
	{
		double result = std::pow(value, otherReal->value);
		return new RealNumber(result);
	}
	else
		return nullptr;
}

std::string RealNumber::toString() const
{
	return std::to_string(value);
}