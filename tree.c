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


Node* create_node(Node* parent, int8* path){
    assert(parent); // non-null

    // create a new Node -> memset -> attach links etc
    Node* current;  

    int16 size = sizeof(struct s_node);
    current = (Node*)malloc( size ); // allocates mem to current

    parent->west = current;

    // memset current before init the other things
    // current = zero( (int8 *)current, size );
    assert(current);
    memset(current, 0, size );

    // west will bge set when it will have child
    // current->east = 0; and current->west = 0;
    current->north = parent;
    current->tag = TagNode;
    strncpy( (char *)current->path, (char *)path, 255 ); // recall: dest, src, size_to_be_init

    return current;
}

int main(){
    // printf("Hello World!");
    // printf("%p\n", (void*)&root); // can print the addr of the root -> 0x104d7e000

    Node* n = create_node((Node *)&root, (int8 *)"/Users");
    assert(n);
    Node* n2 = create_node(n, (int8 *)"/Users/login");
    assert(n2);

    printf("%p %p\n", n, n2); // 0x56030e5c62a0 0x56030e5c63d0
    return 0;
}