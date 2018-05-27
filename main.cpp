/**
 * Даны параметры эллипсоида(x, y, z, a, b, с, угол наклона альфа). Положим b = c, так как мы предполагаем,
 * что эллипсоид только вращается. Необходимо рассчитать площадь проекции данного эллипсоида
 * (проекция - есть эллипс с полуосями a_pro и b_pro) и перевести из метров квадратных в градусы квадратные.
 */

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include "mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString parameters_path = QDir::currentPath() + "/1.txt";
    if (!QFile::exists(parameters_path)) {
        QMessageBox mbox(QMessageBox::Warning, "Внимание", "Файл Parameters.exe не найден!"
                         "\nПроверьте, чтобы он был расположен в каталоге с exe файлом.");
        return mbox.exec();
    }

    MainWindow window(parameters_path);
    window.show();
    return app.exec();
}
