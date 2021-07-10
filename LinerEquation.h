#pragma once
#include "Matrix.h"
#ifndef LINEEQUATION
#define LINEEQUATION
class GaussSolver;

class LinerEquation : private Matrix
{
private:
	double* rVector{nullptr};
	double* ans{nullptr};
	int len;
	friend GaussSolver;

public:
	/*
	*	���캯����
		�βΣ�p1:�������Է��̽���
	*/
	LinerEquation(const int& len);
	
	/*
	*	�������캯����
		�βΣ�p1:���Է��̶�����ֵ��
	*/
	LinerEquation(const LinerEquation& cpyLinerEquation);
	
	/*
	*	�������캯����
		�βΣ�p1:���Է��̶�����ֵ��
	*/
	LinerEquation(LinerEquation&& cpyLinerEquation);

	/*
	*	���캯����
		�βΣ�p1:double** ��ά����->ϵ������	p2:�ұ�����	p3:���̽���
	*/
	LinerEquation(double** coefficients, const double* rVector, const int& len);

	/*
	*	��������
	*/
	~LinerEquation();
	
	/*
	*	��ӡ���Է�����
	*/
	auto printLinerEquation() const->void;

	/*
	*	��ӡ��
	*/
	auto printAns() const -> void;

	/*
	*	�β�:n(�ڼ����Ա����Ľ�)
	*/
	auto getAnsOf(const int& n) const;

	auto operator =( LinerEquation& rhs ) = delete;
	auto operator =(LinerEquation&& rhs ) = delete;

	friend auto operator>>(std::istream& in, LinerEquation& rhs)->std::istream&;
	
	friend auto operator <<(std::ostream& out, const LinerEquation& rhs)->std::ostream&;

	auto operator [](const int& n)const ->double;

};

LinerEquation::LinerEquation(const int& len) :Matrix(len, len), rVector{ new double[len] }, len(len)
{
}

LinerEquation::LinerEquation(const LinerEquation& cpyLinerEquation) : Matrix(cpyLinerEquation),
rVector{ new double[cpyLinerEquation.len] },
len(cpyLinerEquation.len)
{
	for (int i = 0; i < len; ++i)
	{
		this->rVector[i] = cpyLinerEquation.rVector[i];
	}
	if (cpyLinerEquation.ans)
	{
		ans = new double[len];
		for (int i = 0; i < len; ++i)
		{
			this->ans[i] = cpyLinerEquation.ans[i];
		}
	}
}

LinerEquation::LinerEquation(LinerEquation&& cpyLinerEquation) : Matrix(std::move(cpyLinerEquation)),
len(cpyLinerEquation.len)
{
	rVector = cpyLinerEquation.rVector;
	ans = cpyLinerEquation.ans;
	cpyLinerEquation.rVector = nullptr;
	cpyLinerEquation.ans = nullptr;
}

LinerEquation::LinerEquation(double** coefficients, const double* rVector, const int& len) : Matrix(len, len),
rVector(new double[len]),
len(len)
{
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j <= len; ++j)
		{
			if (j != len)
			{
				a[i][j] = coefficients[i][j];
			}
			else
			{
				this->rVector[i] = rVector[i];
			}
		}
	}
}

LinerEquation::~LinerEquation()
{
	if (rVector != nullptr)//must
	{
		delete[]rVector;

	}
	if (ans != nullptr)//must
	{
		delete[]ans;
	}
}

auto LinerEquation::printLinerEquation() const ->void
{
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j <= len; ++j)
		{
			if (j != len)
			{
				std::cout << a[i][j] << " ";
			}
			else
			{
				std::cout << rVector[i] << std::endl;
			}
		}
	}
}

auto LinerEquation::printAns() const -> void
{
	if (ans)
	{
		for (int i = 0; i < len; ++i)
		{
			std::cout << ans[i] << std::endl;
		}
	}
}

auto LinerEquation::getAnsOf(const int& n) const
{
	return ans[n];
}

auto LinerEquation::operator[](const int& n)const->double
{
	return ans[n];
}

auto operator>>(std::istream& in, LinerEquation& rhs) -> std::istream&
{
	for (int i = 0; i < rhs.len; ++i)
	{
		for (int j = 0; j <= rhs.len; ++j)
		{
			if (j != rhs.len)
			{
				in >> rhs.a[i][j];
				Matrix::isZero(rhs.a[i][j]);
			}
			else
			{
				in >> rhs.rVector[i];
				Matrix::isZero(rhs.rVector[i]);
			}
		}
	}
	return in;
}

auto operator<<(std::ostream& out, const LinerEquation& rhs) -> std::ostream&
{
	rhs.printLinerEquation();
	return out;
}

#endif