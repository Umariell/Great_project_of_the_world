#include "groupellipses.h"
#include "ellipse.h"


GroupEllipses::GroupEllipses(Ellipse *new_ellipse)
{
    ellipsis.push_back(new_ellipse);
    upperLeftX = new_ellipse->x - new_ellipse->rect_halfwidth;
    upperLeftY = new_ellipse->y + new_ellipse->rect_halfheight;
    bottomRightX = new_ellipse->x + new_ellipse->rect_halfwidth;
    bottomRightY = new_ellipse->y - new_ellipse->rect_halfheight;
}

bool GroupEllipses::check_overlay(Ellipse *other)
{
    for (auto ellipse : ellipsis)
        if (ellipse->check_overlay(other))
            return true;
    return false;
}

void GroupEllipses::add_ellipse(Ellipse *new_ellipse)
{
    ellipsis.push_back(new_ellipse);
    upperLeftX = min(upperLeftX, new_ellipse->x - new_ellipse->rect_halfwidth);
    upperLeftY = max(upperLeftY, new_ellipse->y + new_ellipse->rect_halfheight);
    bottomRightX = max(bottomRightX, new_ellipse->x + new_ellipse->rect_halfwidth);
    bottomRightY = min(bottomRightY, new_ellipse->y - new_ellipse->rect_halfheight);
}

dbl GroupEllipses::find_S()
{
    if (ellipsis.size() == 1) {
        return ellipsis[0]->S;
    }

    // площадь прямоугольника группы
    dbl rect_S = (bottomRightX - upperLeftX) * (upperLeftY - bottomRightY);

    // шаг разбиения сетки
    // сетка 5000x5000 для любой группы эллипсов
    const size_t step_count = 5000;
    dbl step_x = (bottomRightX - upperLeftX) / (dbl)step_count;
    dbl step_y = (upperLeftY - bottomRightY) / (dbl)step_count;

    size_t cnt = 0;

    for (size_t i = 0; i < step_count; i++)
        for (dbl j = 0; j < step_count; j++) {
            dbl x = upperLeftX + i*step_x;
            dbl y = bottomRightY + j*step_y;
            for (auto ellipse : ellipsis) {
                if (ellipse->check_point(x, y)) {
                    cnt++;
                    break;
                }
            }
        }

    dbl full_cnt = step_count*step_count;

    return ((dbl)cnt / full_cnt) * rect_S;
}

dbl GroupEllipses::find_L()
{
    dbl x, y, z(0.0);

    x = (upperLeftX + bottomRightX)/2;
    y = (upperLeftY + bottomRightY)/2;

    for (auto ellipse : ellipsis)
        z += ellipse->z;

    z /= ellipsis.size();

    return sqrt(x*x+y*y+z*z);
}

dbl GroupEllipses::find_omega()
{
    return (180/PI)*(180/PI)*find_S()/pow(find_L(), 2);
}
