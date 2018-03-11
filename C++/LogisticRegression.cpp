
#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _TIME_H_
	#include <time.h>
	#define _TIME_H_
#endif

#ifndef _STDIO_H_
	#include <stdio.h>
	#define _STDIO_H_
#endif

#ifndef _UTILITY_
	#include <utility>
	#define _UTILITY_
#endif


#include "Vector.cpp"
#include "Matrix.cpp"
#include "DataTransform.cpp"


class LogisticRegression{
private:
	vector <vector <double> > X;
	vector <vector <double> > X_t;
	vector <double> y;
	vector <double> theta;
	vector <double> avg;
	vector <double> std;
	int n;
	int m;
	bool isNormalized;
	DataTransform <double> _d;
	double sigmoid(double z){
		return 1/(1+exp(-z));
	}
	vector <double> hypothesis(){
		return Vector::sigmoid(Matrix::multiply(X,theta));
	}
	double cost(){
		vector <double> h = hypothesis();
		return (-1.0/m)*Vector::sum(Vector::sum(Vector::prod(y,Vector::log(h)), Vector::prod(Vector::diff(Vector::ones(y.size()),y),Vector::log(Vector::diff(Vector::ones(h.size()),h)))));
	}
	double cost(double lambda){
		double reg = 0;
		for(int i=1;i<=n;i++){
			reg += theta[i]*theta[i];
		}
		reg *= (lambda/(2.0*m));
		return cost() + reg;
	}
public:
	LogisticRegression(const vector <vector <double> > &data, const vector <double> &label, bool normalize = false){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		if(normalize){
			avg = Matrix::avg(data);
			std = Matrix::std(data);
			X = Matrix::normalize(data);
			isNormalized = true;
		}
		else{
			X = data;
			isNormalized = false;
		}
		for(int i=0;i<m;i++){
			if(fabs(0-label[i])>0.000001 && fabs(1-label[i])>0.000001){
				throw "y must be either 0 or 1.";
			}
		}
		_d.prependColumn(X,Vector::ones(m));
		X_t = Matrix::transpose(X);
		y = label;
		theta = Vector::random(n+1, true);
	}
	double trainByGradientDescent(double alpha, bool printCost = false){
		if(!isNormalized){
			printf("Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.\n");
		}
		theta = Vector::random(n+1, true);
		double prev_cost = cost(), curr_cost;
		while(true){
			theta = Vector::diff(theta, Vector::prod(Matrix::multiply(X_t,Vector::diff(hypothesis(),y)),alpha/m));
			curr_cost = cost();
			if(curr_cost-prev_cost>0 || fabs(curr_cost-prev_cost)<0.000001){
				if(curr_cost-prev_cost > 0.000001){
					printf("A overshoot was observed during learning. Try to decrease the learning rate.\n");
				}
				break;
			}	
			prev_cost = curr_cost;
			if(printCost)
				printf("Cost: %lf\n",curr_cost);
		}
		return prev_cost;
	}
	double trainByRegularizedGradientDescent(double alpha, double lambda, bool printCost = false){
		if(!isNormalized){
			printf("Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.\n");
		}
		theta = Vector::random(n+1, true);
		double prev_cost = cost(lambda), curr_cost;
		double reg = 1 - (alpha*lambda)/m;
		while(true){
			theta = Vector::diff(Vector::prod(theta,reg), Vector::prod(Matrix::multiply(X_t,Vector::diff(hypothesis(),y)),alpha/m));
			curr_cost = cost();
			if(curr_cost-prev_cost>0 || fabs(curr_cost-prev_cost)<0.000001){
				if(curr_cost-prev_cost > 0.000001){
					printf("A overshoot was observed during learning. Try to decrease the learning rate.\n");
				}
				break;
			}	
			prev_cost = curr_cost;
			if(printCost)
				printf("Cost: %lf\n", curr_cost);
		}
		return prev_cost;
	}

	vector <pair<double, double> > predict(vector <vector<double> > X_p){ //Pass a copy since we will modify it.
		// The matrix is automatically verified by rest of the functions.
		if(isNormalized){
			// Renormalize using the same mean and standard deviation.
			for(int i=0;i<n;i++){
				for(int j=0;j<X_p.size();j++){
					X_p[j][i] -= avg[i];
					X_p[j][i] /= std[i];
				}
			}
		}
		_d.prependColumn(X_p,Vector::ones(X_p.size()));
		vector <double> v = Vector::sigmoid(Matrix::multiply(X_p,theta));
		vector <pair<double, double> > res(v.size()); 
		for(int i=0;i<v.size();i++){
			if(v[i]>=0.5){
				res[i].first = 1; 
				res[i].second = v[i]; //The confidence
			}
			else{
				res[i].first = 0;
				res[i].second = 1-v[i];
			}
		}
		return res;
	}
};