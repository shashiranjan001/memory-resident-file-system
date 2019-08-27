#ifndef MRFS_H
#define MRFS_H

#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;


/*
	assuming the upper bound on number of blocks to be 2^20 
	assuming the upper bound on number of inodes to be 2^10
*/

#define blocks_ub (1<<20)
#define inodes_ub (1<<10)



typedef struct 
{
	int total_size;
	int max_inodes;
	int current_inode;
	int max_blocks;
	int current_block;
	bitset<blocks_ub> free_blocks;
	bitset<inodes_ub> free_inodes;

}super_type;

const int super_size = sizeof(super_type);
const int super_blocks = (super_size % 256==0)?(super_size/256):(super_size/256 +1);
const int super_size_occupied = super_blocks*256;

typedef struct 
{
	bool file_type;
	int file_size;
	time_t last_mod;
	time_t last_read;
	unsigned char acess_perm[3];
	int ptr[10];

}inode_type;

typedef struct 
{
	inode_type inode[inodes_ub];

}inode_list_type;

const int inode_list_size = sizeof(inode_list_type);
const int inode_list_blocks = (inode_list_size % 256==0)?(inode_list_size/256):(inode_list_size/256 +1);
const int inode_list_size_occupied = inode_list_blocks*256;

typedef unsigned char block_type[256];


//map<int,block_type*> block;

typedef struct 
{
	char file_name[30];
	short int inode;

}direct_entry_type;

typedef struct 
{
	direct_entry_type entry[8];
}directory_type;

typedef struct 
{
	int ptr[64];
}indirect_block;

typedef struct 
{
	int inode_no;
	int offset;
	char mode;
	bool open=false;
}file_table_entry;


 //char* mem_start;
// int current_directory;
 //super_type* super;
 //inode_list_type* ilist;
 //map<int,file_table_entry > file_table;
 //int number_of_file_dis =0;




int create_myfs(int size);
int copy_pc2myfs(char* source , char* dest);
int copy_myfs2pc(char* source, char* dest);
int showfile_myfs(char* filename);
int ls_myfs();
int rm_myfs(char *file_del);
int mkdir_myfs (char *dirname);
int chdir_myfs (char *dirname);
int rmdir_myfs (char *dirname);
int close_myfs (int fd );
int eof_myfs(int fd);
int write_myfs (int fd, int nbytes, char *buff);
int read_myfs (int fd, int nbytes, char *buff);
int open_myfs (char *filename, char mode);
int restore_myfs(char* filename);
int dump_myfs(char* filename);
int status_myfs ();
int chmod_myfs (char *name, int mode);


void print( char* str,int size);


#endif



