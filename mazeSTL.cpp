// CpSc 2150 
// G. Monagan
#include <string>
#include <fstream>
#include <cstdlib>

// now debugging
#define NDEBUG


// from the STL
#include <stack>

#include <iostream>


using std::cout;
using std::endl;
using std::cin;
using namespace std;


// size of maze is NxN: global CONSTANT
const int N = 10;

// these are the values expected in the input file
// note that there is no error checking.
const char ENTRY = '*';     
const char GOAL = '%';
const char FREE = '.';
const char BLOCKED = 'X';

// Read into the maze data from a file name obtained from standard input
// there is no error checking for corrupt data
// precondition:
//    the data in the file consists exclusively of character values
//  ENTRY = '*';     
//  GOAL = '%';
//  FREE = '.';
// BLOCKED = 'X'  (upper case X)
//    there is only one ENTRY point  and one GOAL point
//    there is exactly NxN non-blank characters to be read in
//    the array maze has been declared to be at least NxN
//    the size of the maze N is a global constant
// postcondition:
//    the array maze has the characters read in
//    the values of the array were read row by row
void read_maze(char maze[][N]) {
   std::string file_name;
   cout << "The size of the maze is " << N << endl;
   cout << "File with the characters of the maze > ";
   cin >> file_name;
   std::ifstream fin;
   fin.open(file_name.c_str());
   // continue trying to open a file if the open failed
   while (!fin) {
      fin.clear();
      cout << "cout not open file \"" << file_name << "\"... try again: >";
      cin >> file_name;
      fin.open(file_name.c_str());
   } 
   for (int i=0; i<N; i++) 
      for (int j=0; j<N; j++) 
         fin >> maze[i][j];
   fin.close();
}

// convert maze[i][j] with BLOCKED to m[i][j] = false
// and maze[i][j] with ENTRY, EXIT, FREE convert to m[i][j] = true
// precond: maze is full of characters ENTRY, EXIT, FREE, BLOCKED
// postcond: m is a boolean array of what is free (true) and what is blocked (false)
// if there is more than one goal or more than one entry, or if there is no goal or no entry
// exit program abruptly
void convert(const char maze[][N], 
              bool m[][N], int N, Cell &entry, Cell &goal) {
   int num_goal = 0;
   int num_entry = 0;
   for (int i=0; i<N; i++)
      for (int j=0; j<N; j++) {
         if (maze[i][j] == BLOCKED)
            m[i][j] = false;
         else {
            m[i][j] = true;
            if (maze[i][j] == ENTRY) {
               entry.i = i;
               entry.j = j;
               num_entry++;
            }
            else if (maze[i][j] == GOAL) {
               goal.i = i;
               goal.j = j;
               num_goal++;
            }
         }
      } // for j
   if ((num_entry != 1) && (num_goal != 1)) {
      cout << "entry or goal is missing .... bye\n";
      exit(1);
   }
}

// output the NxN array as characters read from a file 
// expected are the symbols for ENTRY, GOAL, BLOCKED and FREE
// N is a global variable
void print_maze(const char maze[][N]) {
   cout << endl;
   for (int i=0; i<N; i++) {
      for (int j=0; j<N; j++) 
         cout << maze[i][j] << " ";
      cout << endl;
   }
   cout << endl;
}

// very primitive, quick-n-dirty way of printing out a solution
// note that I waste lots of memory allocating another array
// I am using a global N too
// precondition:
//   fancy is true means that we want a 2d array printed
//   fancy false means that we output the stack as coordinates
//   a stack (that is possibly empty) needs to be passed with the solution
void print_solution(std::stack<Cell>& st, bool fancy = true) {
   cout << endl;
   Cell x;
   // print the path 
   if (!fancy) {
      while (!st.empty()) {
         x = st.top();
         st.pop();
         cout << x;
      }
      cout << endl;
      return;
   }
   // initialize a board of characters to blanks
   char t[N][N];
   cout << endl;
    for (int i=0; i<N; i++) 
      for (int j=0; j<N; j++) 
         t[i][j] = ' ';
   
   // mark the output path
   while (!st.empty()) {
      Cell a = st.top();
      st.pop();
      t[a.i][a.j] = 'o';
   }

   // print a top line
   cout << "+";
   for (int i=0; i<N-1; i++) 
      cout << "- "; 
   cout << "+\n";

   // print out the array of characters
   for (int i=0; i<N; i++) {
      cout << "|";
      for (int j=0; j<N-1; j++) 
         cout << t[i][j] << ' ';
      cout << "|" << endl;
   }
   // print the bottom line
   cout << "+";
   for (int i=0; i<N-1; i++) 
      cout << "- "; 
   cout << "+\n";
}

   
// find a path from (start_i,start_j) to (goal_i,goal_j) and output the solution
void path(int start_i, int start_j, // coordinates of entry point
	int goal_i, int goal_j,   // coordinates of exit point
	bool maze[][N]) {         // maze with true and false values
	stack<Cell> st;
	Cell start;
		start->i = start_i;
		start->j = start_j;
		start->left = true;
		start->right = true;
		start->up = true;
		start->down = true;
	st.push(start);
	while(st.empty() == false) {
		Cell * current = &st.top();
		int ci;
		int cj;
		if(current->left == true) {
			ci = (current->i)-1;
			cj = (current->j);
			current->left = false;
			if(ci >= 0) {
				Cell * newCell  = new Cell;
				newCell->left = true;
				newCell->right = true;
				newCell->up = true;
				newCell->down = true;
				newCell->i = ci;
				newCell->j = cj;
				st.push(*newCell);
				if(ci == goal_i && cj == goal_j) {
					break;
				}
			}
		}
		else if(current->right == true) {
		
		}
		else if(current->up == true) {
		
		}
		else if(current->down == true) {
		
		}
		else {
			
		}
		
	}
	if (st.empty())
		cout << "SORRY: no answer\n";
	else 
	print_solution(st);

}

int main() {
   char maze[N][N];
   read_maze(maze);   // read from a file of characters the maze
   print_maze(maze);  // output what was read
      
   // convert the ENTRY point, EXIT point and FREE to true
   // and the BLOCKED to false in the array m which is boolean
   bool bool_maze[N][N];    // internal information  of free and blocked cells
   Cell entry, goal;
   convert(maze, bool_maze, N, entry, goal);
   
   // solve the maze and print out the maze
   cout << "One path to the goal ...\n";
   path(entry.i, entry.j, goal.i, goal.j, bool_maze);
   
   // system("PAUSE");
   return 0;
}

