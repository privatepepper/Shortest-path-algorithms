#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <QtGui>


class Graph
{
public:

    Graph();

    QVector <int> *matrix;

    int width = 20;
    int height = 15;

    int Vertices;

    void initialize_matrix(int nodes){
        Vertices = nodes;
        matrix = new QVector <int> [nodes];
    }

    void addEdge(int vertice1, int vertice2){
        matrix[vertice1].push_back(vertice2);
        matrix[vertice2].push_back(vertice1);
    }

    void dijkstra_algorithm();

    QVector <int> finding_end_point;

private:

    QPair<int, int> update();
    void BFS(int s);

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
//QString printGraph(){
//    QString s;
//    for(int i = 0; i < vertices; i++){
//        s.append(QString::number(i) + "=> ");
//        for (auto it : Adjacency_list[i]){
//            s.append(QString::number(it) + ", ");
//        }
//        s.append("\n");

//    }
//    return s;
//}


