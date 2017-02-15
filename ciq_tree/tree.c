#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct node{
    int n;
    int id;
    int numChildren;
    struct node *parent;
    struct node **children;
} node;

typedef struct maxLL{
    int max;
    struct node *node;
    struct maxLL* next;
    node* source;
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
            printf("NEXT NODE: %d  max: %d\n",toCheck->next->node->id,toCheck->max);
            toCheck = toCheck->next;
        }
    }
}

// If source pointer is non-null, we know we've sent parent node in maxLL
boolMaxTuple maxTraverseChildren(maxLL* toCheck, node* b){
    boolMaxTuple ret = { .found = false, .max = INT_MIN };
    maxLL* last = toCheck;
    int newMax;
    do{
        int sLower = toCheck->source ? 1 : 0;
        /* printf("at %d, about to check UP TO %d children\n",toCheck->node->id,toCheck->node->numChildren-sLower); */
        for(int i=0,childrenFound=0; childrenFound < toCheck->node->numChildren - sLower; ++i){
            sLower = toCheck->source ? 1 : 0;
            /* printf("slower: %d\n",sLower); */
            if((toCheck->node->children[i] && toCheck->node->children[i] != toCheck->source)
                    || (toCheck->node->children[i] && !toCheck->source)){
                ++childrenFound;
                printf("found child of %d, %d\n",toCheck->node->id, toCheck->node->children[i]->id);
                newMax = toCheck->node->children[i]->n >= toCheck->max ? toCheck->node->children[i]->n : toCheck->max;
                if(toCheck->node->children[i] == b){
                    ret.max = newMax;
                    ret.found = true;
                    return ret;
                }
                else if(toCheck->node->children[i]->children){
                    last = addToQueue(last,toCheck->node->children[i],newMax);
                    /* printf("added to queue, "); */
                    /* printf("current queue: \n"); */
                    /* printCurrentQueue(toCheck); */
                    /* printf("made it past printing queue\n"); */
                }
             }
        }
        /* printf("finished termination of for loop in traversal\n"); */
        if(toCheck->next)
            toCheck = toCheck->next;
        /* printf("about to run again or fail\n"); */
    }while(toCheck->next);
    /* printf("made it to parent traversal\n"); */
    /* printf("parent pointer: %p\n",first->parent); */
    return ret;
}

void freeMaxLL(maxLL* loc)
{
   maxLL* tmp;
   int count = 0;
   while (loc->next != NULL){

       ++count;
       tmp = loc;
       loc= loc->next;
       printf("node within link being freed: %d  ",tmp->max);
       printf("\n");
       free(tmp);
   }
   printf("\nsuccessfully free %d pointers\n",count);
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
    node* temp;
    toCheck->node = a;
    toCheck->max = a->n;
    toCheck->source = NULL;
    boolMaxTuple result = maxTraverseChildren(toCheck,b);
    if(result.found){
        return result.max;
    }
    /* printf("child traversal finished\n"); */

    do{
        /* printf("parent we're about to go to: %d\n",toCheck->node->parent->id); */
        int newMax = toCheck->node->n >= toCheck->node->parent->n ? toCheck->node->n : toCheck->node->parent->n;
        if(toCheck->node->parent == b){
            printf("found!!\n");
            return newMax;
        }
        /* printf("toCheck node : %d   ",toCheck->node->id); */
        temp = toCheck->node;
        toCheck = addToQueue(toCheck,toCheck->node->parent,newMax);
        toCheck->source = temp;
        /* printf("toCheck node: %d  ",toCheck->node->id); */
        /* printf("toCheck->source id: %d",toCheck->source->id); */
        /* printf("\n"); */
        result = maxTraverseChildren(toCheck,b);
        if(result.found){
            printf("found!!\n");
            return result.max;
        }
    }while(toCheck->node->parent);
    maxLL* actualFirst = first;
    printf("Number of pointers we are about to try and free: ");
    int countPointers = 0;
    while(first->next){
        ++countPointers;
        first = first->next;
    }
    printf("countPointers = %d\n",countPointers);
    freeMaxLL(actualFirst);
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
        node_arr[i].id = i+1;
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

    /* for(int i = 0; i < numNodes; ++i){ */
    /*     printf("%d:  %p  ",i,&node_arr[i]); */
    /* } */
    /* printf("\n"); */
    /* for(int i = 0; i < numNodes; ++i){ */
    /*     printf("%d: %p  ",i,node_arr[i].parent); */
    /* } */
    /* printf("\n"); */

    int numQueries, arg1, arg2;
    scanf("%d",&numQueries);
    char query[4];
    for(int i = 0; i < numQueries; ++i){
        scanf("%s %d %d",&query[0],&arg1,&arg2);

        if(!strcmp("add",query)){
            add(&node_arr[arg1-1],arg2);
        }
        else{
            printf("max %d %d\n",arg1,arg2);
            printf("%d\n",maxNode(&node_arr[arg1-1],&node_arr[arg2-1]));
        }
    }

    free(node_arr);
}

