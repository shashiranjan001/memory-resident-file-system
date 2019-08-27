#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include "myfs.h"
using namespace std;
 
int main(){
	int a;
	a=create_myfs(10);
	int fd= open_myfs("mytest.txt",'w');
	int num[100];
	for(int i=0;i<100;i++){
		num[i]=rand();
	}
	string s="";
	for(int i=0;i<100;i++){
		s+="--"+to_string(num[i]);
	}
	char ch[s.length()+1];
	memcpy(ch, s.c_str(), s.size() + 1);
	a=write_myfs(fd,s.length(),ch);
	a=close_myfs(fd);
	cout<<"enter the number of copies to be generated\n";
	int n;
	cin>>n;
	string name;
	char nm[name.length()+1];
	fd= open_myfs("mytest.txt",'r');
	a=read_myfs(fd,s.length(),ch);
	a=close_myfs(fd);
	for(int i=0;i<n;i++){
		name="mytest-"+to_string(i+1);
		memcpy(nm, name.c_str(), name.size() + 1);
		fd=open_myfs(nm,'w');
		a=write_myfs(fd,s.length(),ch);
		a=close(fd);
	}
	a=ls_myfs();
	a=dump_myfs("mydump-46.backup");
}
