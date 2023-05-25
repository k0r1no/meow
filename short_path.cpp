#include <iostream>
#include <queue>
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Graph {
 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  void BFS(int start) {
    std::queue<int> queue;
    queue.push(start);
    dist_[start] = 0;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      for (auto neighbour : vertexes_[curr]) {
        if (dist_[neighbour] > dist_[curr] + 1) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          queue.push(neighbour);
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  void ShortestPath(int start, int end) {
    BFS(start);

    if (dist_[end] == std::numeric_limits<int>::max()) {
      std::cout << -1;
      return;
    }

    std::cout << dist_[end] << '\n';
    int x = end;
    std::vector<int> path;

    while (parents_[x] != -1) {
      path.push_back(x);
      x = parents_[x];
    }
    path.push_back(x);

    std::reverse(path.begin(), path.end());
    for (auto v : path) {
      std::cout << v + 1 << " ";
    }
  }

  void SetVertex(int begin, int end) {
    vertexes_[begin].insert(end);
    vertexes_[end].insert(begin);
  }

 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.SetVertex(begin, end);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  int begin, end;
  std::cin >> begin >> end;

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.ShortestPath(--begin, --end);
}
