#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    this->setStyleSheet("background-color: rgb(39, 35, 36) ");
    scene->setBackgroundBrush(QColor(39, 35, 36));

    initialize_scene();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_cells()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_scene()
{
    rect = new QGraphicsRectItem(0, 0,800, 600);
    scene->addItem(rect);

    QPen rect_borders = QPen(Qt::black);
    rect_borders.setWidth(5);
    rect->setPen(rect_borders);

    initialize_cells();
}

void MainWindow::reset_cells()
{
    vec.initialize_cells();

    // for testing purposes
    //QMessageBox::about(this, "test", vec.s);

    cells.clear();
    cells.resize(width * height);

    for (int y = 0; y < height; y++){
        QGraphicsRectItem *nothing;
        for (int x = 0; x < width; x++){
            cells[y].push_back(nothing);
        }
    }

}

void MainWindow::initialize_cells()
{
    reset_cells();

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            QGraphicsRectItem *inner_cell = new QGraphicsRectItem(x * inner_cell_width, y * inner_cell_height, inner_cell_width, inner_cell_height, rect);
            inner_cell->setFlag(QGraphicsItem::ItemIsSelectable);
            cells[y][x] = inner_cell;
        }
    }
}





void MainWindow::update_cells()
{
    if (cells_selected < 2){
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                if (cells[y][x]->isSelected() && cells_selected == 0 && vec.cells[y][x] == 0){
                    vec.cells[y][x] = -5;
                    cells[y][x]->setBrush(Qt::green);
                    cells_selected++;
                }
                if (cells[y][x]->isSelected() && cells_selected == 1 && vec.cells[y][x] == 0){
                    vec.cells[y][x] = 5;
                    cells[y][x]->setBrush(Qt::red);
                    cells_selected++;
                }
            }
        }
    }
    if (cells_selected >= 2){
        vec.update_cells();
        for (int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                if (vec.cells[y][x] == 1){
                    cells[y][x]->setBrush(Qt::blue);
                }

                if (vec.cells[y][x] == 2){
                    cells[y][x]->setBrush(Qt::white);
                }
            }
        }
    }
}

