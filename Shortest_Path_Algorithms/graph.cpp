#include "graph.h"
#include <cmath>

#define east 2
#define west 1
#define north 0
#define south 3


Graph::Graph()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
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



bool Graph::heuristic_algorithm(int start, int end)
{

    end_y = end / width;
    end_x = end - (end_y * width);

    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
    }

    visited[start] = true;

    while (true) {

        // selects cells which are nearest to the end
        QVector <QPair <int, int>> y_x = smallest_cell_value(start);

        // while current node is stuck
        while (y_x[1].first == INT_MAX || y_x[0].first == INT_MAX){
            store_searching_path.pop_back();
            y_x = smallest_cell_value(store_searching_path.back());
        }

        if (y_x[0].first != 0){

            store_searching_path.push_back(y_x[0].second);
            start = y_x[0].second;
            visited[y_x[0].second] = true;
        }

        if (y_x[0].first == 0 && y_x[1].first != 0){

            store_searching_path.push_back(y_x[1].second);
            start = y_x[1].second;
            visited[y_x[1].second] = true;
        }

        // if reached the end
        if (y_x[0].first == 0 && y_x[1].first == 0){

            store_searching_path.push_back(y_x[1].second);
            store_searching_path.push_back(y_x[0].second);
            y_x.clear();
            return  true;
        }


    }


    return false;


}

QVector <QPair<int, int>> Graph::smallest_cell_value(int start) {

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

            int weight_x = abs(end_x - x);
            int weight_y = abs(end_y - y);

            // direction_vertice.push_back({});
            direction_vertice[i][0] = v;
            direction_vertice[i][1] = weight_x;
            direction_vertice[i][2] = weight_y;

        }
    }

    int random_pos =  (qrand() % direction_vertice.size()) + 0;
    QPair <int, int> smallest_y = {direction_vertice[random_pos][2], direction_vertice[random_pos][0]};
    QPair <int, int> smallest_x = {direction_vertice[random_pos][1], direction_vertice[random_pos][0]};

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
    direction_vertice.clear();
    int random = (qrand() % 2) + 0;
    if (random == 1)
        return {{smallest_x.first, smallest_x.second}, {smallest_y.first, smallest_y.second}};
    else
        return {{smallest_y.first, smallest_y.second}, {smallest_x.first, smallest_x.second}};
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
                    queue.clear();
                    return true;
                }

            }
        }
    }

    return false;
}

bool Graph::Double_BFS(int start, int end) {

    int end1 = end;

    for (int i = 0; i < Vertices; i++){
        visited.push_back(false);
        store_path.push_back(-1);
        store_path1.push_back(-1);
        visited1.push_back(false);
    }

    QList <int> queue;

    visited[start] = true;
    queue.push_back(start);

    QList <int> queue1;

    visited1[end1] = true;
    queue1.push_back(end1);

    while (true){

        start = queue.front();
        queue.pop_front();

        end1 = queue1.front();
        queue1.pop_front();

        // BFS start - end
        for (int i = 0; i < matrix[start].size(); i++){

            if (!visited[matrix[start][i]]){
                store_searching_path.push_back(matrix[start][i]);
                visited[matrix[start][i]] = true;
                queue.push_back(matrix[start][i]);
                store_path[ matrix[start][i] ] = start;

            }
        }

        // BFS end - start
        for (int i = 0; i < matrix[end1].size(); i++){

            if (!visited1[matrix[end1][i]]){

                store_searching_path1.push_back(matrix[end1][i]);
                visited1[matrix[end1][i]] = true;
                queue1.push_back(matrix[end1][i]);
                store_path1[ matrix[end1][i] ] = end1;



            }
        }

        if (collided()){
            return true;
        }

    }

    return false;
}

bool Graph::collided() {

    for (int i = 0; i < visited.size(); i++){
        if (visited[i] && visited1[i]){
            last_vertice = i;
            return true;
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

// Heuristic search

// if cell has more than 1 choise , copy path and add to the vector?






