# DependencySolver
The dependency resolver is a program that takes in a text file with pairings of integers ("A B" where A allows B to be unlocked for processing). It will then print out all possible iterations of the dependency listing. Ultimately, this can be used to then grade each ordering to determine the best possible route. 

An example file is as follows:
1 2
1 3
2 3
2 6
2 7
3 4
3 5
3 7
4 5
7 8
9 4
10 9
