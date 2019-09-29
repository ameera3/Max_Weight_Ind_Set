# Max_Weight_Ind_Set

## Usage
To compile, type "g++ -o MWIS MWIS.cpp". To run the program, type "./MWIS mwis.txt"

## Introduction
The command line program, MWIS.cpp, takes in one parameter, 
an input file name. The input file specified by the input
file name should describe the weights of the vertices in a
path graph using the format
 
[number of vertices]

[weight of vertex 1]

[weight of vertex 2]

...
 
The program uses dynamic programming to efficiently
compute in linear time the maximum weight independent set
of the specified path graph. The program returns a one-hot vector
indicating if the vertices 1, 2, 3, 4, 17, 117, 517, and 997
are in the maximum weight independent set.
