#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 500001


typedef struct M_PriorityQueue {
    int nodes[MAX_SIZE];
    int size;
} M_PriorityQueue;


void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
    
void insert(M_PriorityQueue *q, int element);    
int delete_min(M_PriorityQueue *q);              
int delete_max(M_PriorityQueue *q);            
int delete_median(M_PriorityQueue *q);          
int find_min(M_PriorityQueue *q);              
int find_max(M_PriorityQueue *q);               
int find_median(M_PriorityQueue *q);           


int print_array[MAX_SIZE];
int print_cnt = 0;


int main()          
{
    clock_t start, end;
    start = clock();

    M_PriorityQueue *pq = (M_PriorityQueue *)malloc(sizeof(M_PriorityQueue));       
    pq->size = 0;

    int n;
    scanf("%d", &n);
    char operation, target;
    int value; 

    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &operation);
        switch (operation)
        {
            case 'I':
                scanf("%d", &value);
                insert(pq, value);
                break;
            case 'D':
                scanf(" %c", &target);
                if (target == 'M') 
                {
                    delete_min(pq);
                    break;
                }
                else if (target == 'X')
                {
                    delete_max(pq);
                    break;
                }
                else if (target == 'E')
                {
                    delete_median(pq);
                    break;
                }
            case 'F':
                scanf(" %c", &target);
                if (target == 'M') 
                {
                    find_min(pq);
                    break;
                }
                else if (target == 'X')
                {
                    find_max(pq);
                    break;
                }
                else if (target == 'E')
                {
                    find_median(pq);
                    break;
                }
            default:
                break;
        }
    }
    end = clock();
    printf("Execution time: %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    for (int i = 0; i < print_cnt; i++) {
        if (print_array[i] == -1) 
        {
            printf("NULL\n");
        }
        else 
        {
            printf("%d\n", print_array[i]);
        }
    }   

    free(pq);
    return 0;
}




void insert(M_PriorityQueue *q, int element)      
{  
    (q->size)++;
    int i;
    for (i = q->size-1; i > 0 && q->nodes[i] > element; i--) {
        q->nodes[i + 1] = q->nodes[i];
    }
    q->nodes[i + 1] = element;
}


int delete_min(M_PriorityQueue *q)                
{
    if (q->size == 0)
    {
        return -1;
    }

    int d_min = q->nodes[1];
    for (int i = 1; i < q->size; i++)
    {
        swap(&q->nodes[i], &q->nodes[i+1]);
    }
    (q->size)--;

    return d_min;
}

int delete_max(M_PriorityQueue *q)         
{
    if (q->size == 0) 
    {
        return -1;
    }
    int d_max = q->nodes[q->size];
    (q->size)--;

    return d_max;
}

int delete_median(M_PriorityQueue *q)           
{
    if (q->size == 0)
    {
        return -1; 
    }
    int index, d_median;
    if (q->size % 2 == 0)
    {
        index = (q->size)/2;
        d_median = q->nodes[index];
        for (int i = index; i <= q->size; i++)
        {
            swap(&q->nodes[i], &q->nodes[i+1]);
        }
    }
    else 
    {
        index = (q->size)/2 + 1;
        d_median = q->nodes[index];
        for (int i = index; i <= q->size; i++)
        {
            swap(&q->nodes[i], &q->nodes[i+1]);
        }
    }
    (q->size)--;
    
    return d_median;
}


int find_min(M_PriorityQueue *q)              
{
    if (q->size == 0)
    {
        print_array[print_cnt++] = -1; 
        return -1;
    }
    print_array[print_cnt++] = q->nodes[1];
    return q->nodes[1];
}

int find_max(M_PriorityQueue *q)                
{
    if (q->size == 0)
    {
        print_array[print_cnt++] = -1; 
        return -1;
    }
    print_array[print_cnt++] = q->nodes[q->size]; 
    return q->nodes[q->size];
}

int find_median(M_PriorityQueue *q)                               
{
    if (q->size == 0)
    {
        print_array[print_cnt++] = -1;
        return -1;
    }

    if (q->size % 2 == 0)
    {
        print_array[print_cnt++] = q->nodes[(q->size) / 2];
        return q->nodes[(q->size) / 2];
    }
    else 
    {
        print_array[print_cnt++] = q->nodes[(q->size) / 2 + 1]; 
        return q->nodes[(q->size) / 2 + 1];
    }
}
