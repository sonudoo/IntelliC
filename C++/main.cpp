#include <iostream>
#include "csv_handler.cpp"
#include "data_analyzer.cpp"
#include "data_transform.cpp"
#include "matrix.cpp"
using namespace std;
int main(){
	CSVHandler c("train.csv");
	vector <vector <string> > data;
	c.readCSV(data);
	//printf("%d %d\n",data.size(),data[0].size());
	DataAnalyzer <string> d(data);
	//DataTransform <string> dt;
	//vector <vector<string> > v = dt.slice(data,1,3,1,3);
	//dt.appendColumn(v,dt.slice(data,1,3,3,5));
	//vector <vector<double> > v_ = dt.parseDouble(data);
	d.printData();
	return 0;
}