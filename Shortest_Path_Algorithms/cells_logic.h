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

private:

    int start;
    int end;

    int index = 0;
    bool done = false;

    QVector <int> path;
    QVector <int> path1;

    int index_draw_path = 0;
    int index_draw_path1 = 0;

    // algorithms
    void initialize_algorithm(int algorithm_name);

    void breadth_first_search();
    void Depth_First_Search();
    void Dijkstra_algorithm();
    void Breadth_first_Search_2();
    void Heuristic_algorithm();



    void shortest_path(int destination, QVector <int> &Path, int &Path_size, QVector <int> Store_path);
    void draw_path(int &index, QVector <int> path);
    void visualize_searching(QVector <int> stored_path);


};

#endif // CELLS_LOGIC_H
