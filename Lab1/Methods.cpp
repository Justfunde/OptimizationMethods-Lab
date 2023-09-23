#include <numeric>
#include <iostream>
#include <cmath>

#include "Methods.hpp"

#pragma pack (1)
union double_cast
{
   double f;
   struct Parts
   {
      u_int64_t mantissa : 52;
      u_int64_t exponent : 11;
      u_int64_t sign : 1;
   };
   Parts parts;
};
#pragma pack (0)


double
BruteForce::GetMin() const
{
   double min = std::numeric_limits<double>::max();

   for(double d = xDiap.first; d <= xDiap.second; d += 0.0001)
   {
      const double tmpMin = mathFunction(d);
      if(tmpMin <  min) { min = tmpMin;}
   }

   return min;
}

double
Dichotomy::GetMin() const
{
   double min = std::numeric_limits<double>::max();

   double right(xDiap.second), left(xDiap.first);

   while(std::abs(right - left) > eps)
   {
      const double mid = (right + left) / static_cast<double>(2);

      const double lhsVal = mathFunction(mid - eps);
      const double rhsVal = mathFunction(mid + eps);
      if(lhsVal < rhsVal)
      {
         right = mid;
      }
      else 
      { 
         left = mid;
      }

   }
   min = mathFunction((right + left) / static_cast<double>(2));

   return min;
}

double
GoldenSection::GetMin() const
{
   double min = std::numeric_limits<double>::max();
   double right(xDiap.second), left(xDiap.first);

   static const double fi = (static_cast<double>(1) + sqrt(5)) / static_cast<double>(2);

   while(std::abs(right - left) > eps)
   {
      const double x_1 = right - (right - left) / fi;
      const double x_2 = left + (right - left) / fi;
      const double y_1 = mathFunction(x_1);
      const double y_2 = mathFunction(x_2);
      if(y_1 < y_2)
      {
         right = x_2;
      }
      else
      {
         left = x_1;
      }
   }

   min = mathFunction((right + left) / static_cast<double>(2));

   return min;
}

double
BitwiseSearch::GetMin() const
{
   static const double fi = (static_cast<double>(1) + sqrt(5)) / static_cast<double>(2);
   double r(xDiap.second), l(xDiap.first);
   double resphi = 2 - fi;
   double x1 = l + resphi * (r - l);
   double x2 = r - resphi * (r - l);
   double f1 = mathFunction(x1);
   double f2 = mathFunction(x2);
   

   while (std::abs(r - l) > eps) 
   {
      if (f1 < f2) 
      {
         r = x2;
         x2 = x1;
         f2 = f1;
         x1 = l + resphi * (r - l);
         f1 = mathFunction(x1);
      } 
      else 
      {
         l = x1;
         x1 = x2;
         f1 = f2;
         x2 = r - resphi * (r - l);
         f2 = mathFunction(x2);
      }
   }

   double min = mathFunction((r + l) / static_cast<double>(2));

   return min;
}