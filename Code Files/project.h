/*Team 31 DSA Project - Directory Manager*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct TreeNode st_TreeNode;
typedef struct TreeNode* ptrcurr;
typedef struct TreeNode* TreePtr;


typedef char* string;
typedef struct aliastable aliastype;
typedef aliastype* Aliasptr;
typedef struct aliasnode antype;
typedef antype* nodeptr;

struct aliastable
{
    int size;
    nodeptr* list;
};

struct aliasnode
{
    char s[100];
    TreePtr ptr;
};

struct TreeNode
{
    char NodeName[20];
    char type[5];
    
    struct TreeNode* TreeChild;
    struct TreeNode* Parent;
    struct TreeNode* Next; 
};

// Low level functions
TreePtr MakeNode(char name[],char type[]);
TreePtr CreateRoot(); //I am root//


Aliasptr maketable(int size); //Abhijith
unsigned int hash(string s, Aliasptr A); //Abhijith
nodeptr  searchtable(Aliasptr A, string s); //Abhijith
TreePtr teleport(string s, Aliasptr A); //Abhijith
int aliastaken(Aliasptr P, string k); //Abhijith

void Alias(Aliasptr P, string k, TreePtr B); //Tirth Motka

ptrcurr ptr_from_path(TreePtr root, char path[]); //Aryamaan Roy
int cut_and_paste(TreePtr tree_root, ptrcurr current_directory, char path[]); //Aryamaan Roy
int delete(TreePtr parent_directory,char name[]); //Aryamaan
//Free Functions
TreePtr free_tree(TreePtr root);//Aryamaan Roy
void free_aliastable(Aliasptr *alias);//Aryamaan Roy


bool prefixcheck(char prefix[], TreePtr dir); //Chinmay
void find(char name[], TreePtr dir); //Chinmay
void findall(char prefix[], TreePtr dir); //Chinmay


void add(ptrcurr CurrentPath, string type, string name);//Akhilesh
void ls(ptrcurr CurrentPtr);//Akhilesh
void path_from_ptr(ptrcurr currentptr,TreePtr root);//Akhilesh
ptrcurr back(ptrcurr CurrentPtr,TreePtr Root);//Akhilesh
int check_name_exists(ptrcurr CurrentPtr, string name);//Akhilesh

/*
Credits :
Teleport - Abhijith
Move - Aryamaan
Alias - Tirth
Find - Chinmay
Add - Akhilesh
*/
