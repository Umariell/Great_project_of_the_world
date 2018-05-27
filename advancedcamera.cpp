#include "advancedcamera.h"
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DCore>


AdvancedCameraCtrl::AdvancedCameraCtrl(QEntity *parent, Qt3DRender::QCamera *ccamera) : QOrbitCameraController(parent)
{
    frameAction = new Qt3DLogic::QFrameAction;

    QObject::connect(frameAction, &Qt3DLogic::QFrameAction::triggered,
                     this, &AdvancedCameraCtrl::handleTriggered);

    addComponent(frameAction);

    setLinearSpeed( 50.0f );
    setLookSpeed( 180.0f );
    setCamera(ccamera);

    camera()->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.01f, 1000.0f);
    camera()->setPosition(QVector3D(0, -20.0f, 0.0001f));
    camera()->setViewCenter(QVector3D(0, 0, 0));
}


void AdvancedCameraCtrl::handleTriggered(float)
{
    camera()->setViewCenter(QVector3D(0, 0, 0));
}
