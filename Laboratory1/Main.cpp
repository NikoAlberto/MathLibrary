#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<cassert>
#include<iostream>
#include<algorithm>
#include "Matrix.h"


int main() {

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filet = "loadings.txt";
	string testwrite = "testwrite.txt";
	string bins = "mybin.dat";
	try {
		vector<double> v1 = { 1,2,3,4,5,6 };
		vector<double> v2 = { -1,-2,-3,-4,-5, -6 };
		vector<double> v3 = { 3,4,5,6,7,8 };
		Matrix m1(3,2, v1);
		Matrix m2(2, 3, v2);
		Matrix m0(3, 2, v3);

		cout << "Basic matrix:" << endl;
		cout << m1<< endl;

		cout << "Multiplication:" << endl;
		Matrix m3 = m1 * m2;
		cout << m3 << endl;

		cout << "Adamara multiplication:" << endl;
		Matrix m4 = m1.Adamara(m0);
		cout << m4 << endl;

		cout << "Diagonal creation:" << endl;
		Diagonal m5(v1);
		cout << m5 << endl;
	
		 cout << "Low Triangular creation:" << endl;
		LowTriangular m6(v1);
		cout << m6 << endl;

		cout << "Up Triangular creation:" << endl;
		UpTriangular m7(v1);
		cout << m7 << endl;
		
		cout << "Symmetric creation:" << endl;
		Symmetric m8(v1);
		cout << m8 << endl;
		
		cout << "Identity matrix creation:" << endl;
		Singles m9(4);
		cout << m9 << endl << endl;

		
		vector<double> v4 = { 1,12,3,14,5,26,7,0, 9};
		vector<double> v5 = { 1,2,3,4,5,6,7,8,9 };

		Matrix sc1(9, 1, v4);
		Matrix sc2(9, 1, v5);
		cout << "Scalar product:" << endl;
		cout<< scalar_product(sc1, sc2)<< endl<< endl;

		Matrix  t1(2, 3, v1);
		cout << "Rank of the matrix:" << endl;
		cout << t1<<endl;
		cout << "Is " <<Rank(t1)<<endl<<endl;

		cout << "Transposed matrix:" << endl;
		cout << t1.Transpose()<< endl;

		cout << "The alteration of type of the matrix to row reduced by Gaussian elimination:" << endl;
		cout << RowReduce(t1) << endl;

		Matrix t2(3, 3, v5);
		cout << "Determinant of the following matrix:"<<endl;
		cout << t2 << endl;
		cout << "Is " << Det(t2) << endl<<endl;

		cout << "Norm of the matrix:" << endl;
		cout << matrix_norm(t2) << endl<<endl;

		Matrix x1(9, 1, v4);
		Matrix x2(9, 1, v5);
		cout << "Angle between the following vectors:" << endl;
		cout << x1 << endl;
		cout << x2 << endl;
		cout <<"Is equal to "<<  vec_angle(x1, x2)<<endl<<endl;
		cout << "Norm of the second vector is: " << endl;
		cout << vector_norm(x2) << endl;
		cout << "And the max norm of the vector is: " << vector_norm_max(x2)<<endl<<endl;

		Matrix inv(3, 3, v4);
		cout << "The trace for the following matrix:" << endl;
		cout << inv<<endl;
	    cout <<"Is "<< trace(inv)<<endl<<endl;
		cout << "Inverse matrix:" << endl;
		Matrix e2 = inv;
		Matrix e1 = inverse_matrix(inv)*e2;
		cout << e1  << endl<<endl<<endl;
	
		cout << "FILES" << endl << endl;
		cout << "Matrix from the file loading.txt" << endl;
		//Запись из исходного файла в матрицу, используя перегрузку, и вывод в консоль
		Matrix tested;
		filet >> tested;
		cout << tested << endl<< endl;
		//hhh
		//Запись содержимого матрицы в файл testwrite.txt, используя перегрузку
		testwrite << tested;

		//Бинарный файл, записываем содержимое tested
		CreateBinary(tested, bins);
	
		//Считаем из бинарного файла матрицу в temp
		Matrix temp;
		cout << "The same matrix written in the binary file and than read and put into console:" << endl;
		cout << ReadBinaryFile(temp, bins) << endl <<endl;

		cout << "Testing the methods of binary file. Doing 'save' in the new file and 'load' from this file. " << endl;
		cout << "The same matrix:" << endl;
		Matrix new1;
		tested.save_file("new.dat");
		new1.load_file("new.dat");
		cout << new1;

		cout << endl << endl << "***************************************************" << endl << endl;
		cout << new_matrix_RCA(tested);
	}

	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}

