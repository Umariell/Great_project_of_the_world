#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ellipse.h"
#include "groupellipses.h"
#include <QElapsedTimer>
#include <QMessageBox>


MainWindow::MainWindow(const QString &parameters_path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget_2->setColumnWidth(0, 170);
    ui->treeWidget_2->setColumnWidth(1, 70);
    ui->treeWidget_2->setColumnWidth(2, 70);
    setWindowState(Qt::WindowMaximized);
    scene_3d = new Scene3D(ui->tab_3d->layout());

    solver = new Solver(parameters_path.toStdString());

    while (true) {
        int flag = solver->readParamEl();

        if (flag == 2) {
            QMessageBox box;
            box.setWindowTitle("Error");
            box.setText("y is too small");
            box.setIcon(QMessageBox::Critical);
            box.exec();
            exit(EXIT_FAILURE);
        } else if (flag != 1)
            break;

        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);

        QString name = QString("Эллипсоид %1").arg(ui->treeWidget->topLevelItemCount());

        item->setText(0, name);

        addToTree(item, "x", solver->x);
        addToTree(item, "y", solver->y);
        addToTree(item, "z", solver->z);
        addToTree(item, "a", solver->a);
        addToTree(item, "b", solver->b);
        addToTree(item, "alpha", solver->alpha_D);
        addToTree(item, "beta", solver->beta_D);
        addToTree(item, "a_pro", solver->a_pro);
        addToTree(item, "b_pro", solver->b_pro);
        addToTree(item, "S_pro", solver->S_pro);
        addToTree(item, "L", solver->L);
        addToTree(item, "omega", solver->omega_D);

        scene_3d->add_ellipsoid(item, solver);
        ui->scene_2d->add_ellipse(solver->current_ellipse, name);

        ui->treeWidget->addTopLevelItem(item);
    }
    ui->scene_2d->add_groups(solver);

    QElapsedTimer timer;
    timer.start();
    ui->common_s_value->setText(QString::number(solver->find_common_S()));
    qDebug() << "Рассчет площади занял:" << timer.elapsed();

    for (auto it_group : solver->groups) {
        if (!it_group)
            continue;
        auto item = new QTreeWidgetItem(ui->treeWidget_2);
        QString name = QString("Группа %1").arg(ui->treeWidget_2->topLevelItemCount());
        item->setText(0, name);
        item->setText(1, QString::number(it_group->find_S()));
        item->setText(2, QString::number(it_group->find_L()));
        item->setText(3, QString::number(it_group->find_omega()));

        for (auto it : it_group->ellipsis) {
            auto subItem = new QTreeWidgetItem(item);
            subItem->setText(0, QString("Эллипсоид %0").arg(it->index));
            //subItem->setText(1, QString::number(data, 'f')); // f - добавляет точность
        }
    }

}

//формирование списка эллипсоидов
void MainWindow::addToTree(QTreeWidgetItem *item, QString name, double data)
{
    QTreeWidgetItem *subItem = new QTreeWidgetItem(item);
    subItem->setText(0, name);
    subItem->setText(1, QString::number(data, 'f')); // f - добавляет точность
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // Если текущий выбранный пункт равен предыдущему нажатому, то выходим из функции
    if (current == previous) return;

    // Если текущий выбранный пункт не является заголовком вида "Элиипсоид ..", то также выходим
    if (current->parent()) return;

    // Выделяем пункт в списке
    current->setSelected(true);

    // Раскрываем список(закомментировано, пока не нужно)
    //current->setExpanded(true);

    // С каждым пунктом меню связан материал (связывается выше - scene->addEllipsoid)
    // Здесь мы его получаем
    WireframeMaterial* mat = current->data(0, Qt::UserRole).value<WireframeMaterial*>();

    // Делаем полученный материал текущим через метод Scene3D
    scene_3d->setCurrent(mat);
}
