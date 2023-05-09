#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_QUEUE_SIZE 50
typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}Deque;

void init_deque(Deque* q)
{
    q->front = q->rear = 0;
}

int is_full(Deque* q)
{
    return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(Deque* q)
{
    return (q->front == q->rear);
}

void queue_print(Deque* q)
{
    printf("Deque(front = %d rear = %d): ", q->front, q->rear);
    if (!is_empty(q))
    {
        int i = q->front;
        do
        {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%3d", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

void add_rear(Deque* q, element item)
{
    if (is_full(q))
    {
        fprintf(stderr, "Queue is Full! ");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element delete_front(Deque* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "Queue is empty.");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}


element get_front(Deque* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "Queue is empty.");
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(Deque* q, element val)
{
    if (is_full(q))
    {
        fprintf(stderr, "Queue is Full! ");
    }
    q->data[q->front] = val;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(Deque* q)
{
    int prev = q->rear;
    if (is_empty(q))
    {
        fprintf(stderr, "Queue is empty.");
    }
    q->rear = (q->rear - 1+ MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

element get_rear(Deque* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "Queue is empty.");
    }
    return q->data[q->rear];
}

int check(char string[])
{
    Deque q;
    int i = 0;
    init_deque(&q);

    while (string[i] != NULL)
    {
        if ('a' <= string[i] && string[i] <= 'z')
        {
            add_rear(&q, string[i]);
        }
        else if ('A' <= string[i] && string[i] <= 'Z')
        {
            char c = string[i] + ('a' - 'A');   //대문자->소문자
            add_rear(&q, c);
        }
        i++;
    }
    i = 0;
    int j = 0;   //알파벳이 아닌 것 카운트 
    while (string[i + j] != NULL)
    {
        if (isalpha(string[i + j]) != 0)
        {
            if ('a' <= string[i + j] && string[i + j] <= 'z')
            {
                if (delete_front(&q) != string[i + j])
                    return 0;
            }
            else if ('A' < string[i + j] && string[i + j] <= 'Z')
            {
                char a = string[i] + ('a' - 'A');
                if (delete_front(&q) != a)
                    return 0;
            }
            i++;
        }
        else j++;   //알파벳이 아닌 것 카운트
    }
    return 1;
}

void string_remove(char* string)
{
    int i, j;
    for (i = 0, j = 0; string[i]; i++)
    {
        if (!isspace(string[i]) && !ispunct(string[i])) // 공백과 구두점 모두 제거
        {
            string[j++] = tolower(string[i]);
        }
    }
    string[j] = '\0';
}

int main()
{
    Deque q;
    init_deque(&q);

    char string[MAX_SIZE] = { NULL };
    char re[MAX_SIZE];

    while (1)
    {
        printf("Enter a string(or input 'exit'): ");
        gets_s(string, sizeof(string));
        string_remove(string);
        if (check(string) == 1)
        {
            printf("%s is a palindrome.\n\n",string);
        }
        else
        {
            printf("%s is not a palindrome.\n\n",string);
        }
    }
}
