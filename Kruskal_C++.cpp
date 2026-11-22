#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
private:
    vector<int> parent;
public:
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]); // Евристика стиснення шляхів
    }
    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            parent[b] = a;
            return true;
        }
        return false;
    }
};

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int V_COUNT = 8;
    vector<Edge> edges = {
        {1, 3, 6}, {1, 4, 7}, {1, 6, 8},
        {2, 4, 3}, {2, 5, 4}, {2, 6, 2},
        {3, 6, 3}, {3, 8, 7},
        {4, 5, 9},
        {5, 7, 5},
        {6, 7, 9}, {6, 8, 3}
    };

    // 1. Сортування множини ребер у неспадному порядку ваг
    sort(edges.begin(), edges.end());

    DSU dsu(V_COUNT);
    int total_weight = 0;
    int step = 0;

    cout << "========================================" << endl;
    cout << "  РЕЗУЛЬТАТ РОБОТИ АЛГОРИТМУ КРУСКАЛА   " << endl;
    cout << "========================================" << endl;
    cout << left << setw(8) << "Крок" << setw(16) << "Ребро (u - v)" << "Вага" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto& edge : edges) {
        if (dsu.union_sets(edge.u, edge.v)) {
            total_weight += edge.weight;
            step++;
            cout << setw(8) << step 
                 << edge.u << " - " << setw(12) << edge.v 
                 << edge.weight << endl;
            if (step == V_COUNT - 1) break;
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "Сумарна вартість MST (Крускал): " << total_weight << endl;
    cout << "========================================" << endl;

    return 0;
}
