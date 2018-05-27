#ifndef ADVANCEDCAMERA_H
#define ADVANCEDCAMERA_H

#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QLogicalDevice>
#include <Qt3DLogic/QFrameAction>



class AdvancedCameraCtrl : public Qt3DExtras::QOrbitCameraController
{
    Q_OBJECT
public:
    explicit AdvancedCameraCtrl(QEntity *parent, Qt3DRender::QCamera *ccamera);
private:
    Qt3DLogic::QFrameAction *frameAction;

    void handleTriggered(float);
};

#endif // ADVANCEDCAMERA_H
