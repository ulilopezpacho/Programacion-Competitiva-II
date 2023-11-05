// AC - Tiempo 0.80s
#include <iostream>
#include <vector>

#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using namespace std;
using tint = int;

struct Node {
  tint value;
  Node *left, *right;
  Node(tint value): value(value) {}
  Node(): value(0) {}
};

struct SegmentTree {
  tint n, segN;
  Node* root;

  SegmentTree (tint _n) {
    n = _n; segN = 1;
    while (segN < n) segN *= 2;
    root = new Node(0);
  }

  tint query(Node &curr, tint a, tint b, tint k, tint x, tint y) {
    if (b < x || a > y) return 0;
    if (a <= x && y <= b) return curr.value;
    tint d = (x+y)/2;

    tint temp = 0;
    if (curr.left != nullptr) temp += query(*curr.left,a,b,2*k,x,d);
    if (curr.right != nullptr) temp += query(*curr.right,a,b,2*k+1,d+1,y);
    return temp;
  }

  tint query(tint a, tint b) {
    return query(*root, a, b, 1, 0, n-1);
  }

  void update(Node &curr, tint pos, tint k, tint x, tint y, tint val) {
    if (x == y) { curr.value += val; return; }
    tint d = (x + y) / 2;

    if (pos <= d) {
      if (curr.left == nullptr) curr.left = new Node(0);
      update(*curr.left, pos, k*2, x, d, val);
    }
    else {
      if (curr.right == nullptr) curr.right = new Node(0);
      update(*curr.right, pos, k*2+1, d+1, y, val);
    }

    curr.value = (curr.left != nullptr? curr.left->value: 0) +
        (curr.right != nullptr? curr.right->value: 0);
  }

  void update(tint pos, tint val) {
    update(*root, pos, 1, 0, n-1, val);
  }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tint n, q;
  cin >> n >> q;

  SegmentTree segTree (1e9+1);
  vector<tint> valores (n+1);
	
  forn (i, n) {
    cin >> valores[i+1];
    segTree.update(valores[i+1], 1);
  }
	
  forn (i, q) {
    char func;
	tint a, b;
	cin >> func >> a >> b;
		
	if (func == '?') {
    cout << segTree.query(a, b) << "\n";
    
  } else {
    segTree.update(valores[a], -1);
    valores[a] = b;
    segTree.update(valores[a], 1);
  }
}