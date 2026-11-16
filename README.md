# Algorithms for Programming Contests

Coursework for the **Algorithms for Programming Contests** practical module at the Technical University of Munich (TUM).

Each week has a set of problems in the style of programming contests. Every problem is solved in C++ and lives next to its problem statement (`*_AI.pdf`). Solutions read from standard input and write to standard output, with `Case #i:` output for multi-test-case problems.

## Layout

| Folder | Problems |
|---|---|
| [week1](week1) | Hello World (`hel`), This is odd... (`odd`), Relativity (`rel`), Students (`stu`), Watson (`wat`) |
| [week2](week2) | Indiana Jones and the lost Soccer Cup (`ind`), Library Hell (`lib`), City Roads (`cityroads`), Correcting Cheeseburgers (`cor`), Dominos for kids (`dom`) |
| [week3](week3) | Diplomacy (`dip`), Walking Straight Into Circles (`wal`), Grading exams (`gra`), Candy Store (`can`), Room Finding (`roo`) |
| [week4](week4) | Fly Deluxe (`fly`), Where to go? (`whe`), Party Planning (`par`), Supermarkets (`sup`), French Dinner (`fre`) |

## Techniques used

- **Week 1:** input/output, string parsing and replacement, 64-bit arithmetic.
- **Week 2:** graph algorithms: topological sort, BFS, strongly connected components, bidirectional BFS.
- **Week 3:** union-find, minimum spanning trees (Kruskal), binary search on the answer, priority-queue simulation (Grading exams), finding a tree's center by peeling off leaves (Candy Store).
- **Week 4:** shortest paths: Floyd-Warshall with offline queries (Fly Deluxe), Dijkstra (Where to go?, Supermarkets with a run from both ends), longest path in a DAG (Party Planning), difference constraints with Bellman-Ford negative-cycle detection (French Dinner).

## Building and running

Solutions are standard C++17 with no dependencies:

```sh
g++ -std=c++17 -O2 -o solution week2/dom.cpp
./solution < input.txt
```
