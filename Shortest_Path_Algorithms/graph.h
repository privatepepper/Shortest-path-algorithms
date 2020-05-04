#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <QtGui>


class Graph
{
public:

    Graph();

    int width = 16;
    int height = 12;

    int Vertices;

    void initialize_matrix(int nodes){
        Vertices = nodes;
        matrix->clear();
        store_searching_path.clear();
        store_path.clear();
        matrix = new QVector <int> [nodes];
    }

    void addEdge(int vertice1, int vertice2){
        matrix[vertice1].push_back(vertice2);
    }

    QVector <int> store_searching_path;
    QVector <int> store_path;

    bool BFS(int start, int end);
    void dijkstra_algorithm();

private:

    QVector <int> *matrix;
};

#endif // GRAPH_H


//private:
//int vertices;
//QList <int> *Adjacency_list;

//public:

//Graph(int V){
//    this->vertices = V;
//    Adjacency_list = new QList <int> [V];
//}

//void addEdge(int u, int v){
//    Adjacency_list[u].push_back(v);
//    Adjacency_list[v].push_back(u);
//}
//QList <int>  *get_list(){
//    QList <int> *n_e_w = Adjacency_list;
//    return n_e_w;
//}

//}


//QString printGraph(){
//    QString s;
//    for(int i = 0; i < Vertices; i++){
//        s.append(QString::number(i) + "=> ");
//        for (auto it : matrix[i]){
//            s.append(QString::number(it) + ", ");
//        }
//        s.append("\n");

//    }
//    return s;
//}



