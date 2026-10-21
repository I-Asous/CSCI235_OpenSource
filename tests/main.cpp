// Runs every registered TEST_CASE. Pass a substring to run only matching tests:
//   ./build/run_tests LinkedStack

#include <exception>
#include <iostream>
#include <string>

#include "framework.hpp"

int main(int argc, char** argv) {
    std::string filter = argc > 1 ? argv[1] : "";
    int passed = 0;
    int failed = 0;

    for (const auto& test : h235test::registry()) {
        if (test.name.find(filter) == std::string::npos) {
            continue;
        }
        try {
            test.fn();
            ++passed;
            std::cout << "  PASS  " << test.name << '\n';
        } catch (const h235test::Failure& f) {
            ++failed;
            std::cout << "  FAIL  " << test.name << "\n    " << f.message << '\n';
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "  FAIL  " << test.name << "\n    unexpected exception: " << e.what() << '\n';
        } catch (...) {
            ++failed;
            std::cout << "  FAIL  " << test.name << "\n    unexpected non-standard exception\n";
        }
    }

    std::cout << '\n' << passed << " passed, " << failed << " failed\n";
    if (passed + failed == 0) {
        std::cout << "No tests matched \"" << filter << "\"\n";
        return 1;
    }
    return failed == 0 ? 0 : 1;
}
