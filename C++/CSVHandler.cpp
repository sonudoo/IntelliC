#ifndef _STDIO_H_
	#include <stdio.h>
	#define _STDIO_H_
#endif

#ifndef _STDLIB_H_
	#include <stdlib.h>
	#define _STDLIB_H_
#endif

#ifndef _VECTOR_
	#include <vector>
	#define _VECTOR_
#endif

#ifndef _STRING_
	#include <string>
	#define _STRING_
#endif

using namespace std;


class FastInput{

private:
	FILE* in;

public:
	FastInput(char *file){
		in = fopen(file, "r");
		if(!in){
			throw "Error opening the file. Please make sure that the file exists\n";
		}
	}
	int readInt(){
		int x = 0;
		register char c = getc(in);
		
		int sign = 0;

		if(c=='+' || c=='-'){
			if(c=='-')
				sign = 1;
			c = getc(in);
		}

		while(c>=48 && c<=57){
			x = (x<<3) + (x<<1) + (c-48);
			c = getc(in);
		}
		ungetc(c, in);
		if(sign)	return -x;
		else	return x;
	}
	long long readLongLong(){
		long long int x = 0;
		register char c = getc(in);
		
		int sign = 0;

		if(c=='+' || c=='-'){
			if(c=='-')
				sign = 1;
			c = getc(in);
		}

		while(c>=48 && c<=57){
			x = (x<<3) + (x<<1) + (c-48);
			c = getc(in);
		}
		ungetc(c, in);
		if(sign)	return -x;
		else	return x;
	}
	double readDouble(){
		double x = 0.0;
		register char c = getc(in);

		int sign = 0;

		if(c=='+' || c=='-'){
			if(c=='-')
				sign = 1;
			c = getc(in);
		}

		while(c>=48 && c<=57){
			x = (10.0*x) + (c-48);
			c = getc(in);
		}
		if(c=='.'){
			c = getc(in);
			double p = 0.1;
			while(c>=48 && c<=57){
				x += p*(c-48);
				p /= 10;
				c = getc(in);
			}
		}
		ungetc(c, in);
		
		if(sign)	return -x;
		else	return x;
	}
	char readNextChar(){
		register char c = getc(in);
		return c;
	}
	string readLine(){
		string s = "";
		register char c = getc(in);
		while(c!='\n' && c!=EOF){
			s += c;
			c = getc(in);
		}
		return s;
	}
	string readQuotedString(){
		string s = "";
		register char c = getc(in);
		if(c!='"'){
			return s;
		}
		else{
			c = getc(in);
			while(c!='"' && c!=EOF){
				s += c;
				c = getc(in);
			}
			return s;
		}
	}
	string readStringTillComma(){
		string s = "";
		register char c = getc(in);
		while(c!='\n' && c!=EOF && c!=','){
			s += c;
			c = getc(in);
		}
		ungetc(c, in);
		return s;
	}
	bool isNextQuotedString(){
		register char c = getc(in);
		ungetc(c, in);
		if(c=='"')	return true;
		return false;

	}
	bool isNextNumber(){
		register char c = getc(in);
		char sign = 'N';
		if(c=='+' || c=='-'){
			sign = c;
			c = getc(in);
		}
		bool res = false;
		if(c>=48 && c<=57){
			res = true;
		}
		ungetc(c, in);
		if(sign!='N'){
			ungetc(sign, in);
		}
		return res;
	}
	bool isNextComma(){
		register char c = getc(in);
		ungetc(c, in);
		if(c==',')	return true;
		return false;
	}
	bool isNextEOL(){
		register char c = getc(in);
		ungetc(c, in);
		if(c=='\n')	return true;
		return false;
	}
	bool isNextEOF(){
		register char c = getc(in);
		if(c==EOF)	return true;
		ungetc(c, in);
		return false;
	}
};



class CSVHandler{

private:
	FastInput *f;
public:
	CSVHandler(char *file){
		f = new FastInput(file);
	}
	void readCSV(vector <vector <int> > &v){
		while(!f->isNextEOF()){
			vector <int> record;
			char c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readInt());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading integers from the file\n";
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <long long> > &v){
		while(!f->isNextEOF()){
			vector <long long> record;
			char c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readLongLong());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading integers from the file\n";
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <double> > &v){
		while(!f->isNextEOF()){
			vector <double> record;
			char c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readDouble());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading doubles from the file\n";
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <string> > &v){
		while(!(f->isNextEOF())){
			vector <string> record;
			char c = '\0';
			while(c!=EOF && c!='\n'){
				if(f->isNextQuotedString()){
					record.push_back(f->readQuotedString());
				}
				else{
					record.push_back(f->readStringTillComma());
				}
				c = f->readNextChar();
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <int> > &v, vector <string> &h){
		char c = '\0';
		while(c!=EOF && c!='\n'){
			if(f->isNextQuotedString()){
				h.push_back(f->readQuotedString());
			}
			else{
				h.push_back(f->readStringTillComma());
			}
			c = f->readNextChar();
		}
		while(!f->isNextEOF()){
			vector <int> record;
			c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readInt());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading integers from the file\n";
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <long long> > &v, vector <string> &h){
		char c = '\0';
		while(c!=EOF && c!='\n'){
			if(f->isNextQuotedString()){
				h.push_back(f->readQuotedString());
			}
			else{
				h.push_back(f->readStringTillComma());
			}
			c = f->readNextChar();
		}
		while(!f->isNextEOF()){
			vector <long long> record;
			c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readLongLong());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading integers from the file\n";
					exit(0);
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <double> > &v, vector <string> &h){
		char c = '\0';
		while(c!=EOF && c!='\n'){
			if(f->isNextQuotedString()){
				h.push_back(f->readQuotedString());
			}
			else{
				h.push_back(f->readStringTillComma());
			}
			c = f->readNextChar();
		}
		while(!f->isNextEOF()){
			vector <double> record;
			c = '\0';
			while(c!=EOF && c!='\n'){
				record.push_back(f->readDouble());
				if(f->isNextComma() || f->isNextEOL() || f->isNextEOF())
					c = f->readNextChar();
				else{
					throw "Error occured while reading doubles from the file\n";
				}
			}
			v.push_back(record);
		}
	}
	void readCSV(vector <vector <string> > &v, vector <string> &h){
		char c = '\0';
		while(c!=EOF && c!='\n'){
			if(f->isNextQuotedString()){
				h.push_back(f->readQuotedString());
			}
			else{
				h.push_back(f->readStringTillComma());
			}
			c = f->readNextChar();
		}
		while(!(f->isNextEOF())){
			vector <string> record;
			char c = '\0';
			while(c!=EOF && c!='\n'){
				if(f->isNextQuotedString()){
					record.push_back(f->readQuotedString());
				}
				else{
					record.push_back(f->readStringTillComma());
				}
				c = f->readNextChar();
			}
			v.push_back(record);
		}
	}
};

