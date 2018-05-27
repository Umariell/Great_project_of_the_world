#pragma once
#include "common.h"


class GroupEllipses
{
public:
    std::vector<Ellipse*> ellipsis;

    dbl upperLeftX, upperLeftY;
    dbl bottomRightX, bottomRightY;

    GroupEllipses(Ellipse *new_ellipse);
    bool check_overlay(Ellipse *other);
    void add_ellipse(Ellipse *new_ellipse);
    dbl find_S();
    dbl find_L();
    dbl find_omega();
};
