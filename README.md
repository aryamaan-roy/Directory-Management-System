# DSA-Project-Team-31
## Directory Management  
The project is completely implemented in C.  
### File Structure  
The repo contains main.c, project.c and a header file project.h which contains declarations of structs and functions used in the project.

### Instructions to run
- Clone the repo using `git clone https://github.com/aforakhilesh/DSA-Project-Team-31.git`
- Run `gcc main.c` in the terminal,which creates an executable file in the same folder which can be executed by running `./a.out`
- You will be taken inside a Command line interface(CLI), which acts as the dummy directory for the entire project. 
- Here, you can add,delete,move and find files and directories and also create aliases and teleport using aliases.
- You can also navigate back and forth in the directory by using `ls` and `back`.
- You can quit by typing quit in the command line, which deletes the tree before quitting preventing permanant loss of memory..

### Test Cases
`root: add dir dsa`  
`root: add dir dab`  
`root: add file readme.md`  
`root: ls`  
(dsa readme.txt)  
`root: move`  
(Asks for path: root/dsa/)  
`root/dsa/: alias`  
(asks for alias: data)  
(asks for path: root/dsa/)  
`root/dsa/: back`  
`root: teleport`  
(asks for alias: data)  
`root/dsa/: back`  
`root/: find`  
(asks for a prefix: d)  
(dsa dab)  
`root/: quit`  
