#pragma once
#include <functional>
#include <utility>



using MathFunction = std::function<double(double, double)>;
using HessianFunction = std::function<void(double&, double&, double&, double&)>;
using InitialApproxPoint = std::pair<double, double>;

class MinCalculator
{
   protected:
   MathFunction f;
   MathFunction dxF;
   MathFunction dyF;
   InitialApproxPoint initApprox; 
   double eps;

   public:
   MinCalculator(
      const MathFunction F,
      const MathFunction DxF,
      const MathFunction DyF,
      const InitialApproxPoint& InitApprox,
      double Eps ) 
      : f(F)
      , dxF(DxF)
      , dyF(DyF)
      , initApprox(InitApprox)
      , eps(Eps) {}

   virtual
   double
   GetMin() const = 0;
};


class GradientDescentMethod : public MinCalculator
{
   public:
   GradientDescentMethod(
      const MathFunction F,
      const MathFunction DxF,
      const MathFunction DyF,
      const InitialApproxPoint& InitApprox,
      double Eps) : MinCalculator(F, DxF, DyF, InitApprox, Eps) {}

   virtual
   double
   GetMin() const override final;
};


class FastestGradientDescentMethod : public MinCalculator
{
   public:
   FastestGradientDescentMethod(
      const MathFunction F,
      const MathFunction DxF,
      const MathFunction DyF,
      const InitialApproxPoint& InitApprox,
      double Eps) : MinCalculator(F, DxF, DyF, InitApprox, Eps) {}

   virtual
   double
   GetMin() const override final;

   private:

   // Функция одной переменной для поразрядного поиска
   double g(double alpha, double x, double y, double dx, double dy) const;
   

   double BitwiseSearch(double x, double y, double dx, double dy, double eps = 1e-6) const;
};

class NewtonMethod  : public MinCalculator
{
   protected:
   HessianFunction hessianF;
   public:

   NewtonMethod(
      const MathFunction F,
      const MathFunction DxF,
      const MathFunction DyF,
      const HessianFunction HessianFunc,
      const InitialApproxPoint& InitApprox,
      double Eps) : MinCalculator(F, DxF, DyF, InitApprox, Eps), hessianF(HessianFunc) {}


   virtual
   double
   GetMin() const override final;

};

