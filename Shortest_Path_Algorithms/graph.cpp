#include "graph.h"
#include "mainwindow.h"
//#include "Node_Class.h"
#include <cmath>

#define east 2
#define west 1
#define north 0
#define south 3

#define Vertex 50

typedef QVector <int> Node;  // - {node_position, h.cost, g.cost, parent}

Graph::Graph() {

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
    //count_vertices();

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

bool Graph::A_Star_Algorithm(int start, int end) {

    end_x = end % width;
    end_y = end / width;

    QList <Node> openSet;
    QList <Node> closedSet;

    for (int i = 0; i < Vertices; i++){
        store_nodes.push_back({i, INT_MAX, INT_MAX, -1});
    }

    Node first_node = {start, 0, 0, -1};
    store_nodes[first_node[0]] = first_node;

    openSet.push_back(first_node);

    while (!openSet.empty()){

        Node current_node = openSet[0];

        for (int i = 1; i < openSet.size(); i++){

            if ( ( f_cost(openSet[i]) < f_cost(current_node) ) || ( f_cost(openSet[i]) == f_cost(current_node) && openSet[i][1] < current_node[1] ) ){
                current_node = openSet[i];
            }
        }

        remove(openSet, current_node[0]);
        closedSet.push_back(current_node);

        if (current_node[0] == end){
            RetracePath(start, current_node);
            return true;
        }

        for (Node neighbour : getNeighbours(current_node)){

            if (contains(neighbour[0], closedSet))
                continue;

                int newMovementCostToNeighbour = current_node[2] + 1;
                if (newMovementCostToNeighbour < neighbour[2] || !contains(neighbour[0], openSet)) {

                    neighbour[2] = newMovementCostToNeighbour;
                    neighbour[1] = Manhattan_Distance(neighbour[0]);
                    neighbour[3] = current_node[0];
                    store_searching_path.push_back(neighbour[0]);



                    if (!contains(neighbour[0], openSet)){
                        openSet.push_back(neighbour);
                        store_nodes[neighbour[0]] = neighbour;

                    }
                }


        }
    }

    return false;
}

int Graph::Manhattan_Distance(int vertex){

    int y = vertex / width;
    int x = vertex % width;
    return abs(x - end_x) + abs(y - end_y);;
}

QList <Node> Graph::getNeighbours(Node vertex){

    QList <Node> neighbours;

    for (int i = 0; i < matrix[vertex[0]].size(); i++){
        neighbours.push_back({matrix[vertex[0]][i], INT_MAX, INT_MAX, 0});
    }

    return neighbours;
}

int Graph::f_cost(QVector<int> node){

    return Manhattan_Distance(node[0]) + node[2];
}

void Graph::remove(QList<QVector<int> > &openList, int node){

    for (int i = 0; i < openList.size(); i++){
        if (openList[i][0] == node){
            openList.removeAt(i); // works?
        }
    }
}

bool Graph::contains(int node, QList <QVector <int>> list) {

    for (int i = 0; i < list.size(); i++){
        if (list[i][0] == node){
            return true;
        }
    }
    return false;
}

void Graph::RetracePath(int start, Node end) {

    Node currentNode = end;

    while (currentNode[0] != start){
        A_star_path.push_back(currentNode[0]);
        currentNode = store_nodes[currentNode[3]];
    }

}

void Graph::generate_random_graph() {

    graph_mode = true;

    if (random_vertixes.size() != 0)
        random_vertixes.clear();

    if (linked.size() != 0)
        linked.clear();

    initialize_matrix(width * height);
    random_vertixes.resize(height * width);
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            random_vertixes[y].push_back(0);
        }
    }

    current_y = 1;
    current_x = width / 2;
    random_vertixes[current_y][current_x] = Vertex;

    generate_tree(current_y, current_x);

    //check_under();
    //check_under();

}

void Graph::random_coordinates() {

    int w = 0, h = 0;

    do {
        current_y -= h;
        current_x -= w;
        h = (qrand() % 2) + 1;
        if (qrand() % 2 == 0)
            w = (qrand() % 4) + 0;
        else
            w = (qrand() % 1) -3;

        current_x += w;
        current_y += h;

    } while (current_x <= 0 || current_x >= width - 2 || current_y >= width -2 || check_around());
}

bool Graph::check_around() {

    if (current_x != width - 1){
        if (random_vertixes[current_y][current_x + 1] == Vertex)
            return true;
    }
    if (current_x != 0){
        if (random_vertixes[current_y][current_x - 1] == Vertex)
            return true;
    }
    if (current_y != height - 1){
        if (random_vertixes[current_y + 1][current_x] == Vertex)
            return true;
    }
    if (current_y != 0){
        if (random_vertixes[current_y - 1][current_x] == Vertex)
            return true;
    }
    if (current_x != 0 && current_y != 0){
        if (random_vertixes[current_y - 1][current_x - 1] == Vertex)
            return true;
    }
    if (current_x != width - 1 && current_y != height - 1){
        if (random_vertixes[current_y + 1][current_x + 1] == Vertex)
            return true;
    }
    if (current_x != 0 && current_y != height - 1){
        if (random_vertixes[current_y + 1][current_x - 1] == Vertex)
            return true;
    }
    if (current_x != width - 1 && current_y != 0){
        if (random_vertixes[current_y - 1][current_x + 1] == Vertex)
            return true;
    }
    return false;
}

void Graph::generate_tree(int source_y, int source_x) {

    int previous_x, previous_y;

    current_y = source_y;
    current_x = source_x;

    while (true) {

        previous_x = current_x;
        previous_y = current_y;
        random_coordinates();

        random_vertixes[current_y][current_x] = Vertex;

        addEdge( ( (previous_y * width) + (previous_x % width) ), ( (current_y * width) + (current_x % width) ) );
        QPair < QPair <int, int > , QPair <int, int> > coords = {{previous_y, previous_x}, {current_y, current_x}};
        linked.push_back(coords);

        if (qrand() % 2 == 0){
            current_y = previous_y;
            current_x = previous_x;
        }

        if (current_y > height - 5)
            break;
    }
}

void Graph::check_under() {

    int y, x;

    for (int i = 0;i < linked.size(); i++){

        int count = 0;
        QPair <int, int> node = linked[i].first;

        y = node.first;
        x = node.second;
        int y_clone = y + 1;

        while(random_vertixes[y][x] == 0 && y > height - 3){
            y_clone++;
            count++;
        }

        if (count == 0){
            generate_tree(y, x);
            break;
        }
    }
}

void Graph::count_vertices() {

   Vertices = 0;
    for (int y = 0; y < random_vertixes.size(); y++){
        for (int x : random_vertixes[y]){
            if (x == Vertex)
                Vertices++;
        }
    }

}







