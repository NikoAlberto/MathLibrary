#include <fstream>
#include <iomanip>
#include <iostream>

#include "RCA.h"

RCA::RCA(string filename) {
		filename >> X;
		X = new_matrix_RCA(X);
		X0 = X;
	};

Matrix& RCA::NIPALS(size_t A, int param) {
	for (size_t h = 0; h < A; h++) {
		auto t1 = extract_col(X, h);
		Matrix t(t1.size(), 1, t1);
		vector<double> d1;
		d1.resize(t1.size());
		Matrix d(t1.size(), 1, d1);
		p1.resize(t1.size());
		Matrix p(1, t1.size(), p1);
		do {
			t.Transpose();
			p = t * X;
			p = p * (1 / (scalar_product(t, t)));
			p.Transpose();
			p = p * (1 / vector_module(p));
			t.Transpose();
			auto t_old = t;


			t = X * p * (1 / scalar_product(p, p));
			d = t_old - t;


		} while (vector_module(d) > EPS);
		Matrix temp = t * p.Transpose();
		X = X - temp;
		p.Transpose();

		P = insert_col(P, p);
		T = insert_col(T, t);
	}
	if (param == 1)
		return X;
	if (param == 2)
		return P;
	else
		return T;
}

void RCA::Scope() {
	Matrix h(1, T.get_Ncols());
	Matrix M;
	M = T;
	M = M * T.Transpose();
	M = inverse_matrix(M);
	T.Transpose();

	double k = 0;
	for (size_t i = 0; i < h.get_Ncols(); i++) {
		Matrix temp;
		double a = 0;
		Matrix t(T.get_Mrows(), 1, extract_col(T, i));//32*1
		t.Transpose();
		temp = t * M;
		a = (temp * t.Transpose()).get_matrix()[0][0];
		h.set_elm(0, i, a);
		k += a / h.get_Ncols();
	}
	this->h = h;
	cout << h;
	//return *this;
	//return k;
}

double RCA::dispersion_av()
{
	Matrix X1(T.get_Mrows(), P.get_Mrows()), E(X.get_Mrows(), X.get_Ncols());//While transposing: get_Mrows->get_Ncols
	X1 = T * P.Transpose();
	E = X0 - X1;
	vector<double> v;
	for (size_t i = 0; i < E.get_Mrows(); i++)
	{
		double k = 0;
		for (size_t j = 0; j < E.get_Ncols(); j++)
			k += (E.get_matrix()[i][j]) * (E.get_matrix()[i][j]);
		v.push_back(k);
	}
	double c = 0;
	for (auto i : v)
		c += i;
	return c / v.size();


}

double RCA::TRV() {
	Matrix v(X.get_Mrows(), 1);

	for (size_t i = 0; i < v.get_Mrows(); i++)
	{
		double a = 0;
		for (size_t j = 0; j < X.get_Ncols(); j++)
			a += X.get_matrix()[i][j] * X.get_matrix()[i][j];
		v.set_elm(i, 0, a);
	}
	double v0 = Mean(v, 0);
	return v0 / X.get_Ncols();
}

double RCA::ERV() {
	double e0 = 0.0, x0 = 0.0;
	for (size_t i = 0; i < X.get_Mrows(); i++)
		for (size_t j = 0; j < X.get_Ncols(); j++) {
			e0 += X.get_matrix()[i][j] * X.get_matrix()[i][j];
			x0 += X0.get_matrix()[i][j] * X0.get_matrix()[i][j];
		}
	return 1 - e0 / x0;

}

