#pragma once
#include <string>

class MathObject
{
public:
	virtual ~MathObject() = default;

	virtual MathObject* add(const MathObject* other) const = 0;
	virtual MathObject* substract(const MathObject* other) const = 0;
	virtual MathObject* multiply(const MathObject* other) const = 0;
	virtual MathObject* divide(const MathObject* other) const = 0;
	virtual MathObject* power(const MathObject* other) const = 0;
	virtual std::string toString() const = 0;
};