#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<vector<int> > edges;
    vector<string> result;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(n+1) // Starting from 1 not 0
    {  }
    // To get vertex index given the color
    int index (int vertex, int j){
      return (vertex - 1) * 3 + j;
    }

    void printEquisatisfiableSatFormula() {
      for(int i = 1; i < numVertices+1; i++){
        string s;
        // Add clauses to check if each vertex is possible to be assigned to at least to one color
        for(int j = 1 ; j < 4; j++){
          s += to_string(index(i,j)) + " ";
        }
        s += "0";
        result.push_back(s);
        // Add clauses to check there are no adjacent vertices have the same color
        for(int x = 0 ; x < edges[i].size(); x++){
          for(int j = 1; j < 4; j++){
            s = to_string(-index(i,j)) + " " + to_string(-index(edges[i][x],j)) + " 0";
            result.push_back(s);
          }
        }
      }
      cout<< result.size() << " " << numVertices * 3 <<endl;
      for(int i = 0; i < result.size(); i++){
        cout << result[i] << endl;
      }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        converter.edges[from].push_back(to);
    }
    converter.printEquisatisfiableSatFormula();

    return 0;
}
