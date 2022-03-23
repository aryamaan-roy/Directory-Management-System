#include "project.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//initializes a node, allocates memory and returns new node
TreePtr MakeNode(char name[], char type[])
{
    TreePtr P = (TreePtr)malloc(sizeof(st_TreeNode));
    assert(P != NULL);
    strcpy(P->NodeName, name);
    P->TreeChild = NULL;
    P->Next = NULL;
    P->Parent = NULL;
    strcpy(P->type, type);
    return P;
}

//creates a root node and returns
TreePtr CreateRoot()
{
    TreePtr P;
    char root[5] = "root";
    P = MakeNode(root, "dir");
    return P;
}

//Time complexity : O(F*C) where C is avg no of children in directory and F is number of directories mentioned in path string
ptrcurr ptr_from_path(TreePtr root, char path[])
{
    ptrcurr ptr = root, current_ptr = NULL;
    char name[20]; //name of the present file/directory
    char ch;
    int n = 0, i = 0;

    while (path[i] != '\0' && path[i] != '/') //skip root in path: root/dir1/dir2/
    {
        i++;
    }
    i++; //skip '/' after root in path array

    while (path[i] != '\0') //runs through full path string
    {
        if (path[i] == '/') //if slash is encountered, then change name and
                            //update ptr to point to directory with that name
        {
            name[n] = '\0';
            current_ptr = ptr->TreeChild;
            while (current_ptr != NULL) //O(s) s:no of siblings in the
            {                           // directory passed as argument
                if (strcmp(current_ptr->NodeName, name) == 0)
                {
                    ptr = current_ptr;
                    n = 0;
                    break;
                }
                current_ptr = current_ptr->Next;
            }
            if (current_ptr == NULL)
            {
                printf("wrong path\n");
                return root;
            }
        }
        else
        {
            name[n] = path[i];
            n++;
        }
        i++;
    }

    return ptr;
}

int cut_and_paste(TreePtr tree_root, ptrcurr current_directory, char path[]) //inputs ptr to current directory and path to new directory
{
    //first we remove the current_directory from the siblings of its parent directory

    if (current_directory == NULL || tree_root == NULL)
    {
        printf("Dir does not exist\n");
        return -1;
    }
    if (current_directory == tree_root)
    {
        printf("Root cannot be cut and pasted\n");
        return -1;
    }
    ptrcurr parent_folder = ptr_from_path(tree_root, path); //recieves pointer to destination directory
    //error handling : destination dir cannot be file
    if (strcmp(parent_folder->type, "file") == 0)
    {
        printf("Cannot insert/paste in a file\n");
        return -1;
    }
    ptrcurr prev_ptr = current_directory->Parent; //points to parent of current dir
    if (current_directory == prev_ptr->TreeChild) //if directory is first child of parent
    {
        prev_ptr->TreeChild = current_directory->Next;
    }
    else
    {
        prev_ptr = current_directory->Parent->TreeChild;
        while (prev_ptr->Next != NULL && prev_ptr->Next != current_directory) //finds the directory (node)
        {                                                                     //before current_directory (required for deletion)
            prev_ptr = prev_ptr->Next;
        }
        if (prev_ptr->Next == current_directory)
        {
            prev_ptr->Next = current_directory->Next; //current_dir removed from list of siblings
        }
        else
            return -1;
    }

    //Now we add current_directory to the destination
    current_directory->Next = parent_folder->TreeChild;
    current_directory->Parent = parent_folder;
    parent_folder->TreeChild = current_directory;
    printf("Successfully moved\n");
    return 0;
}
int delete(TreePtr parent_directory,char name[])
{
    //error handling
    if(parent_directory==NULL||parent_directory->TreeChild==NULL)
    {
        printf("Directory is null or has no children");
        return -1;
    }
    
    //we find child of parent_directory with name (to be deleted) and remove it
    ptrcurr prev_ptr=NULL,to_be_deleted=NULL;
    //if it is the first child of parent
    if(strcmp(parent_directory->TreeChild->NodeName,name)==0)
    {
        to_be_deleted=parent_directory->TreeChild;
        parent_directory->TreeChild = parent_directory->TreeChild->Next;
    }
    else
    {
        prev_ptr=parent_directory->TreeChild;
        while(prev_ptr->Next!=NULL)
        {
            if(strcmp(prev_ptr->Next->NodeName,name)==0)
            {
                to_be_deleted=prev_ptr->Next;
                prev_ptr->Next=prev_ptr->Next->Next;
                break;
            }
            prev_ptr=prev_ptr->Next;
        }
    }
    
    //free the to_be_deleted
    if(to_be_deleted==NULL)
    {
        printf("The directory/file to be deleted does not exist");
        return -1;
    }
    else 
    {
        to_be_deleted = free_tree(to_be_deleted);
    }
    return 0;

}
TreePtr free_tree(TreePtr root) //recursively calls itself to free the full directory system
{
    ptrcurr current = root->TreeChild;
    while (current != NULL && current->Next != NULL) //first frees all children
    {
        ptrcurr temp = current->Next;
        current->Next = current->Next->Next;
        temp = free_tree(temp);
    }
    if (root->TreeChild != NULL) //free first child
    {
        root->TreeChild = free_tree(root->TreeChild);
    }
    free(root); //frees itself
    return NULL;
}
void free_aliastable(Aliasptr *alias) //free function for hashtable storing alias, time complexity: O(n) n:size of table
{
    if ((*alias)->list != NULL)
    {
        for (int i = 0; i < (*alias)->size; ++i)
        {
            if ((*alias)->list[i] != NULL)
                free((*alias)->list[i]);
        }
        free((*alias)->list);
    }
    if ((*alias) != NULL)
        free(*alias);
    *alias = NULL;
}

//This function takes input the name & type of the node and the currentDir is passed from main.
//This adds the given file/dir into the current folder. 
void add(TreePtr Current, string type_of_node, string name)
{
    TreePtr ptr_to_new;
    if(check_name_exists(Current,name))//To check availability of the requested name in the folder.
        ptr_to_new = MakeNode(name, type_of_node);
    else
    {
        printf("Name taken ! \n");
        return;
    }
    if(strcmp(type_of_node,"dir")==0 || strcmp(type_of_node,"file")==0)
    {
        if ((strcmp("dir", Current->type) == 0))
        {
            if (Current->TreeChild == NULL)
                Current->TreeChild = ptr_to_new;
            else
            {
                ptr_to_new->Next = Current->TreeChild;
                Current->TreeChild = ptr_to_new;
            }
            ptr_to_new->Parent = Current;
        }
        else if((strcmp("file", Current->type) == 0)) //To make sure that nothing gets added into a file. 
        {
            printf("Current Pointer is at a file, new node cannot be added!");
        }
    }
    else
    {
        printf("Enter a valid type!\n   "); // to handle unknown types of nodes apart from file/dir.
    }
    strcpy(ptr_to_new->type, type_of_node);
}

void ls(ptrcurr Current) // prints all files and directories in the current folder. Analogical to ls in shell.       
{
    if(strcmp("dir",Current->type)==0) // Files cannot have children and the command doesnt apply.
    {
        if (Current->TreeChild != NULL)
        {
            TreePtr temp;
            temp = Current->TreeChild;
            while (temp != NULL)
            {
                printf("%s ", (temp->NodeName));
                temp = temp->Next;
            }
        }
    }
    else
        printf("A file cannot have children! \n");
}

void path_from_ptr(ptrcurr Current,TreePtr Root) // Recursive function to get current path by inputting the currentPtr.
{
    ptrcurr temp;
    temp = Current;
    if(temp == Root)
    {
        printf("root");
        return;
    }
    path_from_ptr(temp->Parent,Root);
    printf("/%s", temp->NodeName);
}

bool prefixcheck(char prefix[], TreePtr dir)
{
    /*Checks if the prefix entered by the user matches
    the prefix (first few letters) of the directory name.
    Returns true if it matches, false if it does not*/
    
    for(int i=0;i<strlen(prefix);i++) //Iterating until all the elements of the input prefix have been checked
    {
        if (prefix[i]!=dir->NodeName[i])
        {
            return false;
        }
    }
    return true;
}

void find(char name[], TreePtr dir)
{
    bool flag=false;
    dir=dir->TreeChild;
    while(dir!=NULL) //Loop to check all the children of the input directory
    {
        if(prefixcheck(name,dir)) //prefix is checked for match, output boolean value is used in if statement
        {
            printf("%s\n",dir->NodeName);
            flag=true;
        }
        dir=dir->Next;
    }
    
    if(flag)
    {
        printf("Search successful\n");
    }
    else
    {
        printf("No matches found\n");
    }
}

unsigned int hash(string s, Aliasptr A)
{
    int p = 33;
    unsigned int temp = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        temp = temp * p + s[i];
        temp %= A->size;
//         if (temp < 0)
//             temp += A->size;
    }// using folding method and the ASCII values of each characters of the string 
    return (temp % A->size);
}

int aliastaken(Aliasptr P, string k)
{
    int key=hash(k,P);
    int temp=key;
    int i=1;
    while(P->list[temp]!=NULL && strcmp(P->list[temp]->s,k)!=0)
    {
        temp=(key+(i*i))%P->size;
        i++;
    }
    if(P->list[temp]==NULL)
        return 0;
    else if(strcmp(P->list[temp]->s,k)==0)
        return 1;
}

void Alias(Aliasptr P, string k, TreePtr B)
{
    // input B's value from the function ptr_from_path
  
    if (aliastaken(P,k))
    {
        printf("Alias already taken\n");
        return;
    }// checks if Alias is already taken 
    nodeptr A;
    int index = hash(k, P);
    int temp=index;
    int i=1;
    while(P->list[temp]!=NULL)
    {
        temp=(index+(i*i))%P->size;
        i++;
    }// does quadratic probing for collision resolution 
    A=(nodeptr)malloc(sizeof(antype));
    strcpy(A->s, k);
    A->ptr = B; // assigning the ptr field in A with the treenode pointer pointing to the directory which is being given the Alias.
    P->list[temp] = A;//assigning A to aliasnode of the hashtable
}

//standard hashtable creation function, returns pointer to hashtable
Aliasptr maketable(int size)
{
    Aliasptr A=(Aliasptr)malloc(sizeof(aliastype));
    A->size=size;
    A->list=(nodeptr*)malloc(size* sizeof(nodeptr));
    for(int i=0;i<size;i++)
        {
            A->list[i]=(nodeptr)malloc(sizeof(antype));
            A->list[i]=NULL;
        }

    return A;
}

//Standard searching in the hashtable for a given alias
//Uses quadratic probing
nodeptr  searchtable(Aliasptr A, string s)
{
    int siz=A->size;
    int key=hash(s,A);
    nodeptr P=A->list[key];
    int i=1;
    while(P!=NULL && strcmp(P->s,s)!=0)
        {
            P=A->list[(key+(i*i))%siz];
            i++;
        }
    if(P==NULL)
    return NULL;
    else
    return P;
}

//returning to a dummy node variable in main
//If the return value os NULL, dont update the current directory pointer
//If its not null, current pointer is changed to the returned pointer
TreePtr teleport(string s, Aliasptr A)
{
    nodeptr P=searchtable(A,s);
    if(P==NULL)
    {
        //No node with the given alias
        printf("No directory/file with the given alias has been created yet\n");
        return NULL;
    }
    else
    return P->ptr;  
}

ptrcurr back(ptrcurr CurrentPtr,TreePtr Root) // Function to go back one step. similar to `cd ..` from shell.
{
    if(CurrentPtr != Root)
        return CurrentPtr->Parent;
    else
    {
        printf("We have reached Root! No going back..");
        return CurrentPtr;
    }
}

// This function returns 0 or 1 based on availability of the name of the file/directory entered. 
int check_name_exists(ptrcurr CurrentPtr, string name)
{
    ptrcurr temp = CurrentPtr;
    temp = temp->TreeChild;
    while(temp != NULL)
    {
        if(strcmp(temp->NodeName,name)==0)
        {
            return 0;
        }
        temp = temp->Next;
    }
    return 1;
}

void findall(char prefix[], TreePtr dir)
{
    /*Preorder traversal
    First check the current node, then go to childr subtrees
    then go to sibling subtrees*/

    if(dir==NULL) //Checking if the subtree exists
    {
        return;
    }

    if (prefixcheck(prefix,dir)) //Checking for prefix matches
    {
        printf("%s\n",dir->NodeName);
    }

    findall(prefix,dir->TreeChild); //Recursively calling across children
    findall(prefix,dir->Next); //Recursively calling across sibling
}
