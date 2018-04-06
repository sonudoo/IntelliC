#include <vector>
#include <time.h>
#include <stdio.h>
#include <set>
#include <map>
#include <limits.h>
#include "Vector.cpp"
#include "Matrix.cpp"
#include "DataTransform.cpp"

using namespace std;

class DecisionTreeClassifier{
private:
	struct node{
		bool isLeaf;
		double leaf_class;
		vector <int> group;
		int idx;
		double val;
		struct node *left;
		struct node *right;
		node(){
			left = NULL;
			right = NULL;
			isLeaf = false;
		}
	};
	vector <vector <double> > X;
	vector <double> y;
	int n;
	int m;
	int max_depth;
	int min_size;
	vector <double> classes;
	node *start;
	double gini(const vector <vector<int> > &groups){
		double n = 0;
		for(int i=0;i<groups.size();i++){
			n += groups[i].size();
		}
		double ret = 0;
		for(int i=0;i<groups.size();i++){
			if(groups[i].size()==0)	continue;
			double score = 0;
			for(int j=0;j<classes.size();j++){
				double cnt = 0;
				for(int k=0;k<groups[i].size();k++){
					double actual_class = y[groups[i][k]];
					if(fabs(classes[j]-actual_class)<0.000001){
						cnt++;
					}
				}
				double prediction = cnt/groups[i].size();
				score += prediction*prediction;
			}
			ret += (1.0 - score)*(groups[i].size()/n);
		}
		return ret;
	}
	void getBestSplit(const vector <int> &curr_group, int &idx, double &val, vector <vector <int> > &bestGroups){
		double bestScore = std::numeric_limits<double>::max();
		idx = -1;
		val = 0.00;
		for(int i=0;i<n;i++){
			for(int j=0;j<curr_group.size();j++){
				// Trying to split at feature number i and value X[curr_group[j]][i]
				vector <vector <int> > groups;
				vector <int> group1, group2;
				for(int k=0;k<curr_group.size();k++){
					if(X[curr_group[k]][i] < X[curr_group[j]][i])
						group1.push_back(curr_group[k]);
					else
						group2.push_back(curr_group[k]);

				}
				groups.push_back(group1);
				groups.push_back(group2);
				double g = gini(groups);
				if(g < bestScore){
					bestScore = g;
					idx = i;
					val = X[curr_group[j]][i];
					bestGroups = groups;
				}

			}
		}
	}
	double getMostOccuringClass(const vector <int> &group){
		map <double, int> mp;
		for(int i=0;i<group.size();i++){
			if(mp.count(y[group[i]])!=0)
				mp[y[group[i]]] += 1;
			else
				mp[y[group[i]]] = 1;
		}
		map <double, int>::iterator it;
		int m = 0;
		double ret = -1;
		for(it=mp.begin();it!=mp.end();it++){
			if(it->second > m){
				m = it->second;
				ret = it->first;
			}
		}
		return ret;
	}

	void recursiveSplit(node *curr, int level){
		if(level >= max_depth || (curr->group).size() <= min_size){
			curr->isLeaf = true;
			curr->leaf_class = getMostOccuringClass(curr->group);
			curr->left = NULL;
			curr->right = NULL;
			return;
		}
		vector <vector <int> > groups;

		getBestSplit(curr->group, curr->idx, curr->val, groups);

		if(groups[0].size()==0)
			curr->left = NULL;
		else{
			curr->left = new node();
			(curr->left)->group = groups[0];
			recursiveSplit(curr->left, level+1);
		}

		if(groups[1].size()==0)
			curr->right = NULL;
		else{
			curr->right = new node();
			(curr->right)->group = groups[1];
			recursiveSplit(curr->right, level+1);
		}
	}

public:
	DecisionTreeClassifier(const vector <vector <double> > &data, const vector <double> &label){
		if(data.size()==0) throw "Data must not be empty";
		if(data.size()!=label.size())	throw "Number of X and y must match\n";
		if(!Matrix::isMatrix(data))	throw "X must be a matrix (i.e double dimensional vector)\n";
		m = data.size();
		n = data[0].size();
		X = data;
		y = label;
		set <double> s;
		for(int i=0;i<m;i++){
			s.insert(y[i]);
		}
		set <double>::iterator it;
		for(it=s.begin();it!=s.end();it++){
			classes.push_back(*it);
		}
	}
	void train(int size, int depth){
		if(size < 1){
			throw "Minimum size must be at least 1.\n";
		}
		if(depth < 1){
			throw "Depth must be at least 1.\n";
		}
		min_size = size;
		max_depth = depth;
		node *curr = new node();
		for(int i=0;i<m;i++){
			(curr->group).push_back(i);
		}
		recursiveSplit(curr, 0);
		start = curr;
	}
	vector <double> predict(vector <vector <double> > X_p){
		for(int i=0;i<X_p.size();i++){
			if(X_p[i].size()!=n)	throw "Number of features for each row must be same as the training set.\n";
		}
		vector <double> ret;
		for(int i=0;i<X_p.size();i++){
			node *curr = start;
			while(curr->isLeaf==false){
				if(X_p[i][curr->idx] < curr->val)
					curr = curr->left;
				else
					curr = curr->right;
			}
			ret.push_back(curr->leaf_class);
		}
		return ret;
	}
	
};