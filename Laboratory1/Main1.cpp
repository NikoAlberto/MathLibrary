#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<iostream>
#include "Matrix.h"
#include "RCA.h"


int main() {

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string datas = "data.txt";
	Matrix X;
	Matrix Y;
	datas >> X;
	
	cout << "Initial matrix from the file:" << endl;
	Y = new_matrix_RCA(X);
    cout << Y;

	RCA object(datas);
	cout << endl << "##############################" << endl;
	cout << "Matrix - output, depends on a parameter:" << endl;
	cout << object.NIPALS() << endl << endl;
	cout << "TRV and ERV:" << endl;
	cout << object.TRV() << '\t' << object.ERV() << endl;
	cout << "Scope h:" << endl;
	object.Scope();
	cout << "Dispersion: " << endl;
	cout << object.dispersion_av() << endl << endl;

	Matrix m = { 1,2,3,4,5 };

	cout << m << endl;

	return 0;
}