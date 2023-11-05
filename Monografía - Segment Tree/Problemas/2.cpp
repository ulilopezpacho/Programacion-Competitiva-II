// AC - Tiempo 0.15 s

#include <iostream>
#include <vector>
#include <algorithm>

#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using namespace std;
using tint = long long;

template<typename T>
struct SegmentTree {
 private:
  static tint nextPow2(tint x) {
    tint ans = 1;
    while (ans < x) ans *= 2;
    return ans;
  }

  static constexpr tint parent(tint x) { return x / 2; }
  static constexpr tint leftChild(tint x) { return 2 * x; }
  static constexpr tint rightChild(tint x) { return 2 * x + 1; }

 public:
  vector<T> st;

  SegmentTree(tint n) {
    n = nextPow2(n);
    st.resize(2 * n, T::identity());
  }

  tint size() const { return st.size() / 2; }

  void update(tint idx, T val) {
    idx += size();
    st[idx] = val;
    for (tint i = parent(idx); i > 0; i = parent(i)) {
      st[i] = st[leftChild(i)] >> st[rightChild(i)];
    }
  }

  T query(tint start, tint end, tint idx = 1, tint left = -1,
          tint right = -1) const {
    if (idx == 1) left = 0, right = size();

    if (start <= left and right <= end) return st[idx];
    if (end <= left or right <= start) return T::identity();

    tint mid = (left + right) / 2;
    return query(start, end, leftChild(idx), left, mid) >>
           query(start, end, rightChild(idx), mid, right);
  }
};

struct Node {
  tint val;
  Node(tint x): val{x} {}
  static Node identity() {return Node(2e15); }
  Node operator>> (const Node &other) const { return Node(min(val, other.val)); }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tint n, q;
  cin >> n >> q;

  SegmentTree<Node> segTree (n);

  forn(i,n) {
    tint temp; cin >> temp;
    segTree.update(i, Node(temp));
  }

  vector<tint> results;

  for (int i = 0; i < q; i++) {
    tint a, b, func;
    cin >> func >> a >> b;

    if (func == 1) segTree.update(a-1, Node(b));
    else results.push_back(segTree.query(a-1, b).val);
  }

  for (auto g: results) cout << g << "\n";
}