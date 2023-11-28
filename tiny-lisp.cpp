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

