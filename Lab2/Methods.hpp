#pragma once
#include <functional>
#include <utility>



using MathFunction = std::function<double(double)>;
using CoordinateDiap = std::pair<double, double>;

class MinCalculator
{
   protected:
   MathFunction f;
   MathFunction df;
   CoordinateDiap xDiap; 
   double eps;

   public:
   MinCalculator(
      const MathFunction F,
      const MathFunction dF,
      const CoordinateDiap& Diap,
      double Eps ) 
      : f(F)
      , df(dF)
      , xDiap(Diap)
      , eps(Eps) {}

   virtual
   double
   GetMin() const = 0;
};


class BolzanoMethod : public MinCalculator
{
   public:
   BolzanoMethod(
      const MathFunction F,
      const MathFunction dF,
      const CoordinateDiap& Diap,
      double Eps) : MinCalculator(F, dF, Diap, Eps) {}

   virtual
   double
   GetMin() const override final;
};


class ChordMethod : public MinCalculator
{
   public:
   ChordMethod(
      const MathFunction F,
      const MathFunction dF,
      const CoordinateDiap& Diap,
      double Eps) : MinCalculator(F, dF, Diap, Eps) {}


   virtual
   double
   GetMin() const override final;
};

class NewtonMethod  : public MinCalculator
{
   protected:
   MathFunction d2f;
   public:

   NewtonMethod(
      const MathFunction F,
      const MathFunction dF,
      const MathFunction d2F,
      const CoordinateDiap& Diap,
      double Eps) 
      : MinCalculator(F, dF, Diap, Eps)
      , d2f(d2F) {}


   virtual
   double
   GetMin() const override final;

};

