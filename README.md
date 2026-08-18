# Algorithms and Data Structures — C++ Coursework

A collection of C++ assignments completed while studying **Algorithms and Data Structures**. The repository covers fundamental sorting, graph algorithms, set operations, and file processing.

## Assignments

| # | Assignment | Main Topics |
|---|---|---|
| 1 | [Sorting Algorithms](assignments/01-sorting-algorithms) | Insertion Sort, Heap Sort, benchmarking |
| 2 | [Topological Sort](assignments/02-topological-sort) | Directed graphs, adjacency matrix, Kahn's algorithm |
| 3 | [Kruskal MST](assignments/03-kruskal-mst) | Minimum Spanning Tree, Union-Find |
| 4 | [Set of Integers](assignments/04-set-of-integers) | Set operations, classes, fixed-capacity storage |
| 5 | [Employee File Processing](assignments/05-employee-file-processing) | File I/O, sorting, salary statistics |

## Build

The repository uses **CMake** and requires a compiler with C++17 support.

```bash
cmake -S . -B build
cmake --build build
```

Each assignment is built as a separate executable.

## Repository Structure

```text
Algorithms-and-Data-Structures-CPP/
├── assignments/
│   ├── 01-sorting-algorithms/
│   ├── 02-topological-sort/
│   ├── 03-kruskal-mst/
│   ├── 04-set-of-integers/
│   └── 05-employee-file-processing/
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Improvements in This Version

The coursework was reorganized for a clean GitHub presentation while preserving the original assignment goals. The cleanup includes portable C++17 code, safer containers and strings, input validation, clearer naming, cycle/disconnected-graph checks, and corrected sorting benchmark input.
