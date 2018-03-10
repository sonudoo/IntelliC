
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


#include "vector.cpp"
#include "matrix.cpp"
#include "data_transform.cpp"


class NeuralNetwork{
private:
	vector <vector <double> > X;
	vector <vector <double> > X_t;
	vector <vector <double> > Y;
	vector <vector <vector <double> > > theta;
	vector <vector <vector <double> > > neurons; //Triple dimension: This is because there will be m neural network each having same theta. 
	vector <double> avg;
	vector <double> std;
	int n;
	int m;
	int input_layer_size;
	int output_layer_size;
	int hidden_layer_count;
	bool isNormalized;
	DataTransform <double> _d;
	double sigmoid(double z){
		return 1/(1+exp(-z));
	}
	static double randDouble(bool positiveOnly = false){
		if(rand()%2==0 || positiveOnly)
			return (double)rand()/(double)RAND_MAX;
		else
			return -(double)rand()/(double)RAND_MAX;
	}
	vector <vector<double> > hypothesis(){
		return Matrix::sigmoid(neurons[hidden_layer_count]);
	}
	double cost(double lambda){
		vector <vector<double> > h = hypothesis();
		vector <double> v1 = Matrix::sum(Matrix::prod(Y, Matrix::log(h)));
		vector <double> v2 = Matrix::sum(Matrix::prod(Matrix::diff(Matrix::ones(Y.size(), Y[0].size()) , Y),Matrix::log(Matrix::diff(Matrix::ones(h.size(), h[0].size()) , h))));
		double reg = 0;
		for(int i=0;i<theta.size();i++){
			for(int j=0;j<theta[i].size();j++){
				for(int k=1;k<theta[i][j].size();k++){
					reg += theta[i][j][k]*theta[i][j][k];
				}
			}
		}
		return (-1.0/m)*Vector::sum(Vector::sum(v1,v2)) + (lambda/(2*m))*reg;
	}
	void forwardPropagate(){
		vector <vector<double> > v = Matrix::multiply(X, Matrix::transpose(theta[0]));
		_d.prependColumn(v,Vector::ones(m));
		neurons[0] = v;
		for(int i=1;i<hidden_layer_count;i++){
			v = Matrix::multiply(neurons[i-1], Matrix::transpose(theta[i]));
			_d.prependColumn(v,Vector::ones(m));
			neurons[i] = v;
		}
		v = Matrix::multiply(neurons[hidden_layer_count-1], Matrix::transpose(theta[hidden_layer_count]));
		neurons[hidden_layer_count] = v;
	}
	void backPropagate(vector <vector <vector <double> > > &Delta){
		
		vector <vector <double> > h = hypothesis();
		for(int i=0;i<m;i++){
			vector <vector <double> > del;
			del.push_back(Vector::diff(h[i],Y[i]));
			for(int j=1;j<=hidden_layer_count;j++){
				vector <double> al = neurons[hidden_layer_count-j][i];
				vector <double> al1 = Vector::diff(Vector::ones(al.size()),al);
				del.push_back(Vector::prod(Matrix::multiply(Matrix::transpose(theta[hidden_layer_count-j+1]),del[j-1]),Vector::prod(al,al1)));
			}
			reverse(del.begin(),del.end());
			try{
			Delta[0] = Matrix::sum(Delta[0], Matrix::multiply(Vector::upgrade(del[0]),Matrix::transpose(Vector::upgrade(X[i]))));
		}
		catch(const char *s){
			printf("%d %d %d %d\n",Delta[0].size(), Delta[0][0].size(), del[0].size());
		}
			for(int j=1;j<=hidden_layer_count;j++){
				Delta[j] = Matrix::sum(Delta[j], Matrix::multiply(Vector::upgrade(del[j]),Matrix::transpose(Vector::upgrade(neurons[j-1][i]))));
			}
		}

	}
public:
	NeuralNetwork(const vector <vector <double> > &data, const vector <vector<double> > &label, const vector <int> &hidden_unit, bool normalize = false){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		if(!Matrix::isMatrix(label))	throw "Y must be a matrix (i.e double dimensional vector)\n";

		m = data.size();
		n = data[0].size();
		input_layer_size = n+1;
		output_layer_size = label[0].size();

		for(int i=0;i<m;i++){
			int cnt = 0;
			for(int j=0;j<output_layer_size;j++){
				if(fabs(label[i][j]-1)>0.000001 && fabs(label[i][j])>0.000001){
					throw "Y must be either 0 or 1.\n";
				}

				if(fabs(label[i][j]-1)<=0.000001){
					cnt++;
				}
			}
			if(cnt!=1){
				throw "Each X must have exactly one label.\n";
			}
		}
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

		Y = label;

		int curr = input_layer_size;
		for(int l=0;l<hidden_unit.size();l++){
			vector <vector<double> > layer;
			for(int j=0;j<hidden_unit[l];j++){
				vector <double> row = Vector::random(curr);
				for(int i=0;i<row.size();i++){
					row[i] /= 1000;
				}
				layer.push_back(row);
			}
			curr = 1+hidden_unit[l];
			theta.push_back(layer);
		}
		vector <vector<double> > layer;
		for(int j=0;j<output_layer_size;j++){
			vector <double> row = Vector::random(curr);
			for(int i=0;i<row.size();i++){
				row[i] /= 1000;
			}
			layer.push_back(row);
		}
		theta.push_back(layer);

		//We are not adding first layer to the list of neurons. First layer is X itself.
		vector <vector<double> > v = Matrix::multiply(X, Matrix::transpose(theta[0]));
		_d.prependColumn(v,Vector::ones(m));
		neurons.push_back(v);
		for(int i=1;i<hidden_unit.size();i++){
			v = Matrix::multiply(neurons[i-1], Matrix::transpose(theta[i]));
			_d.prependColumn(v,Vector::ones(m));
			neurons.push_back(v);
		}
		v = Matrix::multiply(neurons[hidden_unit.size()-1], Matrix::transpose(theta[hidden_unit.size()]));
		neurons.push_back(v);

		hidden_layer_count = hidden_unit.size();

	}
	double trainByGradientDescent(double alpha, bool printCost = false){
		if(!isNormalized){
			printf("Gradient Descent without Normalization may take a long time to complete. Try to normalize the features for faster descent.\n");
		}
		srand(time(0));
		for(int i=0;i<theta.size();i++){
			for(int j=0;j<theta[i].size();j++){
				for(int k=0;k<theta[i][j].size();k++){
					theta[i][j][k] = randDouble()/1000;
				}
			}
		}

		double prev_cost = cost(100), curr_cost;
		while(true){
			forwardPropagate();

			vector <vector<vector<double> > > Delta  = theta;
			for(int i=0;i<Delta.size();i++){
				for(int j=0;j<Delta[i].size();j++){
					for(int k=0;k<Delta[i][j].size();k++){
						Delta[i][j][k] = 0;
					}
				}
			}

			backPropagate(Delta);

			for(int i=0;i<Delta.size();i++){
				for(int j=0;j<Delta[i].size();j++){
					for(int k=0;k<Delta[i][j].size();k++){
						if(k==0)
							theta[i][j][k] = theta[i][j][k] - (alpha/m)*Delta[i][j][k];
						else
							theta[i][j][k] = theta[i][j][k] - (alpha/m)*(Delta[i][j][k] + 1.0*theta[i][j][k]);
					}
				}
			}

			curr_cost = cost(1);
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

	/*vector <pair<double, double> > predict(vector <vector<double> > X_p){ //Pass a copy since we will modify it.
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
	}*/
};