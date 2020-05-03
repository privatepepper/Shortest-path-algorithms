#include "cells_logic.h"

#include <QTimer>

cells_logic::cells_logic()
{

}

void cells_logic::initialize_cells()
{
    cells.resize(cells_width * cells_height);

    for (int y = 0; y < cells_height; y++){
        for (int x = 0; x < cells_width; x++){
            cells[y].push_back(0);
        }
    }
}



// make update_cell function which will use the graph functions, and update_cell will be called in gui with Qtimer
//



