#include "graph.h"
#include <cmath>

#define east 2
#define west 1
#define north 0
#define south 3


Graph::Graph()
{

}

bool Graph::dijkstra_algorithm(int start, int end)
{
    dist.clear();
    visited.clear();
    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
        dist.push_back(INT_MAX);
        store_path.push_back(-1);
    }

    QList <int> queue;

    dist[start] = 0;

    queue.push_back(start);

    while (!queue.empty()){

        start = queue.front();
        queue.pop_front();

        for (int i = 0; i < matrix[start].size(); i++){

            int v = matrix[start][i];

            if (dist[v] > dist[start] + 1){

                store_searching_path.push_back(v);
                dist[v] = dist[start] + 1;
                queue.push_back(v);
                store_path[v] = start;
            }

            if (matrix[start][i] == end)
                return true;

        }


    }

    return false;
}

// 1 2 3
// 4 5 6
// 7 8 9

bool Graph::heuristic_algorithm(int start, int end)
{
   // qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    QVector <QVector <int> > direction_vertice;

    int end_y = end / width;
    int end_x = end - (end_y * width);

    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
    }

    visited[start] = true;

    while (true) {

        for (int i = 0; i < matrix[start].size(); i++){

            direction_vertice.push_back({});
            direction_vertice[i].push_back(0);
            direction_vertice[i].push_back(INT_MAX);
            direction_vertice[i].push_back(INT_MAX);
            if (!visited[matrix[start][i]]){

                // vertex
                int v = matrix[start][i];
                int y = v / width;
                int x = v - (y * width);
                visited[v] = true;

                int weight_x = abs(end_x - x);
                int weight_y = abs(end_y - y);

               // direction_vertice.push_back({});
                direction_vertice[i][0] = v;
                direction_vertice[i][1] = weight_x;
                direction_vertice[i][2] = weight_y;

            }
        }

        QPair <int, int> smallest_y = {direction_vertice[0][2], direction_vertice[0][0]};
        QPair <int, int> smallest_x = {direction_vertice[0][1], direction_vertice[0][0]};

        for (int i = 0; i < direction_vertice.size();i++){

                if (direction_vertice[i][1] < smallest_x.first){

                    smallest_x.first = direction_vertice[i][1];
                    smallest_x.second = direction_vertice[i][0];
                }

                if (direction_vertice[i][2] < smallest_y.first){

                    smallest_y.first = direction_vertice[i][2];
                    smallest_y.second = direction_vertice[i][0];
                }

        }


        if (smallest_y.first != 0){

            store_searching_path.push_back(smallest_y.second);
            start = smallest_y.second;
        }

        if (smallest_y.first == 0 && smallest_x.first != 0){

            store_searching_path.push_back(smallest_x.second);
            start = smallest_x.second;
        }

        // if reached the end
        if (smallest_y.first == 0 && smallest_x.first == 0){

            store_searching_path.push_back(smallest_x.second);
            store_searching_path.push_back(smallest_y.second);
            return  true;
        }

        direction_vertice.clear();
    }


    return false;
}

bool Graph::BFS(int start, int end)
{


    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
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

bool Graph::DFS(int start, int end) {

    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
    }

    found_end  = false;
    recursive_DFS(start, end);

    return true;
}

bool Graph::recursive_DFS(int source, int end)
{
    visited[source] = true;

    if (source == end){
        found_end = true;
        return true;
    }

    for (int i : matrix[source]){
        if (!visited[i]){

            if (!found_end){
                store_searching_path.push_back(i);
            }

            recursive_DFS(i, end);
        }
    }

    return false;
}

// only up works?



