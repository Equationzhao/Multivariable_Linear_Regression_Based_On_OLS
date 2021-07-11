#pragma once
#include <cmath>

#include "Matrix.h"

#ifndef SQUARE
#define SQUARE

class Square : public Matrix
{
private:
	/*
	* 返回行列式的值
	*/
	auto calDeterminant(double** arr, int n) const -> double;
	
	/*
	* 计算代数余子式
	* 参数：方阵、代数余子式
	*/
	auto calCominor(double** in, double** out) const -> void;
	
	/*
	* 转置
	*/
	auto getTransposition(double** arr)const -> void;

public:
	/*
	*	构造函数
	*	形参:	p1:方阵阶数
	*/
	Square(const int& len) ;

	/*
	*	构造函数
	*	形参:	p1:double** 二维数组	p2:方阵阶数
	*/
	Square(double** a, const int& n);

	/*
	*	拷贝构造函数
	*	形参:	p1:方阵对象（左值）
	*/
	Square(const Square& cpySquare);

	/*
	*	移动构造函数
	*	形参:	p1:方阵对象（右值）
	*/
	Square(Square&& cpySquare) noexcept;

	~Square() = default;

	Square() = delete;
	auto getRow() const -> int = delete;
	auto getColumn() const -> int = delete;

	/*
	*	获得方阵阶数
	*/
	auto getLen()const ->int;

	auto operator =( const Square& rhs ) = delete;
	auto operator =( Square&& rhs ) = delete;

	/*
	 * 计算行列式
	 */
	auto getDeterminant() const -> int;

	/*
	 * 返回代数余子式
	 */
	auto getCominor() const->Square;

	/*
	* Overwrite
	*返回转置矩阵
	*/
	auto getTransposition()const->Square;

	/*
	* 返回伴随矩阵
	*/
	auto getAdjoint()const->Square;

	/*
	 * 是否可逆
	 */
	auto isInversible() const -> bool;	

	/*
	* 返回逆矩阵
	*/
	auto getInverse()const->Square;

};

auto Square::calDeterminant(double** arr, int n) const -> double
{
	if (n == 1)
	{
		return arr[0][0];
	}

	double ans = 0;
	const auto temp = new double* [n];
	for (auto&& i = 0; i < n; ++i)
	{
		temp[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			for (int k = 0; k < n - 1; k++)
			{
				temp[j][k] = arr[j + 1][(k >= i) ? k + 1 : k];
			}
		}
		const int t = calDeterminant(temp, n - 1);
		if (i % 2 == 0)
		{
			ans += arr[0][i] * t;
		}
		else
		{
			ans -= arr[0][i] * t;
		}
	}

	for (auto&& i = 0; i < n; ++i)
	{
		delete[]temp[i];
	}
	delete[]temp;

	return ans;
}

auto Square::calCominor(double** in, double** out) const -> void
{
	if (row == 1)
	{
		out[0][0] = 1;
		return;
	}

	const auto temp = new double* [row];
	for (auto&& i = 0; i < row; ++i)
	{
		temp[i] = new double[row];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			for (int k = 0; k < row - 1; k++)
			{
				for (int t = 0; t < row - 1; t++)
				{
					temp[k][t] = in[k >= i ? k + 1 : k][t >= j ? t + 1 : t];
				}
			}
			out[i][j] = calDeterminant(temp, row - 1);
			if ((i + j) % 2 == 1)
			{
				out[i][j] = -out[i][j];
			}
		}
	}

	for (auto&& i = 0; i < row; ++i)
	{
		delete[]temp[i];
	}
	delete[]temp;
}

auto Square::getTransposition(double** arr)const -> void
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			std::swap(arr[i][j], arr[j][i]);
		}
	}
}

Square::Square(const int& len) : Matrix(len, len)
{
}

Square::Square(const Square& cpySquare) : Matrix(cpySquare)
{
}

Square::Square(Square&& cpySquare)noexcept : Matrix(std::move(cpySquare))
{
}

Square::Square(double** a, const int& n) : Matrix(n, n)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			this->a[i][j] = a[i][j];
		}
	}
}

auto Square::getLen() const -> int
{
	return row;
}

auto Square::getDeterminant() const -> int
{
	return calDeterminant(a, row);
}

auto Square::getCominor() const -> Square
{
	Square temp(row);
	calCominor(a, temp.a);
	return temp;
}

auto Square::getTransposition()const -> Square
{
	Square tempSquare(*this);
	getTransposition(tempSquare.a);
	return tempSquare;
}

auto Square::getAdjoint()const -> Square
{
	Square tempSquare(*this);
	calCominor(a, tempSquare.a);
	getTransposition(tempSquare.a);
	return tempSquare;
}

auto Square::isInversible() const -> bool
{
	if (fabs(getDeterminant()) < 10e-6)
	{
		return false;
	}
	return true;
}

auto Square::getInverse()const -> Square
{
	const double D = getDeterminant();
	if (!isInversible())
	{
		std::cerr << "uninversible\n";
		system("pause");
		exit(0);
	}
	Square temp(getAdjoint());
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			temp.a[i][j] /= D;
		}
	}
	return temp;
}

#endif
