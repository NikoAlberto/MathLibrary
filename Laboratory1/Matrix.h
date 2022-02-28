#pragma once
#include<vector>
#include<random>
#include"Exception.h"
using namespace std;
class Matrix
{
protected:
	int M;
	int N;
	vector<vector<double>> matrix;
public:
	
	Matrix() {
		int M = 1;
		int N = 1;
		matrix = { { 1 } };
		matrix.resize(1);
	
	}
	
	Matrix(int m, int n)
	{
		this->M = m;
		this->N = n;
		matrix.resize(M);
		for (int i = 0; i < M; i ++)
		         matrix[i].resize(N);
			
	}

	Matrix(int m, int n, vector<double> mat) {
		this->M = m;
		this->N = n;

		if (M * N != mat.size())
			throw MyException1();
		matrix.resize(M);
		for (int i = 0; i < mat.size(); i+=N)
		{
			     matrix[i/N].resize(N);
			for (int j = 0; j < N; j++)
			{
				this->matrix[i/N][j] = mat[j+i];
			}
		}
	}

	//overload
	friend ostream& operator<<(ostream& cout, Matrix& object);
	friend Matrix operator+(Matrix& object1, Matrix& object2);
	friend Matrix operator-(Matrix& object1, Matrix& object2);
	friend Matrix operator*(Matrix& object1, Matrix& object2);
	

	Matrix& operator*(int num) {
		for (int i = 0; i < this->M; i++)
			for (int j = 0; j < this->N; j++)
		          this->matrix[i][j] *= num;
		return *this;
	}

	friend Matrix& operator*(int num, Matrix& object);

	//METHODs
	//Adamara multiplication
	Matrix& Adamara(Matrix& object1);
	//Transpose
	Matrix& Transpose();
	//save
	void save_file(string bins);
	//load
	void load_file(string bins);

	//FRIEND-FUNCTIONS
	friend void swaprows(Matrix& object, size_t row1, size_t row2);
	friend Matrix& RowReduce(Matrix& object, vector<double>& bearing_vec);
	friend void rowDivision(Matrix& object, size_t row1, double b_el);
	friend void SumRow(Matrix& object, size_t row1, size_t row2, double k);
	friend double scalar_product(Matrix& object1, Matrix& object2);
	friend double trace(Matrix& object);
	friend double vector_module(Matrix& object);
	friend double vector_norm_max(Matrix& object);
	friend double matrix_module(Matrix& object);
	friend double Det(Matrix& object);
	friend Matrix& RowReduce(Matrix& object);
	friend int Rank(Matrix& object);
	friend Matrix& matrix_norm(Matrix& object);
	friend Matrix& vector_norm(Matrix& object);
	friend Matrix& inverse_matrix(Matrix& object);

	friend Matrix& ReadTextFile(Matrix& object, string filet);//
	friend ofstream& operator<<(string filet, Matrix& object);

	friend void CreateBinary(Matrix& object, string bins);
	friend Matrix& ReadBinaryFile(Matrix& object, string bins);
};

#include "Overloaded.h"

//Adamara multiplication
Matrix& Matrix::Adamara(Matrix& object1)
{
	if (this->N != object1.N || this->M != object1.M)
		throw MyException1();

	for (int i = 0; i < this->M; i++)
		for (int j = 0; j < this->N; j++)
			this->matrix[i][j] = this->matrix[i][j] * object1.matrix[i][j];
	
	return *this;
}

//TRANSPOSE

Matrix& Matrix::Transpose() {

	int M_temp = this->N;
	int N_temp = this->M;
	vector<vector<double>> temp;
	temp.resize(M_temp);
	for (size_t i = 0; i < M_temp; i++) {
		temp[i].resize(N_temp);
		for (int j = 0; j < N_temp; j++)
			temp[i][j] = this->matrix[j][i];
	}
	this->M = M_temp;
	this->N = N_temp;
	this->matrix = temp;
	temp.resize(this->M);
	for (size_t i = 0; i < this->M; i++) {
		matrix[i].resize(this->N);
		for (int j = 0; j < this->N; j++)
			this->matrix[i][j] = temp[i][j];
	}
	return *this;
}

void Matrix::save_file(string bins) {
	if (bins.substr(bins.size() - 3, 3) == "txt")
		throw MyException9();
	CreateBinary(*this, bins);
}

void Matrix::load_file(string bins) {

	*this = ReadBinaryFile(*this, bins);
}

#include "Semi-class.h"