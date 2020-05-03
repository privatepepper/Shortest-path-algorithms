#include "graph.h"

//#include <QtCore>

Graph::Graph()
{

}

void Graph::dijkstra_algorithm()
{

}

bool Graph::BFS(int start, int end)
{
    bool *visited = new bool[Vertices];

    for (int i = 0; i < Vertices; i++){
        visited[i] = false;
        store_path.push_back(-1);
    }

    QList <int> queue;

    visited[start] = true;
    queue.push_back(start);

    while (!queue.empty()){

        start = queue.front();
        queue.pop_front();

        for (int i = 0; i < matrix[start].size(); i++){

            if (!visited[matrix[start][i]]){

                store_searching_path.push_back(matrix[start][i]);
                visited[matrix[start][i]] = true;
                queue.push_back(matrix[start][i]);
                store_path[ matrix[start][i] ] = start;

                if (matrix[start][i] == end){
                    return true;
                }

            }
        }

    }

    return false;
}


