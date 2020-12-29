#include <iostream>
#include <math.h>
#include <functional>
#include <utility>
using namespace std;

double EPS = 0.000001;/*
auto rk_merson(function<double(double, double, double)> func_f,
         function<double(double, double, double)> func_g,
         double t, double z1, double z2, double &dt);*/
pair<double, double> rk_merson(function<double(double, double, double)> func_f,
         function<double(double, double, double)> func_g,
         double t, double z1, double z2, double &dt)
{
    double k1{func_f(t       , z1       , z2)       *dt/3},
           m1{func_g(t       , z1       , z2)       *dt/3},
           k2{func_f(t + dt/3, z1 + k1, z2 + m1)*dt/3},
           m2{func_g(t + dt/3, z1 + k1, z2 + m1)*dt/3},
           k3{func_f(t + dt/3, z1 + k1/2 + k2/2, z2 + m1/2 + m2/2)*dt/3},
           m3{func_g(t + dt/3, z1 + k1/2 + k2/2, z2 + m1/2 + m2/2)*dt/3},
           k4{func_f(t + dt/2, z1 + k1*3/8 + 9*k3/8, z2 + m1*3/8 + 9*m3/8 )*dt/3},
           m4{func_g(t + dt/2, z1 + k1*3/8 + 9*k3/8, z2 + m1*3/8 + 9*m3/8 )*dt/3},
           k5{func_f(t + dt, z1 + k1*3/2 - 9*k3/2 + 6*k4, z2 + m1*3/2 - 9*m3/2 + 6*m4)*dt/3},
           m5{func_f(t + dt, z1 + k1*3/2 - 9*k3/2 + 6*k4, z2 + m1*3/2 - 9*m3/2 + 6*m4)*dt/3},
           new_z1{z1 + (k1 + 4*k4 +k5)/2},
           new_z2{z2 + (m1 + 4*m4 +m5)/2},
           deltak{k1 - 9/2*k3 + 4*k4 -1/2*k5},
           deltam{k1 - 9/2*m3 + 4*m4 -1/2*m5};
    if(min(deltak, deltam) > 5*EPS)
    {
        dt/=2;
        return rk_merson(func_f, func_g, t, z1, z2, dt);
    }
    if(max(deltak, deltam) < 5/32*EPS)
        dt*=2;
    return make_pair(new_z1, new_z2);
}

//auto rk4(function<double(double, double, double)> func_f,
//         function<double(double, double, double)> func_g,
//         double t, double z1, double z2, double &dt)
//{
//    double k1{func_f(t       , z1       , z2)       *dt},
//           m1{func_g(t       , z1       , z2)       *dt},
//           k2{func_f(t + dt/2, z1 + k1/2, z2 + m1/2)*dt},
//           m2{func_g(t + dt/2, z1 + k1/2, z2 + m1/2)*dt},
//           k3{func_f(t + dt/2, z1 + k2/2, z2 + m2/2)*dt},
//           m3{func_g(t + dt/2, z1 + k2/2, z2 + m2/2)*dt},
//           k4{func_f(t + dt  , z1 + k3  , z2 + m3  )*dt},
//           m4{func_g(t + dt  , z1 + k3  , z2 + m3  )*dt},
//           new_z1{z1 + (k1 + 2*k2 + 2*k3 +k4)/6},
//           new_z2{z2 + (m1 + 2*m2 + 2*m3 +m4)/6};
//    if(max(abs(z1-new_z1), abs(z2-new_z2)) < dt)
//        dt/=2;
//    return make_pair(new_z1, new_z2);
//}


int main()
{
    double A[2][2] = {{1.0, 3.0},
                      {3.0, 9.0}};
    double B[2] = {1.0, 3.0};
    const double delta = 0.8;
    const double alfa = 0.5;
    const double delta_h = 0.8;
    double t   {  10.0 },
           z1  {  0.0 },
           z2  {  0.0 },
           dt {  0.0001 };
    function<double(double, double, double)> func_f = [&A, &B, delta, alfa, delta_h](double t, double z1, double z2)
    {

        double delta_t{1/pow(t, delta)},
               alfa_t{1/pow(t, alfa)},
               h_t{1/pow(t, delta_h)};
        return (B[0] + delta_t) - ((A[0][0] + alfa_t + h_t) * z1 + (A[0][1] + h_t) * z2);
    };
    function<double(double, double, double)> func_g = [&A, &B, delta, alfa, delta_h](double t, double z1, double z2)
    {
        double delta_t{1/pow(t, delta)},
               alfa_t{1/pow(t, alfa)},
               h_t{1/pow(t, delta_h)};
        return (B[1] + delta_t) - ((A[1][0] + h_t) * z1 + (A[1][1] + alfa_t + h_t) * z2);
    };
    //double norm1 = 3/11, norm2 =
    while(dt>0.000001)
    {
        auto p = rk_merson(func_f, func_g, t, z1, z2, dt);
        if(max(abs(z1 - p.first),abs(z2 - p.second))< 0.000001)
        {
            cout<<"Нормальное решение \nz1 = 0.1\nz2 = 0.3\n";
            cout <<"Метод Рунге-Кутты-Мерсона\nz1 = " << p.first
                << "  delta = "<< abs(0.1 - p.first)<< "\nz2 = " << p.second << " delta = "
                << abs(p.second - 0.3)<< "\n";
            break;
        }
        z1 = p.first;
        z2 = p.second;
    }
   auto k =1;
}
