// AC - Tiempo 0.13 s

#include <iostream>
#include <vector>

#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using namespace std;
using tint = long long;

struct SegmentTree {
  tint segN;
  tint segTree[1000000]; // Hay que hacerlo de esta forma ya que sino con Vector crashea

  SegmentTree (tint n) {
    segN = 1;
    while (segN < n) segN *= 2;
  }

  tint retrieve(tint a, tint b) {
    a += segN; b += segN;
    tint s = 0;
    while (a <= b) {
      if (a%2 == 1) s += segTree[a++];
      if (b%2 == 0) s += segTree[b--];
      a /= 2; b /= 2;
    }
    return s;
  }

  void update(tint k, tint x) {
    k += segN, segTree[k] = x;
    for (k /= 2; k >= 1; k /= 2) {
        segTree[k] = segTree[2*k]+segTree[2*k+1];
    }
  }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tint n, q;
	cin >> n >> q;

  SegmentTree segTree (n);
	
  forn (i, n) {
    tint temp; cin >> temp;
    segTree.update(i, temp);
  }
	
  forn (i, q) {
    tint func, a, b;
    cin >> func >> a >> b;
        
    if (func == 1) segTree.update(a-1, b);
    else cout << segTree.retrieve(a-1, b-1) << "\n";
  }
}