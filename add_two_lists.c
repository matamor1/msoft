#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Problem:
 *
 *    Given two singly linked lists that each represent two separate numbers. 
 *
 *    e.g:
 *        list_one  1->2->3->NULL : represents the number 321
 *        list_two  6->8->9->1->NULL : represents the number 1986
 *
 *    return a third list that represents the addition of the numbers that the 
 *    other two lists represent.
 *
 *    e.g:
 *        add_two_lists(list_one, list_two) => 7->0->3->2->NULL
 *
 *        since:
 *               321
 *             +1986
 *              ----
 *              2307 
 */    
     

typedef struct node
{
    int value;
    struct node* next;

}node_t;

typedef struct list
{
    node_t *head;
    node_t *current;
}list_t;

node_t *create_node(int val)
{
    node_t *node = malloc(sizeof(node_t *));
    if (node == NULL)
    {
        printf("Failed to create node\n");
        exit(1);
    }

    node->value = val;
    node->next = NULL;

    return node;
}

list_t *create_list()
{
    list_t *list = malloc(sizeof(list_t *));
    if (list == NULL)
    {
        printf("Failed to create list\n");
        exit(1);
    }

    list->head = NULL;
    list->current = NULL;

    return list;
}

list_t *add_to_list(list_t *list, int val)
{
    node_t *node = create_node(val);
    if(list->head == NULL)
    {
        list->head = node;
        list->current = node;
        return list;
    }

    list->current->next = node;
    list->current = node;

    return list;
}

int list_len(list_t *l)
{
    int len = 0;
    node_t *index = l->head;
    while (index != NULL)
    {
        len++;
        index = index->next;
    }
    return len;
}

void make_same_length(list_t *l_one, list_t *l_two)
{
    node_t *l_one_index = l_one->head;
    node_t *l_two_index = l_two->head;

    while(l_one_index || l_two_index)
    {
        if (l_one_index == NULL)
        {
            //printf("Padding list one\n");
            list_t *l_tmp = add_to_list(l_one, 0);
            l_one_index = l_tmp->current;
        }
        if (l_two_index == NULL)
        {
            //printf("Padding list two\n");
            list_t *l_tmp = add_to_list(l_two, 0);
            l_two_index = l_tmp->current;

        }

        l_one_index = l_one_index->next;
        l_two_index = l_two_index->next;

    }

}

list_t *sum_lists(list_t *l_one, list_t *l_two)
{
    list_t *l_combined = create_list();

    make_same_length(l_one, l_two);
    node_t *index = l_one->head;
    node_t *l_two_index = l_two->head;

    int carry = 0;
    while(index != NULL)
    {
        int partial_sum = 0;
        int tmp_sum = 0;

        tmp_sum = index->value + l_two_index->value + carry;
        partial_sum = tmp_sum % 10;
        if (tmp_sum > 9)
        {
            carry = floor(tmp_sum/10); /* carry is any value over 9 divided by ten */
        }
        else
        {
            carry = 0; /* if sum was under 10 then no carry */
        }

        add_to_list(l_combined, partial_sum);

        /* move list pointers along */
        index = index->next;
        l_two_index = l_two_index->next;

    }

    /* Add any leftover carry */
    if(carry)
        add_to_list(l_combined, carry);
   

    return l_combined;
}



void print_list(list_t *list)
{
    printf("Printing list\n");
    node_t *index = list->head;

    while (index != NULL)
    {
        printf("Value is: %d\n",index->value);
        index = index->next;
    }

}

void clean_list(list_t *list)
{
    node_t *index;
    while (list->head != NULL)
    {
        index = list->head;
        list->head = list->head->next;
        free(index);
        index = NULL;

    }
    free(list);
    list = NULL;

}
 
int main()
{
    /* Populate list one */
    list_t *list_one = create_list();
    add_to_list(list_one, 1);
    add_to_list(list_one, 2);
    add_to_list(list_one, 3);
    print_list(list_one);

    /* Populate list two */
    list_t *list_two = create_list();
    add_to_list(list_two, 6);
    add_to_list(list_two, 8);
    add_to_list(list_two, 9);
    add_to_list(list_two, 1);
    print_list(list_two);

    /* Sum lists */
    list_t *list_combined;
    list_combined = sum_lists(list_one, list_two);
    print_list(list_combined);

    /* Clean up */
    clean_list(list_one);
    clean_list(list_two);
    clean_list(list_combined);

    return 0;
}