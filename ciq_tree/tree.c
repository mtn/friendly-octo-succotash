#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct node{
    int n;
    int numChildren;
    struct node *parent;
    struct node **children;
} node;

typedef struct maxLL{
    int max;
    struct node *node;
    struct maxLL* next;
} maxLL;

typedef struct boolMaxTuple{
    int max;
    bool found;
} boolMaxTuple;

// Traverse from the root, identifying parent by double-pairing
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

// Traverse linked list and add to end of queue
void addToQueue(maxLL* toCheck, node* child, int newMax){
    maxLL* next = malloc(sizeof(maxLL));
    // If allocation fails, we might miss the node
    if(next == NULL){
        fprintf(stderr,"Allocation failed");
        exit(-1);
    }

    if(toCheck->next == NULL){
        toCheck->next = next;
    }
    else{
        while(toCheck->next){
            toCheck = toCheck->next;
        }
        toCheck->next = next;
    }
}

void printCurrentQueue(maxLL* toCheck){
    if(toCheck->next == NULL){
        printf("Nothing more in queue\n");
        return;
    }
    else{
        while(toCheck->next){
            printf("%p\n",toCheck);
            toCheck = toCheck->next;
        }
    }
}

boolMaxTuple maxTraverseChildren(maxLL* toCheck, node* b){
    boolMaxTuple ret = { .found = false, .max = INT_MIN };
    int newMax;
    do{
        /* printf("Current queue: \n"); */
        /* printCurrentQueue(toCheck); */
        for(int i=0,found=0; found < toCheck->node->numChildren; ++i){
            if(toCheck->node->children[i]){
                ++found;
                if(toCheck->node->children[i] == b){
                    printf("found b");
                    ret.max = newMax;
                    ret.found = true;
                    return ret;
                }
                else if(toCheck->node->children[i]->children){
                    /* printf("didn't find b, building onto queue"); */
                    addToQueue(toCheck,toCheck->node->children[i],newMax);
                }
            }
            ++i;
        }
        toCheck = toCheck->next;
    }while(toCheck->next);
    return ret;
}

void freeMaxLL(maxLL* fst)
{
   maxLL* tmp;
   while (fst != NULL)
    {
       tmp = fst;
       fst = fst->next;
       free(tmp);
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
    toCheck->node = a;
    printf("numChildren: %d",toCheck->node->children[1]->parent->numChildren);
    printf("Calling traverse children\n");
    maxTraverseChildren(toCheck,b);
    printf("Made it out of traverse children\n");

    freeMaxLL(toCheck);
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

    // Recursively traverse, deleting backwards pointers
    sepParChild(NULL,&node_arr[0]);

    printf("Pointers:\n");
    for(int i = 0; i < numNodes; ++i){
        printf("%d:  %p      ",i,&node_arr[i]);
    }
    printf("\n");
    printf("\n%d\n",node_arr[2].n);

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
            printf("made it here");
            printf("%d",max_node(&node_arr[arg1-1],&node_arr[arg2-1],numNodes));
        }

    }

    free(node_arr);
}

