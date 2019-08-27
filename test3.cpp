#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include "myfs.h"
using namespace std;
 
int main(){
	int a;
	a=restore_myfs("mydump-46.backup");
	a=ls_myfs();
	int fd;
	fd=open_myfs("mytest.txt",'r');
	char ch[10000];
	int n=read_myfs(fd,10000,ch);
	a=close_myfs(fd);
	print(ch,n);
	cout<<endl;
	std::string::size_type sz;
	vector<int>vec;
	int z;
	string temp;
	for(int i=0;i<n;i++){
		if(ch[i]=='-'){
			temp="";
			for(int j=i+2;j<n;j++){
				if(ch[j]!='-')temp+=ch[j];
				else break;
			}
			z=std::stoi(temp);
			vec.push_back(z);
			i++;
		}
	}
	sort(vec.begin(),vec.end());

	fd= open_myfs("sorted.txt",'w');
	string s="";
	for(int i=0;i<vec.size();i++){
		s+="--"+to_string(vec[i]);
	}
	
	memcpy(ch, s.c_str(), s.size() + 1);
	a=write_myfs(fd,s.length(),ch);
	a=close_myfs(fd);
	a=ls_myfs();
	a=showfile_myfs("sorted.txt");

}
