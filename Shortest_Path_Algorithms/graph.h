#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <QtGui>


class Graph
{
public:

    Graph();

    int width = 40;
    int height = 30;

    int Vertices;
    QVector <QVector <int> > matrix;

    void initialize_matrix(int nodes){
        Vertices = nodes;

        if (matrix.size() != 0){
            matrix.clear();
            visited.clear();
            visited1.clear();
        }

        store_searching_path.clear();
        store_searching_path1.clear();
        store_path.clear();
        store_path1.clear();
        A_star_path.clear();
        matrix.resize(nodes);
    }

    void addEdge(int vertice1, int vertice2){
        matrix[vertice1].push_back(vertice2);
    }

    QVector <int> store_searching_path;
    QVector <int> store_searching_path1;
    QVector <int> store_path;
    QVector <int> store_path1;


    bool BFS(int start, int end);
    bool DFS(int start, int end);
    bool dijkstra_algorithm(int start, int end);
    bool heuristic_algorithm(int start, int end);
    bool Double_BFS(int start, int end);
    bool A_Star_Algorithm(int start, int end);

    int last_vertice;
    QVector <int> A_star_path;

    QVector < QVector <int>> random_vertixes;
    void generate_random_graph();
    QVector < QPair < QPair <int, int > , QPair <int, int> >> linked;

private:


    QVector <int> dist;
    QVector <bool> visited;
    QVector <bool> visited1;
    bool recursive_DFS(int source, int end);
    bool found_end = false;
    int end_y;
    int end_x;
    QVector <QVector <int> > direction_vertice;
    QVector <QPair <int, int>> smallest_cell_value(int current_vertice);
    bool collided();

    int Manhattan_Distance(int node);
    int f_cost(QVector <int> node);
    void remove(QList <QVector <int>> &openList, int node);

    QList <QVector <int>> getNeighbours(QVector <int> node);
    void RetracePath(int start, QVector <int> end);
    QList <QVector <int>> store_nodes;

    bool contains(int node, QList <QVector <int>> closedlist);

    int current_y;
    int current_x;
    void random_coordinates();
    bool check_around();

};

#endif // GRAPH_H






