#pragma once
#include <QGraphicsView>
#include <QWheelEvent>
#include <qmath.h>
#include "ellipse.h"


class Scene2D : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Scene2D(QWidget *parent = nullptr);
    void add_ellipse(const Ellipse *ellipse, const QString &name);
    void add_groups(const Solver *solver);

private:
    const double M = 100.0;
    QGraphicsScene *scene_for_view;
    void wheelEvent(QWheelEvent* event);
};
