#include<cmath>
#include<fstream>
#include <iostream>
//#include "Filework.h"
#define EPS 1e-10
#include "Exception.h"
#include "Matrix.h"
//#include "RCA.h"

Matrix& operator*(double num, Matrix& object)
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
			if (abs(object.matrix[i][j]) < 1e-33)
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

	//Cout of subclass
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
		if (object1.M != object2.M || object1.N != object2.N)
			throw MyException6();
		double k = 0;
		if(object1.N ==1 )
		    for (size_t i = 0; i < object1.M; i++)
			    k += object1.matrix[i][0] * object2.matrix[i][0];
		if (object1.M == 1)
			for (size_t i = 0; i < object1.N; i++)
				k += object1.matrix[0][i] * object2.matrix[0][i];
		return k;

	}
	/*double scalar_product(Matrix& object1, Matrix& object2) {
		double k = 0;
		if (object1.N == 1 && object2.N == 1 || object1.M == 1 && object2.N == 1 ||
			object1.M == 1 && object2.M == 1 || object1.N == 1 && object2.M == 1) {

			Matrix v1 = object1;
			Matrix v2 = object2;

			if (v1.M != 1)
				v1.Transpose();
			if (v1.M != v2.M)
				v2.Transpose();
			int subtr = abs(v1.N - v2.N);
			if (v1.N < v2.N) {
				v1.N = v1.N + subtr;
				v1.matrix[0].resize(v1.N);
				for (size_t i = v1.N - 1; i >= v1.N - subtr; i--)
					v1.matrix[0][i] = 0;
			}
			if (v2.N < v1.N) {
				v2.N = v2.N + subtr;
				v2.matrix[0].resize(v2.N);
				for (size_t i = v2.N - 1; i >= v2.N - subtr; i--)
					v2.matrix[0][i] = 0;
			}
			for (size_t i = 0; i < v1.N; i++)
				k += v1.matrix[0][i] * v2.matrix[0][i];
		}
		else
			throw MyException6();
		return k;
	}*/

	
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
	
	double Mean(Matrix& object, int col)
	{
		double sum = 0, mj = 0;
		for (size_t i = 0; i < object.M; i++)
			sum += object.matrix[i][col];
		mj = sum / (object.M);
		return mj;
	}

	double Norm_RCA(Matrix& object, int col)
	{
		double sj = 0, counter = 0;
		
		for (size_t j = 0; j < object.M; j++)
			counter += (object.matrix[j][col] - Mean(object, col))* (object.matrix[j][col] - Mean(object, col));
		sj = sqrt(counter / (double(object.M)-1));
		return sj;
	}

	Matrix new_matrix_RCA(Matrix& object) {
		//Matrix object_new(object.M, object.N);
		Matrix object_new = object;
		for (size_t i = 0; i < object.N; i++)
			for (size_t j = 0; j < object.M; j++)
				object_new.matrix[j][i] = (object.matrix[j][i] - Mean(object, i)) / Norm_RCA(object, i);
		return object_new;
	}

	vector<double> extract_col(Matrix& object, int col) {
		vector<double> vec;
		vec.resize(object.M);
		for (size_t j = 0; j < object.M; j++)
			vec[j] = object.matrix[j][col];
		return vec;
	}


	Matrix& insert_col(Matrix& object1, Matrix& vec) {
		if (vec.N != 1)
			vec.Transpose();
		//if(object1.M != vec.M)
			//throw MyException6();
		if (object1.M == object1.N == 1) {
			object1.matrix.resize(vec.M);
			object1.M = vec.M;
			for (size_t i = 0; i < object1.M; i++)
			     object1.matrix[i] = vec.matrix[i];
		}
		else {
			int N = object1.N;
			for (size_t i = 0; i < object1.M; i++)
			{
				object1.matrix[i].resize(N + 1);
				object1.matrix[i][N] = vec.matrix[i][0];
			}
			object1.N++;
		}
		return object1;
	}





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

	Matrix& Matrix::operator*(double num) {
		for (int i = 0; i < this->M; i++)
			for (int j = 0; j < this->N; j++)
				this->matrix[i][j] *= num;
		return *this;
	}










	





/*	Matrix& ReadTextFile(Matrix& object, string filet) {

		string s;
		ifstream file(filet);
		if (!file) {

			cerr << "Could not be opened for reading!" << endl;
			exit(1);
		}
		size_t array_size = 0;
		while (getline(file, s))
			array_size++;
		s.clear();
		file.clear();
		file.seekg(0);


		string comastr = ",";
		string dotstr = ".";
		stringstream ss;
		vector <vector<double>> rows;
		rows.resize(array_size);
		size_t i = 0;
		while (getline(file, s)) {
			while (s.find(comastr) != -1) {
				size_t pos = s.find(comastr);
				s.replace(pos, 1, dotstr);
			}

			ss.clear();
			ss.str(s);
			string data = "";
			while (getline(ss, data, '\t')) {
				stringstream element;
				element << data;
				double number = 0.0;
				element >> number;
				rows[i].push_back(number);

			}
			i++;
		}

		int M_number = 0;

		M_number = rows.size();

		for (size_t j = 1; j < M_number; j++)
			if (rows[j].size() != rows[j - 1].size())
				throw MyException1();
		int N_number = rows[0].size();
		object.M = M_number;
		object.N = N_number;

		object.matrix.resize(object.M);
		for (size_t j = 0; j < object.M; j++) {
			object.matrix[j].resize(object.N);

			for (size_t l = 0; l < object.N; l++)
				object.matrix[j][l] = rows[j][l];
		}
		file.close();
		cout << "\n" << "Getting Data Successful" << "\n" << endl;

		return object;
	}

	//Cout in text file
	ofstream& operator<<(string filet, Matrix& object)
	{
		ofstream out;
		out.open(filet, ios_base::out);

		for (int i = 0; i < object.get_Mrows(); i++)
		{
			for (int j = 0; j < object.get_Mrows(); j++) {
				if (abs(object.get_matrix()[i][j]) < pow(10, -5))
					out << "0.000" << '\t';
				else
				{

					out << setw(5) << object.get_matrix()[i][j] << '\t';
				}
			}
			out << endl;
		}
		return out;
	}

	//Get the file into matrix
	Matrix& operator>>(string filet, Matrix& object)
	{
		ReadTextFile(object, filet);

		return object;
	}

	//BINARY ENTER&&OUT
	void CreateBinary(Matrix& object, string bins)
	{
		ofstream binary_file(bins, ios::out | ios::binary);
		if (!binary_file)
			throw MyException8();
		binary_file.seekp(0);
		for (size_t i = 0; i < object.M; i++)
			for (size_t j = 0; j < object.N; j++)
				binary_file.write((char*)&object.matrix[i][j], sizeof(double));
		binary_file.write((char*)&object.M, sizeof(object.M));
		binary_file.write((char*)&object.N, sizeof(object.N));
		binary_file.close();

	}
	Matrix& ReadBinaryFile(Matrix& object, string bins)
	{
		int size_bin, size_temp = 0;
		vector<vector<double>> vec = {};
		ifstream binary_file(bins, ios::binary | ios::in);
		if (!binary_file)
			throw MyException8();

		binary_file.seekg(0, ios::end);
		size_temp = binary_file.tellg();

		size_bin = size_temp - 2 * sizeof(int);
		binary_file.seekg(size_bin, ios::beg);
		binary_file.read((char*)&object.M, sizeof(object.M));
		binary_file.read((char*)&object.N, sizeof(object.N));

		binary_file.seekg(0, ios::beg);

		object.matrix.resize(object.M);
		for (size_t i = 0; i < object.M; i++) {
			object.matrix[i].resize(object.N);
			for (size_t j = 0; j < object.N; j++)
				binary_file.read((char*)&object.matrix[i][j], sizeof(double));
		}

		binary_file.close();

		return object;
	}

	*/



	