#pragma once

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>

class OnTopEffect : public Qt3DRender::QEffect
{
public:
    explicit OnTopEffect(Qt3DCore::QNode *parent = 0);
};
