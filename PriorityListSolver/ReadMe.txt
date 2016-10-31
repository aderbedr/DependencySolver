PriorityListSolver:

Command line: 
PriorityListSolver.exe <file of dependencies>

The file passed in by argument should be of the format of lines of numbers such as:
1 2
Where 1 depends on 2. For instance, if the text file were as follows:

1 4
1 2
3 4
2 5
3 5
6 5
3 7
7 0

It could be drawn as following:

1->4
|  ^
v  |
2  3->7->0
|  |
v  v
 5
 ^
 |
 6

1 depends on 4 and 2, 3 depends on 4, 2 depends on 5, etc. A possible solution then would be to first resolve 0, then 7, 5, 6, 4, 3, 2, and finally 1.