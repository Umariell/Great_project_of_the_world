#include "solver.h"
#include "groupellipses.h"
#include "ellipse.h"


Solver::Solver(const string &filepath)
{
    file.open(filepath);
    if (!file) {
        cout << "File Parameters.txt not found!" << endl;
        return;
    }
}


//function for reading ellipsoid parameters from a file
int Solver::readParamEl()
{
    if (!file || file.eof()) {
        return 0; // end file
    }

    file >> x >> y >> z >> alpha_D >> beta_D >> a >> b;

    // произошел сбой при считывании из файла
    if (file.fail()) {
        return 0; // also end file
    }

    if (y < 1) {
        cout << "Warning: y is too small" << endl;
        return 2; // error value
    }

    cout << "ELLIPSOID: " << endl;
    cout << "  X: " << x << " m" << endl << "  Y: " << y << " m" << endl << "  Z: " << z << " m" << endl;
    cout << "  alpha: " << alpha_D << " (in gradus)" <<"  beta: " << beta_D << " (in gradus)"<< endl;
    alpha = GradusToRadian(alpha_D);
    cout<<"  alpha: " << alpha << " (in radian)" << endl;
    beta = GradusToRadian(beta_D);
    cout<<"  beta: " << beta << " (in radian)" << endl;
    cout<<  "  a: " << a << " m" << endl << "  b: " << b << " m"<<endl;
    cout<<endl;
    calculationOfSquare();
    cout << endl;
    theDistance();

    current_index++;
    current_ellipse = new Ellipse(this);

    GroupEllipses *tmpGroup = nullptr;
    for (size_t i = 0; i < groups.size(); i++) {
        if (groups[i] && groups[i]->check_overlay(current_ellipse)) {
            groups[i]->add_ellipse(current_ellipse);
            if (!tmpGroup) {
                tmpGroup = groups[i];
            } else {
                for (auto ellipse : groups[i]->ellipsis) {
                    groups[i]->add_ellipse(ellipse);
                }
                delete groups[i];
                groups[i] = nullptr;
            }
        }
    }
    if (!tmpGroup) {
        groups.push_back(new GroupEllipses(current_ellipse));
    }

    return 1; // ok
}

//function of calculating the square of the ellipsoid projection (ellipse)
void Solver::calculationOfSquare()
{
    dbl delta = 0;
    b_pro = b;
    delta = a - b;
    a_pro = b + delta*cos(alpha);
    S_pro = PI*a_pro*b_pro;

    cout << "ELLIPS: " << endl;
    cout << "  a_pro: " << a_pro << " m " << endl << "  b_pro: " << b_pro << " m " << endl;
    cout << fixed << "  S_pro: " << S_pro << " m^2 " << endl;
}

//method of conversion from radians to gradus
dbl Solver::GradusToRadian(dbl angle)
{
    return angle*(PI/180);
}

//method of conversion from radians^2 to gradus^2
dbl Solver::Radian2ToGradus2(dbl omega)
{
    return omega*(180/PI)*(180/PI);
}

//The function of finding the distance from the station to the center of the ellipsoid
void Solver::theDistance()
{
    //dbl L;                      //the distance
    //dbl omega;                  //solid angle

    L=sqrt(x*x+y*y+z*z);
    omega=S_pro/(x*x+y*y+z*z);
    cout << "DISTANCE: " << endl;
    cout << fixed << "  L: " << L << " m " << endl << "  omega: " << omega << " (in radian^2)"<< endl;
    omega_D = Radian2ToGradus2(omega);
    cout<<"  omega: " << omega_D << " (in gradus^2)" << endl;
}


dbl Solver::find_common_S()
{
    dbl result = 0.0;
    for (auto group : groups) {
        if (group)
            result += group->find_S();
    }
    return result;
}
/*
dbl Solver::find_common_angle()
{
    dbl result = 0.0;
    L=sqrt(x*x+y*y+z*z);
    omega=S_pro/(x*x+y*y+z*z);
    return result;
}
*/
