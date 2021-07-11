#include "Matrix.h"
#include "Square.h"
#include "LinerEquation.h"
#include "OLS_MLR.h"

using namespace std;

auto get( double** x, double* y, const int& m, const int& n ) -> void
{
	for (int i = 0; i < n; ++i)
	{
		printf("�������%d�����ݵ�%d���Ա���: ", i + 1, m);
		for (int j = 0; j < m; ++j)
		{
			cin >> x[j][i];
		}
		printf("�������%d�����ݵ��������: ", i + 1);
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
	cout << "�������Ա�������m\n";
	cin >> m;
	cout << "��������������n\n";
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
		"\n\n\nƫ��ƽ����Ϊ %lf\nƽ����׼ƫ��Ϊ %lf\n�����ϵ��Ϊ %lf\n",
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