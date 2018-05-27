#include "scene3d.h"
#include "ontopeffect.h"
#include "advancedcamera.h"
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include <QWidget>


using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;


Scene3D::Scene3D(QLayout *layout) : QEntity()
{
    view = new Qt3DWindow();
    layout->addWidget(QWidget::createWindowContainer(view));

    // For camera controls
    AdvancedCameraCtrl *camController = new AdvancedCameraCtrl(this, view->camera());


    QEntity *lightEntity = new QEntity(this);
    QPointLight *light = new QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(camController->camera()->position());
    lightEntity->addComponent(lightTransform);



    view->setRootEntity(this);
    createHelperArrows();
}

QEntity* Scene3D::createArrowEntity(const QString &axisname,
                                    const QColor &color,
                                    const QMatrix4x4 &matrix,
                                    const QVector3D &axispos)
{
    QEntity *arrow = new QEntity(this);

    QMaterial *material = new QMaterial(this);
    material->setEffect(new OnTopEffect());
    material->addParameter(new QParameter(QStringLiteral("handleColor"), color));

    QMesh *mesh = new QMesh();
    mesh->setSource(QUrl(QStringLiteral("qrc:/arrow.obj")));

    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
    transform->setMatrix(matrix);
    transform->setScale(3);

    arrow->addComponent(mesh);
    arrow->addComponent(material);
    arrow->addComponent(transform);

    QExtrudedTextMesh *text_mesh = new QExtrudedTextMesh(arrow);
    text_mesh->setText(axisname);
    text_mesh->setDepth(0.01f);
    text_mesh->setFont(QFont("Calibri"));

    QEntity *textArrows = new QEntity(this);
    textArrows->addComponent(text_mesh);
    textArrows->addComponent(material);

    transform = new Qt3DCore::QTransform();
    transform->setTranslation(axispos);

    textArrows->addComponent(transform);

    return arrow;
}

void Scene3D::createHelperArrows()
{
    QEntity *helperArrows = new QEntity(this);

    // Ось Y
    QMatrix4x4 matrix;
    QEntity *arrow = createArrowEntity(
                "Y",
                QColor("#50C878"),
                matrix,
                QVector3D(0, 5, 0));

    // Ось Z
    matrix.rotate(90.0f, QVector3D(1.0f, 0.0f, 0.0f));
    arrow = createArrowEntity(
                "Z",
                QColor("#6600FF"),
                matrix,
                QVector3D(0, 0, 5));

    // Ось X
    matrix = QMatrix();
    matrix.rotate(-90.0f, QVector3D(0.0f, 0.0f, 1.0f));
    arrow = createArrowEntity(
                "X",
                QColor("#FC2847"),
                matrix,
                QVector3D(5, 0, 0));

    Qt3DCore::QTransform *helperArrowsTransform = new Qt3DCore::QTransform();
    helperArrows->addComponent(helperArrowsTransform);
}

WireframeMaterial* Scene3D::add_ellipsoid(QTreeWidgetItem *item, const Solver *solver)
{
    QMatrix4x4 matrix = QMatrix4x4();
    matrix.translate(
                solver->x,
                solver->y,
                solver->z
                );
    matrix.rotate(solver->beta_D, QVector3D(0, 1, 0));
    matrix.rotate(solver->alpha_D, QVector3D(0, 0, 1));
    matrix.scale(solver->a, solver->b, solver->b);

    QSphereMesh *sphereMesh = new QSphereMesh;
    sphereMesh->setRings(40);
    sphereMesh->setSlices(40);

    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();
    sphereTransform->setMatrix(matrix);

    QObjectPicker *picker = new QObjectPicker(this);

    WireframeMaterial *sphereMaterial = new WireframeMaterial();

    connect(picker, SIGNAL(clicked(Qt3DRender::QPickEvent *)), sphereMaterial, SLOT(pickMesh(Qt3DRender::QPickEvent *)));

    item->setData(0,
                  Qt::UserRole,
                  QVariant::fromValue(sphereMaterial));

    sphereMaterial->tree_item = item;;

    QEntity *sphereEntity = new QEntity(this);
    sphereEntity->addComponent(picker);
    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereMaterial);
    sphereEntity->addComponent(sphereTransform);
    return sphereMaterial;
}

void Scene3D::setCurrent(WireframeMaterial *mat)
{
    if (current_mat)
        current_mat->parameter->setValue(QColor("gray"));
    mat->parameter->setValue(QColor("#ff1940"));

    current_mat = mat;
}
