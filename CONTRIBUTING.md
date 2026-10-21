# Contributing to h235

## The workflow at a glance

```
 upstream  (I-Asous/CSCI235)    the shared repo; nobody pushes here directly
    │  ▲
    │  │  pull request
fork│  │
    ▼  │
 origin    (you/CSCI235)        your copy on GitHub; you push here
    │  ▲
clone  │  push
    ▼  │
 local     (your laptop)        where you edit, commit, and run tests
```

1. **Sync** your local `main` with upstream:
   `git switch main && git pull upstream main && git push origin main`
2. **Branch:** `git switch -c issue-17-insertion-sort`
3. **Code and test:** `make test`
4. **Commit:** `git add <files>` then `git commit -m "Add insertion sort with tests"`
5. **Push:** `git push -u origin issue-17-insertion-sort`
6. **Open a PR** on GitHub from your branch to `I-Asous/CSCI235:main`
7. **Respond to review:** edit, commit, and `git push` again. The PR updates by itself.
8. **After it merges:** sync `main` again and delete the branch.

## Rules of the road

- **Never commit directly to `main`**, not even in your fork. `main` should always match upstream.
- **One branch per task, one task per PR.** Small PRs get reviewed and merged faster.
- **Claim an issue before you start** by commenting on it. Wait to be assigned.
- **Only touch the files your issue needs.** If you notice something unrelated, open a new issue for it.
- **Every change needs tests.** CI must be green before anyone reviews your code.

## Code conventions

- C++17, everything in `namespace h235`.
- One algorithm per header in `include/h235/algorithms/<name>.hpp`, with tests in `tests/algorithms/test_<name>.cpp`. ADTs go in `include/h235/<Name>.hpp` with tests in `tests/adt/`.
- Headers start with `#pragma once`.
- **Mark non-template functions defined in a header as `inline`.** Otherwise each `.cpp` that includes the header gets its own copy and the linker fails with "duplicate symbol". Templates don't need it.
- Classes that own heap memory follow the **Rule of Three**: copy constructor, copy assignment, and destructor.
- Put a short comment above each public function saying what it does, what it returns, and what it throws.
- Copy the style of [`binary_search.hpp`](include/h235/algorithms/binary_search.hpp) and [`test_binary_search.cpp`](tests/algorithms/test_binary_search.cpp).

## Writing tests

```cpp
#include "framework.hpp"
#include "h235/algorithms/insertion_sort.hpp"

TEST_CASE("insertionSort: sorts a reversed vector") {
    std::vector<int> v{5, 4, 3, 2, 1};
    h235::insertionSort(v);
    CHECK_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}
```

- `CHECK(condition)`, `CHECK_EQ(actual, expected)`, `CHECK_THROWS(expression, ExceptionType)`.
- Wrap brace-initializers in parentheses inside macros: `CHECK_EQ(v, (std::vector<int>{1, 2}))`.
- Compare like types to avoid sign warnings: `CHECK_EQ(v.size(), 3u)`.
- Name tests `"functionName: what is being checked"`.
- Any `.cpp` under `tests/` is compiled automatically. You never edit the `Makefile`.

## Commit messages

Write the subject in the imperative, as if completing the sentence "This commit will…":

```
Add merge sort with stability test        ✅
Fix off-by-one in LinkedList::insert       ✅
updated stuff                              ❌
final version for real                     ❌
```

## What CI checks

Every push to a PR runs [`.github/workflows/ci.yml`](.github/workflows/ci.yml), which:

- builds with **g++ and clang++**, with warnings treated as errors;
- runs every test with **AddressSanitizer and UndefinedBehaviorSanitizer**, so leaks, use-after-free, and out-of-bounds access fail the build;
- checks that files in `contributors/` are formatted correctly and that you only added your own.

To run the same thing locally on Linux or WSL: `make test WERROR=1 SANITIZE=1`.
(AddressSanitizer is unreliable on some recent macOS versions. If it hangs on a Mac, run plain `make test WERROR=1` and let CI do the sanitizer check.)
