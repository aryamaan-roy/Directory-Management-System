#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "project.c"

int main()
{
    ptrcurr CurrentDir;
    ptrcurr Root;
    string CurrentPath;
    TreePtr dummy;
    Aliasptr ptr_to_aliastable = (Aliasptr)malloc(sizeof(aliastype));
    Root = CreateRoot();
    CurrentDir = Root;
    char command[30] = {};
    char prefix[10] = {};
    char path[20] = {};
    char alias[10] = {};
    printf("1. add <type(file/dir)> <name of the directory/file>\n");
    printf("2. move <path to the destination directory>\n");
    printf("3. alias <name of the alias> <path of the directory/file>\n");
    printf("4. teleport <alias of the destination directory>\n");
    printf("5. find <prefix>\n");
    printf("6. ls\n");
    printf("7. back\n");
    printf("8. delete <name of the dir/file>\n");
    printf("9. findall <prefix> (recursive search in the entire directory)\n");
    printf("10. C&P <destination folder>\n");
    printf("11. quit\n");
    //printf("\n");

    char type[10] = {};
    char name[10] = {};
    Aliasptr Alias_HT = maketable(51);
    while (1)
    {
        if(CurrentDir != NULL)
        {
            printf("\n");
            path_from_ptr(CurrentDir,Root);
            printf(": ");
            // printf("\n");
        }
        scanf("%s", command);

        if (strcmp(command, "add") == 0)
        {
            scanf("%s %s", type, name);
            add(CurrentDir, type, name);
        }
        else if (strcmp(command, "move") == 0)
        {
            printf("\nEnter path : [root/...dir/]");
            scanf("%s", path);
            CurrentDir = ptr_from_path(Root, path);
            printf("\ncurrent directory: %s\n",CurrentDir->NodeName);
        }
        else if(strcmp(command,"C&P")==0)
        {
            printf("Enter path: ");
            scanf("%s",path);
            cut_and_paste(Root,CurrentDir,path);
        }
        
        else if (strcmp(command, "alias") == 0)
        {
            printf("\nEnter path : [root/...dir/]");
            scanf("%s", path);
            ptrcurr temp = ptr_from_path(Root, path);
            printf("Enter alias: ");
            scanf("%s",alias);
            Alias(Alias_HT,alias,temp);
        }
        
        else if (strcmp(command, "teleport") == 0)
        {
            printf("Alias: ");
            scanf("%s", alias);
            dummy = teleport(alias, Alias_HT);
            if (dummy != NULL)
            {
                CurrentDir = dummy;
            }
        }
        else if (strcmp(command, "find") == 0)
        {
            printf("Enter prefix: ");
            scanf("%s", prefix);
            find(prefix, CurrentDir);
        }
        else if (strcmp(command, "quit") == 0)
        {
            Root = free_tree(Root);
            free_aliastable(&Alias_HT);
            break;
        }
        else if (strcmp(command, "ls") == 0)
            ls(CurrentDir);
        else if (strcmp(command,"back")==0)
            CurrentDir = back(CurrentDir,Root);
        else if (strcmp(command,"delete")==0)
        {
            scanf("%s",name);
            delete(CurrentDir,name);
        }
        else if (strcmp(command,"findall")==0)
        {
            printf("Enter a prefix: ");
            scanf("%s",prefix);
            findall(prefix,CurrentDir->TreeChild);
        }
        else
            printf("Enter a valid command! \n");
    }
}   
