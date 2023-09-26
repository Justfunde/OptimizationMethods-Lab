#include <numeric>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <list>

#include "Methods.hpp"




double
BolzanoMethod::GetMin() const
{
   double right(xDiap.second), left(xDiap.first);

   std::size_t iterCnt = 0;
   std::vector<double> minYvalues;

   double xMin = std::numeric_limits<double>::max();

   do
   {
      xMin = (left + right) / 2;

      double currY = df(xMin);
      if(currY > 0)
      {
         right = xMin;
      }
      else
      {
         left = xMin;
      }
      minYvalues.push_back(f(xMin));
      iterCnt++;
   } while (std::abs(df(xMin)) > eps);
   
   const double yMin = f(xMin);
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
ChordMethod::GetMin() const
{
   const auto xFunc = 
      [=]
      (const double left, const double right)
      {
         return left - df(left) * ( left - right)/ (df(left) - df(right));
      };
   
   double right(xDiap.second), left(xDiap.first);

   std::size_t iterCnt = 0;
   std::vector<double> minYvalues;

   double x;
   double df_val;
   do
   {
      x = xFunc(left, right);
      df_val = df(x);
      if(df_val > 0)
      {
         right = x;
      }
      else
      {
         left = x;
      }

      minYvalues.push_back(f(x));
      iterCnt++;
   } while (std::abs(df_val) > eps);
   
   const double yMin = f(x);
   std::cout << "Iteration count: " << iterCnt << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) << x << "," << std::setprecision(20) << yMin << ")" << std::endl; 
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
NewtonMethod::GetMin() const
{
   std::list<double> xList;

   const auto calcNextXval = 
   [=](double x)
      {
         return x - df(x)/ d2f(x);
      };

   xList.push_back(xDiap.first + 1);

   while (std::abs(df(xList.back())) > eps)
   {
      xList.push_back(calcNextXval(xList.back()));
   }
   
   const double yMin = f(xList.back());
   std::cout << "Iteration count: " << xList.size() << std::endl;
   std::cout << "Min point coordinates (x_min,y_min) = (" << std::setprecision(20) << xList.back() << "," << std::setprecision(20) << yMin << ")" << std::endl; 
   std::cout << "Min values on last 3 iterations [";
   for(std::list<double>::const_iterator iter = std::prev(std::prev(std::prev(xList.end()))); iter != xList.end(); ++iter)
   {
      std::cout << std::setprecision(20) << f(*iter);
      if(iter != std::prev(xList.end())) { std::cout << ", ";}
   }
   std::cout << "]" << std::endl;

   return yMin;
}
