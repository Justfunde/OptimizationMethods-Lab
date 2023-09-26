#include <numeric>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <list>

#include "Methods.hpp"



// Метод градиентного спуска
double GradientDescentMethod::GetMin() const
{
    // Начальное приближение для минимизации функции
    double x = initApprox.first, y = initApprox.second;
    double dx, dy;
    const double step_size = 0.1; // Размер шага для обновления x и y

    while (true) 
    {
        // Градиент функции f в точке (x, y) представляет собой вектор из частных производных:
        // dx = df/dx и dy = df/dy
        dx = dxF(x, y);
        dy = dyF(x, y);

        // Условие остановки: если обе компоненты градиента меньше заданной точности eps, 
        // это означает, что мы достигли минимума
        if (std::abs(dx) < eps && std::abs(dy) < eps) break;

        // Обновление текущей точки, двигаясь в направлении, противоположном градиенту
        // x_new = x_old - step_size * df/dx
        // y_new = y_old - step_size * df/dy
        x -= step_size * dx;
        y -= step_size * dy;
    }

    // Вывод результатов
    std::cout << "Минимум достигается в: (" << std::setprecision(20) << x << ", " << std::setprecision(20) << y << ")" << std::endl;
    std::cout << "Значение функции в этой точке: " << std::setprecision(20) << f(x, y) << std::endl;

    return f(x,y);
}


inline
double 
FastestGradientDescentMethod::g(
   double alpha,
   double x,
   double y,
   double dx,
   double dy) const
{
   // Функция g(alpha) представляет собой значение функции f после шага в направлении градиента с коэффициентом alpha
    // g(alpha) = f(x - alpha*dx, y - alpha*dy)
   return f(x - alpha * dx, y - alpha * dy);
}


double 
FastestGradientDescentMethod::BitwiseSearch(
   double x,
   double y,
   double dx,
   double dy,
   double eps) const
{
   // Поразрядный поиск для определения оптимального значения alpha
   // Этот метод используется для нахождения оптимального размера шага в методе наискорейшего градиентного спуска
   // Основная идея: искать минимум функции g(alpha) с учетом заданной точности
   double yMin = g(0, x, y, dx, dy); // начальное значение при alpha = 0
   double step = 0.001;
   double currX = 0; // начнем с alpha = 0
   double prevY = yMin + 1; // чтобы начать цикл
   constexpr int maxIterations = 1000; // максимальное количество итераций
   int iterations = 0;

   const double alpha_max = (dx > 0 || dy > 0) ? -1 : 1; // предполагаемый максимальный диапазон для alpha

   while (std::abs(yMin - prevY) > eps && iterations < maxIterations) 
   {
      iterations++;
      while (true) 
      {
         const double tmpYmin = g(currX, x, y, dx, dy);
         if(tmpYmin <= yMin && currX != alpha_max) 
         {
            prevY = yMin;
            yMin = tmpYmin;
         } else { break;}
            currX += step;
            if (currX > alpha_max || currX < -alpha_max) break; // выход, если вышли за пределы диапазона
        }
        step = (-step) / 4;
        currX += step;
    }

    return currX;
}


double
FastestGradientDescentMethod::GetMin() const
{
   double x = initApprox.first, y = initApprox.second; // начальное приближение
   double dx, dy;

   while (true) 
   {
      dx = dxF(x, y);
      dy = dyF(x, y);
      if (std::abs(dx) < eps && std::abs(dy) < eps) break;
        
      double optimalStep = BitwiseSearch(x, y, dx, dy);
      x -= optimalStep * dx;
      y -= optimalStep * dy;
   }

   std::cout << "Минимум достигается в: (" << std::setprecision(20) << x << ", " << std::setprecision(20) <<y << ")\n";
   std::cout << "Значение функции в этой точке: " << std::setprecision(20) << f(x, y) << "\n";

   return f(x, y);
}


double NewtonMethod::GetMin() const
{
    // Начальное приближение для минимизации функции
    double x = initApprox.first, y = initApprox.second;
    double dx, dy, dxx, dxy, dyx, dyy;
    const double step_size = 0.1; // Размер шага для обновления x и y
    const int max_iterations = 1000; // Максимальное количество итераций для предотвращения зацикливания

    for (int i = 0; i < max_iterations; ++i) 
    {
      // Вычисление градиента функции f в точке (x, y)
      dx = dxF(x, y);
      dy = dyF(x, y);

      // Условие остановки: если обе компоненты градиента меньше заданной точности eps, 
      // это означает, что мы достигли минимума
      if (std::abs(dx) < eps && std::abs(dy) < eps) break;

      // Вычисление матрицы Гессе для функции f в точке (x, y)
      // Матрица Гессе - это матрица вторых частных производных:
      // | d^2f/dx^2   d^2f/dxdy |
      // | d^2f/dydx  d^2f/dy^2  |
      hessianF(dxx, dxy, dyx, dyy);

      // Вычисление обратной матрицы Гессе
      double det = dxx*dyy - dxy*dyx;
      double inv_dxx = dyy / det;
      double inv_dxy = -dxy / det;
      double inv_dyx = -dyx / det;
      double inv_dyy = dxx / det;

      // Обновление текущей точки, используя направление, полученное из метода Ньютона
       // x_new = x_old - step_size * (inv_dxx * df/dx + inv_dxy * df/dy)
      // y_new = y_old - step_size * (inv_dyx * df/dx + inv_dyy * df/dy)
      x -= step_size * (inv_dxx * dx + inv_dxy * dy);
      y -= step_size * (inv_dyx * dx + inv_dyy * dy);
    }

    // Вывод результатов
    std::cout << "Минимум достигается в: (" << std::setprecision(20) << x << ", " << std::setprecision(20) <<y << ")\n";
    std::cout << "Значение функции в этой точке: " << std::setprecision(20) << f(x, y) << "\n";

    return f(x, y);
}