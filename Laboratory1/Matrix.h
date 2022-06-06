#pragma once
#include<vector>
#include<iomanip>
#include<fstream>
#include <initializer_list> 
#include <cassert>  
#include<cstring>
#include<sstream>
#include"Exception.h"
using namespace std;
class Matrix
{
protected:
	int M;
	int N;
	vector<vector<double>> matrix;
public:
	
	Matrix();
	Matrix(int m, int n);
	Matrix(int m, int n, vector<double> mat);


	Matrix(initializer_list<double> list);
	int get_Mrows();
	int get_Ncols();
	void set_elm(size_t i, size_t j, double a);
	vector<vector<double>>& get_matrix();
	//overload
	friend ostream& operator<<(ostream& cout, Matrix& object);
	friend Matrix operator+(Matrix& object1, Matrix& object2);
	friend Matrix operator-(Matrix& object1, Matrix& object2);
	friend Matrix operator*(Matrix& object1, Matrix& object2);
	

	
	Matrix& operator*(double num);
	friend Matrix& operator*(double num, Matrix& object);

	//METHODs
	//Adamara multiplication
	Matrix& Adamara(Matrix& object1);
	//Transpose
	Matrix& Transpose();
	//save
	void save_file(string bins);
	//load
	void load_file(string bins);
	//init
	//Matrix& Matrix(initializer_list<double> list);

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
	friend double Mean(Matrix& object, int num);
	friend double Norm_RCA(Matrix& object, int row);
	friend Matrix new_matrix_RCA(Matrix& object);
	friend vector<double> extract_col(Matrix& object, int col);
	friend Matrix& insert_col(Matrix& object1, Matrix& vec);

	friend Matrix& ReadTextFile(Matrix& object, string filet);
	friend ofstream& operator<<(string filet, Matrix& object);
	friend Matrix& operator>>(string filet, Matrix& object);

	friend void CreateBinary(Matrix& object, string bins);
	friend Matrix& ReadBinaryFile(Matrix& object, string bins);
};


      void swaprows(Matrix& object, size_t row1, size_t row2);
	  Matrix& RowReduce(Matrix& object, vector<double>& bearing_vec);
	 void rowDivision(Matrix& object, size_t row1, double b_el);
	 void SumRow(Matrix& object, size_t row1, size_t row2, double k);
	 double scalar_product(Matrix& object1, Matrix& object2);
	 double trace(Matrix& object);
	 double vector_module(Matrix& object);
	 double vector_norm_max(Matrix& object);
	 double matrix_module(Matrix& object);
	 double Det(Matrix& object);
	 Matrix& RowReduce(Matrix& object);
	 int Rank(Matrix& object);
	 Matrix& matrix_norm(Matrix& object);
	 Matrix& vector_norm(Matrix& object);
	 Matrix& inverse_matrix(Matrix& object);
	 double Mean(Matrix& object, int num);
	 double Norm_RCA(Matrix& object, int row);
	 Matrix new_matrix_RCA(Matrix& object);
	 vector<double> extract_col(Matrix& object, int col);
	 Matrix& insert_col(Matrix& object1, Matrix& vec);

	 Matrix& ReadTextFile(Matrix& object, string filet);
	 ofstream& operator<<(string filet, Matrix& object);
	 Matrix& operator>>(string filet, Matrix& object);

	 void CreateBinary(Matrix& object, string bins);
	 Matrix& ReadBinaryFile(Matrix& object, string bins);

	 ostream& operator<<(ostream& cout, Matrix& object);
	 Matrix operator+(Matrix& object1, Matrix& object2);
	 Matrix operator-(Matrix& object1, Matrix& object2);
	 Matrix operator*(Matrix& object1, Matrix& object2);
	 Matrix& operator*(double num, Matrix& object);

//#include "Overloaded.h"

//#include "Semi-class.h"

	 class Singles : public Matrix
	 {

	 public:
		 Singles(int m);
	 };

	 //Symmetric (filling with random numbers)
	 class Symmetric : public Matrix {

	 public:
		 Symmetric(vector<double> sym);
	 };

	 //Triangular

	 class UpTriangular : public Matrix {

	 public:
		 UpTriangular(vector<double> Uptr);

	 };

	 class LowTriangular : public Matrix {

	 public:
		 LowTriangular(vector<double> Uptr);

	 };


	 //Diagonal

	 class Diagonal : public Matrix
	 {

	 public:
		 Diagonal(vector<double> diagon);
	 };