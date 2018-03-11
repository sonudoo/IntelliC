
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


#include "Vector.cpp"
#include "Matrix.cpp"
#include "DataTransform.cpp"


class LinearRegression{
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
	vector <double> hypothesis(){
		return Matrix::multiply(X,theta);
	}
	double cost(){
		return (0.5/m)*Vector::sum(Vector::pow(Vector::diff(hypothesis(),y),2));
	}
	double cost(double lambda){
		double reg = 0;
		for(int i=1;i<=n;i++){
			reg += theta[i]*theta[i];
		}
		reg *= lambda;
		return (0.5/m)*(Vector::sum(Vector::pow(Vector::diff(hypothesis(),y),2)) + reg);
	}
public:
	LinearRegression(const vector <vector <double> > &data, const vector <double> &label, bool normalize = false){
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
				printf("Cost: %lf\n",curr_cost);
		}
		return prev_cost;
	}
	void trainByNormalEquation(){
		try{
			// Calculate inv(X'X)*X'*y. It can be mathematically proved that multiplying X' and y first has asymptotically less complexity (O(mn+n^2)). 
			theta = Matrix::multiply(Matrix::inverse(Matrix::multiply(X_t,X)),Matrix::multiply(X_t,y));
		}
		catch(const char *s){
			//May throw inverse doesn't exists exception.
			//Use regularization as for any lambda > 1, the matrix will be invertible.
			theta = Matrix::multiply(Matrix::pinverse(Matrix::multiply(X_t,X)),Matrix::multiply(X_t,y));
		}
	}

	void trainByRegularizedNormalEquation(double lambda){
		//Calculate inv(X'X  + lambda*(0 0....))*X'*y
		vector <vector <double> > mat = Matrix::multiply(X_t,X); //(n+1)x(n+1)
		for(int i=1;i<mat.size();i++){
			mat[i][i] += lambda;
		}
		theta = Matrix::multiply(Matrix::inverse(mat),Matrix::multiply(X_t,y));
		//printf("Cost: %lf %lf %lf\n",theta[0], theta[1], cost());
	}
	void trainByRegularizedNormalEquation(){
		//Automatically decide the best lambda. Split training and cross-validation set

		vector <int> rand = Vector::random_permutation(m);

		vector <vector<double> > X_train;
		vector <vector<double> > X_val;
		vector <double> y_train;
		vector <double> y_val;
		int m_train = 0.7*m;
		int m_val = m - m_train;
		for(int i=0;i<m_train;i++){
			X_train.push_back(X[rand[i]-1]);
			y_train.push_back(y[rand[i]-1]);
		}
		for(int i=m_train;i<m;i++){
			X_val.push_back(X[rand[i]-1]);
			y_val.push_back(y[rand[i]-1]);
		}

		vector <vector<double> > X_train_t = Matrix::transpose(X_train);
		vector <vector<double> > X_t_X = Matrix::multiply(X_train_t,X_train);

		//Calculate inv(X'X  + lambda*(0 0....))*X'*y
		double low = 0;
		double high = 100000;
		double val_error_1, val_error_2;
		while(fabs(high-low)>0.000001){
			double lambda1 = (high+2*low)/3;
			double lambda2 = (2*high+low)/3;
			for(int i=1;i<X_t_X.size();i++){
				X_t_X[i][i] += lambda1;
			}
			theta = Matrix::multiply(Matrix::inverse(X_t_X),Matrix::multiply(X_train_t,y_train));
			for(int i=1;i<X_t_X.size();i++){
				X_t_X[i][i] -= lambda1;
			}
			val_error_1 = (0.5/m_val)*Vector::sum(Vector::pow(Vector::diff(Matrix::multiply(X_val,theta),y_val),2));

			for(int i=1;i<X_t_X.size();i++){
				X_t_X[i][i] += lambda2;
			}
			theta = Matrix::multiply(Matrix::inverse(X_t_X),Matrix::multiply(X_train_t,y_train));
			for(int i=1;i<X_t_X.size();i++){
				X_t_X[i][i] -= lambda2;
			}
			val_error_2 = (0.5/m_val)*Vector::sum(Vector::pow(Vector::diff(Matrix::multiply(X_val,theta),y_val),2));

			//printf("Cost: %lf %lf %lf %lf\n",lambda1, lambda2, val_error_1, val_error_2);

			if(val_error_1 > val_error_2){
				low = lambda1;
			}
			else{
				high = lambda2;
			}
		}
		trainByRegularizedNormalEquation(low);
	}


	vector <double> predict(vector <vector<double> > X_p){ //Pass a copy since we will modify it.
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
		return Matrix::multiply(X_p,theta);
	}
};