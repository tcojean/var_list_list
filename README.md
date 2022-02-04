Generic container of var list
=====================================

The purpose of this example is to showcase one way of creating in C++ a
container which can contain any other type of container. It is not designed to
be efficient yet, merely at trying one of many possible solutions. It is also
designed to be overly generic, and maybe too much if the actual use cases are
restricted to only a handful of key, value types for the var list.

Currently, this example requires C++17 and its [`std::any` feature](https://en.cppreference.com/w/cpp/utility/any).

### Compiling and running

The project relies on a somewhat recent version of CMake. This should work on most systems:

``` shell
# Generate the Makefile and build
cmake -H. -Bbuild
cmake --build build
# Run the example
build/var_list_list
```

### Overview of the code and discussion

Some aspects of the solution are detailed in the comments, at a high level there is:
+ `var_list`, templated on a key type and contained value type, in
  `tiny_var_list.hpp`
+ `var_list_list`, a generic container which is not templated and contains any
  template instantiation of `var_list`, in `var_list_list.hpp`. The goal of this
  project is that every operation can go through this abstract container in a
  relatively cheap fashion.
+ the main test function is in `var_list_list_test`.
+ the file `type_map.hpp` contains an enum and a constexpr function which, at
  compile time, maps the pair of types of the underlying `var_list`, like `int,
  double` or `string, string` to a runtime enum value like `std::pair<INT,
  DOUBLE>`. This can be used to search at little cost a list which matches the
  requested types in the `var_list_list`.

There are unknowns in this solution which would decide whether it fits or not:
+ The overhead of `std::any`. Overall, only the
  [`std::any_cast`](./var_list_list.hpp#L66) is relevant, but it is only called
  once when accessing a matching `var_list` to obtain its concrete type in the
  `var_list_list`. The enum trick should not cost anything, particularly since it
  can be prepared at compile-time.
+ Data lifetime, and pointer accesses. Should the `var_list_list` contain the
  actual `var_list` instantiation, or only a pointer? Changing to
  `var_list_list` taking ownership of the `var_list` can easily be done with
  `std::move`.
+ The search function requires knowing the key and the **type** of value being
  searched.
+ As previously said, this is very generic, is this much genericity required?
