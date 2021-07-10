#pragma once
#include "LinerEquation.h"
#ifndef GAUSSSOLVER
#define GAUSSSOLVER

inline class GaussSolver
{
private:
	friend LinerEquation;
public:
	auto operator()( LinerEquation& equation ) const
	{
		const int& n = equation.len;
		for (int i = 0; i < n; i++)
		{
			if (LinerEquation::isZero(equation.a[i][i]))
			{
				std::cerr << ":-(\n" << std::endl;
				return;
			}
		}

		int i, j;
		const auto c = new double[n];

		//消元
		for (int k = 0; k < n - 1; k++)
		{
			//求出第K次初等行变换的系数
			for (i = k + 1; i < n; i++)
			{
				c[i] = equation.a[i][k] / equation.a[k][k];
			}

			//第K次的消元计算
			for (i = k + 1; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					equation.a[i][j] = equation.a[i][j] - c[i] * equation.a[k][j];
				}
				equation.rVector[i] = equation.rVector[i] - c[i] * equation.rVector[k];
			}
		}
		delete[]c;

		if (!equation.ans)
		{
			equation.ans = new double[n];
		}

		equation.ans[n - 1] = equation.rVector[n - 1] / equation.a[n - 1][n - 1];
		for (i = n - 2; i >= 0; i--)
		{
			double sum = 0;
			for (j = i + 1; j < n; j++)
			{
				sum += equation.a[i][j] * equation.ans[j];
			}
			equation.ans[i] = (equation.rVector[i] - sum) / equation.a[i][i];
		}
	}

	auto operator()(LinerEquation&& equation) const
	{
		const int& n = equation.len;
		for (int i = 0; i < n; i++)
		{
			if (LinerEquation::isZero(equation.a[i][i]))
			{
				std::cerr << ":-(\n" << std::endl;
				return;
			}
		}

		int i, j;
		const auto c = new double[n];

		//消元
		for (int k = 0; k < n - 1; k++)
		{
			//求出第K次初等行变换的系数
			for (i = k + 1; i < n; i++)
			{
				c[i] = equation.a[i][k] / equation.a[k][k];
			}

			//第K次的消元计算
			for (i = k + 1; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					equation.a[i][j] = equation.a[i][j] - c[i] * equation.a[k][j];
				}
				equation.rVector[i] = equation.rVector[i] - c[i] * equation.rVector[k];
			}
		}
		delete[]c;

		if (!equation.ans)
		{
			equation.ans = new double[n];
		}

		equation.ans[n - 1] = equation.rVector[n - 1] / equation.a[n - 1][n - 1];
		for (i = n - 2; i >= 0; i--)
		{
			double sum = 0;
			for (j = i + 1; j < n; j++)
			{
				sum += equation.a[i][j] * equation.ans[j];
			}
			equation.ans[i] = (equation.rVector[i] - sum) / equation.a[i][i];
		}
	}

} solver;
#endif
