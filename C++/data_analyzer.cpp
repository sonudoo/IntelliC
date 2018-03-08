#ifndef _MATH_H_
	#include <math.h>
	#define _MATH_H_
#endif

#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _STDIO_H_
	#include <stdio.h>
	#define _STDIO_H_
#endif

#ifndef _ALGORITHM_
	#include <algorithm>
	#define _ALGORITHM_
#endif

#ifndef _LIMITS_H_
	#include <limits.h>
	#define _LIMIT_H_
#endif

#ifndef _SET_
	#include <set>
	#define _SET_
#endif

#ifndef _IOSTREAM_
	#include <iostream>
	#define _IOSTREAM_
#endif

using namespace std;

template <typename T>
class DataAnalyzer{
private:
	vector <vector<T> > cwd;  //Column-wise data
	int n;
	int m;
public:
	DataAnalyzer(const vector <vector <T> > &data){
		if(data.size()==0){
			return;
		}
		for(int i=0;i<data[0].size();i++){
			vector <T> column;
			for(int j=0;j<data.size();j++){
				column.push_back(data[j][i]);
			}
			cwd.push_back(column);
		}
		n = data[0].size();
		m = data.size();
	}
	DataAnalyzer(const vector <T> &data){
		cwd.push_back(data);
		n = 1;
		m = data.size();
	}
	void printStats(int col = 0){
		if(col>=n || col<0)	printf("No such column exists\n");
		sort(cwd[col].begin(),cwd[col].end());
		double linear_sum = 0;
		double squared_sum = 0;
		double mx = -std::numeric_limits<double>::max();
		double mn = std::numeric_limits<double>::max();
		set <T> st;
		for(int i=0;i<m;i++){
			double x = 1.0*cwd[col][i];
			linear_sum += x;
			squared_sum += x*x;
			mx = max(mx, x);
			mn = min(mn, x);
			st.insert(cwd[col][i]);
		}
		double avg = linear_sum/m;
		double stddev = sqrt((squared_sum/m) - (avg*avg));
		double median;
		if(m%2==0){
			median = (cwd[col][m/2]+cwd[col][(m-2)/2])/2.0;
		}
		else{
			median = cwd[col][(m-1)/2];
		}
		printf(" Average: %lf\n Max: %lf\n Min: %lf\n Unique: %d\n Stddev: %lf\n Median: %lf\n",avg, mx, mn, st.size(), stddev, median);
	}
	void printStats(int x, int y){
		if(m==0){
			printf("No data available to print statistics.\n");
		}
		else{
			for(int i=x;i<=y;i++){
				printf("\n\n**Stats for Column %d**\n\n",i);
				printStats(i);
			}
			printf("\n");
		}
	}
	void printAllStats(){
		if(m==0){
			printf("No data available to print statistics.\n");
		}
		else{
			for(int i=0;i<n;i++){
				printf("\n\n**Stats for Column %d**\n\n",i);
				printStats(i);
			}
			printf("\n");
		}
	}
	double correlate(int x, int y){
		if(x>=n || y>=n || x<0 || y<0)	return 0;
		double linear_sum_x = 0, linear_sum_y = 0, squared_sum_x = 0, squared_sum_y = 0, product_sum = 0;
		for(int i=0;i<m;i++){
			double x = 1.0*cwd[x][i];
			double y = 1.0*cwd[y][i];
			linear_sum_x += x;
			linear_sum_y += y;
			squared_sum_x += x*x;
			squared_sum_y += y*y;
			product_sum += x*y;
		}
		return (m*product_sum - linear_sum_x*linear_sum_y)/sqrt((m*squared_sum_x - linear_sum_x*linear_sum_x)*(m*squared_sum_y - linear_sum_y*linear_sum_y));
	}
	void preview(){
		//Print column wise data in row wise order
		if(m<=4){
			if(n<=4){
				for(int i=0;i<m;i++){
					for(int j=0;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
			else{
				for(int i=0;i<m;i++){
					for(int j=0;j<2;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
		}
		else{
			if(n<=4){
				for(int i=0;i<2;i++){
					for(int j=0;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
				for(int j=0;j<n;j++){
					cout << "..." << "\t";
				}
				cout << "\n";
				for(int i=m-2;i<m;i++){
					for(int j=0;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
			else{
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
				for(int j=0;j<5;j++){
					cout << "..." << "\t";
				}
				cout << "\n";
				for(int i=m-2;i<m;i++){
					for(int j=0;j<2;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << fixed << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
		}
	}
	void printData(){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				cout << fixed << cwd[j][i] << "\t";
			}
			cout << "\n";
		}
	}
};

template <>
class DataAnalyzer <string>{
private:
	vector <vector<string> > cwd;  //Column-wise data
	int n;
	int m;
	bool canParseToDouble(int col){
		for(int i=0;i<cwd[col].size();i++){
			if(cwd[col][i]=="")	return false;
			for(int j=0;j<cwd[col][i].size();j++){
				if((cwd[col][i][j]<48 || cwd[col][i][j]>57) && cwd[col][i][j]!='.'){
					return false;
				}
			}
		}
		return true;
	}
	double parseDouble(const string &s){
		double res = 0;
		int i = 0;
		bool sign = false;
		if(s[i]=='-'){
			sign = true;
			i++;
		}
		if(s[i]=='+')	i++;
		while(i<s.size() && s[i]!='.'){
			res = (res*10) + (s[i]-48);
			i++;
		}
		if(i==s.size())	return res;
		double p = 0.1;
		i++;
		while(i<s.size()){
			res += p*(s[i]-48);
			p /= 10;
			i++;
		}
		if(sign)
			return -res;
		else
			return res;
	} 
	void parseDouble(int col, vector <double> &target){
		for(int i=0;i<cwd[col].size();i++){
			target.push_back(parseDouble(cwd[col][i]));
		}
	}
public:
	DataAnalyzer(const vector <vector <string> > &data){
		if(data.size()==0){
			return;
		}
		for(int i=0;i<data[0].size();i++){
			vector <string> column;
			for(int j=0;j<data.size();j++){
				column.push_back(data[j][i]);
			}
			cwd.push_back(column);
		}
		n = data[0].size();
		m = data.size();
	}
	DataAnalyzer(const vector <string> &data){
		cwd.push_back(data);
		n = 1;
		m = data.size();
	}
	void printStats(int col = 0){
		if(col>=n || col<0)	printf("No such column exists\n");
		if(!canParseToDouble(col)){
			printf("This column contains missing/non-numeric data. No Stats found\n");
			return;
		}
		else{
			vector <double> d;
			parseDouble(col, d);
			sort(d.begin(),d.end());
			double linear_sum = 0;
			double squared_sum = 0;
			double mx = -std::numeric_limits<double>::max();
			double mn = std::numeric_limits<double>::max();
			set <double> st;
			for(int i=0;i<m;i++){
				double x = 1.0*d[i];
				linear_sum += x;
				squared_sum += x*x;
				mx = max(mx, d[i]);
				mn = min(mn, d[i]);
				st.insert(d[i]);
			}
			double avg = linear_sum/m;
			double stddev = sqrt((squared_sum/m) - (avg*avg));
			double median;
			if(m%2==0){
				median = (d[m/2]+d[(m-2)/2])/2.0;
			}
			else{
				median = d[(m-1)/2];
			}
			printf(" Average: %lf\n Max: %lf\n Min: %lf\n Unique: %d\n Stddev: %lf\n Median: %lf\n",avg, mx, mn, st.size(), stddev, median);

		}
	}
	void printStats(int x, int y){
		if(m==0){
			printf("No data available to print statistics.\n");
		}
		else{
			for(int i=x;i<=y;i++){
				printf("\n\n**Stats for Column %d**\n\n",i);
				printStats(i);
			}
			printf("\n");
		}
	}
	void printAllStats(){
		if(m==0){
			printf("No data available to print statistics.\n");
		}
		else{
			for(int i=0;i<n;i++){
				printf("\n\n**Stats for Column %d**\n\n",i);
				printStats(i);
			}
			printf("\n");
		}
	}
	double correlate(int x, int y){
		if(x>=n || y>=n || x<0 || y<0)	return 0;
		if(canParseToDouble(x)==false || canParseToDouble(y)==false)	return 0;
		vector <double> dx;
		vector <double> dy;
		parseDouble(x, dx);
		parseDouble(y, dy);
		double linear_sum_x = 0, linear_sum_y = 0, squared_sum_x = 0, squared_sum_y = 0, product_sum = 0;
		for(int i=0;i<m;i++){
			double x = 1.0*dx[i];
			double y = 1.0*dy[i];
			linear_sum_x += x;
			linear_sum_y += y;
			squared_sum_x += x*x;
			squared_sum_y += y*y;
			product_sum += x*y;
		}
		return (m*product_sum - linear_sum_x*linear_sum_y)/sqrt((m*squared_sum_x - linear_sum_x*linear_sum_x)*(m*squared_sum_y - linear_sum_y*linear_sum_y));
	}
	void preview(){
		//Print column wise data in row wise order
		if(m<=4){
			if(n<=4){
				for(int i=0;i<m;i++){
					for(int j=0;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
			else{
				for(int i=0;i<m;i++){
					for(int j=0;j<2;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
		}
		else{
			if(n<=4){
				for(int i=0;i<2;i++){
					for(int j=0;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
				for(int j=0;j<n;j++){
					cout << "..." << "\t";
				}
				cout << "\n";
				for(int i=m-2;i<m;i++){
					for(int j=0;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
			else{
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
				for(int j=0;j<5;j++){
					cout << "..." << "\t";
				}
				cout << "\n";
				for(int i=m-2;i<m;i++){
					for(int j=0;j<2;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "...\t";
					for(int j=n-2;j<n;j++){
						cout << cwd[j][i] << "\t";
					}
					cout << "\n";
				}
			}
		}
	}
	void printData(){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				cout << cwd[j][i] << "\t";
			}
			cout << "\n";
		}
	}
};