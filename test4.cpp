#include <bits/stdc++.h>
#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>#include <time.h>
#include <unistd.h>
#include "myfs.h"
using namespace std;
 
int main(){
	int a;
	a=create_myfs(10);
	a=mkdir_myfs("mydocs");
	a=mkdir_myfs("mycode");
	a=chdir_myfs("mydocs");
	a=mkdir_myfs("mytext");
	a=mkdir_myfs("mypapers");
	a=chdir_myfs("dotdot");
	a=ls_myfs();
	pid_t p = fork();
		if(p<0)
		{
			fprintf(stderr, "fork Failed" );
        	return 1;
		}
		else if(p==0)
		{
			chdir_myfs("mydocs");
			chdir_myfs("mytext");
			int fd = open_myfs("file.txt",'w');
			char c[26];
			for(int i=0;i<26;i++){
				c[i]='A'+i;
			}
			int a=write_myfs(fd,26,c);
			a=close_myfs(fd);
			a=showfile_myfs("file.txt");
			cout<<endl;
			exit(0);
		}

		else
		{
			wait(NULL);
			a=chdir_myfs("mycode");
			a=copy_pc2myfs("makefile","testfile");
			a=ls_myfs();
			a=showfile_myfs("testfile");
		}


}