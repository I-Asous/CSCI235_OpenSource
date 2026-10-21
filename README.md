# h235: a C++ data structures and algorithms library


**h235** is an open-source, header-only C++17 library of abstract data types and algorithms. It is built and maintained by students in **CSCI 235: Software Analysis and Design II at Hunter College**.

Every line of code got in the way it does at a software company. A student forked the repo, wrote the code on a branch, added tests, and opened a pull request. Automated tests (CI) checked it, and a classmate and an instructor reviewed it before it was merged.

> **CSCI 235 students: start here →** [Lab 0: Setup](docs/labs/00-setup.md).
> Do the labs in order. Don't clone yet; [Lab 1](docs/labs/01-fork-and-clone.md) shows you how to fork first.

```cpp
#include "h235/LinkedStack.hpp"
#include "h235/algorithms/binary_search.hpp"

h235::LinkedStack<int> s;
s.push(42);

std::vector<int> v{1, 3, 5, 7};
int index = h235::binarySearch(v, 5);   // 2
```

## What's inside

| Area                                                                   | Examples                                                                      | Status                                               |
| ---------------------------------------------------------------------- | ----------------------------------------------------------------------------- | ---------------------------------------------------- |
| ADTs                                                                   | `ArrayBag`, `LinkedBag`, `LinkedStack`, `LinkedQueue`, `LinkedList` | provided                                             |
| Searching                                                              | `binarySearch` (worked example)                                             | provided                                             |
| Recursion, sorting, searching, stacks, queues, linked lists, more ADTs | ~45 open tasks                                                                | [built by students: see open issues](../../issues) |

## Quick start

Just want to try the library? You need `git`, `make`, and a C++17 compiler (`g++` or `clang++`). Students: follow the [labs](#contributing) instead.

```bash
git clone https://github.com/I-Asous/CSCI235.git
cd CSCI235
make test                 # build and run all tests
make test ONLY=Stack      # run only tests whose name contains "Stack"
```

## Project layout

```
include/h235/              library headers (ADTs)
include/h235/algorithms/   one header per algorithm
tests/                     one test file per header; picked up automatically
contributors/              one file per contributor
docs/labs/                 the step-by-step Git labs
scripts/                   CI and instructor tooling
```

## Contributing

New here? Work through the labs in order. Each one builds on the last.

| # | Lab                                                          | You will learn                                                       |
| - | ------------------------------------------------------------ | -------------------------------------------------------------------- |
| 0 | [Setup](docs/labs/00-setup.md)                                | Install and configure Git, connect to GitHub                         |
| 1 | [Fork and clone](docs/labs/01-fork-and-clone.md)              | `fork`, `clone`, `remote`, `upstream` vs `origin`          |
| 2 | [Your first pull request](docs/labs/02-first-pull-request.md) | `branch`, `add`, `commit`, `push`, PRs, syncing your fork    |
| 3 | [Merge conflicts](docs/labs/03-merge-conflicts.md)            | Causing, reading, and resolving conflicts; `rebase`                |
| 4 | [Claim an issue and ship it](docs/labs/04-claim-an-issue.md)  | Issues, feature branches, tests, CI, iterating on review             |
| 5 | [Code review](docs/labs/05-code-review.md)                    | Reviewing a classmate's PR, checking it out locally                  |
| 6 | [Undo and recover](docs/labs/06-undo-and-recover.md)          | `restore`, `amend`, `revert`, `reset`, `stash`, `reflog` |

Also see [CONTRIBUTING.md](CONTRIBUTING.md), the [Git cheat sheet](docs/git-cheatsheet.md), and [how to put this on your resume](docs/resume.md).

## Contributors

See [`contributors/`](contributors/) and the [contributors graph](../../graphs/contributors).

Instructors and TAs: see the [instructor guide](docs/instructor-guide.md).
