#pragma once
#include <functional>
#include <utility>



using MathFunction = std::function<double(double)>;
using CoordinateDiap = std::pair<double, double>;

class MinCalculator
{

   public:
   MinCalculator(
      const MathFunction F,
      const CoordinateDiap& Diap,
      double Eps ) 
      : mathFunction(F)
      , xDiap(Diap)
      , eps(Eps) {}

   virtual
   double
   GetMin() const = 0;

   protected:
   MathFunction mathFunction;
   CoordinateDiap xDiap; 
   double eps;
};


class BruteForce : public MinCalculator
{
   public:
   BruteForce(const MathFunction F, const CoordinateDiap& Diap, double Eps) : MinCalculator(F, Diap, Eps) {}

   virtual
   double
   GetMin() const override final;
};


class Dichotomy : public MinCalculator
{
   public:
   Dichotomy(const MathFunction F, const CoordinateDiap& Diap, double Eps) : MinCalculator(F, Diap, Eps) {}

   virtual
   double
   GetMin() const override final;
};

class GoldenSection  : public MinCalculator
{
   public:
   GoldenSection(const MathFunction F, const CoordinateDiap& Diap, double Eps) : MinCalculator(F, Diap, Eps) {}

   virtual
   double
   GetMin() const override final;
};

class BitwiseSearch  : public MinCalculator
{
   public:
   BitwiseSearch(const MathFunction F, const CoordinateDiap& Diap, double Eps) : MinCalculator(F, Diap, Eps) {}

   virtual
   double
   GetMin() const override final;
};