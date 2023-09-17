// AC - Tiempo 0.18 s

#include <iostream>
#include <vector>

#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using namespace std;
using tint = long long;

struct SegmentTree {
  tint n, segN;
  tint segTree[1000000];

  SegmentTree (tint _n) {
    n = _n; segN = 1;
    while (segN < n) segN *= 2;
  }

  tint retrieve(tint a, tint b, tint k, tint x, tint y) {
    if (b < x || a > y) return 0;
    if (a <= x && y <= b) return segTree[k];
    tint d = (x+y)/2;
    return retrieve(a,b,2*k,x,d) + retrieve(a,b,2*k+1,d+1,y);
  }

  tint retrieve(tint a, tint b) {
    return retrieve(a, b, 1, 0, n-1);
  }

  void update(tint pos, tint k, tint x, tint y, tint val) {
    if (x == y) { segTree[k] = val; return; }
    tint d = (x + y) / 2;
    if (pos <= d) update(pos, k*2, x, d, val);
    else update(pos, k*2+1, d+1, y, val);
    segTree[k] = segTree[k*2] + segTree[k*2+1];
  }

  void update(tint pos, tint val) {
    update(pos, 1, 0, n-1, val);
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