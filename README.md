# IPC-Driver-For-Shortest-Path-Calculation
In graph theory, the shortest path problem consists of finding a path between 2 vertices in a given graph such that the path is shortest among all possible paths between the 2 vertices. Finding the shortest between vertices has several applications in the real world including finding the short path between 2 physical location - just like what Google Maps does.

## Overview
In the context of taking a set of streets and converting the set into an undirected graph, the IPC driver in this repository does the following:
- Generates random street specifications
- Converts the set of random street into an undirected graph
- Allows the user to then calculate the shortest path between vertices in the now generated graph 

The above is done through forking multiple processes that handle each step and the driver uses I/O redirection to pass the output from one sub-program to the input of the other


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

Before, the program can be run, it first needs to be built (aka compiled). After cloning the repository, run the following command under the same folder as the repository, to build the program on your CLI:
```
mkdir build && cd build && cmake ../ && make 
```
### Running the Program

#### Optional Arguments

The random street spec generator takes in 4 optional arguments which allow you alter change the number of streets, the number of segments in each street, the duration between each graph generation and the bounds of the coordinates of the generated streets. The arguments are as follows:

- ```-s k``` where k is an integer >= 2. The number of streets should be a random integer in [2,k].
If this option is not specified, a default of k = 10 is used; that is, the number of street is a random integer in [2,10].
- ```-n k``` where k is an integer >= 1. The number of line-segments in each street is a random integer in [1,k]. 
Default: k = 5.
- ```-l k``` where k is an integer >= 5. The process waits a random number w seconds, where w is in [5,k] before generating the next (random) input. Default: k = 5.
- ```-c k``` where k is an integer >= 1. The process generates (x,y) coordinates such that every x and y value is in the range [-k,k]. For example, if k = 15, all coordinate values are integers between -15 and 15. Default: k = 20.


#### Default Mode
Since all the above arguments are optional, the driver can be run in default mode as follows under the ```/build``` folder:
```
cd /run/bin
./ipc_driver

# Example Run
# driver output
V 5
E {<0,1>,<1,2>,<3,1>,<1,4>}

# user input to find shortest path between vertex 3 and vertex 2
s 3 2
3-1-2
```

#### Special Mode
This mode runs the driver under the optional arguments defined above. This is can be done by running the driver under the ```/build``` folder as follows:
```
cd /run/bin
./ipc_driver ./ipc_driver -s 5 -n 4 -l 5

# Example Run
# driver output
V 13
E {<0,1>,<1,2>,<2,3>,<3,4>,<4,5>,<6,7>,<7,4>,<4,8>,<9,1>,<1,10>,<10,2>,<2,11>,<11,7>,<7,3>,<3,12>}

s 1 12    # user input to find shortest path between vertex 3 and vertex 2
1-2-3-12  # driver output  
```





