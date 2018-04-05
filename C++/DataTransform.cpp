#include <vector>
#include <string>

#ifndef _DATA_TRANSFORM_CPP_

#define _DATA_TRANSFORM_CPP_

using namespace std;

template <class T>
class DataTransform{
private:
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
	void swap(T &x, T&y){
		x = x+y;
		y = x-y;
		x = x-y;
	}
	void reverse(vector <T> &v){
		int i = 0;
		int j = v.size()-1;
		while(i<j){
			swap(v[i],v[j]);
			i++;
			j--;
		}
	}
public:
	vector <vector<T> > sliceColumn(const vector <vector<T> > &data, int start, int end){
		vector <vector<T> > sliced_data;
		if(data.size()==0)	return sliced_data;
		int m = data.size();
		int n = data[0].size();
		start = max(start,0);
		end = min(end,n);
		for(int i=0;i<data.size();i++){
			vector <T> sliced_row;
			for(int j=start;j<end;j++){
				sliced_row.push_back(data[i][j]);
			}
			sliced_data.push_back(sliced_row);
		} 
		return sliced_data;
	}
	vector <vector<T> > sliceRow(const vector <vector<T> > &data, int start, int end){
		vector <vector<T> > sliced_data;
		if(data.size()==0)	return sliced_data;
		int m = data.size();
		int n = data[0].size();
		start = max(start,0);
		end = min(end,m);
		for(int i=start;i<end;i++){
			sliced_data.push_back(data[i]);
		} 
		return sliced_data;
	}
	vector <vector<T> > slice(const vector <vector <T> > &data, int start_row, int end_row, int start_column, int end_column){
		vector <vector<T> > sliced_data;
		if(data.size()==0)	return sliced_data;
		int m = data.size();
		int n = data[0].size();
		start_row = max(start_row,0);
		end_row = min(end_row,m);
		start_column = max(start_column,0);
		end_column = min(end_column,n);
		for(int i=start_row;i<end_row;i++){
			vector <T> sliced_row;
			for(int j=start_column;j<end_column;j++){
				sliced_row.push_back(data[i][j]);
			}
			sliced_data.push_back(sliced_row);
		} 
		return sliced_data;
	}
	vector <T> extractColumn(const vector <vector <T> > &data, int col){
		vector <T> column;
		if(data.size()==0)	return column;
		int m = data.size();
		int n = data[0].size();
		if(col>=n || col <0)	return column;
		for(int i=0;i<data.size();i++){
			column.push_back(data[i][col]);
		}
		return column;
	}
	vector <T> extractRow(const vector <vector <T> > &data, int row){
		vector <T> res;
		if(data.size()==0)	return res;
		int m = data.size();
		int n = data[0].size();
		if(row<0 || row>=m)	return res;
		return data[row];
	}
	void appendColumn(vector <vector <T> > &orig, const vector <T> &column){
		if(orig.size()!=column.size()){
			throw "Column append Failed. Number of rows must match\n";
		}
		for(int i=0;i<orig.size();i++){
			orig[i].push_back(column[i]);
		}
	}
	void prependColumn(vector <vector <T> > &orig, const vector <T> &column){
		if(orig.size()!=column.size()){
			throw "Column append Failed. Number of rows must match\n";
		}
		for(int i=0;i<orig.size();i++){
			reverse(orig[i]);
			orig[i].push_back(column[i]);
			reverse(orig[i]);
		}
	}
	void appendColumn(vector <vector <T> > &orig, const vector <vector <T> > &columns){
		if(orig.size()!=columns.size()){
			throw "Column append Failed. Number of rows must match\n";
		}
		for(int i=0;i<orig.size();i++){
			for(int j=0;j<columns[i].size();j++)
				orig[i].push_back(columns[i][j]);
		}
	}
	void appendRow(vector <vector <T> > &orig, const vector <T> &row){
		if(orig.size()==0){
			orig.push_back(row);
			return;
		}
		if(orig[0].size()!=row.size()){
			throw "Row append Failed. Number of columns must match\n";
		}
		orig.push_back(row);
	}
	void appendRow(vector <vector <T> > &orig, const vector <vector<T> > &rows){
		if(orig.size()==0){
			for(int i=0;i<rows.size();i++){
				orig.push_back(rows[i]);
			}
			return;
		}
		if(rows.size()==0)	return;
		if(orig[0].size()!=rows[0].size()){
			throw "Row append Failed. Number of columns must match\n";
		}
		for(int i=0;i<rows.size();i++){
			appendRow(orig, rows[i]);
		}
	}

	vector <vector<double> > parseDouble(const vector <vector<T> > &data){
		vector <vector<double> > res;
		for(int i=0;i<data.size();i++){
			vector <double> row;
			for(int j=0;j<data[i].size();j++){
				row.push_back(1.0*data[i][j]);
			}
			res.push_back(row);
		}
		return res;
	} 

};

template <>


vector <vector<double> > DataTransform<string>::parseDouble(const vector <vector <string> > &data){
	vector <vector<double> > res;
	for(int i=0;i<data.size();i++){
		vector <double> row;
		for(int j=0;j<data[i].size();j++){
			row.push_back(parseDouble(data[i][j]));
		}
		res.push_back(row);
	}
	return res;
}

#endif