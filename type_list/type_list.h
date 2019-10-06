// Requires C++14

#pragma once

#include <initializer_list>
#include <string>
#include <type_traits>

namespace bds {

template <typename... Rest> struct TypeList {
  // Test whether the input type T is a member of the type list.
  template <typename T> static constexpr bool HasExactly() {
    // This packs the operation on the type list into an (constexpr)
    // initializer list, which is a common technique.
    auto list = {std::is_same<T, Rest>::value...};
    // The main logic. Note that the logic (including the for loop)
    // here is evaluated at COMPILE TIME, which makes it very similar
    // to Lisp's macros in some sense.
    bool result = false;
    for (auto entry : list) {
      result |= entry;
    }
    return result;
  }

  // Has() is similar to HasExactly(), except for that it allows for
  // comparison after std::decay.
  template <typename T> static constexpr bool Has() {
    auto list = {std::is_same<std::decay_t<T>, Rest>::value...};
    bool result = false;
    for (auto entry : list) {
      result |= entry;
    }
    return result;
  }
};

// +-----------------------------------------------+
// | Static unit tests for TypeList::HasExactly    |
// +-----------------------------------------------+

static_assert(TypeList<int, bool, std::string>::HasExactly<int>(),
              "Should have int!");
static_assert(TypeList<int, bool, std::string>::HasExactly<bool>(),
              "Should have bool!");
static_assert(!TypeList<int, bool, std::string>::HasExactly<const int &>(),
              "Can not recognize references!");

// +-----------------------------------------------+
// | Static unit tests for TypeList::Has           |
// +-----------------------------------------------+

static_assert(TypeList<int, bool, std::string>::Has<int>(), "Should have int!");
static_assert(TypeList<int, bool, std::string>::Has<bool>(),
              "Should have bool!");
static_assert(TypeList<int, bool, std::string>::Has<const int &>(),
              "Can recognize references!");
static_assert(!TypeList<int, bool, std::string>::Has<int *>(),
              "But not pointers");

} // namespace bds
