#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
typedef vector<vector<double>> Graph;

double dot(const vector<double> &x, const vector<double> &y) {
  assert(x.size() == y.size());
  double r = 0.0;
  for (int i = 0; i < x.size(); i++) {
    r = r + x[i] * y[i];
  }
  return r;
}

Graph transpose(const Graph &g) {
  vector<vector<double>> t(g.size());
  for (int i = 0; i < g.size(); i++) {
    t[i] = vector<double>(g.size(), 0.0);
  }
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g.size(); j++) {
      t[i][j] = g[j][i];
    }
  }
  return t;
}

vector<double> multMatVect(const Graph &g, const vector<double> &v) {
  vector<double> r(g.size(), 0.0);
  for (int i = 0; i < g.size(); i++) {
    r[i] = dot(g[i], v);
  }
  return r;
}

vector<vector<double>> multMatMat(const vector<vector<double>> &A,
                                  const vector<vector<double>> &B) {
  int rowsA = A.size();
  int colsA = A[0].size();
  int rowsB = B.size();
  int colsB = B[0].size();

  assert(colsA == rowsB);

  vector<vector<double>> R(rowsA);
  for (int i = 0; i < rowsA; i++) {
    R[i] = vector<double>(colsB, 0.0);
  }

  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      double c = 0.0;
      for (int k = 0; k < colsA; k++) {
        c = c + A[i][k] * B[k][j];
      }
      R[i][j] = c;
    }
  }
  return R;
}

vector<vector<double>> matPow(const vector<vector<double>> &X, int k) {
  vector<vector<double>> B(X);
  for (int i = 0; i < k - 1; i++) {
    B = multMatMat(X, B);
  }
  return B;
}

vector<double> BFS(const Graph &g, int start) {
  int nodes = g.size();
  vector<double> v(nodes, 0.0);
  v[start] = 1.0;
  vector<vector<double>> gt = transpose(g);
  vector<vector<double>> pg = matPow(gt, 2);
  return multMatVect(pg, v);
}
int main() {
  double inf = numeric_limits<double>::max();
  Graph g{
      {0.0, 1.0, inf, 1.0, inf, inf, inf}, //
      {inf, 0.0, inf, inf, 1.0, inf, 1.0}, //
      {inf, inf, 0.0, inf, inf, 1.0, inf}, //
      {1.0, inf, 1.0, 0.0, inf, inf, inf}, //
      {inf, inf, inf, inf, 0.0, 1.0, inf}, //
      {inf, inf, 1.0, inf, inf, 0.0, inf}, //
      {inf, inf, 1.0, 1.0, 1.0, inf, 0.0}  //
  };

  Graph g2{
      {0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0}, // 0
      {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0}, // 1
      {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0}, // 2
      {1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0}, // 3
      {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0}, // 4
      {0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0}, // 5
      {0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0}  // 6
  };

  // auto s = multMatMat(g2, g2);
  // auto r = multMatMat(g2, s);

  auto r = matPow(transpose(g2), 2);
  for (int i = 0; i < r.size(); i++) {
    for (int j = 0; j < r[0].size(); j++) {
      cout << " " << r[i][j];
    }
    cout << endl;
  }

  /*
    vector<double> visited = BFS(g2, 3);
    for (double i : visited) {
      cout << " " << i;
    }
    cout << endl;
  */
  return 0;
}
