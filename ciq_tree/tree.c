#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int n;
    int numChildren;
    struct node *parent;
    struct node **children;
} node;

typedef struct maxLL{
    int max;
    struct node** children;
    struct maxLL* next;
} maxLL;

typedef struct boolMaxTuple{
    int max;
    bool found;
} boolMaxTuple;

// Traverse from the root, eliminating double-pairings so that we end up with a list of children, not pairs
void sepParChild(node* source, node* new){
    int iterations = new->numChildren; // Necessary because we modify numChildren but don't want to stop iteration early
    for(int i = 0; i < iterations; ++i){
        if(new->children[i] == source){
            new->parent = new->children[i];
            new->children[i] = NULL;
            --new->numChildren;
        }
        else{
            sepParChild(new,new->children[i]);
        }
    }
}

boolMaxTuple maxTraverseChildren(maxLL* toCheck, node* b){
    int i = 0;
    while(toCheck->children[i]){
        if(toCheck->children[i] == b){
            if(toCheck->children[i]->n > toCheck->max)
                toCheck->max = toCheck->children[i]->n;
        }
        ++i;
    }
}

void add(node* n, int val){
    n->n += val;
    for(int i = 0; i <= n->numChildren; ++i){
        if(n->children[i]){
            add(n->children[i],val);
        }
    }
}

int max_node(node* a, node* b, int numNodes){
    int currMax = a->n;

    // First, breadth-first traversal of children of a
    // Array of structs that contain linked-list of node path and max along path
    maxLL* toCheck = malloc(sizeof(maxLL));
    toCheck->children = a->children;
    maxTraverseChildren(toCheck,b);

    free(toCheck);
    return currMax;
}

int main(){
    int numNodes = 0;
    scanf("%d",&numNodes);
    node* node_arr = malloc(numNodes*sizeof(node));

    // Initializing our nodes
    // Node id will be index + 1
    for(int i = 0; i < numNodes; ++i){
        node_arr[i].n = 0;
        node_arr[i].numChildren= 0;
        node_arr[i].children = malloc((numNodes-1)*sizeof(node_arr[i]));
        node_arr[i].parent = malloc(sizeof(node_arr[i]));
    }

    int fInd, sInd;
    for(int i = 0; i < numNodes-1; ++i){
        scanf("%d %d",&fInd,&sInd);
        ++node_arr[fInd-1].numChildren;
        ++node_arr[sInd-1].numChildren;
        node_arr[fInd-1].children[node_arr[fInd-1].numChildren-1] = &node_arr[sInd-1];
        node_arr[sInd-1].children[node_arr[sInd-1].numChildren-1] = &node_arr[fInd-1];
    }

    /* for(int i = 0;i < numNodes; ++i){ */
    /*     printf("%d:  %p\n",i+1, &node_arr[i]); */
    /* } */

    // Recursively traverse, deleting backwards pointers
    sepParChild(NULL,&node_arr[0]);

    /* for(int i = 0; i < numNodes; ++i){ */
    /*     printf("%d:  numNodes: %d, n: %d\n",i+1,node_arr[i].numChildren,node_arr[i].n); */
    /* } */

    int numQueries, arg1, arg2;
    scanf("%d",&numQueries);
    char query[4];
    for(int i = 0; i < numQueries; ++i){
        scanf("%s %d %d",&query[0],&arg1,&arg2);
        printf("%s %d %d",query,arg1,arg2);

        if(!strcmp("add",query)){
            add(&node_arr[arg1-1],arg2);
            /* printf("%d",node_arr[4].n); */
        }
        else{
            max_node(&node_arr[arg1-1],&node_arr[arg2-1],numNodes);
        }
    }

    free(node_arr);
}

