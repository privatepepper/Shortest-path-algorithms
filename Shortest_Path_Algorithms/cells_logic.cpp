#include "cells_logic.h"
#include "graph.h"
#include <QMessageBox>

#define visualize_path 3
#define cell_visualize_searching 1

cells_logic::cells_logic() {

}

void cells_logic::initialize_cells() {

    my_graph.initialize_matrix(cells_width * cells_height);

    path.clear();
    path1.clear();
    cells.clear();
    cells.resize(cells_width * cells_height);

    index = 0;
    done = false;

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

    switch (algorithm_name) {

        case 0:my_graph.BFS(start, end);break;

        case 1:my_graph.DFS(start, end);break;

        case 2:my_graph.dijkstra_algorithm(start, end);break;

        case 3:my_graph.heuristic_algorithm(start, end);break;

        case 4:my_graph.Double_BFS(start, end);break;
    }
}



void cells_logic::breadth_first_search() {
    if (!done){

        initialize_algorithm(0);
        done = true;
        shortest_path(end, path, index_draw_path, my_graph.store_path);   
    }

    if (index < my_graph.store_searching_path.size() - 1){

        visualize_searching(my_graph.store_searching_path);
        index++;

    } else {

        if (index_draw_path > 0)
            draw_path(index_draw_path, path);
    }
}



void cells_logic::Depth_First_Search() {

    if (!done){

        initialize_algorithm(1);
        done = true;

    }

    if (index < my_graph.store_searching_path.size() - 1){

        visualize_searching(my_graph.store_searching_path);
        index++;

    }
}



void cells_logic::Dijkstra_algorithm() {

    if (!done){
        initialize_algorithm(2);
        done = true;
        shortest_path(end, path, index_draw_path, my_graph.store_path);
    }
    if (index < my_graph.store_searching_path.size() - 1){

        visualize_searching(my_graph.store_searching_path);
        index++;

    }   else {

        if (index_draw_path > 0)
           draw_path(index_draw_path, path);

    }

}



void cells_logic::Heuristic_algorithm()
{
    if (!done){

        initialize_algorithm(3);
        done = true;

    }
    if (index < my_graph.store_searching_path.size() - 1){

        visualize_searching(my_graph.store_searching_path);
        index++;

    }

}



void cells_logic::Breadth_first_Search_2(){

    if (!done){

        initialize_algorithm(4);
        shortest_path(my_graph.last_vertice, path, index_draw_path, my_graph.store_path);
        shortest_path(my_graph.last_vertice, path1, index_draw_path1, my_graph.store_path1);
        done = true;
    }

    if (index < my_graph.store_searching_path.size() - 1){

        visualize_searching(my_graph.store_searching_path);

        if (my_graph.store_searching_path1.size() > index)
            visualize_searching(my_graph.store_searching_path1);
        index++;
    }   else {

        if (index_draw_path >= 0)
            draw_path(index_draw_path, path);

        if (index_draw_path1 > 0)
            draw_path(index_draw_path1, path1);
    }
}



void cells_logic::draw_path(int &Index, QVector<int> Path) {

    QPair <int, int> coordinates = {Path[Index] / cells_width, Path[Index] % cells_width};
    cells[coordinates.first][coordinates.second] = visualize_path;
    Index--;
}

void cells_logic::visualize_searching(QVector <int> stored_path){

    int vertex = stored_path[index];
    QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
    cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = cell_visualize_searching;

}

void cells_logic::shortest_path(int destination, QVector <int> &Path, int &Path_size, QVector <int> Store_path){

    int vertex = destination;
    Path.push_back(destination);

    while (Store_path[vertex] != -1){
        Path.push_back(Store_path[vertex]);
        vertex = Store_path[vertex];
    }

    Path_size = Path.size() - 2;
}




