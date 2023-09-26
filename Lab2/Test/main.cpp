#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>
#include <memory>

#include <gtest/gtest.h>

#include "Methods.hpp"

constexpr double eps = 0.001;
constexpr double etalonMin = -4.82057;

static
double
MathFunc(double x)
{
   return x * sin(x) + 2 * cos(x);
}

static
double
D_MathFunc(double x)
{
   return x * cos(x) - sin(x);
}


static
double
D2_MathFunc(double x)
{
   return -x * sin(x);
}


TEST(MinFunctionCalcTest_Bolzano, Bolzano_Method)
{
   BolzanoMethod bolzano(MathFunc, D_MathFunc, {-6, -4}, eps );
   EXPECT_NEAR(etalonMin, bolzano.GetMin(), eps);
}

TEST(MinFunctionCalcTest_Chord, Chord_Method)
{
   ChordMethod chord(MathFunc, D_MathFunc, {-6, -4}, eps );
   EXPECT_NEAR(etalonMin, chord.GetMin(), eps);
}

TEST(MinFunctionCalcTest_Newton, Newton_SecMethod)
{
   NewtonMethod newton(MathFunc, D_MathFunc, D2_MathFunc, {-6, -4}, eps );
   EXPECT_NEAR(etalonMin, newton.GetMin(), eps);
}



int32_t main(int32_t argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
   return 0;
}