#pragma once

#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "MathObject.h"

class JsonParser 
{
public:
    JsonParser(const std::string& jsonStr);
    std::string getCalculatorType() const;
    std::string getExpression() const;
    std::unordered_map<std::string, MathObject*> getVariables() const;

private:
    nlohmann::json data;
    void parseVariables(std::unordered_map<std::string, MathObject*>& variables) const;
    MathObject* createMathObject(const std::string& type, const nlohmann::json& value) const;
};