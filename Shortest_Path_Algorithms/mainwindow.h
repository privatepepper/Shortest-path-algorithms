#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QWidget>
#include "cells_logic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    cells_logic vec;

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
    int cells_selected = 0;

    QTimer *timer;

private slots:

    void update_cells();
};
#endif // MAINWINDOW_H
