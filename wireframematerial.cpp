#include "wireframematerial.h"
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QParameter>
#include <QUrl>
#include <QVector4D>
#include <QVector3D>
#include "scene3d.h"


using namespace Qt3DRender;


WireframeMaterial::WireframeMaterial(Qt3DCore::QNode *parent) : Qt3DRender::QMaterial(parent)
{
    new_effect = new QEffect(this);
    technique = new QTechnique(new_effect);
    firstPass = new QRenderPass(technique);
    shader = new QShaderProgram(firstPass);
    filterKey = new QFilterKey(technique);

    shader->setVertexShaderCode(QShaderProgram::loadSource(QUrl("qrc:/shaders/robustwireframe.vert")));
    shader->setFragmentShaderCode(QShaderProgram::loadSource(QUrl("qrc:/shaders/robustwireframe.frag")));
    shader->setGeometryShaderCode(QShaderProgram::loadSource(QUrl("qrc:/shaders/robustwireframe.geom")));

    technique->graphicsApiFilter()->setApi(QGraphicsApiFilter::OpenGL);
    technique->graphicsApiFilter()->setMajorVersion(3);
    technique->graphicsApiFilter()->setMinorVersion(3);
    technique->graphicsApiFilter()->setProfile(QGraphicsApiFilter::CoreProfile);
    firstPass->setShaderProgram(shader);

    filterKey->setName(QStringLiteral("renderingStyle"));
    filterKey->setValue(QStringLiteral("forward"));

    technique->addParameter(new QParameter("light.position", QVector4D(0.0, 0.0, 0.0, 1.0)));
    technique->addParameter(new QParameter("light.intensity", QVector3D( 1.0, 1.0, 1.0 )));
    technique->addParameter(new QParameter("line.width", 0.1));
    technique->addParameter(new QParameter("line.color", QVector4D( 1.0, 1.0, 1.0, 1.0 )));

    technique->addFilterKey(filterKey);
    technique->addRenderPass(firstPass);

    new_effect->addParameter(new QParameter("ka", QVector3D( 0.1f, 0.1f, 0.1f )));
    parameter = new QParameter("kd", QVector3D( 0.7f, 0.7f, 0.7f ));
    new_effect->addParameter(parameter);
    new_effect->addParameter(new QParameter("ks", QVector3D( 0.95f, 0.95f, 0.95f )));
    new_effect->addParameter(new QParameter("shininess", 150.0f));
    new_effect->addTechnique(technique);

    setEffect(new_effect);
}

void WireframeMaterial::pickMesh(Qt3DRender::QPickEvent*)
{
    Scene3D *s = reinterpret_cast<Scene3D *>(parentNode()->parentNode());
    s->setCurrent(this);

    for (auto it : tree_item->treeWidget()->selectedItems()) {
        it->setSelected(false);
    }
    tree_item->setSelected(true);
}

