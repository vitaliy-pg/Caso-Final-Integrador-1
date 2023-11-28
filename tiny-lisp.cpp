#include <iostream>
#include <variant>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include "json11.hpp"
#include "jsonlib.hpp"
enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };
struct Entorno;


class Variant {
public:
    typedef Variant(*proc_type) ( const std::vector<Variant>& );
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    variant_type type;
    std::string val;
    std::vector<Variant> list;
    proc_type proc;
    Entorno* env;

    Variant(variant_type type = Symbol) : type(type), env(0), proc(0) {}
    Variant(variant_type type, const std::string& val) : type(type), val(val), env(0), proc(0) {}
    Variant(proc_type proc) : type(Proc), proc(proc), env(0) {}

    std::string to_string();
    std::string to_json_string();
    static Variant from_json_string(const std::string& sjson);
    static Variant parse_json(const json11::Json& job);

    };


std::string Variant::to_string() {
    switch (type) {
        case Symbol:
            return val;
        case Number:
            return std::to_string(std::stod(val));
        case List: {
            std::string result = "(";
            for (auto it = list.begin(); it != list.end(); ++it) {
                result += it->to_string();
                if (std::next(it) != list.end()) {
                    result += " ";
                }
            }
            result += ")";
            return result;
        }
        case Proc:
            return "#<procedure>";
        case Lambda:
            return "#<lambda>";
        case Cadena:
            return '"' + val + '"';
        default:
            return "";
    }
}
std::string Variant::to_json_string() {
    json11::Json::array arr;
    switch (type) {
        case Symbol:
            return val;
        case Number:
            return std::to_string(std::stod(val));
        case List: {
            for (const auto& elem : list) {
                arr.push_back(json11::Json(elem.to_json_string()));
            }
            return json11::Json(arr).dump();
        }
        case Proc:
            return "#<procedure>";
        case Lambda:
            return "#<lambda>";
        case Cadena:
            return '"' + val + '"';
        default:
            return "";
    }
}
Variant Variant::from_json_string(const std::string& sjson) {
    std::string err;
    json11::Json json = json11::Json::parse(sjson, err);
    if (!err.empty()) {
        throw std::runtime_error("Error parsing JSON: " + err);
    }
    return parse_json(json);
}

Variant Variant::parse_json(const json11::Json& job) {
    switch (job.type()) {
        case json11::Json::NUMBER:
            return Variant(Number, job.string_value());
        case json11::Json::STRING:
            return Variant(Cadena, job.string_value());
        case json11::Json::ARRAY: {
            Variant result(List);
            for (const auto& elem : job.array_items()) {
                result.list.push_back(parse_json(elem));
            }
            return result;
        }
        default:
            return Variant();
    }
}
