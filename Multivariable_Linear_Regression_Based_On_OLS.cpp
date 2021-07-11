#include "Matrix.h"
#include "Square.h"
#include "LinerEquation.h"
#include "OLS_MLR.h"

using namespace std;

auto get( double** x, double* y, const int& m, const int& n ) -> void
{
	for (int i = 0; i < n; ++i)
	{
		printf("请输入第%d组数据的%d个自变量: ", i + 1, m);
		for (int j = 0; j < m; ++j)
		{
			cin >> x[j][i];
		}
		printf("请输入第%d组数据的随机变量: ", i + 1);
		cin >> y[i];
	}
}

auto printAns(const OLS_MLR& mlr )
{
	for (int i = 0, size = mlr.getAns().size(); i < size; ++i)
	{
		if (!i)
		{
			printf("%lfX%d", mlr.getAnsOf(i), i);
		}
		else
		{
			if (mlr.getAnsOf(i) > 0)
			{
				cout << "+";
			}
			if (i == size - 1)
			{
				printf("%lf", mlr.getAnsOf(i));
			}
			else
			{
				printf("%lfX%d", mlr.getAnsOf(i), i);
			}
		}
	}
}

Square getSq()
{
	return Square(2);
}

auto main() -> int
{
	
	int m, n;
	cout << "请输入自变量个数m\n";
	cin >> m;
	cout << "请输入数据组数n\n";
	cin >> n;

	const auto x = new double *[m];
	for (int i = 0; i < m; ++i)
	{
		x[i] = new double[n];
	}
	const auto y = new double[n];

	get(x, y, m, n);

	OLS_MLR mlr(x, y, m, n);

	printAns(mlr);

	printf
	(
		"\n\n\n偏差平方和为 %lf\n平均标准偏差为 %lf\n复相关系数为 %lf\n",
		mlr.getSumOfSquares(),
		mlr.getStdDeviation(),
		mlr.getMultiple_Correlation_Coefficient()
	);

	for (int i = 0; i < m; ++i)
	{
		delete[]x[i];
	}
	delete[]x;
	delete[]y;

	system("pause");
}