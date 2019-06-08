#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


typedef struct node{
    int life;
    struct node *l2,*l4,*l6,*l8;
    int next;
    int sum;
}node;


void n_print(node *cur){
    node *p = cur;
    while(p != NULL){
        printf("%d ", p -> life);
        p = p -> l6;
    }
    printf("\n");
    if(cur -> l8 != NULL){
        n_print(cur -> l8);
    }
}
void sum_print(node *cur){
    node *p = cur;
    while(p != NULL){
        printf("%d ", p -> sum);
        p = p -> l6;
    }
    printf("\n");
    if(cur -> l8 != NULL){
        sum_print(cur -> l8);
    }
}

node *initnode(void){
    struct node *p = malloc(sizeof(struct node));
    p -> life = 0;
    p -> l2 = NULL; p -> l4 = NULL; p -> l6 = NULL; p -> l8 = NULL;
    p -> next = 0;
    p -> sum = 0;
    return p;
}




node *mkmat(int row, int column){
    node *f = initnode();
    node *u = f;
    node *b = f;
    node *a;
    for(int i = 0; i < row -1 ; i++){
        node *a = initnode();
        b -> l6 = a;
        a -> l4 = b;
        b = a;
    }
    for(int j = 0; j < column - 1 ; j++){
        b = initnode();
        node *bu = b;
        b -> l2 = u;
        u -> l8 = b;
        u = u -> l6;
        for(int i = 0; i < row -1 ; i++){
            a = initnode();
            b -> l6 = a;
            a -> l4 = b;
            a -> l2 = u;
            u -> l8 = a;
            b = a;
            u = u -> l6;
        }
        u = bu;
    }
    return f;
}



void nodesum(node *cur){
    if(cur -> life == 1){
        if(cur -> l2 != NULL){
            cur -> l2 -> sum++;
            if(cur -> l2 -> l4 != NULL){
                cur -> l2 -> l4 -> sum++;
            }
            if(cur -> l2 -> l6 != NULL){
                cur -> l2 -> l6 -> sum++;
            }
        }
        if(cur -> l4 != NULL){
            cur -> l4 -> sum++;
        }
        if(cur -> l6 != NULL){
            cur -> l6 -> sum++;
        }
        if(cur -> l8 != NULL){
            cur -> l8 -> sum++;
            if(cur -> l8 -> l4 != NULL){
                cur -> l8 -> l4 -> sum++;
            }
            if(cur -> l8 -> l6 != NULL){
                cur -> l8 -> l6 -> sum++;
            }
        }
    }
}

void msum(node*cur){
    node *p = cur;
    while(p != NULL){
        nodesum(p);
        p = p -> l6;
    }
    if(cur -> l8 != NULL){
        msum(cur -> l8);

    }
}
void countnext(node *cur){
    node *p = cur;
    while(p != NULL){
        if((p -> life == 1) && ((p -> sum == 2) || (p -> sum == 3))) p->next = 1;
        else if((p -> life == 0) && (p->sum == 3)) p->next = 1;
        else p -> next = 0;
        p = p -> l6;
    }
    if(cur -> l8 != NULL){
        countnext(cur -> l8);
    }
}

node *initmat(node *f,int list[][2],int n){
    if(n<1){
        return f;
    }
    else{
        node *p = f;
        for(int i=0;i<list[0][0];i++){
            p = p -> l8;
        }
        for(int i=0;i<list[0][1];i++){
            p = p -> l6;
        }
        p -> life = 1;
        for(int k = 1; k < n  ; k ++){
            int b = list[k][1]-list[k-1][1];
            for(int i=0;i<list[k][0]-list[k-1][0];i++){
                p = p -> l8;
            }
            if(b < 0){
                for(int i=0;i>b;i--){
                    p = p -> l4;
                }
            }
            else{
                for(int i=0;i<b;i++){
                    p = p -> l6;
                }
            }
            p -> life = 1;
        }
    }
    msum(f);
    countnext(f);
    return f;
}


node *nextmat(node *cur){
    node *p = cur;
    while(p != NULL){
        p -> life = p->next;
        p -> sum = 0;
        p = p -> l6;
    }
    if(cur -> l8 != NULL){
        nextmat(cur -> l8);
    }

    return cur;
}

int main(void){
    node *p = mkmat(11,11);
    p = mkmat(11,11);
    printf("\n");
    int list[][2] = {{4,5},{5,4},{5,5},{5,6},{6,5}};
    p = initmat(p,list,5);

    while(1){
        system("clear");
        n_print(p);
        printf("\n");
        sleep(1);
        nextmat(p);
        msum(p);
        countnext(p);
            
    }
    
    return 0;
}