#pragma once
#include <iostream>
#include <string>

#ifndef _MATRIX_
#define _MATRIX_

class Matrix
{
protected:
	int row, column;
	double** a{ nullptr };

	auto checkZero() const -> void;

	static auto isZero(double& t) -> bool;

public:
	Matrix(const int& row, const int& column);

	explicit Matrix(const Matrix& cpyMatrix);

	explicit Matrix(Matrix&& cpyMatrix) noexcept;

	Matrix() = delete;

	auto set(const int& numOfRow, const int& numOfColumn, const double& elementToAssign) const -> void;

	auto get(const int& numOfRow, const int& numOfColumn) const -> double;

	~Matrix();

	auto getRow() const -> int;

	auto getColumn() const -> int;

	static auto isCalculatable(const Matrix& lhs, const Matrix& rhs, const std::string& mode) -> bool;

	auto isCalculatable(const Matrix& rhs, const std::string& mode);

	auto getTransposition() const->Matrix;

	friend auto operator>>( std::istream& in, Matrix& rhs ) -> std::istream&
	{
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				in >> rhs.a[i][j];
				isZero(rhs.a[i][j]);
			}
		}
		return in;
	}

	friend auto operator<<( std::ostream& out, const Matrix& rhs ) -> std::ostream&
	{
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				out << rhs.a[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	friend auto operator+(const Matrix& lhs, const Matrix& rhs ) -> Matrix
	{
		Matrix tempMatrix(rhs.row, rhs.column);
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				tempMatrix.a[i][j] = rhs.a[i][j] + lhs.a[i][j];
				isZero(tempMatrix.a[i][j]);
			}
		}
		return tempMatrix;
	}

	friend auto operator-(const Matrix& lhs, const Matrix& rhs ) -> Matrix
	{
		Matrix tempMatrix(rhs.row, rhs.column);
		for (int i = 0; i < rhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				tempMatrix.a[i][j] = lhs.a[i][j] - rhs.a[i][j];
				isZero(tempMatrix.a[i][j]);
			}
		}
		return tempMatrix;
	}

	friend auto operator*(const Matrix& lhs, const Matrix& rhs ) -> Matrix
	{
		Matrix tempMatrix(lhs.row, rhs.column);
		for (int i = 0; i < lhs.row; ++i)
		{
			for (int j = 0; j < rhs.column; ++j)
			{
				tempMatrix.a[i][j] = 0;
				for (int k = 0; k < lhs.column; k++)
				{
					tempMatrix.a[i][j] += lhs.a[i][k] * rhs.a[k][j];
					isZero(tempMatrix.a[i][j]);
				}
			}
		}
		return tempMatrix;
	}

	auto operator ()(const int& row,const int& column) -> double

	auto operator =( const Matrix& rhs ) = delete;
	auto operator =( Matrix&& rhs ) = delete;
};

inline auto Matrix::checkZero() const -> void
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			isZero(a[i][j]);
		}
	}
}

inline auto Matrix::isZero(double& t) -> bool
{
	if (fabs(t) < 10e-6)
	{
		t = 0;
		return true;
	}
	return false;
}

inline Matrix::Matrix(const int& row, const int& column) : row(row), column(column)
{
	this->a = new double* [row];
	for (int i = 0; i < row; ++i)
	{
		this->a[i] = new double[column] {0};
	}
}

inline Matrix::Matrix(const Matrix& cpyMatrix) : row(cpyMatrix.row), column(cpyMatrix.column)
{
	this->a = new double* [row];
	for (int i = 0; i < row; ++i)
	{
		this->a[i] = new double[column];
		for (int j = 0; j < column; ++j)
		{
			this->a[i][j] = cpyMatrix.a[i][j];
		}
	}
}

inline Matrix::Matrix(Matrix&& cpyMatrix) noexcept : row(cpyMatrix.row), column(cpyMatrix.column)
{
	this->a = cpyMatrix.a;
	cpyMatrix.a = nullptr;
}

inline auto Matrix::set(const int& numOfRow, const int& numOfColumn, const double& elementToAssign) const -> void
{
	a[numOfRow][numOfColumn] = elementToAssign;
	isZero(a[numOfRow][numOfColumn]);
}

inline auto Matrix::get(const int& numOfRow, const int& numOfColumn) const -> double
{
	return a[numOfRow][numOfColumn];
}

inline Matrix::~Matrix()
{
	if (a != nullptr)
	{
		for (int i = 0; i < row; ++i)
		{
			delete[]a[i];
		}
		delete a;
	}
}

inline auto Matrix::getRow() const -> int
{
	return row;
}

inline auto Matrix::getColumn() const -> int
{
	return column;
}

inline auto Matrix::isCalculatable(const Matrix& lhs, const Matrix& rhs, const std::string& mode) -> bool
{
	if (mode == "+" || mode == "-")
	{
		return rhs.column == lhs.column && rhs.row == lhs.row;
	}
	if (mode == "*")
	{
		return lhs.column == rhs.row;
	}

	return NULL;
}

inline auto Matrix::isCalculatable(const Matrix& rhs, const std::string& mode)
{
	return isCalculatable(*this, rhs, mode);
}

inline auto Matrix::getTransposition() const -> Matrix
{
	Matrix tempMatrix(column, row);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			tempMatrix.a[j][i] = a[i][j];
		}
	}
	return tempMatrix;
}

auto operator ()(const int& row,const int& column) -> double
{
	return a[row][column];
}

#endif
