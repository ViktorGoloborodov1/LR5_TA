#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

const int INF = 1e9;
const int V_COUNT = 8; // Кількість вершин для варіанта № 9

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Матриця суміжності зваженого графа (вершини 1..8 відповідають індексам 0..7)
    int G[V_COUNT][V_COUNT] = {
        //  1    2    3    4    5    6    7    8
        { INF, INF,   6,   7, INF,   8, INF, INF}, // 1
        { INF, INF, INF,   3,   4,   2, INF, INF}, // 2
        {   6, INF, INF, INF, INF,   3, INF,   7}, // 3
        {   7,   3, INF, INF,   9, INF, INF, INF}, // 4
        { INF,   4, INF,   9, INF, INF,   5, INF}, // 5
        {   8,   2,   3, INF, INF, INF,   9,   3}, // 6
        { INF, INF, INF, INF,   5,   9, INF, INF}, // 7
        { INF, INF,   7, INF, INF,   3, INF, INF}  // 8
    };

    vector<bool> selected(V_COUNT, false);
    selected[0] = true; // Стартуємо з вершини 1 (індекс 0)

    int edges_count = 0;
    int total_weight = 0;

    cout << "========================================" << endl;
    cout << "   РЕЗУЛЬТАТ РОБОТИ АЛГОРИТМУ ПРІМА     " << endl;
    cout << "========================================" << endl;
    cout << left << setw(8) << "Крок" << setw(16) << "Ребро (u - v)" << "Вага" << endl;
    cout << "----------------------------------------" << endl;

    while (edges_count < V_COUNT - 1) {
        int min_weight = INF;
        int u_best = -1, v_best = -1;

        for (int i = 0; i < V_COUNT; ++i) {
            if (selected[i]) {
                for (int j = 0; j < V_COUNT; ++j) {
                    if (!selected[j] && G[i][j] < min_weight) {
                        min_weight = G[i][j];
                        u_best = i;
                        v_best = j;
                    }
                }
            }
        }

        if (u_best != -1 && v_best != -1) {
            selected[v_best] = true;
            edges_count++;
            total_weight += min_weight;
            cout << setw(8) << edges_count 
                 << (u_best + 1) << " - " << setw(12) << (v_best + 1) 
                 << min_weight << endl;
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "Сумарна вартість MST (Прім): " << total_weight << endl;
    cout << "========================================" << endl;

    return 0;
}
