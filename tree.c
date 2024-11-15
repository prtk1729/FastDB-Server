/* tree.c */

#include "tree.h"

/*
struct s_node{
    struct s_node* west; // downwards node is a internal node
    struct s_node* north; // parent directory
    struct s_leaf* east; // These are diff types of struct -> leaves containing actual data
    int8 path[256];
    Tag tag;
};
typedef struct s_node Node;
*/


// define the Root
Tree root = {
// union -> Either Node or Leaf
.n = {
        .west = 0, // similar type i.e Node
        .north = (Node*)&root, // points to itself as it is a root -> No par
        .east = 0, // leaf
        .path = "/",
        .tag = ( TagRoot | TagNode )
     }
};

int main(){
    // printf("Hello World!");
    printf("%p\n", (void*)&root); // can print the addr of the root -> 0x104d7e000
    return 0;
}