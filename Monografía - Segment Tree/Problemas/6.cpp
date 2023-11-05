// AC - Time 0.36s

#include <iostream>
#include <algorithm>
#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

typedef long long tint;

struct Node {
  tint suma = 0, sumaLazy = 0, setValueLazy = 0;

  void propagate(Node &o) {
    if (o.setValueLazy > 0) {
      sumaLazy = o.sumaLazy;
      setValueLazy = o.setValueLazy;
    } else {
      sumaLazy += o.sumaLazy;
    }
  }

  void updateSuma(Node &o1, Node &o2, int l, int r) {
    int m = (l + r) / 2;
    suma = o1.evaluate(l, m) + o2.evaluate(m + 1, r);
  }

  void setValue(int val, bool setValue) {
    if (setValue) {
      setValueLazy = val;
      sumaLazy = 0;
    } else {
      sumaLazy += val;
    }
  }

  tint evaluate(int l, int r) {
    const tint abarca = tint(r - l + 1);
    if (setValueLazy > 0)
      return abarca * setValueLazy + abarca * sumaLazy;
    else
      return abarca * sumaLazy + suma;
  }

  void clearLazy() {
    sumaLazy = 0;
    setValueLazy = 0;
  }
};

struct LazySegmentTree {
  int segN;
  vector<Node> segTree;

  LazySegmentTree(int n) {
    segN = 1;
    while (segN < n) segN *= 2;
    segTree.resize(segN * 2);
  }

  void update(int a, int b, int val, bool setValue) {
    update(a, b, val, setValue, 1, 0, segN - 1);
  }

  void update(int a, int b, int val, bool setValue, int k, int l, int r) {
    if (a > r || b < l) return;

    if (a <= l && r <= b) {
      segTree[k].setValue(val, setValue);
      return;
    }

    segTree[k * 2].propagate(segTree[k]);
    segTree[k * 2 + 1].propagate(segTree[k]);
    segTree[k].clearLazy();

    tint m = (l + r) / 2;
    update(a, b, val, setValue, k * 2, l, m);
    update(a, b, val, setValue, k * 2 + 1, m + 1, r);
    segTree[k].updateSuma(segTree[k * 2], segTree[k * 2 + 1], l, r);
  }

  tint query(int a, int b) { return query(a, b, 1, 0, segN - 1); }

  tint query(int a, int b, int k, int l, int r) {
    if (b < l || a > r) return 0;
    if (a <= l && r <= b) return segTree[k].evaluate(l, r);

    segTree[k * 2].propagate(segTree[k]);
    segTree[k * 2 + 1].propagate(segTree[k]);
    segTree[k].clearLazy();

    tint m = (l + r) / 2;
    tint q1 = query(a, b, k * 2, l, m);
    tint q2 = query(a, b, k * 2 + 1, m + 1, r);

    segTree[k].updateSuma(segTree[k * 2], segTree[k * 2 + 1], l, r);
    return q1 + q2;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  LazySegmentTree tree(n);

  forn(i, n) {
    int temp;
    cin >> temp;
    tree.update(i, i, temp, true);
  }

  forn(i, q) {
    int op;
    cin >> op;
    if (op == 1) {
      int a, b, x;
      cin >> a >> b >> x;
      a--; b--;
      tree.update(a, b, x, false);
    } else if (op == 2) {
      int a, b, x;
      cin >> a >> b >> x;
      a--; b--;
      tree.update(a, b, x, true);
    } else {
      int a, b;
      cin >> a >> b;
      a--; b--;
      cout << tree.query(a, b) << "\n";
    }
  }
}