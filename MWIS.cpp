/* Filename: MWIS.cpp
 * Description: The command line program, MWIS.cpp, takes in one parameter, 
 *              an input file name. The input file specified by the input
 *              file name should describe the weights of the vertices in a
 *              path graph using the format
 *
 *              [number of vertices]
 *              [weight of vertex 1]
 *              [weight of vertex 2]
 *              ...
 *
 *              The program will use dynamic programming to efficiently
 *              compute in linear time the maximum weight independent set
 *              of a graph. The program will return a one-hot vector
 *              indicating if the vertices 1, 2, 3, 4, 17, 117, 517, and 997
 *              are in the max weight independent set.
 */

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

#define IN_IDX 1
#define EXPECTED_ARGS 2
#define V1 1
#define V2 2
#define V3 3
#define V4 4
#define V5 17
#define V6 117
#define V7 517
#define V8 997

using namespace std;

// reads the input file, stores the weights, caches intermediate solutions 
// to MWIS
void buildArray(const char* filename, vector<int>& weights, 
		vector<int>& solutions) {

	// input file stream
	ifstream * in = new ifstream(filename);

	// used for parsing input file
	string line;

	// Raise an error if file can't be read and exit
	if( in->eof() ){
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		exit(-1);
	}

	// store number of vertices
	getline(*in, line);
	int numVertices = stoi(line);

	// initialize weights and solutions
	// we want weights and solutions to have the same length
	// we want weights[1] to be the weight of the first vertex
	solutions.push_back(0);
	weights.push_back(0);
	getline(*in, line);
	solutions.push_back(stoi(line));
	weights.push_back(stoi(line));

	// store weights and cache intermediate solutions to MWIS
	for(int i = 2; i <= numVertices; ++i) {
		getline(*in, line);
		weights.push_back(stoi(line));
		solutions.push_back(max(solutions[i-1], 
					solutions[i-2] + stoi(line)));
	}	

	// no memory leaks here
	delete in;

}

// reconstructs the max weight independent set from the
// cached intermediate solutions to MWIS
string reconstruct(vector<int>& weights, vector<int>& sols) {

	// for quick insert and lookup
	unordered_set<int> indSet;
        
	// scan through sols from right to left
	unsigned int i = sols.size() - 1;

	while( i > 1 ) {

                // Case 1: vertex i not in max weight ind set
		if( sols[i-1] >= sols[i-2] + weights[i] ) {
			--i;
		}

		// Case 2: vertex i is in max weight ind set
		else {
			indSet.insert(i);
			i = i - 2;
		}
	}	

	// vertex 1 is in the max weight ind. set iff vertex 3 is
	if( indSet.count(3) > 0 ){
		indSet.insert(1);
	}

	// the one-hot vector indicating if the vertices
	// 1, 2, 3, 4, 17, 117, 517, and 997 are in the MWIS
	string oneHot;

	// check if the vertices 1, 2, 3, 4, 17, 117, 517, and 997
	// belong to the max weight independent set and update the
	// one hot vector accordingly
	vector<int> vect{ V1, V2, V3, V4, V5, V6, V7, V8 };
        vector<int>::iterator it;
	for( it = vect.begin(); it != vect.end(); ++it ) {
		if(indSet.count(*it) > 0) {
			oneHot = oneHot + '1';
		}
		else {
			oneHot = oneHot + '0';
		}
	}

	return oneHot;
}	
		
int main(int argc, char** argv) {

	// check for arguments
	if( argc != EXPECTED_ARGS ) {
		cout << "This program expects 2 arguments!" << endl;
		return -1;
	}

	// vector storing all weights of vertices
	vector<int> weights;

	// vector storing all solutions of MWIS
	vector<int> MWISSol;
       
	// store all weights and cache all intermediate solutions to MWIS
	buildArray(argv[IN_IDX], weights, MWISSol);

	// reconstruct the max weight independent set
	// from the cached intermediate solutions to MWIS
	string MWISOneHot = reconstruct(weights, MWISSol);

	// output the one-hot vector indicating if the vertices
	// 1, 2, 3, 4, 17, 117, 517, and 997 are in the MWIS.
	cout << MWISOneHot << endl;
}

