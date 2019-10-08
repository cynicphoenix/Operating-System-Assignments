Ques : Do the programming project number 1 of chapter 4 of the textbook 
“Operating System Concepts by Silberschatz, Gagne, and Galvin, Ninth Edition”.
This project is called “Sudoku Solution Validator”.

To run the program :

gcc sudoku_validator.cpp -lpthread
./a.out


Input sudoku matrix row-wise i.e. row by row :
(or copy paste the given sudoku matrix)
e.g.
Correct :
6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 9 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 6

Incorrect :
6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 9 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 3

Correct :
4 3 5 2 6 9 7 8 1
6 8 2 5 7 1 4 9 3
1 9 7 8 3 4 5 6 2
8 2 6 1 9 5 3 4 7
3 7 4 6 8 2 9 1 5
9 5 1 7 4 3 6 2 8
5 1 9 3 2 6 8 7 4
2 4 8 9 5 7 1 3 6
7 6 3 4 1 8 2 5 9

Correct :
1 2 8 5 4 7 6 9 3
6 3 7 9 8 1 5 2 4
4 9 5 6 3 2 7 1 8
2 1 3 7 9 4 8 5 6
5 7 4 1 6 8 9 3 2
9 8 6 3 2 5 4 7 1
3 5 1 4 7 6 2 8 9
7 4 2 8 1 9 3 6 5
8 6 9 2 5 3 1 4 7

Incorrect :
1 2 8 5 4 7 6 9 3
6 3 7 9 8 1 5 2 4
4 9 5 6 3 2 7 1 8
2 1 3 7 9 4 8 5 6
5 7 4 1 6 8 9 3 2
9 8 6 3 2 5 4 7 1
3 5 1 4 7 6 2 8 9
7 4 2 8 1 9 3 6 5
8 6 9 2 5 3 1 4 9

Incorrect :
1 2 3 4 5 6 7 8 9
2 1 3 4 5 6 7 8 9
3 2 1 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
