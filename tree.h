/* tree.h */

#define _GNU_SOURCE // To Extend other functionalities other than std libraries

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>


// Design 
// Tree
// - Node (Has pointers to other nodes) recall: Up, Down, 1st leaf
// - Leaf (Has data and Next leaf pointer)

/*

/                               // -> root level
    /Users/prateek
    /Users/rakesh
    /Users/animesh

    /Users/login/prateek -> Posssible for duplicate names just not at the same directory level

*/


/* typedefs -> need them for as I will use them here and there*/ 
typedef unsigned int int32;
typedef unsigned short int16;
typedef unsigned char int8;
typedef unsigned char Tag;

typedef void*  Nullptr;
Nullptr nullptr = 0; 

/* #define macros */
#define TagRoot 1 /* 00 01 */
#define TagNode 2 /* 00 10 */ // Trap -> #define no ';'
#define TagLeaf 4 /* 01 00 */   /* When a node is both node and root -> 00 11 */
#define find_last(x) find_last_linear(x)
#define reterr(x)      \
        errno = (x);   \
        return nullptr

#define NoError 0



struct s_node{
    struct s_node* west; // downwards node is a internal node
    struct s_node* north; // parent directory
    struct s_leaf* east; // These are diff types of struct -> leaves containing actual data

    // data info
    int8 path[256];

    // Node-type? 
    Tag tag;
};
typedef struct s_node Node;


struct s_leaf{
    union u_tree* west; // decision for union as either it can be leaf or node NOT both (share the same memory)
    struct s_leaf* east; // will be leaves

    // data info
    int8 key[256];
    int8 *value; // actual data
    int16 size; // size of the actual data in Bytes (for values_size)

    // Node type
    Tag tag;
};
typedef struct s_leaf Leaf;


union u_tree{
    Node n;
    Leaf l;
};
typedef union u_tree Tree;