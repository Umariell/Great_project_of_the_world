#include "ellipse.h"
#include "solver.h"


Ellipse::Ellipse(Solver *solver)
{
    index = solver->current_index;
    z = solver->y;
    x = solver->x;
    y = solver->z; // переобозначение для 2D-проекции
    a = solver->a_pro;
    b = solver->b_pro;
    S = solver->S_pro;
    alpha = solver->alpha;
    beta = solver->beta;
    beta_D = solver->beta_D;

    bbox_center = solver->y;

    // Для оптимизации, чтобы не пересчитывать тысячи раз одно и то же
    sin_beta = sin(beta);
    cos_beta = cos(beta);
    // деление выполняется медленнее, чем умножение
    a_2 = 1.0/pow(a, 2);
    b_2 = 1.0/pow(b, 2);

    {
        // вид сбоку
        dbl uy = a * sin(alpha);
        dbl vy = b * sin(alpha + PI/2);
        bbox_halfheight = sqrt(uy*uy + vy*vy);
    }

    // вид снизу
    dbl ux = a * cos_beta;
    dbl uy = a * sin_beta;
    dbl vx = b * cos(beta + PI/2);
    dbl vy = b * sin(beta + PI/2);

    rect_halfwidth = sqrt(ux*ux + vx*vx);
    rect_halfheight = sqrt(uy*uy + vy*vy);
}

bool Ellipse::check_overlay(Ellipse *other)
{
    dbl loc_bbox_center = abs(bbox_center - other->bbox_center);

    dbl delta_L = abs(bbox_halfheight - abs(loc_bbox_center - other->bbox_halfheight));

    if (delta_L > DEPTH)
        return false;

    if (x - rect_halfwidth > other->x + other->rect_halfwidth + DEPTH)
        return false;

    if (x + rect_halfwidth < other->x - other->rect_halfwidth - DEPTH)
        return false;

    if (y + rect_halfheight < other->y - other->rect_halfheight - DEPTH)
        return false;

    if (y - rect_halfheight > other->y + other->rect_halfheight + DEPTH)
        return false;

    return true;
}

bool Ellipse::check_point(dbl px, dbl py)
{
    if (x - rect_halfwidth > px)
        return false;

    if (x + rect_halfwidth < px)
        return false;

    if (y + rect_halfheight < py)
        return false;

    if (y - rect_halfheight > py)
        return false;

    dbl tmpX = (px-x)*cos_beta - (py-y)*sin_beta; // тут минус?
    dbl tmpY = (py-y)*cos_beta + (px-x)*sin_beta; // а почему тут плюс?
    return (pow(tmpX, 2) * a_2 + pow(tmpY, 2) * b_2) <= 1.0;
}
