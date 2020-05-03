#include "graph.h"

//#include <QtCore>

Graph::Graph()
{

}

void Graph::dijkstra_algorithm()
{

}

void Graph::BFS(int s)
{
    bool *visited = new bool[Vertices];

    for (int i = 0; i < Vertices; i++){
        visited[i] = false;
    }

    QList <int> queue;

    visited[s] = true;
    queue.push_back(s);

    while (!queue.empty()){
        s = queue.front();
        queue.pop_front();

        for (int i = 0; i < matrix[s].size(); i++){
            if (!visited[i]){
                finding_end_point.push_back(matrix[s][i]);
                visited[i] = true;
            }
        }
    }

}

QPair <int, int> Graph::update()
{

    return {};
}
