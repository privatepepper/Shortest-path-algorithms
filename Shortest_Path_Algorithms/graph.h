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
        }

        store_searching_path.clear();
        store_path.clear();
        matrix.resize(nodes);
    }

    void addEdge(int vertice1, int vertice2){
        matrix[vertice1].push_back(vertice2);
    }

    QVector <int> store_searching_path;
    QVector <int> store_path;

    bool BFS(int start, int end);
    bool DFS(int start, int end);
    bool dijkstra_algorithm(int start, int end);
    bool heuristic_algorithm(int start, int end);

private:


    QVector <int> dist;
    QVector <bool> visited;
    bool recursive_DFS(int source, int end);
    bool found_end = false;

};

#endif // GRAPH_H








