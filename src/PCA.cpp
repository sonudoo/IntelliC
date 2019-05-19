#include <vector>
#include "Matrix.cpp"
#include "DataTransform.cpp"

class PCA{
private:
	vector <vector <double> > X;
	vector <vector <double> > X_t;
	vector <vector <double> > U;
	vector <vector <double> > E;
	vector <vector <double> > V_t;
	DataTransform <double> _d;
	int m;
	int n;
public:
	PCA(const vector <vector <double> > &data){
		if(data.size()==0) throw "Data must not be empty";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		X = Matrix::normalize(data);
		X_t = Matrix::transpose(X);
		Matrix::svd(Matrix::prod(Matrix::multiply(X_t,X),1.0/m), U, E, V_t);
	}
	vector <vector<double> > reduce(int k){
		// It is advised to reduce all of the dataset - training, validation and test set at the same time. This will take care of any further normalization issue

		if(k>n || k<=0)
			throw "Reduce dimensions must be between 1 and N";

		return Matrix::multiply(X, _d.sliceColumn(U, 0, k));
	}
	vector <vector<double> > getReduceMatrix(int k){
		// It is advised to reduce all the dataset - training, validation and test set at the same time. This will take care of any further normalization issue
		if(k>n || k<=0)
			throw "Reduce dimensions must be between 1 and N";
		return _d.sliceColumn(U, 0, k);
	}
	double retainedVariance(int k){
		if(k>n || k<=0)
			throw "Reduce dimensions must be between 1 and N";
		double s1 = 0, s2 = 0;
		for(int i=0;i<n;i++){
			s1 += E[i][i];
			if(i<k)
				s2 += E[i][i];
		}
		return s2/s1;
	}
};