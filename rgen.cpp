//g++ rgen.cpp -std=c++11 -o rgen

#include <iostream>
#include <string>
#include <getopt.h>
#include <unistd.h>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

// stores number of points of intersection in graph/street spec
int num_ip = 0;

// Class that represents a point object
class Point{
public:
	int x;
	int y;

	Point(){

	}

	// create point object with x1, y1
	Point(int x1, int y1){
		x = x1;
		y = y1;

	}

	// print point object 
	void print_point(){
		std::cerr << "(" << x << "," << y << ")";
	}


	// function to compare points
	friend bool operator==(const Point &p1, const Point &p2)
	{
	    return (p1.x == p2.x && p1.y == p2.y);
	    
	}


};

// generate random coordinate
int* rand_coord(int bounds){

	// read /dev/urandom 
	std::fstream randfile("/dev/urandom");

	unsigned int seed = 0;
	int coord_val_x;
	int coord_val_y;

	// array to store x,y
	static int point[2]; 

	int l_bound = 0-bounds;
	//std::cout << l_bound << std::endl;
	int u_bound = bounds;

	// check if file can be read
	if (!randfile){

		std::cerr << "Error opening /dev/urandom. Exiting.\n";
		//return NULL;
		exit(0);
	}
 
	// generate rand number between -bound and bound
	else{

		// reed seed value for x1
		randfile.read((char*)&seed, sizeof(seed));
		//coord_val = (seed % (bounds*2 + 1)) - bounds;
		coord_val_x = l_bound + (seed % (u_bound - l_bound + 1));

		//seed = 0;

		//read seed value for y1
		randfile.read((char*)&seed, sizeof(seed));
		coord_val_y = l_bound + (seed % (u_bound - l_bound + 1));

		//std::cout << "Coord_val " << coord_val_x << "," << coord_val_y << std::endl;

		point[0] = coord_val_x;
		point[1] = coord_val_y;

		//cstd::cout << "Point x:" << point[0] << " y:" << point[1] << "\n";

		randfile.close();

		return point;

	}	

}

// generate random number of streets 
unsigned int num_street(unsigned int s){

	//if default value given return it
	if (s == 2){
		return 2;
	}

	// read /dev/urandom 
	std::fstream randfile("/dev/urandom");

	unsigned int s_rand = 0;
	unsigned int s_val;

	// check if file can be read
	if (!randfile){

		std::cerr << "Error opening /dev/urandom. Exiting.\n";
		//return 1;
		exit(0);
	}

	// generate rand number between 2 and s
	else{

		randfile.read((char*)&s_rand, sizeof(s_rand));
		s_val = 2 + (s_rand % (s - 2 + 1)) ;
		//std::cout << "HERE num_street" << s_val << std::endl;

		randfile.close();

		return s_val;

	}
}

unsigned int num_lineseg(int n){

	//if default value given, return default value
	if (n == 1){
		return 1;
	}

	// read /dev/urandom 
	std::fstream randfile("/dev/urandom");

	unsigned int n_rand = 0;
	unsigned int n_val;

	// check if file can be read
	if (!randfile){

		std::cerr << "Error opening /dev/urandom. Exiting.\n";
		//return 1;
		exit(0);
	}

	// generate rnad number between 1 and n
	else{

		randfile.read((char*)&n_rand, sizeof(n_rand));
		n_val = 1 + (n_rand % n) ;
		//std::cout << "HERE num_street" << n_val << std::endl;

		randfile.close();

		return n_val;
	}

	
}

// print out streets 
void print_streetdb(const std::map<string,vector<Point>> &street_db){
	
	// go through map (dictionary) and print key(str_name) and val(points)
	for (auto const& x : street_db){
		
		std::cerr << x.first;
		std::cerr << " ";
		
		for (unsigned int i = 0; i < x.second.size(); i++){
			
			Point temp = x.second[i];
			temp.print_point();
			std::cerr << ",";

		}

		std::cerr << std::endl;
	}

	
}


unsigned int num_wait(int w){

	// if default value given, return default value
	if (w == 5){
		return 5;
	}

	// read /dev/urandom 
	std::fstream randfile("/dev/urandom");

	unsigned int w_rand = 0;
	unsigned int w_val;

	// check if file can be read
	if (!randfile){

		std::cerr << "Error opening /dev/urandom. Exiting.\n";
		return 1;
	}

	// generate rnad number between 5 and w
	else{

		randfile.read((char*)&w_rand, sizeof(w_rand));
		w_val = 5 + (w_rand % (w - 5 + 1)) ;

		randfile.close();

		return w_val;
	}

}

bool check_intersect_overlap(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){

	float t_val = ((x1-x3)*(y3-y4)) - ((y1-y3)*(x3-x4));
	float t_val_denom = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));

	float u_val = -(((x1-x2)*(y1-y3)) - ((y1-y2)*(x1-x3)));
	float u_val_denom = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));

	//colinear -> overlapping
	if (t_val_denom == 0 && u_val_denom == 0 && t_val == 0 && u_val == 0)
		return true;

	return false;
	
}



bool check_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){


	float t_val = ((x1-x3)*(y3-y4)) - ((y1-y3)*(x3-x4));
	float t_val_denom = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));

	float u_val = -(((x1-x2)*(y1-y3)) - ((y1-y2)*(x1-x3)));
	float u_val_denom = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));

	//colinear -> overlapping
	if (t_val_denom == 0 && u_val_denom == 0 && t_val == 0 && u_val == 0)
		return true;
	
	//parallel
	if (t_val_denom == 0 && u_val_denom == 0)
		return false;

	float t = t_val/t_val_denom;
	float u = u_val/u_val_denom;


	if ( (t>=0.0) && (t<=1.0) && (u>=0.0) && (u<=1.0) ){
		return true;
	}

	else
		return false;
	
}

bool valid_lineseg(std::string name, std::map<string,vector<Point>> &street_db, Point p1, Point p2){
	
	bool is_length_zero = false; // check for zero length
	bool self_street_check = true; // check for current street
	bool other_street_check = true; // check for other street

	// check if length of line is 0
	if (p1.x == p2.x && p1.y == p2.y)
		return false;

	//check line segment intersects its own street
	std::vector<Point> curr_street = street_db[name];

	for (unsigned int i = 0; i < curr_street.size() - 1; i++){

		Point p3 = curr_street[i];
		Point p4 = curr_street[i+1];

		int x1 = p1.x;
		int y1 = p1.y;
		int x2 = p2.x;
		int y2 = p2.y;
		int x3 = p3.x;
		int y3 = p3.y;
		int x4 = p4.x;
		int y4 = p4.y;

		// If at last line seg of street, can have one point of ip (point at which adj segments meet)
		if ((i+1) == (curr_street.size()-1)){

			
			if (check_intersect_overlap(x1,y1,x2,y2,x3,y3,x4,y4))
			{
				//std::cerr << "Fails here 1\n";
				return false;
				//self_street_check = false;
				//break;
			}
			
			if (check_intersect(x1,y1,x2,y2,x3,y3,x4,y4)){

				self_street_check = true;
				break;
				//return true;
			}

		}

		// else check with other line segments
		else{

			// if there is a point of intersection, invalid line seg, return 0
			if (check_intersect(x1,y1,x2,y2,x3,y3,x4,y4)){
				return false;

			}

		}

	}

	// check if the line segment, overlaps + intersects with all other streets
	// go through map (dictionary) and print key(str_name) and val(points)

	for (auto const& x : street_db){
		
		std::string curr_name = x.first;

		// check for every other street 
		if (curr_name != name){

			// get points for current street
			std::vector<Point> curr_points = x.second;
		
			for (unsigned int i = 0; i < curr_points.size() - 1; i++){
				
				Point p3 = curr_points[i];
				Point p4 = curr_points[i+1];

				int x1 = p1.x;
				int y1 = p1.y;
				int x2 = p2.x;
				int y2 = p2.y;
				int x3 = p3.x;
				int y3 = p3.y;
				int x4 = p4.x;
				int y4 = p4.y;
                    
				//check for overlap - if overlap, return false ( line seg not valid )
				if (check_intersect_overlap(x1,y1,x2,y2,x3,y3,x4,y4)){

					other_street_check = false;
					return false;
				}

				// if point of intersection present, increment global num_ip counter
				if (check_intersect(x1,y1,x2,y2,x3,y3,x4,y4)){
					num_ip = num_ip + 1;
				}

				other_street_check = true;

			}
		}
	}


	if(is_length_zero==false && self_street_check==true && other_street_check==true)
		return true;

	return false;

}


int main(int argc, char* argv[]) {

   
	int opt;
	unsigned int s_val = 10;
	unsigned int n_val = 5;
	unsigned int l_val = 5;
	int c_val = 20;

	unsigned int lineseg_num, wait_num, coord_bound;

	// map(dictionary) to store street info
	std::map<string,vector<Point>> street_db;

	opterr = 0;
	
	// parse command line arguments 
	while((opt = getopt(argc,argv,"s:n:l:c:")) != -1){
		
		switch(opt){
			
			
			// parse a option
			case 's':
				
				s_val = std::atoi(optarg);

				if (s_val == 0){

					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;;
					exit(0);

				}

				if (s_val < 2){

					std::cerr << "Error: Number of streets cannot be less that 2." << std::endl;;
					exit(0);
				}
				break;
			
			// parse n option
			case 'n':

				n_val = std::atoi(optarg);

				if (n_val == 0){

					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;;
					exit(0);

				}

				if (n_val < 1){

					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;
					exit(0);
				}

				break;

			
			// parse l option
			case 'l':

				l_val = std::atoi(optarg);
				
				if (l_val == 0){

					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;;
					exit(0);

				}


				if (l_val < 5){
					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;
					exit(0);

				}
				break;

			// parse c option
			case 'c':

				c_val = std::atoi(optarg);

				if (c_val == 0){

					std::cerr << "Error: Invalid argument, argument must be a postive integer." << std::endl;;
					exit(0);

				}


				if (c_val < 1){
					std::cerr << "Error: Coordinate bounds are [-k,k], where k >= 1." << std::endl;
					exit(0);
				}
				break;

			case '?':
				std::cerr << "Error: Invalid argument format given." << std::endl;
				exit(0);

			default:
				std::cerr << "Error: You have entered an incorrect option." << std::endl;
				exit(0);
				break;
			
		}
	}

	
	// keep rgenerating street specification
	while(true){

		//std::cerr << "Creating streets" << std::endl;

		unsigned int street_num = num_street(s_val);

		//std::cerr << "Number of streets - " << street_num << std::endl;

		// if streets are present in the map, remove streets from A1 street db and from rgen street map
		if (street_db.size() != 0){

			for (auto const& x : street_db){

				string name = x.first;
				std::cout << "r " << "\"" << name << "\"" << std::endl; 
			}

			// clear rgen map
			street_db.clear();
		}

		std::string street_name = "S";

		unsigned int tries_lineseg = 0;

		unsigned int i,j;

		//generating each street 
		for (i = 0; i < street_num; i++){

			// calculating number of linesegments and wait time for each street
			lineseg_num = num_lineseg(n_val);
			coord_bound = c_val;
		
			int* point_1 = rand_coord(coord_bound);
			Point p1(point_1[0], point_1[1]);

			street_db[street_name].push_back(p1);

			// create the line segments for the current street
			for (j = 0; j < lineseg_num; j++){

				int* point_2 = rand_coord(coord_bound);
				Point p2(point_2[0], point_2[1]);


				// while line segment is not valid keep regenerating point
				while ((valid_lineseg(street_name, street_db, p1, p2)==false) && tries_lineseg < 25){
					
					point_2 = rand_coord(coord_bound);

					p2.x = point_2[0];
					p2.y = point_2[1];

					tries_lineseg = tries_lineseg + 1;

				}

				// if tried 25 times to regenerate line segment, exit program
				if ((tries_lineseg) == 25){
					std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts.\n";
					//return 0;
					exit(0);
				}

				// if line segment is valid, add it to vector of points for current streets
				else{

					tries_lineseg = 0;
					street_db[street_name].push_back(p2);

					// make last point, the src for the next line segments
					p1 = p2;

				}

			}

			street_name = street_name + "S";

		}

		// No points of intersection between all streets, regenerate last point
		if (num_ip == 0){

			
			// create a iterator to point to last element of vector
			std::map<std::string,std::vector<Point>>::reverse_iterator rit;

			rit = street_db.rbegin();
			std::string last_name = rit->first;

			// remove last point from street
			street_db[last_name].pop_back();
			// get the last point from current street
			Point last = street_db[last_name].back();

			int* temp;
			Point temp_p;

			int tries_null = 0;
			
			//Regenerate last point in order to create a graph with atleast one point
			while(num_ip == 0 && tries_null < 25){

				temp = rand_coord(coord_bound);
				temp_p.x = temp[0];
				temp_p.y = temp[1];

				// while line segment is not valid, keep regenerating
				while (valid_lineseg(last_name, street_db, last, temp_p)==false && tries_null < 25){

					temp = rand_coord(coord_bound);

					//p1.x = point_1[0];
					//p1.y = point_1[1];

					temp_p.x = temp[0];
					temp_p.y = temp[1];

					tries_null = tries_null + 1;

				}

				tries_null = tries_null + 1;

			}


			if (tries_null >= 25){
				std::cerr << "Error: Failed to generate valid input for 25 simultaneous attempts.\n";
					//return 0;
					exit(0);
			}

			street_db[last_name].push_back(temp_p);

			//std::cerr << "CHANGED STREET and num_ip - " << num_ip << std::endl;

			//print_streetdb(street_db);


		}

		tries_lineseg = 0;
		num_ip = 0;
		
		// Send streets to A1 street database
		for (auto const& x : street_db){

				string name = x.first;
				
				std::vector<Point> street_points = x.second;

				std::cout << "a " << "\"" << name << "\"" << " ";

				unsigned int i;

				for(i = 0; i < street_points.size()-1; i++){

					Point p1 = street_points[i];
					std::cout << "(" << p1.x << "," << p1.y << ")" << " ";

				}
				Point p1 = street_points[i];
				std::cout << "(" << p1.x << "," << p1.y << ")" << std::endl;
		}

	

		// send g command to A1
		std::cout << "g" << std::endl;

		wait_num = num_wait(l_val);

		//sleep for given wait_num
		sleep(wait_num);
		
	
	}

    return 0;
}



