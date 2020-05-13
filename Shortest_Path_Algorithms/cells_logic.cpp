#include "cells_logic.h"
#include "graph.h"
#include <QMessageBox>

cells_logic::cells_logic() {

}

void cells_logic::initialize_cells() {
    cells.clear();
    my_graph.initialize_matrix(cells_width * cells_height);
    index = 0;
    path.clear();
    path1.clear();

    cells.resize(cells_width * cells_height);

    done = false;
    path_drawn = false;

    for (int y = 0; y < cells_height; y++){
        for (int x = 0; x < cells_width; x++){

            // all cells wasn't visited or modifed yet
            cells[y].push_back(0);

        }
    }
}

void cells_logic::update_cells(QString algorithm) {

    if (algorithm == "Breadth-first Search")
        breadth_first_search();


    if (algorithm == "Depth-first Searsh")
        Depth_First_Search();


    if (algorithm == "Dijkstra's algorithm")
        Dijkstra_algorithm();

    if (algorithm == "Heuristic Search")
        Heuristic_algorithm();
    if (algorithm == "Breadth-first Search.2")
        Breadth_first_Search_2();


}




void cells_logic::add_eges() {
    int count = 0;
    for (int y = 0; y < cells_height; y++){
        for (int x = 0; x < cells_width; x++){
            if (x != 0 && cells[y][x - 1] != 2){
                my_graph.addEdge(count, count - 1);
            }

            if (x != cells_width - 1 && cells[y][x + 1] != 2){
                my_graph.addEdge(count, count + 1);
            }

            if (y != 0 && cells[y - 1][x] != 2){
                my_graph.addEdge(count, count - cells_width);
            }

            if (y != cells_height - 1 && cells[y + 1][x] != 2){
                my_graph.addEdge(count, count + cells_width);
            }

            // move to the next cell
            count++;
        }
    }
}

void cells_logic::initialize_algorithm(int algorithm_name)
{
    for (int y = 0; y < cells_height; y++){
        for (int x = 0; x < cells_width; x++){

            if (cells[y][x] == -5)
                start = (y * cells_width) + x;

            if (cells[y][x] == 5)
                end = (y * cells_width) + x;
        }
    }
    // BFS
    if (algorithm_name == 0)
        my_graph.BFS(start, end);

    // DFS
    if (algorithm_name == 1)
        my_graph.DFS(start, end);

    // Dijkstra
    if (algorithm_name == 2)
        my_graph.dijkstra_algorithm(start, end);

    // Heuristic
    if (algorithm_name == 3)
        my_graph.heuristic_algorithm(start, end);

    // BFS.2
    if (algorithm_name == 4)
        my_graph.Double_BFS(start, end);


}

// Algorithms

void cells_logic::breadth_first_search() {
    if (!done){
        initialize_algorithm(0);
        done = true;
        shortest_path();
    }

    if (index < my_graph.store_searching_path.size() - 1){
        int vertex = my_graph.store_searching_path[index];
        index++;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;
    } else {
        if (index_draw_path > 0){
            QPair <int, int> coordinates = {path[index_draw_path] / cells_width, path[index_draw_path] % cells_width};
            cells[coordinates.first][coordinates.second] = 3;
            index_draw_path--;
        }
    }
}

void cells_logic::Depth_First_Search() {

    if (!done){
        initialize_algorithm(1);
        done = true;
    }

    if (index < my_graph.store_searching_path.size() - 1 && !path_drawn){
        int vertex = my_graph.store_searching_path[index];
        index++;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;
        if (index == my_graph.store_searching_path.size() - 1)
            path_drawn = true;
    }
    if (path_drawn && index > 0){

        int vertex = my_graph.store_searching_path[index - 1];
        index--;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 3;
    }



}

void cells_logic::Dijkstra_algorithm() {

    if (!done){
        initialize_algorithm(2);
        done = true;
        shortest_path();
    }
    if (index < my_graph.store_searching_path.size() - 1 && !path_drawn){
        int vertex = my_graph.store_searching_path[index];
        index++;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;
        if (index == my_graph.store_searching_path.size() - 1)
            path_drawn = true;
    }   else {
        if (index_draw_path > 0){
            QPair <int, int> coordinates = {path[index_draw_path] / cells_width, path[index_draw_path] % cells_width};
            cells[coordinates.first][coordinates.second] = 3;
            index_draw_path--;
        }
    }

}

// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16
void cells_logic::Heuristic_algorithm()
{
    if (!done){
        initialize_algorithm(3);
        done = true;
    }
    if (index < my_graph.store_searching_path.size() - 1){

        int vertex = my_graph.store_searching_path[index];
        index++;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        if (vertex != end)
            cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;

    }

}

void cells_logic::shortest_path()
{
    // find shortest path
    int vertex = end;
    path.push_back(end);

    while (my_graph.store_path[vertex] != -1){
        path.push_back(my_graph.store_path[vertex]);
        vertex = my_graph.store_path[vertex];
    }

    index_draw_path = path.size() - 2;
}

void cells_logic::Breadth_first_Search_2(){

    if (!done){
        initialize_algorithm(4);
        done = true;

        int vertex = my_graph.last_vertice;
        path.push_back(my_graph.last_vertice);

        while (my_graph.store_path[vertex] != -1){
            path.push_back(my_graph.store_path[vertex]);
            vertex = my_graph.store_path[vertex];
        }

        index_draw_path = path.size() - 2;

        int vertex1 = my_graph.last_vertice;
        path1.push_back(my_graph.last_vertice);

        while (my_graph.store_path1[vertex1] != -1){
            path1.push_back(my_graph.store_path1[vertex1]);
            vertex1 = my_graph.store_path1[vertex1];
        }

        index_draw_path1 = path1.size() - 2;
    }



    if (index < my_graph.store_searching_path.size() - 1 && !path_drawn){

        if (my_graph.store_searching_path1.size() > index){

            int vertex1 = my_graph.store_searching_path1[index];
            QPair <int, int> coordinates_of_vertex1 = {vertex1 / cells_width, vertex1 % cells_width};
            cells[coordinates_of_vertex1.first][coordinates_of_vertex1.second] = -1;

        }

        int vertex = my_graph.store_searching_path[index];
        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;

        index++;

        if (index == my_graph.store_searching_path.size() - 1)
            path_drawn = true;

    }   else {

        if (index_draw_path >= 0){
            QPair <int, int> coordinates = {path[index_draw_path] / cells_width, path[index_draw_path] % cells_width};
            cells[coordinates.first][coordinates.second] = 3;
            index_draw_path--;
        }

        if (index_draw_path1 > 0) {
        QPair <int, int> coordinates1 = {path1[index_draw_path1] / cells_width, path1[index_draw_path1] % cells_width};
        cells[coordinates1.first][coordinates1.second] = 3;
        index_draw_path1--;

        }

    }
}



//
