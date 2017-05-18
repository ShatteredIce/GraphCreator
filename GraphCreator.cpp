//C++ Project 13 - GraphCreator - 4/12/17
//Creates an graph in the console

#include <iostream>
#include <vector>

using namespace std;

//Vertex variables
struct Vertex {
  char nameFirst[81];
  int id;
};

int main(){

  vector<Vertex*> graph;
  vector<Vertex*> * graphPointer = & graph;
  int adjacencyMatrix[20][20];

  for(int i = 0; i < 20; i++){
    for(int j =0; j < 20; j++){
      adjacencyMatrix[i][j] = -1;
    }
  }
  cout << "\n-----Graph Creator v1.0-----\n";
  cout << "Creates a graph in the console\n";
  cout << "Availible commands are: 'vertex', 'edge', 'table', 'search', or 'quit'.\n";
  cout << "C++ Project 13 - Nathan Purwosumarto\n\n" << endl;

  return 0;
}
