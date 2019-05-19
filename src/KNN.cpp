#include <vector>
#include <algorithm>
#include <map>
#include "Vector.cpp"
#include "Matrix.cpp"
#include "DataTransform.cpp"

using namespace std;

class KNN{
private:
	vector <vector <double> > X;
	vector <double> y;
	int n;
	int m;
public:
	KNN(const vector <vector <double> > &data, const vector <double> &label){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		X = data;
		y = label;
	}
	vector <double> predict(vector <vector <double> > X_p, int k){
		for(int i=0;i<X_p.size();i++){
			if(X_p[i].size()!=n)	throw "Number of features for each row must be same as the training set.\n";
		}
		vector <double> ret;
		for(int i=0;i<X_p.size();i++){
			vector <pair<double, int> > dist;
			for(int j=0;j<m;j++){
				dist.push_back(make_pair(Vector::sum(Vector::pow(Vector::diff(X[j],X_p[i]),2)),j));
			}
			sort(dist.begin(),dist.end());
			map <double, int> mp;
			for(int j=0;j<k;j++){
				if(mp.count(y[dist[j].second])!=0)
					mp[y[dist[j].second]] += 1;
				else
					mp[y[dist[j].second]] = 1;
			}
			int m = 0;
			double val = -1;
			map <double, int>::iterator it;
			for(it=mp.begin();it!=mp.end();it++){
				if(it->second > m){
					m = it->second;
					val = it->first;
				}
			}
			ret.push_back(val);
		}
		return ret;
	}
	
};