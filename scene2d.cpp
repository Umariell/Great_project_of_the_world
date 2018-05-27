#include "scene2d.h"
#include "ellipse.h"
#include "solver.h"
#include "groupellipses.h"
#include <QGraphicsSimpleTextItem>
#include <QWheelEvent>
#include <qmath.h>


Scene2D::Scene2D(QWidget *parent) : QGraphicsView(parent)
{
    scene_for_view = new QGraphicsScene(this);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setScene(scene_for_view);
    // Добавить линии для осей координат
    scene_for_view->addLine(-10000, 0, 20000, 0);
    scene_for_view->addLine(0, -10000, 0, 20000);
}

//масштаб
void Scene2D::wheelEvent(QWheelEvent* event)
{
    qreal scaleFactor = qPow(2.0, event->delta() / 240.0);          //How fast we zoom
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if(0.05 < factor && factor < 10)                                //Zoom factor limitation
    scale(scaleFactor, scaleFactor);
}

// Добавляет 2D проекцию
void Scene2D::add_ellipse(const Ellipse *ellipse, const QString &name)
{
    qreal x = ellipse->x * M;
    qreal y = -ellipse->y * M;
    qreal w = ellipse->a * M * 2.0;
    qreal h = ellipse->b * M * 2.0;

    auto elItem = scene_for_view->addEllipse(x-w/2, y-h/2, w, h, QPen(QColor("black")));
    elItem->setTransformOriginPoint(x, y);
    elItem->setRotation(ellipse->beta_D);

    QGraphicsSimpleTextItem *item = scene_for_view->addSimpleText(name);
    item->setFont(QFont("Century Gothic", 40));
    item->setPos(x, y);
}

void Scene2D::add_groups(const Solver *solver)
{
    for (auto group : solver->groups) {
        if (!group)
            continue;
        qreal x = group->upperLeftX * M;
        qreal y = -group->upperLeftY * M;
        qreal w = (group->bottomRightX - group->upperLeftX) * M;
        qreal h = (group->upperLeftY - group->bottomRightY) * M;
        scene_for_view->addRect(x, y, w, h);
    }
}
