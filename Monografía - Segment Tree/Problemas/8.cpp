// AC 0.58s

#include <iostream>
#include <vector>
#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using namespace std;
using tint = long long;

struct Node {
  tint val;
  Node *left, *right;

  // Instanciador sin hijos para valores base
  Node (tint _val): val(_val), left(nullptr), right(nullptr) {}

  // Instanciador que aplica operación sobre nodos hijos, en este caso la suma.
  Node (Node *_left, Node *_right) {
    left = _left; right = _right;
    val = 0;
    if (left) val += left->val;
    if (right) val += right->val;
  }
};

struct PSegmentTree {
  tint n;
  Node *root;

  PSegmentTree (tint _n): n(_n), root(new Node(tint(0))) {}
  PSegmentTree (PSegmentTree *copy): n(copy->n), root(copy->root) {}

  PSegmentTree *copy () {
    return new PSegmentTree(this);
  }

  Node *update(Node *node, tint val, tint pos, tint x, tint y) {
    if (x == y) { return new Node(val); }
    tint mid = (x + y) / 2;
    
    if (node == nullptr) {
      if (pos <= mid) return new Node(update(nullptr, val, pos, x, mid), nullptr);
      else return new Node(nullptr, update(nullptr, val, pos, mid+1, y));
    }

    if (pos <= mid) return new Node(update(node->left, val, pos, x, mid), node->right);
    else return new Node(node->left, update(node->right, val, pos, mid+1, y));
  }

  void update (tint pos, tint val) {
    root = update(root, val, pos, 0, n-1);
  }

  tint query (Node *node, tint a, tint b, tint x, tint y) {
    if (b < x || a > y) return 0;
    if (a <= x && y <= b) return node->val;

    tint mid = (x+y) / 2;
    tint tempAns = 0;

    if (node->left) tempAns += query(node->left, a, b, x, mid);
    if (node->right) tempAns += query(node->right, a, b, mid+1, y);
    return tempAns;
  }

  tint query (tint a, tint b) {
    return query(root, a, b, 0, n-1);
  }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tint n, q;
  cin >> n >> q;

  PSegmentTree segTreeInicial (n+1);

  forn (i, n) {
    tint val; cin >> val;
    segTreeInicial.update(i+1, val);
  }

  vector<PSegmentTree*> segTrees;
  segTrees.push_back(nullptr);
  segTrees.push_back(&segTreeInicial);

  forn (i, q) {
    tint type; cin >> type;
    if (type == 1) {
      tint k, a, x;
      cin >> k >> a >> x;
      segTrees[k]->update(a, x);
    } else if (type == 2) {
      tint k, a, b;
      cin >> k >> a >> b;
      cout << segTrees[k]->query(a, b) << "\n";
    } else {
      tint k; cin >> k;
      segTrees.push_back(segTrees[k]->copy());
    }
  }
}