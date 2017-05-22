//C++ Project 13 - GraphCreator - 4/12/17
//Creates an graph in the console

#include <iostream>
#include <string.h>
#include <limits>
#include <vector>

using namespace std;

//Vertex variables
struct Vertex {
  char label[81];
  int id;
};

//prototypes
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);
void setLowercase(char* text);

int getValidVertex(char* label, vector<Vertex> graph);

const int INPUT_SIZE = 201;

int main(){

  vector<Vertex> graph;
  Vertex v;
  int adjacencyMatrix[20][20];

  //fill adjacencyMatrix with starting values
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      adjacencyMatrix[i][j] = -1;
    }
  }

  char input[INPUT_SIZE];
  int numVertex = 0;
  int edgeLength;
  char edgeStart[81];
  char edgeEnd[81];

  cout << "\n-----Graph Creator v1.0-----\n";
  cout << "Creates a graph in the console\n";
  cout << "Availible commands are: 'vertex', 'edge', 'list', 'table', 'search', or 'quit'.\n";
  cout << "C++ Project 13 - Nathan Purwosumarto\n\n";

  while(true){
    cout << "Awaiting input: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "Program Terminated." << endl;
      break;
    }
    //add a vertex
    else if(strcmp(input, "vertex") == 0){
      cout << endl << "-----ADDING VERTEX-----" << endl;
      do{
        cout << "Enter unique label: ";
        getInput(v.label);
      } while(getValidVertex(v.label, graph) != -1 || strcmp(v.label, "back") == 0);
      v.id = numVertex;
      graph.push_back(v);
      numVertex++;
      cout << endl;
    }
    //debug method to see all vertices
    else if(strcmp(input, "list") == 0){
       cout << endl << "-----ALL VERTICES-----" << endl;
       for(int a = 0; a < graph.size(); a++){
         cout << graph[a].label << " " << graph[a].id << endl;
       }
       cout << endl;
    }
    //add an edge
    else if(strcmp(input, "edge") == 0){
      cout << endl << "-----ADDING EDGE-----" << endl;
      cout << "(input 'back' to cancel)\n" << endl;
      do{
        cout << "Enter starting vertex: ";
        getInput(edgeStart);
      } while(getValidVertex(edgeStart, graph) == -1 && strcmp(edgeStart, "back") != 0);
      if(strcmp(edgeStart, "back") == 0){
        cout << endl;
        continue;
      }
      do{
        cout << "Enter ending vertex: ";
        getInput(edgeEnd);
      } while(getValidVertex(edgeEnd, graph) == -1 && strcmp(edgeEnd, "back") != 0);
      if(strcmp(edgeEnd, "back") == 0){
        cout << endl;
        continue;
      }
      edgeLength = getInt("Enter edge length: ");
      cin.ignore(81, '\n');
      adjacencyMatrix[getValidVertex(edgeStart, graph)][getValidVertex(edgeEnd, graph)] = edgeLength;
      cout << endl;
    }
    else if(strcmp(input, "table") == 0){
      for(int m = 0; m < 20; m++){
        for(int n = 0; n < 20; n++){
          cout << adjacencyMatrix[m][n] << " ";
        }
        cout << endl;
      }
    }
  }

  return 0;
}

//checks if a vertex with specified label is in the graph
int getValidVertex(char* label, vector<Vertex> graph){
  for(int a = 0; a < graph.size(); a++){
    if(strcmp(graph[a].label, label) == 0){
      return graph[a].id;
    }
  }
  return -1;
}

//stores user input into a char*
void getInput(char* input){
  fill(input, input + sizeof(input), ' ');
  cin.getline(input, INPUT_SIZE);
  trimWhitespace(input);
  setLowercase(input);
}

//remove extra whitespaces to make sure input is compared as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}

//prompts the user for an integer
int getInt(char* message){
  int number;
  bool valid = false;
  while (!valid){
    cout << message;
    cin >> number;
    //delete excess whitespace
    while (cin.peek() == ' '){
      cin.ignore(1);
    }
    if(cin.peek() != '\n'){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else{
      valid = true;
    }
  }
  return number;
}

//sets all characters in a char* to lowercase
void setLowercase(char* text){
  for(int i = 0; i < strlen(text); i++){
    text[i] = tolower(text[i]);
  }
}
