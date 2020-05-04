#include "cells_logic.h"
#include "graph.h"

#include <QMessageBox>

cells_logic::cells_logic()
{

}

void cells_logic::initialize_cells()
{
    cells.clear();
    my_graph.initialize_matrix(cells_width * cells_height);
    index = 0;
    path.clear();

    cells.resize(cells_width * cells_height);

    int count = 0;
    done = false;

    for (int y = 0; y < cells_height; y++){
        for (int x = 0; x < cells_width; x++){

            // all cells wasn't visited or modifed yet
            cells[y].push_back(0);

            // add edges to the graph

            if (x != 0){
                my_graph.addEdge(count, count - 1);
            }

            if (x != cells_width - 1){
                my_graph.addEdge(count, count + 1);
            }

            if (y != 0){
                my_graph.addEdge(count, count - cells_width);
            }

            if (y != cells_height - 1){
                my_graph.addEdge(count, count + cells_width);
            }

            // move to the next cell
            count++;

        }
    }
}

void cells_logic::update_cells()
{
    breadth_first_search();
}

void cells_logic::breadth_first_search()
{
    if (!done){
        for (int y = 0; y < cells_height; y++){
            for (int x = 0; x < cells_width; x++){

                if (cells[y][x] == -5)
                    start = (y * cells_width) + x;

                if (cells[y][x] == 5)
                    end = (y * cells_width) + x;
            }
        }
        my_graph.BFS(start, end);
        done = true;

        // find shortest path
        int vertex = end;
        path.push_back(end);
        while (my_graph.store_path[vertex] != -1){
            path.push_back(my_graph.store_path[vertex]);
            vertex = my_graph.store_path[vertex];
        }
        index_draw_path = path.size() - 1;
    }

    if (index < my_graph.store_searching_path.size()){
        int vertex = my_graph.store_searching_path[index];
        index++;

        QPair <int, int> coordinates_of_vertex = {vertex / cells_width, vertex % cells_width};
        cells[coordinates_of_vertex.first][coordinates_of_vertex.second] = 1;
    } else {
        if (index_draw_path >= 0){
            QPair <int, int> coordinates = {path[index_draw_path] / cells_width, path[index_draw_path] % cells_width};
            cells[coordinates.first][coordinates.second] = 2;
            index_draw_path--;
        }
    }
}






