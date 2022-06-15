#pragma once
//ПОДКЛАССЫ
//Единичная
class Singles : public Matrix
{

public:
	Singles(int m) {
		if (m <= 0)
			throw MyException5();
		M = m;
		N = m;
		matrix.resize(M);
		for (size_t i = 0; i < M; i++)
		{
			matrix[i].resize(N);
			for (size_t j = 0; j < M; j++) {
				if (i == j)
					matrix[i][j] = 1;
				else
					matrix[i][j] = 0;
			}
		}
	}
};

//Symmetric (filling with random numbers)
class Symmetric : public Matrix {

public:
	Symmetric(vector<double> sym)
	{
		if (sym.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * sym.size())) - sqrt(1 + 8 * sym.size())) > pow(10, -5))
			throw MyException2();
		M = (-1 + sqrt(1 + 8 * sym.size())) / 2;
		N = (-1 + sqrt(1 + 8 * sym.size())) / 2;
		matrix.resize(M);//Получение размерности матрицы из длины вектора
		for (size_t i = 0; i < M; i++)
		{
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = i; j < N; j++) {
				matrix[i][j] = sym.front();
				reverse(sym.begin(), sym.end());
				sym.pop_back();
				reverse(sym.begin(), sym.end());
				if (j != i)
					matrix[j][i] = matrix[i][j];
			}
	}
};

//Triangular

class UpTriangular : public Matrix {

public:
	UpTriangular(vector<double> Uptr)
	{
		if (Uptr.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * Uptr.size())) - sqrt(1 + 8 * Uptr.size())) > pow(10, -5))
			throw MyException2();
		M = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		N = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		matrix.resize(M);//Получение размерности матрицы из длины вектора
		for (size_t i = 0; i < M; i++)
		{
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = i; j < N; j++) {
				matrix[i][j] = Uptr.front();
				reverse(Uptr.begin(), Uptr.end());
				Uptr.pop_back();
				reverse(Uptr.begin(), Uptr.end());
				if (j != i)
					matrix[j][i] = 0;
			}
	}

};

class LowTriangular : public Matrix {

public:
	LowTriangular(vector<double> Uptr)
	{
		if (Uptr.size() <= 0)
			throw MyException5();
		if (abs(int(sqrt(1 + 8 * Uptr.size())) - sqrt(1 + 8 * Uptr.size())) > pow(10, -5))
			throw MyException4();
		M = (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		N= (-1 + sqrt(1 + 8 * Uptr.size())) / 2;
		matrix.resize(M);//Получение размерности матрицы из длины вектора
		for (size_t i = 0; i < M; i++)
		{
			matrix[i].resize(N);
		}

		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j <= i; j++) {
				matrix[i][j] = Uptr.front();
				reverse(Uptr.begin(), Uptr.end());
				Uptr.pop_back();
				reverse(Uptr.begin(), Uptr.end());
				if (j != i)
					matrix[j][i] = 0;
			}
	}


};


//Diagonal

class Diagonal : public Matrix
{

public:
	Diagonal(vector<double> diagon) {
		if (diagon.size() <= 0)
			throw MyException5();
		M = diagon.size();
		N = diagon.size();
		matrix.resize(diagon.size());
		for (size_t i = 0; i < diagon.size(); i++)
		{
			matrix[i].resize(diagon.size());
			for (size_t j = 0; j < diagon.size(); j++) {
				if (i == j)
					matrix[i][j] = diagon[j];
				else
					matrix[i][j] = 0;
			}
		}
	}
};