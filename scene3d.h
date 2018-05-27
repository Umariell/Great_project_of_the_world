#pragma once
#include "wireframematerial.h"
#include "solver.h"
#include <QLayout>
#include <QVector3D>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <QTreeWidgetItem>


class Scene3D : public Qt3DCore::QEntity
{
    Q_OBJECT
private:
    Qt3DExtras::Qt3DWindow *view;
    WireframeMaterial *current_mat = nullptr;
    void createHelperArrows();
    QEntity* createArrowEntity(const QString &, const QColor &, const QMatrix4x4 &, const QVector3D &axispos);

public:
    Scene3D(QLayout *layout);
    WireframeMaterial* add_ellipsoid(QTreeWidgetItem *item, const Solver *solver);
    void setCurrent(WireframeMaterial* mat);
};
