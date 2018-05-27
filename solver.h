#pragma once
#include "common.h"
#include <fstream>


class Solver
{
public:
    vector<GroupEllipses*> groups;
    Ellipse *current_ellipse; // текущий эллипс
    int current_index = 0;

    ifstream file;
    dbl x,y,z;          //xyz of ellipsoid center
    dbl alpha;          //angle of slope
    dbl beta;
    dbl alpha_D;
    dbl beta_D;
    dbl a,b;            //large and small semiaxes of ellipsoid

    dbl a_pro, b_pro;   //large and small semiaxes of ellips
    dbl S_pro;          //square of ellips

    dbl L;              //the distance
    dbl omega;          //solid angle
    dbl omega_D;        //solid angle

    Solver(const std::string &filepath);

    /**
     * функция чтения параметров эллипсоида из файла
     */
    int readParamEl();


    /**
     * функция расчета площади проекции эллипсоида
     */
    void calculationOfSquare();


    /**
     * функция нахождения расстояния от станции на Земле до эллипсоида
     */
    void theDistance();


    /**
     * метод перехода от радиан к градусам
     */
    dbl GradusToRadian(dbl angle);


    /**
     * метод перехода от радиан^2 к градусам^2
     */
    dbl Radian2ToGradus2(dbl omega);

    /**
     * метод поиска общей площади проекций эллипсоидов
     * с учетом наложений
     */
    dbl find_common_S();
};
