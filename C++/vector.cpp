
#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _TIME_H_
	#include <time.h>
	#define _TIME_H_
#endif

#ifndef _MATH_H_
	#include <math.h>
	#define _MATH_H_
#endif


#ifndef _LIMITS_H_
	#include <limits.h>
	#define _LIMITS_H_
#endif

#ifndef _ALGORITHM_
	#include <algorithm>
	#define _ALGORITHM_
#endif

#ifndef _UTILITY_
	#include <utility>
	#define _UTILITY_
#endif



class Vector{
private:
	double randDouble(bool positiveOnly = false){
		if(rand()%2==0 || positiveOnly)
			return (double)rand()/(double)RAND_MAX;
		else
			return -(double)rand()/(double)RAND_MAX;
	}
	double power(double x, int n){
		double res = 1;
		while(n){
			if(n&1)
				res = res*x;
			x = x*x;
			n >>= 1;
		}
		return res;
	}
	double max(double x, double y){
		if(x>y)	return x;
		return y;
	}
	double min(double x, double y){
		if(x<y)	return x;
		return y;
	}
public:
	vector <double> zeros(int n){
		vector <double> res;
		for(int i=0;i<n;i++)
			res.push_back(0);
		return res;
	}
	vector <double> ones(int n){
		vector <double> res;
		for(int i=0;i<n;i++)
			res.push_back(1);
		return res;
	}
	vector <double> random(int n, bool positiveOnly = false){
		srand(time(0));
		vector <double> res;
		for(int i=0;i<n;i++)
			res.push_back(randDouble(positiveOnly));
		return res;
	}
	double sum(const vector <double> &data){
		double s = 0;
		for(int i=0;i<data.size();i++)
			s += data[i];
		return s;
	}
	double avg(const vector <double> &data){
		if(data.size()==0)	return 0;
		double s = 0;
		for(int i=0;i<data.size();i++)
			s += data[i];
		return s/data.size();
	}
	double max(const vector <double> &data){
		double s = -std::numeric_limits<double>::max();
		for(int i=0;i<data.size();i++)
			s = max(data[i],s);
		return s;
	}
	double min(const vector <double> &data){
		double s = std::numeric_limits<double>::max();
		for(int i=0;i<data.size();i++)
			s = min(data[i],s);
		return s;
	}
	vector <double> normalize(const vector <double> &data){
		if(data.size()==0)	return data;
		double mx = max(data);
		double mn = min(data);
		double ag = avg(data);
		vector <double> res;
		for(int i=0;i<data.size();i++){
			res.push_back((data[i]-ag)/(mx-mn));
		}
		return res;
	}
	vector <int> random_permutation(int n){
		srand(time(0));
		vector <int> res;
		vector <pair<double,int> > v;
		for(int i=1;i<=n;i++){
			v.push_back(make_pair(randDouble(),i));
		}
		sort(v.begin(),v.end());
		for(int i=1;i<=n;i++){
			res.push_back(v[i-1].second);
		}
		return res;
	}
	vector <double> sum(const vector <double> &data, double c){
		vector <double> res;
		for(int i=0;i<data.size();i++)
			res.push_back(data[i]+c);
		return res;
	}
	vector <double> prod(const vector <double> &data, double c){
		vector <double> res;
		for(int i=0;i<data.size();i++)
			res.push_back(data[i]*c);
		return res;
	}
	vector <double> pow(const vector <double> &data, int c){
		vector <double> res;
		for(int i=0;i<data.size();i++)
			res.push_back(power(data[i], c));
		return res;
	}
	vector <double> sum(const vector <double> &data1, const vector <double> data2){
		if(data1.size()!=data2.size())	throw "Vectors must be of same size\n";
		vector <double> res;
		for(int i=0;i<data1.size();i++)
			res.push_back(data1[i]+data2[i]);
		return res;
	}
	vector <double> prod(const vector <double> &data1, const vector <double> data2){
		if(data1.size()!=data2.size())	throw "Vectors must be of same size\n";
		vector <double> res;
		for(int i=0;i<data1.size();i++)
			res.push_back(data1[i]*data2[i]);
		return res;
	}
	vector <double> diff(const vector <double> &data1, const vector <double> data2){
		if(data1.size()!=data2.size())	throw "Vectors must be of same size\n";
		vector <double> res;
		for(int i=0;i<data1.size();i++)
			res.push_back(data1[i]-data2[i]);
		return res;
	}
	vector <vector <double> > upgrade(const vector <double> &data){
		vector <vector <double> > res;
		for(int i=0;i<data.size();i++){
			vector <double> row;
			row.push_back(data[i]);
			res.push_back(row);
		}
		return res;
	}
};