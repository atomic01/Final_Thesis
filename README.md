# Final_Thesis
Solving The Maze Problems using A * algorithm

The program is not optimized. For labyrinths larger than 1000px x 1000px you need over 8GB RAM. The biggest ones I handled were 2000px x 2000px and it took about 13GB of RAM. It is also necessary to compile the program as a 64-bit application not a 32-bit one because it runs out of addresses in memory. If they are smaller mazes then this is not even necessary.

The code folder contains the entire code ...
main.c contains the main program
Declarations.h contains function declarations
StackFunctions.h contains list related functions (ie priority queue)
GraphFunctions.h contains graph related functions

The BMP_folder contains all the BMP files, mazes. When the program is executed the solution is saved in the BMP file result.bmp.
When running the program it is important that all the images are in the same file as the main.c.
Braid and combo bitmaps are imperfect multiple solution labyrinths, and all others are perfect with 1 solution.

