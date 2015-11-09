#include <sstream>
#include <iostream>
#include <fstream>
#include <istream>
#include "Matrix.h"
using namespace std;

double* readTXT(char *fileName, int sizeR, int sizeC);
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

void organise_logo();
void find_wally();

double get(int arr[], int i, int j);
int main()
{
	int userselection;

	cout << "select program to run:" << endl;
	cout << "1 - logo re-organisation" << endl;
	cout << endl;

	cin >> userselection;

	switch (userselection)
	{
	case 1:
		cout << "\norganising logo..." << endl;
		organise_logo();
		break;
	default:
		cout << "\nthat is not a valid input..." << endl;
		break;
	}
	cin.get();
	cin.get();
}
void organise_logo()
{
	int m = 512; int n = 512;
	double* input_data = 0;
	double* input_data2 = 0;

	double* output_data = new double[m * n];

	char* inputFileName = "E:\\My Documents\\Github\\PuzzleMatrix\\logo_shuffled.txt";
	input_data = readTXT(inputFileName, m, n);

	char* inputFileName2 = "E:\\My Documents\\Github\\PuzzleMatrix\\logo_with_noise.txt";
	input_data2 = readTXT(inputFileName2, m, n);

	Matrix logo_shuffled(512, 512, input_data);
	Matrix logo_with_noise(512, 512, input_data2);
	Matrix logo_completed(512, 512);

	double score = 0.0;
	double best_score = 0.0;
	int bestX = 0;
	int bestY = 0;

	for (int xx = 0; xx < 481; xx += 32)//reorganises the picture.
	{
		for (int yy = 0; yy < 481; yy += 32)
		{
			Matrix submatrix_shuffle = logo_shuffled.getblock(xx, (xx + 32), yy, (yy + 32));
			best_score = 70000000.0;
			for (int vb = 0; vb < 481; vb += 32)
			{
				for (int as = 0; as < 481; as += 32)
				{
					Matrix submatrix_noise = logo_with_noise.getblock(vb, (vb + 32), as, (as + 32));
					Matrix difference = submatrix_noise - submatrix_shuffle;
					Matrix product = difference * difference;
					score = product.sum();
					if (score < best_score)
					{
						best_score = score;
						bestX = vb;
						bestY = as;
					}
				}
			}
			logo_completed.setblock(bestX, bestY, submatrix_shuffle);
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double temp = logo_completed.get(i, j);
			output_data[i * n + j] = temp;
		}
	}
	char* outputFileName = "E:\\My Documents\\Github\\PuzzleMatrix\\logo_restored.pgm";
	int Q = 255;
	WritePGM(outputFileName, output_data, m, n, Q);

	delete[] input_data;
	delete[] output_data;
}
double Matrix::sum()
{
	double total = 0.0;
	for (int ii = 0; ii < m*n; ii++)
	{
		total = total + data[ii];
	}
	return total;
}
double get(int arr[], int i, int j)
{
	int n = 2;
	return arr[(i * n) + j];
}
Matrix::Matrix(int sizeR, int sizeC)
{
	m = sizeR;
	n = sizeC;

	data = new double[m * n];

	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
		{
			data[i * n + j] = 0;
		}
	}
}
Matrix::Matrix(int sizeR, int sizeC, double value)
{
	//cout<<"\nMatrix::Matrix(int sizeR, int sizeC, double val) is invoked...\n";
	m = sizeR;
	n = sizeC;
	data = new double[m * n];

	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
		{
			data[i * n + j] = value;
		}
	}
}
Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	//cout<<"\nMatrix::Matrix(int sizeR, int sizeC, double* input_data) is invoked...";
	m = sizeR;
	n = sizeC;
	data = new double[m * n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[i * n + j] = input_data[i * n + j];
		}
	}

}
double Matrix::get(int i, int j)const
{
	return data[(i * n) + j];
}
void Matrix::set(int i, int j, double value)
{
	data[i * n + j] = value;
}
Matrix::Matrix(const Matrix& MatrixB)
{
	//cout<<"\nMatrix::Matrix (const Matrix&) is invoked...";

	m = MatrixB.m;
	n = MatrixB.n;

	data = new double[m * n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[i * n + j] = MatrixB.get(i, j);
		}
	}
}
Matrix Matrix::getblock(int start_row, int end_row, int start_column, int end_column)
{
	int row = end_row - start_row;
	int column = end_column - start_column;
	int n = end_column - start_column;

	Matrix t(row, column, 1.2);
	double temp = 0;
	for (int i = start_row; i < end_row; i++)
	{
		for (int j = start_column; j < end_column; j++)
		{
			temp = get(i, j);
			t.set(i - start_row, j - start_column, temp);
		}
	}
	return t;
}
Matrix Matrix::setblock(int start_row, int start_column, Matrix& rhs)
{
	int end_row = start_row + rhs.getm();
	int end_column = start_column + rhs.getn();

	for (int ii = start_row; ii < end_row; ii++)
	{
		for (int jj = start_column; jj < end_column; jj++)
		{
			double temp = rhs.get(ii - start_row, jj - start_column);
			this->set(ii, jj, temp);
		}
	}
	return rhs;
}
Matrix Matrix::operator + (const Matrix& B)
{
	//cout<<"\nMatrix::operator + is invoked...";
	double temp = 0;
	Matrix v(m, n, temp);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp = data[i * n + j] + B.get(i, j);
			v.set(i, j, temp);
		}
	}
	return v;
}
Matrix Matrix::operator - (const Matrix& B)
{
	//cout<<"\nMatrix::operator - is invoked...";
	double temp = 0;
	Matrix v(m, n, temp);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp = data[i * n + j] - B.get(i, j);
			v.set(i, j, temp);
		}
	}
	return v;
}
Matrix Matrix::operator * (const Matrix& B)
{
	//cout<<"\nMatrix::operator * is invoked...";
	double temp = 0;
	Matrix v(m, n, temp);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp = data[i * n + j] * B.get(i, j);
			v.set(i, j, temp);
		}
	}
	return v;
}
Matrix Matrix::operator / (const Matrix& B)
{
	//cout<<"\nMatrix::operator / is invoked...";
	double temp = 0;
	Matrix v(m, n, temp);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp = data[i * n + j] / B.get(i, j);
			v.set(i, j, temp);
		}
	}
	return v;
}
int Matrix::getm() const
{
	return m;
}
int Matrix::getn() const
{
	return n;
}
Matrix Matrix::operator = (const Matrix& B)
{
	if (this == &B)
	{
		return *this;
	}
	else
	{
		delete[] data;

		m = B.getm();
		n = B.getn();

		data = new double[m * n];
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				data[i * n + j] = B.get(i, j);
			}

		}
		return *this;
	}
}
Matrix Matrix::operator ++(int)
{
	for (int i = 0; i < m * n; i++)
	{
		data[i] = data[i] ++;
	}
	return *this;
}
double Matrix::operator () (int i, int j)
{
	//cout<<"\nMatrix::operator() is invoked...";

	return data[(i * n) + j];
}
BinaryImage::BinaryImage(int sizeR, int sizeC, double* input_data, double thresh)
	:Matrix(sizeR, sizeC, input_data)
{
	//cout<<"BinaryImage::BinaryImage(int m, int n, double* input_data, double thresh) is invoked...";

	for (int i = 0; i < m * n; i++)
	{
		if (data[i] > thresh)
		{
			data[i] = 1;
		}
		else
		{
			data[i] = 0;
		}
	}

}
void Matrix::display()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << " " << get(i, j);
		}cout << endl;
	}
}
BinaryImage::BinaryImage(const BinaryImage& rhs)
{
	//cout<<"BinaryImage::BinaryImage(const BinaryImage&) is invoked...";

	m = rhs.getm();
	n = rhs.getn();

	data = new double[m * n];
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[i * n + j] = rhs.get(i, j);
		}
	}
}
Matrix::~Matrix()
{
	//cout<<"\nMatrix::~Matrix is invoked...\n";
	delete[] data;
}
BinaryImage::~BinaryImage()
{
	//cout<<"\nBinaryImage::~BinaryImage() is invoked...\n";
	delete[] data;
}

double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}