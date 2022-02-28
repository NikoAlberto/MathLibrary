#pragma once
#include <exception>

using namespace std;

class MyException1 : public exception {
	const char* what() const noexcept {
		return "Dimensional matrix Exception";
	}
};

class MyException2 : public exception {
	const char* what() const noexcept {
		return "UpTriangular Exception";
	}
};

class MyException3 : public exception {
	const char* what() const noexcept {
		return "Multiplication Exception";
	}
};
class MyException4 : public exception {
	const char* what() const noexcept {
		return "LowTriangular Exception";
	}
};

class MyException5 : public exception {
	const char* what() const noexcept {
		return "Dimensions are not more than zero";
	}
};
class MyException6 : public exception {
	const char* what() const noexcept {
		return "Dimensions of vectors are imcompatible";
	}
};

class MyException7 : public exception {
	const char* what() const noexcept {
		return "Determinant is equal to zero";
	}
};

class MyException8 : public exception {
	const char* what() const noexcept {
		return "The file cannot be opened";
	}
};

class MyException9 : public exception {
	const char* what() const noexcept {
		return "The file is not binary. Please, check";
	}
};