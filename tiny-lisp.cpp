#include <iostream>
#include <variant>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include "json11.hpp"
#include "jsonlib.hpp"

class Variant {
public:
    using ValueType = std::variant<int, double, std::string, std::vector<Variant>, std::map<std::string, Variant>>;

    // Constructor que acepta un valor inicial
    Variant(const ValueType& value) : value_(value) {}

    // Método para obtener el valor interno
    ValueType getValue() const {
        return value_;
    }
};