// AC - Tiempo 0.18 s

#include <iostream>
#include <vector>

#define forn(i, n) for (tint i = 0; i < tint(n); i++)

using namespace std;
using tint = long long;

struct Node {
  tint value;
  tint x, y;
  Node *left, *right;
  Node(tint value, tint x, tint y) : value(value), x(x), y(y) {}
  Node() : value(0), x(0), y(0) {}
};

struct SegmentTree {
  tint n, segN;
  Node *root;

  SegmentTree(tint _n) {
    n = _n;
    segN = 1;
    while (segN < n) segN *= 2;
    root = new Node(0, 0, segN - 1);
  }

  tint retrieve(Node &curr, tint a, tint b, tint k, tint x, tint y) {
    if (b < x || a > y) return 0;
    if (a <= x && y <= b) return curr.value;
    tint d = (x + y) / 2;

    if (curr.left == nullptr) curr.left = new Node(0, x, d);
    if (curr.right == nullptr) curr.right = new Node(0, d + 1, y);

    return retrieve(*curr.left, a, b, 2 * k, x, d) +
           retrieve(*curr.right, a, b, 2 * k + 1, d + 1, y);
  }

  tint retrieve(tint a, tint b) { return retrieve(*root, a, b, 1, 0, n - 1); }

  void update(Node &curr, tint pos, tint k, tint x, tint y, tint val) {
    if (x == y) {
      curr.value = val;
      return;
    }
    tint d = (x + y) / 2;

    if (curr.left == nullptr) curr.left = new Node(0, x, d);
    if (curr.right == nullptr) curr.right = new Node(0, d + 1, y);

    if (pos <= d)
      update(*curr.left, pos, k * 2, x, d, val);
    else
      update(*curr.right, pos, k * 2 + 1, d + 1, y, val);
    curr.value = curr.left->value + curr.right->value;
  }

  void update(tint pos, tint val) { update(*root, pos, 1, 0, n - 1, val); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tint n, q;
  cin >> n >> q;

  SegmentTree segTree(n);

  forn(i, n) {
    tint temp;
    cin >> temp;
    segTree.update(i, temp);
  }

  forn(i, q) {
    tint func, a, b;
    cin >> func >> a >> b;

    if (func == 1)
      segTree.update(a - 1, b);
    else
      cout << segTree.retrieve(a - 1, b - 1) << "\n";
  }
}