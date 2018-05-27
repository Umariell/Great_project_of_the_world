#pragma once
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QPickEvent>
#include <QTreeWidgetItem>



class WireframeMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT

public:
    explicit WireframeMaterial(Qt3DCore::QNode *parent = nullptr);

    QTreeWidgetItem *tree_item;
    Qt3DRender::QEffect *new_effect;
    Qt3DRender::QTechnique *technique;
    Qt3DRender::QRenderPass *firstPass;
    Qt3DRender::QShaderProgram *shader;
    Qt3DRender::QFilterKey *filterKey;
    Qt3DRender::QParameter *parameter;

public slots:
    void pickMesh(Qt3DRender::QPickEvent*);
};
