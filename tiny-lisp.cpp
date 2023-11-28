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