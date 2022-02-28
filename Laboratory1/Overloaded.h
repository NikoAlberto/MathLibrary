#pragma once
#include<cmath>
#include "Filework.h"
Matrix& operator*(int num, Matrix& object)
{

	for (int i = 0; i < object.M; i++)
		for (int j = 0; j < object.N; j++)
			object.matrix[i][j] *= num;

	return object;
}


ostream& operator<<(ostream& cout, Matrix& object)
{
	for (int i = 0; i < object.M; i++)
	{
		for (int j = 0; j < object.N; j++) {
			if (abs(object.matrix[i][j]) < pow(10, -8))
				cout << "0" << '\t';
			else
				cout << object.matrix[i][j] << '\t';
		}
		cout << endl;
	}
	return cout;
}

Matrix operator+(Matrix& object1, Matrix& object2)
{
	if (object1.N != object2.N || object1.M != object2.M)
		throw MyException1();
	
    for (int i = 0; i < object1.M; i++)
		for (int j = 0; j < object1.N; j++)
			object1.matrix[i][j] = object1.matrix[i][j] + object2.matrix[i][j];
	
	return object1;


}
Matrix operator-(Matrix& object1, Matrix& object2)
{
	if (object1.N != object2.N || object1.M != object2.M)
		throw MyException1();

	for (int i = 0; i < object1.M; i++)
		for (int j = 0; j < object1.N; j++)
			object1.matrix[i][j] = object1.matrix[i][j] - object2.matrix[i][j];
	
	return object1;

}

Matrix operator*(Matrix& object1, Matrix& object2)
{
	Matrix object3(object1.M, object2.N);
	if (object1.N != object2.M )
		throw MyException3();

	for (int i = 0; i < object1.M; i++)
		for (int j = 0; j < object2.N; j++)
		{
			object3.matrix[i][j] = 0;
			for (int k = 0; k < object1.N; k++)
				object3.matrix[i][j] += object1.matrix[i][k] * object2.matrix[k][j];
		}
	

	return object3;
}

	//Вывод подкласса
	ostream& operator<<(ostream & cout, vector<vector<double>> v)
	{
		int lenv = v.size();
		for (int i = 0; i < lenv; i++)
		{
			cout << endl;
			for (int j = 0; j < lenv; j++)
				cout << v[i][j] << '\t';
		}
		return cout;
	}



	//Gaussian elimination
	void swaprows(Matrix& object, size_t row1, size_t row2)
	{
		if (row1 == row2)
			return;
		for (size_t i = 0; i < object.N; i++)
			std::swap(object.matrix[row1][i], object.matrix[row2][i]);
	}

	void rowDivision(Matrix& object, size_t row1, double b_el) {

		for (size_t i = 0; i < object.N; i++)
			object.matrix[row1][i] /= b_el;
	}
	void SumRow(Matrix& object, size_t row1, size_t row2, double k) {

		for (size_t i = 0; i < object.N; i++)
			object.matrix[row1][i] += k* object.matrix[row2][i];
	
	}

	Matrix& RowReduce(Matrix& object, vector<double>& bearing_vec) {
	
		vector<int> bearing_elm = { 0,0 };
		vector<int> start_pos = { 0,0 }; 
		int counter = 0, sign = 0;
		while (start_pos[0] < object.M && start_pos[1] < object.N)
		{
			bearing_elm = start_pos;
			for (size_t i = start_pos[0]; i < object.N; i++)
				for (size_t j= start_pos[1]; j < object.M; j++)
					if (object.matrix[i][j] != 0 && j < object.N) {
						bearing_elm[0] = i;
						bearing_elm[1] = j;
						counter++;
						goto out;
					}
			out:
			if (counter == 0) return object;

			bearing_vec.push_back(object.matrix[bearing_elm[0]][bearing_elm[1]]);//vector for leading elements to count the det

			if (object.matrix[bearing_elm[0]][bearing_elm[1]] != 0)
			{
			
				sign++;
				swaprows(object, bearing_elm[0], start_pos[0]);
				
				bearing_elm[0] = start_pos[0];
				rowDivision(object, bearing_elm[0], object.matrix[bearing_elm[0]][bearing_elm[1]]);

				
				for (size_t i = 0; i < object.M; i++)
					if (object.matrix[i][bearing_elm[1]] != 0 && i != bearing_elm[0]) {
						double k = -(double)object.matrix[i][bearing_elm[1]];
						SumRow(object, i, bearing_elm[0], k);
					}

			}
			start_pos[1] = bearing_elm[1] + 1;
			start_pos[0]++;
		}
		bearing_vec.push_back(sign - object.M);
	
		return object;
	
	}

	//RowReduce overloaded with other quantity of parameters
	Matrix& RowReduce(Matrix& object)
	{
		vector<double> bearing_vec = {};
		return RowReduce(object, bearing_vec);
	}

	//DETERMINANT
	double Det(Matrix& object) {
		vector<double> bearing_vec = {};
		int sign = 0;
		Matrix object1(object.M, object.N);
		object1 = object;
		RowReduce(object1, bearing_vec);
		double det_value = 1;
		for (size_t i = 0; i < object1.M; i++)
			det_value *= object1.matrix[i][i];
		sign = bearing_vec.back();
		bearing_vec.pop_back();
		for (double it : bearing_vec)
			det_value *= it;
		det_value = det_value * pow(-1, sign);
		return det_value;
	}


	//SCALAR PRODUCT
	double scalar_product(Matrix& object1, Matrix& object2) {
		if (object1.M != object2.M || object1.N != object2.N || object1.N != 1)
			throw MyException6();
		double k = 0;
		for (size_t i = 0; i < object1.M; i++)
			k += object1.matrix[i][0] * object2.matrix[i][0];
		return k;

	}

	
	//TRACE
	double trace(Matrix& object) {
		if (object.M != object.N)
			throw MyException1();
		double k = 0;
		for (size_t i = 0; i < object.M; i++)
			k += object.matrix[i][i];
		return k;

	}

	//Normalization
	//Evklid norm
	double vector_module(Matrix& object)
	{
		if (object.M != 1 && object.N != 1)
			throw MyException6();
		double k = 0, norm = 0;
		if (object.N == 1)
		{
			for (size_t i = 0; i < object.M; i++)
				k += pow(object.matrix[i][0], 2);
			norm = sqrt(k);
		}
		else
		{
			for (size_t i = 0; i < object.N; i++)
				k += pow(object.matrix[0][i], 2);
			norm = sqrt(k);
		}
		return norm;

	}

	Matrix& vector_norm(Matrix& object)
	{
		double k = matrix_module(object);
		for (size_t i = 0; i < object.M; i++)
			for (size_t j = 0; j < object.N; j++)
				object.matrix[i][j] /= k;
		return object;
	}
	//Max Normal
	double vector_norm_max(Matrix& object)
	{
		if (object.M != 1 && object.N != 1)
			throw MyException6();
		double max = abs(object.matrix[0][0]);
		if (object.N == 1) {
			for (size_t i = 0; i < object.M; i++)
				if (max < abs(object.matrix[i][0]))
					max = abs(object.matrix[i][0]);
		}
		else {
			for (size_t i = 0; i < object.N; i++)
				if (max < abs(object.matrix[0][i]))
					max = abs(object.matrix[0][i]);
		}
		return max;
	}


	//Frobenius norm
	double matrix_module(Matrix& object)
	{
		double sum = 0, norm = 0;
		for (size_t i = 0; i < object.M; i++)
			for (size_t j = 0; j < object.N; j++)
				sum += pow(object.matrix[i][j], 2);
		norm = sqrt(sum);
		return norm;
	}
	
	
	Matrix& matrix_norm(Matrix& object)
	{
		double k = matrix_module(object);
		for (size_t i = 0; i < object.M; i++)
			for (size_t j = 0; j < object.N; j++)
				object.matrix[i][j] /= k;
		return object;
	}


	//Angle betweeen vectors
	
	double vec_angle(Matrix& object1, Matrix& object2)
	{
		double v1 = vector_module(object1);
		double v2 = vector_module(object2);

		return acos((scalar_product(object1, object2)) / (v1 * v2));
	}

	//RANK
	int Rank(Matrix& object) {
		int rank = object.M;
		vector<double> bearing_vec = {};

		Matrix object1(object.M, object.N);
		object1 = object;

		RowReduce(object1, bearing_vec);

		for (size_t i = object1.M - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < object1.N; j++)
				if (object1.matrix[i][j] != 0)
					goto out1;
			rank--;
		}
		out1:
		return rank;
	}

//Inverse

	Matrix& inverse_matrix(Matrix& object)
	{
		if (object.M != object.N)
			throw MyException1();
		if(Det(object) ==0)
			throw MyException7();

		Matrix augmented(object.M, object.N*2);

		for (size_t i = 0; i < object.M; i++)
			for (size_t j = 0; j < object.N; j++)
				augmented.matrix[i][j] = object.matrix[i][j];
		for (size_t i = 0; i < object.M; i++)
		{
			for (size_t j = object.N; j < object.N * 2; j++)
				augmented.matrix[i][j] = 0;
			augmented.matrix[i][i + object.N] = 1;
		}

		RowReduce(augmented);

		Matrix inverse(object.M, object.N);

		for (size_t i = 0; i < object.M; i++)
			for (size_t j = object.N; j < object.N * 2; j++)
				inverse.matrix[i][j - object.N] = augmented.matrix[i][j];

		object = inverse;
		return object;
	}
	
