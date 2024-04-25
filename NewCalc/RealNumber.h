#pragma once
#include "MathObject.h"

class RealNumber : public MathObject
{
public:
	RealNumber(double value);

	 MathObject* add(const MathObject* other) const override;
	 MathObject* substract(const MathObject* other) const override;
	 MathObject* multiply(const MathObject* other) const override;
	 MathObject* divide(const MathObject* other) const override;
	 MathObject* power(const MathObject* other) const override;
	 std::string toString() const override;

private:
	double value;
};
