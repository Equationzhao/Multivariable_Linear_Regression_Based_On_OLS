#pragma once
#ifndef _OLS_MLR_
#define _OLS_MLR_
#include <vector>

#include "Matrix.h"
#include "Square.h"

class OLS_MLR
{
private:
	Matrix *c{ nullptr }, *y{ nullptr };
	int m, n;
	std::vector<double> ans;
	double SumOfSquares, StdDeviation, Multiple_Correlation_Coefficient;

	auto calSS();

	auto calSD() -> void;

	auto calMCC() -> void;

public:
	friend Matrix;

	OLS_MLR(double** x, double* y, const int& m, const int& n);

	~OLS_MLR();

	auto getAns()const ->std::vector<double>;

	auto getAnsOf(const int& n)const -> double;

	auto getSumOfSquares()const -> double;

	auto getStdDeviation()const -> double;

	auto getMultiple_Correlation_Coefficient()const -> double;
};

inline auto OLS_MLR::calSS()
{
	for (int i = 0; i < n; ++i)
	{
		double temp_Yi = y->get(i, 0);
		for (int j = 0; j <= m; ++j)
		{
			temp_Yi -= ans.at(j) * c->get(j, i);
		}
		SumOfSquares += temp_Yi * temp_Yi;
	}
}

inline auto OLS_MLR::calSD() -> void
{
	StdDeviation = sqrt(SumOfSquares / n);
}

inline auto OLS_MLR::calMCC() -> void
{
	double sum = 0;
	for (const auto& i : ans)
	{
		sum += i / n;
	}
	double t = 0;
	for (const auto& i : ans)
	{
		t += pow(i - sum, 2);
	}
	Multiple_Correlation_Coefficient = sqrt(1 - SumOfSquares / t);
}

inline OLS_MLR::OLS_MLR(double** x, double* y, const int& m, const int& n) : m(m), n(m), SumOfSquares(0), StdDeviation(0),
																			Multiple_Correlation_Coefficient(0)
{
	c = new Matrix(m + 1, n);
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			i != m ? c->set(i, j, x[i][j]) : c->set(m, j, 1);
		}
	}
	this->y = new Matrix(n, 1);
	for (int i = 0; i < n; ++i)
	{
		this->y->set(i, 0, y[i]);
	}

	const Matrix temp(*c * c->getTransposition());
	auto a = new double* [temp.getColumn()];
	for (int i = 0; i < temp.getColumn(); ++i)
	{
		a[i] = new double[temp.getColumn()];
		for (int j = 0; j < temp.getColumn(); ++j)
		{
			a[i][j] = temp.get(i, j);
		}
	}

	const Matrix res((Square(a, temp.getColumn()).getInverse() * (*c)) * (*this->y));

	for (int i = 0; i < res.getRow(); ++i)
	{
		ans.emplace_back(res.get(i, 0));
	}

	for (int i = 0; i < temp.getColumn(); ++i)
	{
		delete[]a[i];
	}
	delete[]a;
	calSS();
	calSD();
	calMCC();
}

inline OLS_MLR::~OLS_MLR()
{
	delete c;
	delete this->y;
}

inline auto OLS_MLR::getAns()const -> std::vector<double>
{
	return ans;
}

inline auto OLS_MLR::getAnsOf(const int& n)const -> double
{
	return ans.at(n);
}

inline auto OLS_MLR::getSumOfSquares()const -> double
{
	return SumOfSquares;
}

inline auto OLS_MLR::getStdDeviation()const -> double
{
	return StdDeviation;
}

inline auto OLS_MLR::getMultiple_Correlation_Coefficient()const -> double
{
	return Multiple_Correlation_Coefficient;
}
#endif
