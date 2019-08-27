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
	char c[4];
	for(int i=0;i<12;i++){
		cout<<"copying client.c to myfs as "<<i+1<<endl;
		sprintf(c,"%d",i+1);
		a=copy_pc2myfs("client.c",c);
	}
	a=ls_myfs();
	cout<<"enter the name of the file to delete \n";
	string d;
	cin>>d;
	a=rm_myfs((char*)(d.c_str()));
	a=ls_myfs();
}
