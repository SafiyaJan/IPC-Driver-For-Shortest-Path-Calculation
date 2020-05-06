//g++ ece650-a3.cpp -std=c++11 -o a3ece650

#include <vector>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>

#define read 0
#define write 1

int main (int argc, char **argv) {

	std::vector<pid_t> children;

	// create pipe between rgen and A1
	int rgenToA1[2];
	pipe(rgenToA1);

	// create pipe between A1 and A2
	int A1toA2[2];
	pipe(A1toA2);

	// create process for executing A1
	pid_t child_pid;

	// Fork process for A1
	child_pid = fork();

	if (child_pid == 0){

		// rgen sends input to A1
		dup2(rgenToA1[read],STDIN_FILENO);
		
		// a1 sends input to A2 
		dup2(A1toA2[write], STDOUT_FILENO);

		//close read end of pipe from rgen-A1
		close(rgenToA1[read]);

		//close read end of pipe A1-A2
		close(A1toA2[read]);

		close(A1toA2[write]);

		close(rgenToA1[write]);

		// create args for execvp 
		char* args[] = {(char*) "python3", (char*) "input_parser.py", (char*)NULL};
		// execute A1
		execvp("python3", args);
		//std::cerr << "Returned from A1" << std::endl;
		
		return 1;

	}

	// if forking process fails
	else if (child_pid < 0){
		std::cerr << "Error: could not fork" << std::endl;
		return 1;
	}

	// add child to list of children
	children.push_back(child_pid);

	//std::cerr << "Executing a2" << std::endl;	

	// create child for executing A2
	child_pid = fork();

	if (child_pid == 0){

		// a1 output to a2 input
		dup2(A1toA2[read],STDIN_FILENO);

		// close read end of pipe A1-A2
		close(A1toA2[write]);

		//close read end of pipe A1-A2
		close(A1toA2[read]);

		char* args[] = {(char*)"shortest_path", (char*)NULL};

		// execute A2
		execvp("./shortest_path", args);

		//std::cerr << "Returned from A2" << std::endl;

		return 1;

	}

	// if forking process fails
	else if (child_pid < 0){
		std::cerr << "Error: could not fork" << std::endl;
		return 1;
	}

	// add child to list of children
	children.push_back(child_pid);

	// create child for executing rgen
	child_pid = fork();

	if (child_pid == 0){

		// take output from rgen into input of A1
		dup2(rgenToA1[write],STDOUT_FILENO);

		// close read of pipe rgen-a1
		close(rgenToA1[read]);

		//close read end of pipe A1-A2
		close(A1toA2[read]);

		argv[0] = (char*)"rgen";

		execvp("./rgen", argv);
		//std::cerr << "Returned from rgen"<< std::endl;
		return 1;

	}

	else if (child_pid < 0){
		std::cerr << "Error: could not fork" << std::endl;
		return 1;
	}

	// add child to list of children
	children.push_back(child_pid);

	// send user input to A2
	dup2(A1toA2[write], STDOUT_FILENO);

	//for process to handle user input
	child_pid = fork();

	if (child_pid == 0){

		// keep reading user input while not eof
		while(!std::cin.eof()){

			std::string input_line;
	        std::getline(std::cin,input_line);

	        std::cout << input_line << std::endl;
		}

		return 1;
	}

	// if forking process fails
	else if (child_pid < 0){
		std::cerr << "Error: could not fork." << std::endl;
		return 1;
	}

	// add child to list of children
	children.push_back(child_pid);

	// wait for any child process to terminate/exit
	wait(NULL);

	// kill all proess
	for (pid_t k : children) {
        kill (k, SIGTERM);
    }

    return 0;
}
