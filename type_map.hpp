#ifndef TYPE_MAP_H_
#define TYPE_MAP_H_

#include <string>
#include <type_traits>


/**
 * Enum which maps C++ static type to a convenient runtime search field.
 */
enum MY_TYPE {
INVALID,
INT,
CHAR,
DOUBLE,
STRING
};


/**
 * Converts a C++ type to a runtime value of the MY_TYPE enum
 *
 * @tparam T the C++ type to convert
 *
 * @return a runtime MY_TYPE enum value
 */
template <typename T>
constexpr MY_TYPE to_my_type() {
    if constexpr (std::is_same<T, double>::value)
        return DOUBLE;
    else if constexpr (std::is_same<T, int>::value)
        return INT;
    else if constexpr (std::is_same<T, char>::value)
        return CHAR;
    else if constexpr (std::is_same<T, std::string>::value)
        return STRING;
    else {
        return INVALID;
    }
}


#endif // TYPE_MAP_H_
