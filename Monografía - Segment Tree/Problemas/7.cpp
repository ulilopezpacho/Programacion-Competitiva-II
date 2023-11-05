#include <vector>
#include <iostream>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;
using tint = long long;

int largo = 1;
int segN = 1;

struct node {
  tint suma = 0, lazy = 0, cantidad = 0;
};

vector<node> segTree;

// Logica para evaluar un nodo
tint eval(tint pos, tint x, tint y) {
  tint cantHijos = y - x + 1;
  tint sumaPoli = (cantHijos * (cantHijos - 1)) / 2;
  tint parcial =
      (sumaPoli * segTree[pos].cantidad) + (segTree[pos].lazy * cantHijos);
  return segTree[pos].suma + parcial;
}

void update(int pos, int a, int b, tint value, int x = 0, int y = segN - 1) {
  // Si esta en el rango, sumar al lazy y retornar
  if (a <= x && b >= y) {
    segTree[pos].lazy += value;
    segTree[pos].cantidad++;
    return;
  }

  // Si esta por fuera, retornar
  if (a > y || b < x) return;

  tint med = (y - x + 1) / 2;
  // Propagación izquierda
  segTree[pos * 2].lazy += segTree[pos].lazy;
  segTree[pos * 2].cantidad += segTree[pos].cantidad;
  // Propagación derecha
  segTree[pos * 2 + 1].lazy +=
      (segTree[pos].lazy + segTree[pos].cantidad * med);
  segTree[pos * 2 + 1].cantidad += segTree[pos].cantidad;
  // Reseteo
  segTree[pos].lazy = 0;
  segTree[pos].cantidad = 0;

  // Recursión
  tint prom = (x + y) / 2;
  tint toLeft = max(0ll, prom + 1 - max(a, x));
  update(pos * 2, a, b, value, x, prom);
  update(pos * 2 + 1, a, b, value + toLeft, prom + 1, y);

  // Actualización del nodo actual
  segTree[pos].suma = eval(pos * 2, x, prom) + eval(pos * 2 + 1, prom + 1, y);
}

tint query(int pos, int a, int b, int x = 0, int y = segN - 1) {
  // Returnear suma de los hijos
  if (a <= x && b >= y) return eval(pos, x, y);

  // Returnear nada porque no está en el rango
  if (a > y || b < x) return 0;

  tint med = (y - x + 1) / 2;
  // Propagación izquierda
  segTree[pos * 2].lazy += segTree[pos].lazy;
  segTree[pos * 2].cantidad += segTree[pos].cantidad;
  // Propagación derecha
  segTree[pos * 2 + 1].lazy +=
      (segTree[pos].lazy + segTree[pos].cantidad * med);
  segTree[pos * 2 + 1].cantidad += segTree[pos].cantidad;
  // Reseteo
  segTree[pos].lazy = 0;
  segTree[pos].cantidad = 0;

  // Si es que no está totalmente contenido en el rango, retornar los hijos
  int prom = (x + y) / 2;
  segTree[pos].suma = eval(pos * 2, x, prom) + eval(pos * 2 + 1, prom + 1, y);
  return query(pos * 2, a, b, x, prom) + query(pos * 2 + 1, a, b, prom + 1, y);
}

int main() {
  cin.sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  cin >> N >> Q;

  while (segN < N) segN *= 2;
  largo = segN * 2;
  segTree.resize(largo);

  forn(i, N) {
    int temp;
    cin >> temp;
    update(1, i, i, temp);
  }

  forn(i, Q) {
    int t;
    cin >> t;
    if (t == 1) {
      // Update
      int a, b;
      cin >> a >> b;
      update(1, a - 1, b - 1, 1);
    } else {
      // Query
      int a, b;
      cin >> a >> b;
      cout << query(1, a - 1, b - 1) << "\n";
    }
  }
}