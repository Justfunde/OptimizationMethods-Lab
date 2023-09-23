#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <fstream>
#include <memory>

#include <gtest/gtest.h>

#include "Methods.hpp"
/*
class Test_Ast : public ::testing::Test
{
   protected:
   AstReader reader;
   AstWriter writer;
};

TEST_F(Test_Ast, TestFile1)
{
   const auto astArr = reader.ReadFile(std::string(g_InputFileDir) + "1.txt");
   const auto res = writer.WriteBuf(astArr);
   //std::cout << res << std::endl;
   const auto etalonRes = InGetFileBuf(std::string(g_OutputFileDir) + "1.txt");
   EXPECT_EQ(res, etalonRes);
}

TEST_F(Test_Ast, TestFile2)
{
   const auto astArr = reader.ReadFile(std::string(g_InputFileDir) + "2.txt");
   const auto res = writer.WriteBuf(astArr);
   //std::cout << res;
   const auto etalonRes = InGetFileBuf(std::string(g_OutputFileDir) + "2.txt");
   EXPECT_EQ(res, etalonRes);
}

TEST_F(Test_Ast, TestFile3)
{
   const auto astArr = reader.ReadFile(std::string(g_InputFileDir) + "3.txt");
   const auto res = writer.WriteBuf(astArr);
   //std::cout << res;
   const auto etalonRes = InGetFileBuf(std::string(g_OutputFileDir) + "3.txt");
   EXPECT_EQ(res, etalonRes);
}*/

/*TEST_F(Test_Ast, TestFile4)
{
   const auto astArr = reader.ReadFile(std::string(g_InputFileDir) + "1.txt");
   const auto res = writer.WriteBuf(astArr);
   std::cout << res;
   const auto etalonRes = InGetFileBuf(std::string(g_OutputFileDir) + "1.txt");
   EXPECT_EQ(res, etalonRes);
}*/

static
double
InMathFunc(double x)
{
   return x * sin(x) + 2 * cos(x);
}

constexpr double eps = 0.001;

int32_t main(int32_t argc, char** argv)
{
   
   BruteForce bruteSolver(InMathFunc, {-6, -4}, eps);
   Dichotomy dichotomySolver(InMathFunc, {-6, -4}, eps);
   GoldenSection goldenSectionSolver(InMathFunc, {-6, -4}, eps);
   BitwiseSearch bs(InMathFunc, {-6, -4}, eps);
   std::cout << "Brute:" << bruteSolver.GetMin() << std::endl;
   std::cout << "Dich:" << dichotomySolver.GetMin() << std::endl;
   std::cout << "GoldenSec:" << goldenSectionSolver.GetMin() << std::endl;
   std::cout << "bitwise:" << bs.GetMin() << std::endl;
   //::testing::InitGoogleTest(&argc, argv);
   //return RUN_ALL_TESTS();
   return 0;
}