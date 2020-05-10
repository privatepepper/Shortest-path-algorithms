#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>

#define wall 2;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->setEditable(true);
    ui->comboBox->lineEdit()->setReadOnly(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox->addItem("Breadth-first Search");
    ui->comboBox->addItem("Dijkstra's algorithm");
    ui->comboBox->addItem("Depth-first Searsh");
    ui->comboBox->addItem("A* Search");
    ui->comboBox->addItem("Heuristic Search");
    for (int i = 0; i < ui->comboBox->count(); i++){
        ui->comboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    // colors
    inner_cells_brush = QBrush(QColor(49, 62, 80));//
    start_brush = QBrush(QColor(155, 197, 61));
    end_brush = QBrush(QColor(229, 89, 52));
    path_finding_visualization = QBrush(QColor(0, 48, 73));
    shortest_path_visualization = QBrush(QColor(224, 251, 252));
    walls_brush = QBrush(QColor(2, 24, 43));


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    initialize_scene();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_cells()));
    timer->start(timer_speed);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(change_speed()));
}

void MainWindow::initialize_scene()
{
    rect = new QGraphicsRectItem(0, 0,800, 600);
    scene->addItem(rect);

    QPen rect_borders = QPen(Qt::black);
    rect_borders.setWidth(10);
    rect->setPen(rect_borders);

    initialize_cells();
}

void MainWindow::reset_cells()
{
    vec.initialize_cells();
    cells_selected = 0;
    add_edge_one_time = true;
    boolean_start = false;

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
            inner_cell->setBrush(inner_cells_brush);
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
                    cells[y][x]->setBrush(start_brush);
                    cells_selected++;
                }
                if (cells[y][x]->isSelected() && cells_selected == 1 && vec.cells[y][x] == 0){
                    vec.cells[y][x] = 5;
                    cells[y][x]->setBrush(end_brush);
                    cells_selected++;
                }
            }
        }
    }
    if (boolean_start){
        if (add_edge_one_time){
            vec.add_eges();
            add_edge_one_time = false;
        }

        vec.update_cells(ui->comboBox->lineEdit()->text());
        for (int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){

                if (vec.cells[y][x] == 1){
                    cells[y][x]->setBrush(path_finding_visualization);
                }
                // shortest path
                if (vec.cells[y][x] == 3){
                    cells[y][x]->setBrush(shortest_path_visualization);
                }
            }
        }
    }
}

void MainWindow::change_speed(){

    timer_speed = ui->horizontalSlider->value();
    timer->start(timer_speed);

}

void MainWindow::on_pushButton_clicked(){

    scene->clear();
    initialize_scene();
    initialize_cells();
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Space){

        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){

                if (cells[y][x]->isUnderMouse()){
                    cells[y][x]->setBrush(walls_brush);
                    cells[y][x]->setPen(Qt::NoPen);
                    vec.cells[y][x] = wall;
                }

            }
        }
    }

}



void MainWindow::on_pushButton_2_clicked()
{
    boolean_start = true;
}

// fix clear button




