#include <iostream>
#include <vector>

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