#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#include "Matrix.cpp"
#include "DataTransform.cpp"

class AnomalyDetection{
private:
	vector <vector <double> > X;
	vector <double> avg;
	vector <double> std;
	int m;
	int n;
	double PI = 3.14159265359;
	double gaussianProbability(double x, int i){
		return (1.0/sqrt(2*PI*std[i]*std[i]))*exp((0-((x-avg[i])*(x-avg[i])))/(2*std[i]*std[i]));
	}
public:
	AnomalyDetection(const vector <vector <double> > &data){
		if(data.size()==0) throw "Data must not be empty";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		X = Matrix::normalize(data);
		avg = Matrix::avg(data);
		std = Matrix::std(data);
	}
	vector <double> predict(const vector <vector<double> > &X_p){

		printf("Anamoly detection works best when the features are Gaussian distributed.\n");

		vector <double> res (X_p.size());
		if(X_p.size()==0)	return res;
		if(X_p[0].size()!=n)
			throw "Incorrect number of features for prediction.\n";

		for(int i=0;i<X_p.size();i++){
			res[i] = 1.0;
			for(int j=0;j<n;j++){
				//Normalize
				double x = (X_p[i][j]-avg[j])/std[j];
				res[i] *= gaussianProbability(x, j);
			}
		}
		return res;
	}
	vector <int> predict(const vector <vector<double> > &X_p, double eps){
		vector <double> v = predict(X_p);
		vector <int> res;
		for(int i=0;i<v.size();i++){
			if(v[i]<eps)
				res.push_back(1);
			else
				res.push_back(0);
		}
		return res;
	}

};