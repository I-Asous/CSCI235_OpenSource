#pragma once

// A tiny test framework so the project has zero dependencies.
//
//   TEST_CASE("LinkedStack: push then peek") {
//       h235::LinkedStack<int> s;
//       s.push(7);
//       CHECK_EQ(s.peek(), 7);
//   }
//
// Any .cpp file under tests/ is compiled automatically -- you never edit the Makefile.

#include <functional>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace h235test {

struct TestCase {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(std::string name, std::function<void()> fn) {
        registry().push_back({std::move(name), std::move(fn)});
    }
};

struct Failure {
    std::string message;
};

template <class T, class = void>
struct IsStreamable : std::false_type {};
template <class T>
struct IsStreamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

template <class T>
std::string show(const T& value) {
    if constexpr (IsStreamable<T>::value) {
        std::ostringstream out;
        out << value;
        return out.str();
    } else {
        return "<unprintable>";
    }
}

template <class T>
std::string show(const std::vector<T>& values) {
    std::string out = "{";
    for (std::size_t i = 0; i < values.size(); ++i) {
        out += (i == 0 ? "" : ", ") + show(values[i]);
    }
    return out + "}";
}

inline std::string location(const char* file, int line) {
    return std::string(file) + ":" + std::to_string(line) + ": ";
}

}  // namespace h235test

#define H235_CONCAT_INNER(a, b) a##b
#define H235_CONCAT(a, b) H235_CONCAT_INNER(a, b)

#define TEST_CASE(name)                                                             \
    static void H235_CONCAT(h235_test_, __LINE__)();                                \
    static ::h235test::Registrar H235_CONCAT(h235_registrar_, __LINE__)(            \
        name, H235_CONCAT(h235_test_, __LINE__));                                   \
    static void H235_CONCAT(h235_test_, __LINE__)()

#define CHECK(expr)                                                                 \
    do {                                                                            \
        if (!(expr)) {                                                              \
            throw ::h235test::Failure{::h235test::location(__FILE__, __LINE__) +    \
                                      "CHECK(" #expr ") failed"};                   \
        }                                                                           \
    } while (0)

#define CHECK_EQ(actual, expected)                                                  \
    do {                                                                            \
        const auto& h235_actual = (actual);                                         \
        const auto& h235_expected = (expected);                                     \
        if (!(h235_actual == h235_expected)) {                                      \
            throw ::h235test::Failure{::h235test::location(__FILE__, __LINE__) +    \
                                      "CHECK_EQ(" #actual ", " #expected ")\n"      \
                                      "      got:      " +                          \
                                      ::h235test::show(h235_actual) +               \
                                      "\n      expected: " +                        \
                                      ::h235test::show(h235_expected)};             \
        }                                                                           \
    } while (0)

#define CHECK_THROWS(expr, ExceptionType)                                           \
    do {                                                                            \
        bool h235_threw = false;                                                    \
        try {                                                                       \
            (void)(expr);                                                           \
        } catch (const ExceptionType&) {                                            \
            h235_threw = true;                                                      \
        }                                                                           \
        if (!h235_threw) {                                                          \
            throw ::h235test::Failure{::h235test::location(__FILE__, __LINE__) +    \
                                      "expected " #expr " to throw " #ExceptionType}; \
        }                                                                           \
    } while (0)
