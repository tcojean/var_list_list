#include "tiny_var_list.hpp"
#include "var_list_list.hpp"

#include <iostream>

template <typename K, typename V>
void print_search_value(const var_list_list& list, const K& key)
{
    std::cout << "Searching key " << key << " with types (k,v)=(" <<
        typeid(K).name() << "," << typeid(V).name() << "): ";
    auto *val = list.search<K,V>(key);
    if (val != nullptr) {
      std::cout << *val;
    } else {
      std::cout << "nullptr";
    }
    std::cout << "\n";
}

int main() {
  var_list<int, double> int_double{{0, 13.3}, {2, 44.4}, {5, 77.7}};
  var_list<int, char> int_char{{0, 'a'}, {2, 'c'}, {3, 'd'}, {10, 'k'}};
  var_list<std::string, std::string> str_str{{"foo", "bar"},
                                             {"dummy", "value"}};
  var_list_list list{};
  list.append(&int_double);
  list.append(&int_char);
  list.append(&str_str);

  print_search_value<int, double>(list, 0);
  print_search_value<int, char>(list, 2);
  print_search_value<int, char>(list, 10);
  print_search_value<std::string, std::string>(list, "foo");

  int_double.append({13, 172.74});
  print_search_value<int, double>(list, 13);

  // invalid
  print_search_value<int, double>(list, 1);
  print_search_value<int, int>(list, 1);

  return 0;
}
