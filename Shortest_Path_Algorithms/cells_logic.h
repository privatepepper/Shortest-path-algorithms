#ifndef CELLS_LOGIC_H
#define CELLS_LOGIC_H

#include <QtCore>
#include <QtGui>
#include "graph.h"

class cells_logic
{
public:
    cells_logic();

    Graph my_graph;

    int cells_height = my_graph.height;
    int cells_width = my_graph.width;

    QVector < QVector < int > > cells;
    void initialize_cells();
    void update_cells(QString s);


    void add_eges();

    //QString s; -> for testing

private:

    // update cell
    bool done = false;
    int start;
    int end;
    int index = 0;
    QVector <int> path;
    int index_draw_path = 0;

    void initialize_algorithm(int algorithm_name);

    // algorithms
    void breadth_first_search();

    void Depth_First_Search();

    void Dijkstra_algorithm();

    void Heuristic_algorithm();
    void highlighter(int current_node);

    bool path_drawn = false;
    void shortest_path();



};

#endif // CELLS_LOGIC_H
