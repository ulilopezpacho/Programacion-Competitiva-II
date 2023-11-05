#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define DBG(x) cerr << #x << " = " << x << endl

using namespace std;

vector<int> salaryValues;
vector<int> possibleSalaryValues;
vector<tuple<bool, int, int>> queries;
map<int, int> valueCompression;

int compressionN;

struct SegmentTree {
  int segN;
  vector<int> segTree;

  SegmentTree(int n) {
    segN = 1;
    while (segN < n) segN *= 2;
    segTree.resize(segN * 2);
  }

  void update(int pos, int val) {
    pos = valueCompression[pos] + segN;
    segTree[pos] += val;
    for (pos /= 2; pos >= 1; pos /= 2) {
      segTree[pos] = segTree[pos * 2] + segTree[pos * 2 + 1];
    }
  }

  int getNoCompression(int a, int b) {
    a += segN;
    b += segN;
    int suma = 0;
    while (a <= b) {
      if (a % 2 == 1) suma += segTree[a++];
      if (b % 2 == 0) suma += segTree[b--];
      a /= 2;
      b /= 2;
    }
    return suma;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  salaryValues.resize(n);
  queries.resize(k);

  forn(i, n) {
    cin >> salaryValues[i];
    possibleSalaryValues.push_back(salaryValues[i]);
  }

  forn(i, k) {
    char type;
    int a, b;
    cin >> type >> a >> b;
    if (type == '!') {
      possibleSalaryValues.push_back(b);
      queries[i] = make_tuple(false, a, b);
    } else {
      queries[i] = make_tuple(true, a, b);
    }
  }

  sort(possibleSalaryValues.begin(), possibleSalaryValues.end());

  vector<int> aux;
  forn(i, possibleSalaryValues.size()) 
    if (aux.empty() || possibleSalaryValues[i] != aux.back())
      aux.push_back(possibleSalaryValues[i]);
  possibleSalaryValues = aux;

  compressionN = int(possibleSalaryValues.size());
  forn(i, compressionN) valueCompression[possibleSalaryValues[i]] = i;
  SegmentTree segTree(compressionN);

  for (auto &e : salaryValues) {
    segTree.update(e, 1);
  }
  for (auto &q : queries) {
    bool type;
    int a, b;
    tie(type, a, b) = q;

    if (type == false) {
      a--;
      segTree.update(salaryValues[a], -1);
      salaryValues[a] = b;
      segTree.update(salaryValues[a], 1);
    }

    if (type == true) {
      int la = int(lower_bound(possibleSalaryValues.begin(),
        possibleSalaryValues.end(), a) - possibleSalaryValues.begin());
      int lb = int(upper_bound(possibleSalaryValues.begin(),
        possibleSalaryValues.end(), b) - possibleSalaryValues.begin());
      if (lb > 0) lb--;
      cout << segTree.getNoCompression(la, lb) << "\n";
    }
  }
}