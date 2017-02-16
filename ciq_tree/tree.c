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
    node* node;
    struct maxLL* next;
    node* source;
    bool fromParent;
} maxLL;

typedef struct boolMaxTuple{
    int max;
    bool found;
} boolMaxTuple;

// Traverse from the root, identifying parent by double-pairing
void sepParChild(node* source, node* new){
    int iterations = new->numChildren; // Because we modify numChildren
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

// Add to end of linked-list queue
maxLL* addToQueue(maxLL* last, node* node, int newMax){
    maxLL* next = malloc(sizeof(maxLL));
    // If allocation fails, we might miss the node
    if(next == NULL){
        fprintf(stderr,"Allocation failed");
        exit(-1);
    }
    next->next = NULL;

    if(last->next == NULL){
        last->next = next;
    }
    else{
        while(last->next){
            last = last->next;
        }
        last->next = next;
    }
    last->next->max = newMax;
    last->next->node = node;
    return last->next;
}

// Handles traversal, ignoring source node if we've traversed upwards
boolMaxTuple maxTraverse(maxLL* toCheck, node* b){
    boolMaxTuple ret = { .found = false, .max = toCheck->max };
    maxLL* last = toCheck;
    node* source;
    int newMax;
    do{
        for(int i=0,childrenFound=0; childrenFound < toCheck->node->numChildren - (int)toCheck->fromParent; ++i){
            if((toCheck->node->children[i] && toCheck->node->children[i] != toCheck->source)){
                ++childrenFound;
                newMax = toCheck->node->children[i]->n >= toCheck->max ? toCheck->node->children[i]->n : toCheck->max;
                if(toCheck->node->children[i] == b){
                    ret.max = newMax;
                    ret.found = true;
                    return ret;
                }
                else if(toCheck->node->children[i]->children){
                    last = addToQueue(last,toCheck->node->children[i],newMax);
                    last->fromParent = false;
                    last->source = toCheck->node;
                }
             }
        }
        if(toCheck->node->parent && toCheck->node->parent != toCheck->source){
            newMax = toCheck->node->parent->n >= toCheck->max ? toCheck->node->parent->n : toCheck->max;
            if (toCheck->node->parent == b){
                ret.max = newMax;
                ret.found = true;
                return ret;
            }
            last = addToQueue(last,toCheck->node->parent,newMax);
            last->fromParent = true;
            last->source = toCheck->node;
        }

        if(toCheck->next)
            toCheck = toCheck->next;
        else
            toCheck = NULL;
    }while(toCheck);

    return ret;
}

void freeMaxLL(maxLL* loc)
{
   maxLL* tmp;
   int count = 0;
   while (loc->next != NULL){
       tmp = loc;
       loc= loc->next;
       free(tmp);
   }
}

void add(node* n, int val){
    n->n += val;
    for(int i = 0, found = 0; found < n->numChildren; ++i){
        if(n->children[i]){
            ++found;
            add(n->children[i],val);
        }
    }
}

int maxNode(node* a, node* b){
    // First, breadth-first traversal of children of a
    // Linked-list that contains max along path and node
    if(a == b)
        return a->n;

    maxLL* toCheck = malloc(sizeof(maxLL));
    maxLL* first = toCheck;

    toCheck->node = a;
    toCheck->max = a->n;
    toCheck->next = NULL;
    toCheck->source = NULL;
    boolMaxTuple result = maxTraverse(toCheck,b);
    if(result.found){
        return result.max;
    }

    freeMaxLL(first);
    return INT_MIN;
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
        node_arr[i].parent = calloc(1,sizeof(node_arr[i]));
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
    node_arr[0].parent=NULL;

    int numQueries, arg1, arg2;
    scanf("%d",&numQueries);
    char query[4];
    for(int i = 0; i < numQueries; ++i){
        scanf("%s %d %d",&query[0],&arg1,&arg2);

        if(!strcmp("add",query))
            add(&node_arr[arg1-1],arg2);
        else
            printf("%d\n",maxNode(&node_arr[arg1-1],&node_arr[arg2-1]));
    }

    free(node_arr);
}

