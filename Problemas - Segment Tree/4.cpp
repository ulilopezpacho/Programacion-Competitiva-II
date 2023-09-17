// AC - Tiempo 0.11 s

#include <iostream>
#include <vector>

#define forn(i, n) for(tint i = 0; i < tint(n); i++)

using tint = long long;
using namespace std;
 
tint n, m, s = 1;
vector<tint> t;
 
void update (int a, int val) {
	a += s;
	t[a] = val; a /= 2;
	while (a >= 1) {
		t[a] = max(t[a*2], t[a*2+1]);
		a /= 2;
	}
}
 
tint occupy (int amount) {
	if (t[1] < amount) return 0;
	tint i = 1;
	while (i < s) {
		if (t[i*2] >= amount) i*= 2;
		else i = i * 2 + 1;
	}
	i -= s;
	update (i, t[i + s] - amount);
	return i+1;
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

	cin >> n >> m;
	while (s <= n) s*=2;
	
	t = vector<tint> (2*s, -1);
	vector<tint> answers(m);
	
	forn (i, n) {
		tint val; cin >> val;
		update(i, val);
	}
	
	forn (i, m) {
		tint temp; cin >> temp;
		answers[i] = occupy(temp);
	}
	
	for (auto x: answers) cout << x << " ";
}