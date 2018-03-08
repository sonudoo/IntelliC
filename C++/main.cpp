#include <iostream>
#include "csv_handler.cpp"
#include "data_analyzer.cpp"
#include "LinearRegression.cpp"
using namespace std;
int main(){
	CSVHandler c("housing_prices.csv");
	vector <vector <double> > data;
	vector <string> label;
	c.readCSV(data, label);
	DataTransform <double> dt;
	vector <vector <double> > X_train;
	vector <double> y_train;
	vector <vector <double> > X_val;
	vector <double> y_val;
	for(int i=0;i<3;i++){
		X_train.push_back(data[i]);
		y_train.push_back(data[i][4]);
	}
	X_val.push_back(data[3]);
	y_val.push_back(data[3][4]);
	X_train = dt.sliceColumn(X_train,0,4);
	X_val = dt.sliceColumn(X_val,0,4);
	Vector _v;
	LinearRegression model(X_train,y_train);
	try{
		model.trainByNormalEquation();
	}
	catch(const char *s){
		printf("%s\n",s);
	}
	vector <double> y_p = model.predict(X_train);
	double train_err = (1/(2.0*X_train.size()))*_v.sum(_v.pow(_v.diff(y_p,y_train),2));
	y_p = model.predict(X_val);
	double val_err = (1/(2.0*X_val.size()))*_v.sum(_v.pow(_v.diff(y_p,y_val),2));
	printf("Train- %lf Validation- %lf\n",train_err,val_err);
	for(int i=0;i<y_p.size();i++){
		printf("%lf %lf\n",y_p[i],y_val[i]);
	}
	return 0;
}