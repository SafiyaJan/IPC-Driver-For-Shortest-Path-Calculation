# IPC-Driver-For-Shortest-Path-Calculation
In graph theory, the shortest path problem consists of finding a path between 2 vertices in a given graph such that the path is shortest among all possible paths between the 2 vertices. Finding the shortest between vertices has several applications in the real world including finding the short path between 2 physical location - just like what Google Maps does. The program in this repository, written in C++, takes as input, an edge-list of a graph and the 2 vertices, where the shortest path between the 2 vertices is to be found. In order to calculate the shortest path, the Breadth First Algorithm has been used.

## Getting Started

In order to run the program, firstly, you must clone the repository on your local machine. You can do this by running the following line on your machine's CLI:

```git clone https://github.com/SafiyaJan/IPC-Driver-For-Shortest-Path-Calculation.git```

### Prerequisites

- Ensure that you have the latest version of CMake installed on your local machine. You can checkout the following link to download CMake for your specific machine: https://cmake.org/download/
- You will also need a C++ compiler in order to compile the program. GCC and Clang are 2 such compilers and either can be used to compile the program
  - Installing Clang - https://clang.llvm.org/get_started.html
  - Installing GCC - https://gcc.gnu.org/wiki/InstallingGCC

## Usage 

### Building the Executable

Before, the program can be run, it first needs to be built (aka compiled). After cloning the repository, run the following command to build the program on you CLI:
```
mkdir build && cd build && cmake ../ && make 
```

#### Running the Program
