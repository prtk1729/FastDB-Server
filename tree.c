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

void zero(int8* str, int16 size){
    int8* p;
    int16 i;

    for(p = str, i = 0; i < size; i++, p++)
        *p = 0; 
    return;
}



Node* create_node(Node* parent, int8* path){
    assert(parent); // non-null

    // create a new Node -> memset -> attach links etc
    Node* current;  

    int16 size = sizeof(struct s_node);
    current = (Node*)malloc( size ); // allocates mem to current
    assert(current);

    parent->west = current;

    // memset current before init the other things
    zero( (int8 *)current, size );
    // memset(current, 0, size );

    // west will bge set when it will have child
    // current->east = 0; and current->west = 0;
    current->north = parent;
    current->tag = TagNode;
    strncpy( (char *)current->path, (char *)path, 255 ); // recall: dest, src, size_to_be_init

    return current;
}


Leaf* find_last_linear(Node* parent){
    assert(parent);

    // assume parent exists
    Leaf* l;

    if( !parent->east )
        reterr(NoError); // both are pragmas for when no leaf

    for(l = parent->east; l->east; l = l->east)
    assert(l);

    return l;
}

Leaf* create_leaf( int8* key, int8* value, Node* parent, int16 value_size ){

    assert(parent);
    // Need to figure out the last leaf or is it the Node(i.e not a Leaf?)?
    // Node -> leaf1 -> leaf2 -> leaf3 ... [parent can be leaf/Node]
    Leaf* l;
    Node* n;

    // create a leaf
    Leaf* new_leaf = (Leaf*)malloc(sizeof(struct s_leaf));
    assert(new_leaf); // actually mem allocated?
    // zero( (int8 *)new_leaf, leaf_size ); // each byte is zeroed.

    l = find_last(parent); // l can be null or the last leaf that exists
    if(!l) {// 1st Node
        parent->east = new_leaf;
        new_leaf->west = (Tree *)parent; // this new_leaf is why we made .west as Union
    }
    else{
        l->east = new_leaf;
        new_leaf->west = (Tree *)l; 
    }

    new_leaf->tag = TagLeaf;

    // set key and value
    strncpy( (char *)new_leaf->key, (char *)key, 127 ); // 255 max

    // allocate mem for value
    new_leaf->value = (int8 *)malloc(sizeof(value_size));
    assert(new_leaf->value);
    zero( (int8 *)new_leaf->value, value_size );
    strncpy( (char *)new_leaf->value, (char *)value, value_size );

    return new_leaf;
}

int main(){
    /* Verify Skeleton */ 
    printf("Hello World!");
    printf("Root: %p\n", (void*)&root); // can print the addr of the root -> 0x104d7e000

    /* Verify create_node() */ 
    Node* n = create_node((Node *)&root, (int8 *)"/Users");
    assert(n);
    Node* n2 = create_node(n, (int8 *)"/Users/login");
    assert(n2);
    printf("Par-NodeAddr, Child-NodeAddr: %p %p\n", n, n2); // 0x56030e5c62a0 0x56030e5c63d0
    // free after use -> Best prac
    free(n);
    free(n2);

    /* Verify create_leaf() */ 
    Leaf* l1;
    int8 *key = (int8 *)"/prateek";
    int8 *value = (int8 *)"abc123"; // some cookie for prateek's session(say) 
    int16 value_size = (int16)strlen((char *)value);
    l1 = create_leaf(key, value, n, value_size); // size = sizeof string
    assert(l1);
    printf("Leaf-Addr: %p\n", l1);
    printf("value: %s\n", l1->value);
    free(l1);

    Leaf* l2;
    key = (int8 *)"/prateek";
    value = (int8 *)"abc234"; // some cookie for prateek's session(say) 
    value_size = (int16)strlen((char *)value);
    l2 = create_leaf(key, value, n, value_size); // size = sizeof string
    assert(l2);
    printf("Leaf-Addr: %p\n", l2);
    printf("key: %s\n", l2->key);
    free(l2);



    return 0;
}