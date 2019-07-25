#include<bits/stdc++.h>

using namespace std;
typedef vector<vector<long long> > Matrix;

const long long INF = 10e9;


Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<long long>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

int ones_count(int n){ // Count the number of 1 bits in integer
  int res = 0;
  while(n){
    n &= n-1;
    res++;
  }
  return res;
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
    int n = pow(2, graph.size()) -1; // Integer to hold the sets, each number from 1 to n represent a set after converting it to binary, 3 in decimal equals 101 in binary means that node 1 and 3 are visited
    pair<long long, vector<int>> res = {INF, {}};
    vector<vector<int>> sets(graph.size()); // Hold the sets
    vector<vector<pair<long long, vector<int>>>> dp(n+1, vector<pair<long long, vector<int>>>(graph.size()+1,{INF,{}})); // DP array

    dp[1][1] = {0,{1}};
    for(int i = 3; i <= n; i++){ // Append sets having same number of nodes together
      if(i & 1)
        sets[ones_count(i)-1].push_back(i);
    }
    for(int one_bits = 1; one_bits < sets.size(); one_bits++){
      for(auto i : sets[one_bits]){
        dp[i][1].first = INF;
        for(int j = 1; j < graph.size(); j++){
          if( (1 << j) & i){
            for(int k = 0; k < graph.size(); k++){
              if( (k != j) && (1 << k & i)){
                if(dp[i ^ (1 << j)][k+1].first + graph[j][k] < dp[i][j+1].first ){
                  dp[i][j+1].first = dp[i ^ (1 << j)][k+1].first + graph[j][k];
                  dp[i][j+1].second = dp[i ^ (1 << j)][k+1].second;
                  dp[i][j+1].second.push_back(j+1);
                }
              }
            }
          }
        }
      }
    }
    for(int i = 2; i <= graph.size(); i++){
      if(dp[n][i].first + graph[0][i-1] < res.first){
      res.first = dp[n][i].first + graph[0][i-1];
      res.second = dp[n][i].second;
      }
    }
    if(res.first == INF) res.first = -1;
    return res;
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first<<"\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}

