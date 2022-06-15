#pragma once

#include "Matrix.h"
//#include "Filework.h"

#define EPS 1e-10

class RCA {
public:
	RCA(string filename);
	Matrix X0;
	Matrix X;
	Matrix T;
	Matrix P;
	Matrix h;

	vector<double> p1;
	vector<double> t1;

	Matrix& NIPALS(size_t A = 12, int param = 2);
	void Scope();
	double dispersion_av();
	double TRV();
	double ERV();
};

//#include "Overloaded.h"