// Compile with g++ ece650-a2.cpp -std=c++11 -o a2ece650
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>
#include <list>
#include <iterator>
#include <queue>
#include <stack>

using namespace std;

// Adpated through algo provided on https://www.eecs.yorku.ca/course_archive/2006-07/W/2011/Notes/BFS_part2.pdf
void find_path(unsigned int src, unsigned int dest, unsigned int num_vert, vector<unsigned int> adj_list[]){

    // variables for algo
    int pred[num_vert];
    bool visited[num_vert];
    queue<unsigned int> queue;

    // instantiating, visited array values to false, and pred array values to -1
    for (unsigned int i = 0; i < num_vert; i++){

        visited[i] = false;
        pred[i] = -1;
    }

    
    // flag to check if path exists
    bool flag = false;
    
    //set the src as visited and push it on to the queue
    visited[src] = true;
    queue.push(src);

    // go through the entire qeueue
    while(!queue.empty()){

        // remove the first vertex from the queue
        unsigned int curr_v = queue.front();
        queue.pop();

        // ensure that the adj_list for the current vertex is not empty
        if (adj_list && !adj_list[curr_v].empty()){
            
            // go through the neighbors of the current vertex 
            for (unsigned int i = 0; i < adj_list[curr_v].size(); i++){

                // if neighbor not visited, mark neighbor as visited
                if (visited[adj_list[curr_v][i]] == false){

                    visited[adj_list[curr_v][i]] = true;
                    
                    //set the predecessor of neighbor as current vertex
                    pred[adj_list[curr_v][i]] = curr_v;
                    
                    // oush the neighbor vertex on to the stack
                    queue.push(adj_list[curr_v][i]);
                }

                // if the current vertex is the destination vertex, path is found and break
                if (adj_list[curr_v][i] == dest){
                    flag = true;
                    break;
                }


            }

        }

    }


    // no path was found, print error
    if(flag == false){

        std::cerr << "Error: No path was found between given vertices." << std::endl;
        exit(0);
    }


    // path is found, print the path out
    else{

        // create a new stack to store vertices in the path
        std::stack<unsigned int> path_stack;

        int curr_v = dest;

        // add vertices to the stack usign the pred array
        while(pred[curr_v] != -1)
        {
            
            path_stack.push(curr_v);
            curr_v = pred[curr_v];

        }

        //push src vertex on to stack
        path_stack.push(src);

        // pop vertices off of stack and print one by one 
        while(path_stack.size()!=1){

            std::cout << path_stack.top() << "-";
            path_stack.pop();

        }

        // print dest vertex the last
        std::cout << path_stack.top() << std::endl;
        
        return;

    }


}

// Check for duplicate edges
bool check_edge(unsigned int src, unsigned int dest, vector<unsigned int> adj_list[]){

    // check for edge between src->dest
    for(unsigned int i = 0; i < adj_list[src].size(); i++){
        
        // if edge found, return true
        if (adj_list[src][i] == dest)
            return true;
    }

    // check for edge between dest->src
    for(unsigned int i = 0; i < adj_list[dest].size(); i++){
        
        // if edge found, return true
        if (adj_list[dest][i] == src)
            return true;
    }

    // no edge found, return false
    return false;
}


int main(int argc, char** argv) {

    //initialize num_vert and adjacency list
    unsigned int num_vert = 1;
    vector<unsigned int> *adj_list = NULL;


    // read from stdin until EOF
    while (!std::cin.eof()) {

        //read line of input until EOL and store in string
        std::string input_line;
        std::getline(std::cin,input_line);

        // Split into options and arguments 
        // Adapted from https://www.techiedelight.com/split-string-cpp-using-delimiter/
        std::regex split_rgx (" ");
        std::vector<std::string> elem_1(std::sregex_token_iterator(input_line.begin(), input_line.end(), split_rgx, -1), 
            std::sregex_token_iterator());


        //Save option that the user entered
        std::string option = elem_1[0];

        //If option is V, retrieve the number of vertices and save in num_vert
        if(option.compare("V") == 0){

            std::cout << input_line << std::endl;

            num_vert = stoi(elem_1[1]);

            if (num_vert == 0){
                std::cerr << "Error: Cannot have graph with 0 vertices." << std::endl;
                exit(0);
            }

            adj_list = new vector<unsigned int>[num_vert];
            


        }

        //If option is E, retrieve the edges and save edges in adj list
        if(option.compare("E") == 0){

            std::cout << input_line << std::endl;

            std::vector<std::string> edges;

            std::string edges_str = elem_1[1];
            
            //Regex to extract edges
            std::regex edge_regex(R"([0-9]+,[0-9]+)");

            //Create an iterator to go through edges_str and extract all edges (X,Y)
            //https://stackoverflow.com/questions/32553593/c-regex-extract-all-substrings-using-regex-search
            std::sregex_iterator start(edges_str.begin(), edges_str.end(), edge_regex);
            std::sregex_iterator end;

            // go through the string and extract all edges
            while(start!=end){

                for(unsigned int i = 0; i < start->size(); ++i)    
                    
                    //Add edges to edges vector
                    edges.push_back((*start)[i]);
                
                start++;

            }

            //create adj list
            //go through edges vector, split each edge by comma
            for(unsigned int i = 0; i < edges.size(); i++){

                // split each edge by comma
                std::regex comma_rgx (",");

                //std::cout << "printing edges - " << edges_str << std::endl; 
                std::vector<std::string> curr_edge(std::sregex_token_iterator(edges[i].begin(), edges[i].end(), comma_rgx, -1), 
                std::sregex_token_iterator());

                //convert src and dest vertice unsigned into unsigned integers
                unsigned int src = stoi(curr_edge[0]);
                unsigned int dest = stoi(curr_edge[1]);

                //ensure they are valid
                if (src >= num_vert || dest >= num_vert){
                     std::cerr << "Error: Cannot have edges between verticies that do not exist." << std::endl;
                     //break;
                     exit(0);
                }

                if (src == dest){
                     std::cerr << "Error: An edge cannot exist between a vertice and itself." << std::endl;
                    // break;
                     exit(0);
                }

                //Add src->dest and dest->src to adj list
                else{

                    if(adj_list){

                        // before adding edge, check if edge already exists
                        if (!check_edge(src,dest,adj_list)){
                            adj_list[src].push_back(dest);
                            adj_list[dest].push_back(src); 
                        }

                        else{
                            std::cerr << "Error: Cannot have duplicate egdes." << std::endl;
                            //break;
                            exit(0);
                        }
        
                    }

                }
            }

        }

        // if option is s 
        if(option.compare("s") == 0){

            unsigned int source = stoi(elem_1[1]);
            unsigned int destination = stoi(elem_1[2]);

            if (source >= num_vert || destination >= num_vert){
                std::cerr << "Error: Cannot find a path between vertices that do not exist." << std::endl;
                //continue;
                exit(0);
            }
            
            if (source == destination){
                std::cerr << "Error: There is no self loop in an undirected graph, so a path cannot exist." << std::endl;
                //continue;
                exit(0);
            }

            if (adj_list){
                if (adj_list[source].size() == 0 || adj_list[destination].size() == 0){
                    std::cerr << "Error: Cannot find a path between vertices that do not exist." << std::endl;
                    //continue;
                    exit(0);
                }
            }

            find_path(source, destination, num_vert, adj_list);
            continue;

        }

    }

    return 0;
}