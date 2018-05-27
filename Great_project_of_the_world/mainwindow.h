#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "scene3d.h"
#include "solver.h"


class QTreeWidgetItem;
class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &parameters_path, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Solver *solver = nullptr;
    Scene3D *scene_3d;
    Ui::MainWindow *ui;

    void addToTree(QTreeWidgetItem *item, QString name, double data);
};

#endif // MAINWINDOW_H
