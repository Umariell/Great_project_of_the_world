#pragma once
#include "common.h"


class Ellipse
{
public:
    int index;
    dbl z;

    dbl bbox_halfheight;
    dbl bbox_center;

    dbl rect_halfheight;
    dbl rect_halfwidth;

    dbl x, y, a, b;
    dbl alpha, beta, beta_D;
    dbl S;

    // Для оптимизации
    dbl sin_beta, cos_beta, a_2, b_2;

    Ellipse(Solver *solver);
    bool check_overlay(Ellipse *other);
    bool check_point(dbl px, dbl py);
};
