#include <numeric>
#include <iostream>
#include <iomanip>
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
   double yMin = std::numeric_limits<double>::max();
   double xMin = 0;
   std::size_t iterCnt = 0;

   for(double d = xDiap.first; d <= xDiap.second; d += 0.0001)
   {
      const double tmpMin = mathFunction(d);
      if(tmpMin <  yMin) 
      { 
         yMin = tmpMin;
         xMin = d;
      }
      iterCnt++;
   }
   std::cout << "Iteration count: " << iterCnt << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) <<  xMin << "," << std::setprecision(20) <<  yMin << ")" << std::endl; 

   return yMin;
}

double
Dichotomy::GetMin() const
{
   double yMin = std::numeric_limits<double>::max();

   double right(xDiap.second), left(xDiap.first);

   std::size_t iterCnt = 0;
   std::vector<double> minYvalues;
   while(std::abs(right - left) > eps)
   {
      const double mid = (right + left) / static_cast<double>(2);

      const double lhsVal = mathFunction(mid - eps);
      const double rhsVal = mathFunction(mid + eps);
      if(lhsVal < rhsVal)
      {
         right = mid;
         minYvalues.push_back(lhsVal);
      }
      else 
      { 
         left = mid;
         minYvalues.push_back(rhsVal);
      }
      iterCnt++;
   }
   const double xMin = (right + left) / static_cast<double>(2);
   yMin = mathFunction(xMin);

   std::cout << "Iteration count: " << iterCnt << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) << xMin << "," << std::setprecision(20) << yMin << ")" << std::endl; 
   std::cout << "Min values on last 3 iterations [";
   for(std::size_t i = minYvalues.size() - 3; i < minYvalues.size(); ++i)
   {
      std::cout << std::setprecision(20) << minYvalues[i];
      if(i != minYvalues.size() - 1) { std::cout << ", ";}
   }
   std::cout << "]" << std::endl;


   return yMin;
}

double
GoldenSection::GetMin() const
{
   double yMin = std::numeric_limits<double>::max();
   double right(xDiap.second), left(xDiap.first);

   static const double fi = (static_cast<double>(1) + sqrt(5)) / static_cast<double>(2);

   std::size_t iterCnt = 0;
   std::vector<double> minYvalues;

   while(std::abs(right - left) > eps)
   {
      const double x_1 = right - (right - left) / fi;
      const double x_2 = left + (right - left) / fi;
      const double y_1 = mathFunction(x_1);
      const double y_2 = mathFunction(x_2);
      if(y_1 < y_2)
      {
         right = x_2;
         minYvalues.push_back(y_1);
      }
      else
      {
         left = x_1;
         minYvalues.push_back(y_2);
      }
      iterCnt++;
   }
   const double xMin = (right + left) / static_cast<double>(2);
   yMin = mathFunction(xMin);

   std::cout << "Iteration count: " << iterCnt << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) << xMin << "," << std::setprecision(20) << yMin << ")" << std::endl; 
   std::cout << "Min values on last 3 iterations [";
   for(std::size_t i = minYvalues.size() - 3; i < minYvalues.size(); ++i)
   {
      std::cout << std::setprecision(20) << minYvalues[i];
      if(i != minYvalues.size() - 1) { std::cout << ", ";}
   }
   std::cout << "]" << std::endl;

   return yMin;
}

double
Bitwise::GetMin() const
{
   double yMin = std::numeric_limits<double>::max();
   std::size_t iterCnt = 0;
   std::vector<double> minYvalues;
   double right(xDiap.second), left(xDiap.first);
   double step = 0.001;
   double currX = left;
   double prevY = 0;
   while (std::abs(yMin - prevY) > eps)
   {
      while (true)
      {
         ++iterCnt;
         const double tmpYmin = mathFunction(currX);
         if(tmpYmin <= yMin)
         {
            prevY = yMin;
            yMin = tmpYmin;
            minYvalues.push_back(yMin);
         }
         else 
         { 
            break;
         }
         currX += step;
      }
      step = (-step) / 4;
      currX += step;
   }
   

   const double xMin = currX;
   yMin = mathFunction(xMin);

   std::cout << "Iteration count: " << iterCnt << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) << xMin << "," << std::setprecision(20) << yMin << ")" << std::endl; 
   std::cout << "Min values on last 3 iterations [";
   for(std::size_t i = minYvalues.size() - 3; i < minYvalues.size(); ++i)
   {
      std::cout << std::setprecision(20) << minYvalues[i];
      if(i != minYvalues.size() - 1) { std::cout << ", ";}
   }
   std::cout << "]" << std::endl;

   return yMin;
}