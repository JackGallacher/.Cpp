#pragma
#ifndef MATRIX_H//define header file
#define MATRIX_H//define header file

class Matrix//matrix class
{
public://public function
	Matrix(){ m = 0, n = 0, data = 0; }//default values
	Matrix(int sizeR, int sizeC);//int, int matrix
	Matrix(int sizeR, int sizeC, double value);//int, int, double matrix
	Matrix(int sizeR, int sizeC, double* input_data);//in, int, double* matrix
	double get(int i, int j)const;//get function
	void set(int i, int j, double value);//set function
	Matrix(const Matrix& MatrixB);//copy constrctor
	Matrix getblock(int start_row, int end_row, int start_column, int end_column);//getblock function
	Matrix setblock(int start_row, int start_column, Matrix& rhs);//setblock function
	Matrix operator + (const Matrix& B);//+ operator
	Matrix operator - (const Matrix& B);// - operator
	Matrix operator * (const Matrix& B);// * operator
	Matrix operator / (const Matrix& B);// / operator
	Matrix operator = (const Matrix& B);//= operator
	double operator () (int i, int j);//() operator
	int getm() const;//gets m
	int getn() const;// gets n 
	Matrix operator ++(int);//increments by 1
	void display();//displays matrix
	double sum();//sums matrix
	~Matrix();//deconstructor

protected://protected function
	int m;//m value
	int n;//n vlaue
	double* data;// pointer value
};
class BinaryImage//binaray image class
	:public Matrix//sub of matrix
{
public://public function
	BinaryImage(int sizeR, int sizeC, double* input_data, double thresh);//sets matrix to binary
	BinaryImage(const BinaryImage& BinaryImageF);//binary 
	~BinaryImage();//deconstrctor
};

#endif//ends if