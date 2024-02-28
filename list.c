#include "shell.h"

/**
 * create_node - creates a new node with given values
 * @str: string value for the new node
 * @num: node index used by history
 *
 * Return: newly created node
 */
list_t *create_node(const char *str, int num)
{
    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }

    return new_node;
}

/**
 * add_node - adds a node to the specified position in the list
 * @head: address of pointer to the head node
 * @str: str field of the new node
 * @num: node index used by history
 * @position: position to add the new node
 *
 * Return: size of the list
 */
list_t *add_node(list_t **head, const char *str, int num, unsigned int position)
{
    if (!head)
        return NULL;

    list_t *new_node = create_node(str, num);
    if (!new_node)
        return NULL;

    if (position == 0)
    {
        new_node->next = *head;
        *head = new_node;
        return new_node;
    }

    list_t *current = *head;
    while (--position && current)
        current = current->next;

    if (!current)
    {
        free(new_node->str);
        free(new_node);
        return NULL; // Position out of bounds
    }

    new_node->next = current->next;
    current->next = new_node;

    return new_node;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to the head node
 * @str: str field of the new node
 * @num: node index used by history
 *
 * Return: size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    if (!head)
        return NULL;

    list_t *new_node = create_node(str, num);
    if (!new_node)
        return NULL;

    if (!*head)
    {
        *head = new_node;
        return new_node;
    }

    list_t *current = *head;
    while (current->next)
        current = current->next;

    current->next = new_node;

    return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to the head node
 *
 * Return: size of the list
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return i;
}

/**
 * delete_node_at_index - deletes the node at the specified index
 * @head: address of pointer to the head node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        list_t *temp = *head;
        *head = (*head)->next;
        free(temp->str);
        free(temp);
        return 1;
    }

    list_t *current = *head;
    list_t *prev = NULL;

    while (index && current)
    {
        prev = current;
        current = current->next;
        index--;
    }

    if (!current)
        return 0;

    prev->next = current->next;
    free(current->str);
    free(current);

    return 1;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    if (!head_ptr || !*head_ptr)
        return;

    list_t *current = *head_ptr;
    list_t *next_node;

    while (current)
    {
        next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }

    *head_ptr = NULL;
}

