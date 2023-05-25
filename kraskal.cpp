#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int first;
  int second;
  int weight;

  Edge(int begin, int end, int w) : first(begin), second(end), weight(w) {
  }
};

class DSU {
 public:
  explicit DSU(size_t n) {
    rank_ = std::vector<int>(n, 0);
    p_ = std::vector<int>(n);
    for (size_t i = 0; i < n; ++i) {
      p_[i] = i;
    }
  }

  int FindSet(int x) {
    if (x == p_[x]) {
      return x;
    }

    return (p_[x] = FindSet(p_[x]));
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      p_[x] = y;
    } else if (rank_[x] > rank_[y]) {
      p_[y] = x;
    } else {
      p_[x] = y;
      rank_[y] += 1;
    }
  }

  int Kraskal(std::vector<Edge> edges) {
    int mst_size = 0;

    for (auto edge : edges) {
      if (FindSet(edge.first) != FindSet(edge.second)) {
        Union(edge.first, edge.second);
        mst_size += edge.weight;
      }
      if (FindSet(edge.second) != FindSet(edge.first)) {
        Union(edge.second, edge.first);
        mst_size += edge.weight;
      }
    }
    return mst_size;
  }

 private:
  std::vector<int> p_;
  std::vector<int> rank_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  DSU dsu(n);
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int first, end, weight;
    std::cin >> first >> end >> weight;
    edges.emplace_back(Edge(--first, --end, weight));
  }
  std::cout << dsu.Kraskal(edges);
}
