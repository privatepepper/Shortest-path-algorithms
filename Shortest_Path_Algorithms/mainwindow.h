#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QWidget>
#include "cells_logic.h"
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Ui::MainWindow *ui;

    cells_logic vec;
    //Graph my_graph;

    int height = vec.cells_height;
    int width = vec.cells_width;

    int inner_cell_width = 800 / width;
    int inner_cell_height = 600 / height;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    void initialize_scene();
    void initialize_cells();
    void reset_cells();

    QVector <QVector < QGraphicsRectItem* > > cells;
    QVector <QVector < QGraphicsEllipseItem* > > ellipses;
    int cells_selected = 0;

    QTimer *timer;
    int timer_speed = 0;

    bool boolean_start = false;
    bool add_edge_one_time = true;
    bool tree = false;
    bool tree1 = false;

    // colors
    QBrush inner_cells_brush;
    QBrush start_brush;
    QBrush end_brush;
    QBrush path_finding_visualization;
    QBrush shortest_path_visualization;
    QBrush walls_brush;

    void reset_colors();

    void search_start_end();



private slots:

    void update_cells();

    void change_speed();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_radioButton_clicked();

protected:

    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
