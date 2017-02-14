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

// Traverse linked list and add to end of queue
maxLL* addToQueue(maxLL* last, node* child, int newMax){
    maxLL* next = malloc(sizeof(maxLL));
    // If allocation fails, we might miss the node
    if(next == NULL){
        fprintf(stderr,"Allocation failed");
        exit(-1);
    }

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
    last->next->node = child;
    return last->next;
}

void printCurrentQueue(maxLL* toCheck){
    if(toCheck->next == NULL){
        printf("Nothing more in queue\n");
        return;
    }
    else{
        while(toCheck->next){
            printf("%p  %d\n",toCheck->next,toCheck->max);
            toCheck = toCheck->next;
        }
    }
}

// If source pointer is non-null, we know we've sent parent node in maxLL
boolMaxTuple maxTraverseChildren(maxLL* toCheck, node* b, node* source){
    boolMaxTuple ret = { .found = false, .max = INT_MIN };
    maxLL* last = toCheck;
    int newMax;
    do{
        int sLower = source ? 1 : 0;
        printf("about to traverse %d children\n",toCheck->node->numChildren-sLower);
        for(int i=0,childrenFound=0; childrenFound < toCheck->node->numChildren - sLower; ++i){
            if((toCheck->node->children[i] && toCheck->node->children[i] != source)
                    || (toCheck->node->children[i] && !source)){
                ++childrenFound;
                printf("found child of %p, %p\n",toCheck->node, toCheck->node->children[i]);
                newMax = toCheck->node->children[i]->n >= toCheck->max ? toCheck->node->children[i]->n : toCheck->max;
                if(toCheck->node->children[i] == b){
                    ret.max = newMax;
                    ret.found = true;
                    return ret;
                }
                else if(toCheck->node->children[i]->children){
                    last = addToQueue(last,toCheck->node->children[i],newMax);
                    source = NULL;
                    /* printf("current queue: \n"); */
                    /* printCurrentQueue(toCheck); */
                }
             }
        }
        if(toCheck->next)
            toCheck = toCheck->next;
    }while(toCheck->next);
    /* printf("made it to parent traversal\n"); */
    /* printf("parent pointer: %p\n",first->parent); */
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
    for(int i = 0, found = 0; found < n->numChildren; ++i){
        if(n->children[i]){
            ++found;
            add(n->children[i],val);
        }
    }
}

int max_node(node* a, node* b){
    // First, breadth-first traversal of children of a
    // Linked-list that contains max along path and node
    maxLL* toCheck = malloc(sizeof(maxLL));
    maxLL* first = toCheck;
    node* source;
    toCheck->node = a;
    toCheck->max = a->n;
    boolMaxTuple result = maxTraverseChildren(toCheck,b,NULL);
    if(result.found){
        return result.max;
    }
    printf("child traversal finished\n");

    do{
        printf("parent: %p\n",toCheck->node->parent);
        int newMax = toCheck->node->n >= toCheck->node->parent->n ? toCheck->node->n : toCheck->node->parent->n;
        if(toCheck->node->parent == b)
            return newMax;
        source = toCheck->node;
        printf("toCheck node : %p   ",toCheck->node);
        toCheck = addToQueue(toCheck,toCheck->node->parent,newMax);
        printf("toCheck node: %p",toCheck->node);
        printf("\n");
        result = maxTraverseChildren(toCheck,b,source);
        if(result.found){
            printf("found!!\n");
            return result.max;
        }
    }while(toCheck->node->parent);
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

    for(int i = 0; i < numNodes; ++i){
        printf("%d:  %p  ",i,&node_arr[i]);
    }
    printf("\n");
    for(int i = 0; i < numNodes; ++i){
        printf("%d: %p  ",i,node_arr[i].parent);
    }
    printf("\n");

    int numQueries, arg1, arg2;
    scanf("%d",&numQueries);
    char query[4];
    for(int i = 0; i < numQueries; ++i){
        scanf("%s %d %d",&query[0],&arg1,&arg2);

        if(!strcmp("add",query)){
            add(&node_arr[arg1-1],arg2);
        }
        else{
            printf("%d\n",max_node(&node_arr[arg1-1],&node_arr[arg2-1]));
        }
    }

    free(node_arr);
}

