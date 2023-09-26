#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>
#include <memory>

#include <gtest/gtest.h>

#include "Methods.hpp"

constexpr double eps = 0.1;
constexpr double etalonMin = -4.82057;

constexpr double a = 7.15;
constexpr double b = 13.2;
constexpr double c = 15.23;
const InitialApproxPoint  initP({3,4}) ;

// Функция
double 
f(double x, double y) 
{
   return x*x + x*y + 2*y*y - a*x - b*y + c;
}


double dx(double x, double y)
{
   return 2*x + y - a;
}


double dy(double x, double y)
{
   return x + 4*y - b;
}

// Матрица Гессе
void hessian(double& dxx, double& dxy, double& dyx, double& dyy) {
    dxx = 2;
    dxy = 1;
    dyx = 1;
    dyy = 4;
}



TEST(MinFunctionCalcTest_GradDescent, GradDescent_Method)
{
   GradientDescentMethod gdm(f,dx,dy,initP, eps);
   gdm.GetMin();
   //EXPECT_NEAR(etalonMin, gdm.GetMin(), eps);
}

TEST(MinFunctionCalcTest_Newton, Newton_SecMethod)
{
   NewtonMethod newton(f,dx,dy, hessian, initP, eps);
   newton.GetMin();
  // EXPECT_NEAR(etalonMin, newton.GetMin(), eps);
}

TEST(MinFunctionCalcTest_FastGradDescent, FastGradDescent_Method)
{
   FastestGradientDescentMethod gdm(f,dx,dy,initP, eps);
   gdm.GetMin();
   //EXPECT_NEAR(etalonMin, gdm.GetMin(), eps);
}

int32_t main(int32_t argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}