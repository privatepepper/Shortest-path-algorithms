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

   // void update_cells();

};

#endif // CELLS_LOGIC_H
