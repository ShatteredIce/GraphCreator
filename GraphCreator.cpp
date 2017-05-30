//C++ Project 13 - GraphCreator - 5/23/17
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
  int dist;
  int previousId;
};

//prototypes
void getInput(char* input);
void trimWhitespace(char* text);
int getInt(char* message);
void setLowercase(char* text);

int getValidVertex(char* label, vector<Vertex> graph);
void findPath(int startId, int endId, vector<Vertex> graph, int adjacencyMatrix[20][20]);
bool targetUnvisited(int targetId, vector<Vertex> unvisited);
int getLeastDistanceId(vector<Vertex> unvisited);
int getEmptyIndex(vector<Vertex> graph);

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
  int edgeLength;
  char edgeStart[81];
  char edgeEnd[81];
  int firstVertexId;
  int secondVertexId;

  cout << "\n-----MLG Graph Creator v1.0-----\n";
  cout << "Creates a graph in the console\n";
  cout << "Availible commands are: 'vertex', 'edge', 'list', 'table', 'search', 'help', or 'quit'.\n";
  cout << "C++ Project 13 - Nathan Purwosumarto\n\n";

  while(true){
    cout << "Awaiting input: ";
    getInput(input);
    //if input = quit, then end the program
    if(strcmp(input, "quit") == 0){
      cout << "Program Terminated." << endl;
      break;
    }
    //if input = help, displays project information
    if(strcmp(input, "help") == 0){
      cout << "\n-----MLG Graph Creator v1.0-----\n";
      cout << "Creates a graph in the console\n";
      cout << "Availible commands are: 'vertex', 'edge', 'list', 'table', 'search', 'help', or 'quit'.\n";
      cout << "C++ Project 13 - Nathan Purwosumarto\n\n";
    }
    //if input = vertex, allow user to add or remove vertex
    else if(strcmp(input, "vertex") == 0){
      char vLabel[INPUT_SIZE];
      cout << endl << "Do you wish to 'add' or 'remove' vertices? ('back' to exit): ";
      getInput(input);
      //add vertices
      if(strcmp(input, "add") == 0){
        do{
          cout << endl << "-----ADDING VERTEX-----" << endl;
          do{
            cout << "Enter unique label: ";
            getInput(vLabel);
            firstVertexId = getValidVertex(vLabel, graph);
          } while(firstVertexId != -1 && strcmp(vLabel, "back") != 0);
          if(strcmp(vLabel, "back") != 0){
            strcpy(v.label, vLabel);
            v.id = getEmptyIndex(graph);
            v.dist = -1;
            graph.insert(graph.begin()+v.id, v);
            cout << "<vertex successfully added>" << endl;
          }
        } while(strcmp(vLabel, "back") != 0);
      }
      //remove vertices
      else if(strcmp(input, "remove") == 0){
        do{
          cout << endl << "-----REMOVING VERTEX-----" << endl;
          do{
            cout << "Enter existing label: ";
            getInput(vLabel);
            firstVertexId = getValidVertex(vLabel, graph);
          } while(firstVertexId == -1 && strcmp(vLabel, "back") != 0);
          if(strcmp(vLabel, "back") != 0){
            for(int a = 0; a < graph.size(); a++){
              //remove adjacency matrix connections for the deleted vertex
            	if(strcmp(vLabel,graph[a].label) == 0){
                for(int b = 0; b < 20; b++){
                  adjacencyMatrix[b][a] = -1;
                  adjacencyMatrix[a][b] = -1;
                }
            	  graph.erase(graph.begin()+a);
                cout << "<vertex successfully removed>" << endl;
            	}
            }
          }
        } while(strcmp(vLabel, "back") != 0);
      }
      cout << endl;
    }
    //debug method to see all vertices
    else if(strcmp(input, "list") == 0){
       cout << endl << "-----ALL VERTICES-----" << endl;
       for(int a = 0; a < graph.size(); a++){
         cout << "Label: " << graph[a].label << " Id: " << graph[a].id << endl;
       }
       cout << endl;
    }
    //if input = edge, let user add or remove an edge
    else if(strcmp(input, "edge") == 0){
      cout << endl << "Do you wish to 'add' or 'remove' edges? ('back' to exit): ";
      getInput(input);
      //add an edge
      if(strcmp(input, "add") == 0){
        cout << endl << "-----ADDING EDGE-----" << endl;
        //prompt user for first vertex
        do{
          cout << "Enter starting vertex: ";
          getInput(edgeStart);
          firstVertexId = getValidVertex(edgeStart, graph);
        } while(firstVertexId == -1 && strcmp(edgeStart, "back") != 0);
        if(strcmp(edgeStart, "back") == 0){
          cout << endl;
          continue;
        }
        //prompt user for second vertex
        do{
          cout << "Enter ending vertex: ";
          getInput(edgeEnd);
          secondVertexId = getValidVertex(edgeEnd, graph);
        } while(secondVertexId == -1 && strcmp(edgeEnd, "back") != 0);
        if(strcmp(edgeEnd, "back") == 0){
          cout << endl;
          continue;
        }
        //prompt user for edge length
        edgeLength = getInt("Enter edge length: ");
        cin.ignore(81, '\n');
        //update adjacency matrix
        adjacencyMatrix[firstVertexId][secondVertexId] = edgeLength;
        cout << "<edge successfully added>" << endl;
      }
      //remove an edge
      else if(strcmp(input, "remove") == 0){
        cout << endl << "-----REMOVING EDGE-----" << endl;
        //prompt user for first vertex
        do{
          cout << "Enter starting vertex: ";
          getInput(edgeStart);
          firstVertexId = getValidVertex(edgeStart, graph);
        } while(firstVertexId == -1 && strcmp(edgeStart, "back") != 0);
        if(strcmp(edgeStart, "back") == 0){
          cout << endl;
          continue;
        }
        //prompt user for second vertex
        do{
          cout << "Enter ending vertex: ";
          getInput(edgeEnd);
          secondVertexId = getValidVertex(edgeEnd, graph);
        } while(secondVertexId == -1 && strcmp(edgeEnd, "back") != 0);
        if(strcmp(edgeEnd, "back") == 0){
          cout << endl;
          continue;
        }
        //remove an edge if it exists
        if(adjacencyMatrix[firstVertexId][secondVertexId] != -1){
          adjacencyMatrix[firstVertexId][secondVertexId] = -1;
          cout << "<edge successfully removed>" << endl;
        }
        //inform user if the edge does not exist
        else{
          cout << "<no edge found>" << endl;
        }
      }
      cout << endl;
    }
    //prints the adjacency matrix to the console
    else if(strcmp(input, "table") == 0){
      cout << "Adjacency Matrix: " << endl;
      for(int m = 0; m < 20; m++){
        for(int n = 0; n < 20; n++){
          cout << adjacencyMatrix[m][n] << " ";
        }
        cout << endl;
      }
    }
    //searchs for a path using Dijkstra's algorithm
    else if(strcmp(input, "search") == 0){
      cout << endl << "-----SEARCH PATH-----" << endl;
      cout << "(input 'back' to cancel)\n" << endl;
      //prompt for first vertex
      do{
        cout << "Enter starting vertex: ";
        getInput(edgeStart);
        firstVertexId = getValidVertex(edgeStart, graph);
      } while(firstVertexId == -1 && strcmp(edgeStart, "back") != 0);
      if(strcmp(edgeStart, "back") == 0){
        cout << endl;
        continue;
      }
      //prompt for second vertex
      do{
        cout << "Enter ending vertex: ";
        getInput(edgeEnd);
        secondVertexId = getValidVertex(edgeEnd, graph);
      } while(secondVertexId == -1 && strcmp(edgeEnd, "back") != 0);
      if(strcmp(edgeEnd, "back") == 0){
        cout << endl;
        continue;
      }
      findPath(firstVertexId, secondVertexId, graph, adjacencyMatrix);
      cout << endl;
    }
  }

  return 0;
}

//attempts to find a path between two vertices using djikstra's algorithm
void findPath(int startId, int endId, vector<Vertex> graph, int adjacencyMatrix[20][20]){
  int leastDistanceId = -1;
  int currentDistance;

  vector<Vertex> unvisited;
  //push all vertices in the graph into the unvisited list
  for(int a = 0; a < graph.size(); a++){
    unvisited.push_back(graph[a]);
  }
  //set distance of starting vertex to 0
  for(int b = 0; b < unvisited.size(); b++){
    if(unvisited[b].id == startId){
      unvisited[b].dist = 0;
      graph[startId].previousId = -1;
    }
  }
  //loop until target is not in the unvisited list
  while(targetUnvisited(endId, unvisited)){
    //debug code to print out all vertices in the unvisited list
    // for(int test = 0; test < unvisited.size(); test++){
    //   cout << unvisited[test].label << " " << unvisited[test].id << " " << unvisited[test].dist << endl;
    // }
    leastDistanceId = getLeastDistanceId(unvisited);
    //cout << "least distance ID: " << leastDistanceId << endl;
    //exit if there is no vertex with a distance value other than -1
    if(leastDistanceId == -1){
      break;
    }
    //remove least distance node from the unvisited list
    for(int c = 0; c < unvisited.size(); c++){
    	if(leastDistanceId == unvisited[c].id){
        //cout << "erase :" << leastDistanceId << endl;
        currentDistance = unvisited[c].dist;
    	  unvisited.erase(unvisited.begin()+c);
    	}
    }

    //for each of the neighbors
    for(int d = 0; d < 20; d++){
      //if there is a path to the neighbor
      if(adjacencyMatrix[leastDistanceId][d] != -1){
        //if neighbor is in unvisited set
        if(targetUnvisited(d, unvisited)){
          //update distance
          for(int e = 0; e < unvisited.size(); e++){
          	if(d == unvisited[e].id){
              if(unvisited[e].dist == -1 || unvisited[e].dist > currentDistance + adjacencyMatrix[leastDistanceId][d]){
                unvisited[e].dist = currentDistance + adjacencyMatrix[leastDistanceId][d];
                graph[d].previousId = leastDistanceId;
              }
            }
          }
        }
      }
    }
  }
  if(leastDistanceId != -1){
    cout << "\nLeast distance is: " << currentDistance << endl;
    cout << "Path: ";
    Vertex current = graph[endId];
    while(current.previousId != -1){
      cout << current.label << " <- ";
      current = graph[current.previousId];
    }
    cout << graph[startId].label << endl;
  }
  else{
    cout << "\nNo path found." << endl;
  }
}

//checks if the target is in the unvisited set
bool targetUnvisited(int targetId, vector<Vertex> unvisited){
  for(int i = 0; i < unvisited.size(); i++){
    if(unvisited[i].id == targetId){
      return true;
    }
  }
  return false;
}

//loops through the unvisited list and gets the id of the vertex with the least distance value
//returns -1 if no vertices have a distance value that is not -1
int getLeastDistanceId(vector<Vertex> unvisited){
  int leastDistance = -1;
  int leastDistanceId = -1;
  for(int i = 0; i < unvisited.size(); i++){
    //cout << "testing = " << "label: "  << unvisited[i].label << " distance: " << unvisited[i].dist << endl;
    if(unvisited[i].dist != -1 && (leastDistance == -1 || (leastDistance != -1 && unvisited[i].dist < leastDistance))){
      leastDistance = unvisited[i].dist;
      leastDistanceId = unvisited[i].id;
    }
  }
  //cout << "final = " << "id: " << leastDistanceId << "least distance: " << leastDistance << endl;
  return leastDistanceId;
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

//loops through the graph vector to return the smallest vertex id value that can be used
int getEmptyIndex(vector<Vertex> graph){
  int counter = 0;
  for(int i = 0; i < graph.size(); i++){
    if(counter != graph[i].id){
      return counter;
    }
    counter++;
  }
  return counter;
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
