#include "minishell.h"
void free_node(s_env *n)
{
    free(n->name);
    free(n->value);
    free(n);
}
int destroy_node(char *name)
{
    s_env *node = get_env_str(name,shell_data.env_list);
    if(!node)
        return 0;
    s_env **head = &(shell_data.env_list);
    if(*head != node)
    {
    s_env *temp = shell_data.env_list;
    while (temp->next != node)
        temp=temp->next;
    temp->next = node->next;
    free_node(node);
    }
    else
    {
        *head = node->next;
        free_node(node);
    }
    return (0);
}
int ft_unset(char **str)
{
    if((!str) || (str && !str[1]))
        return (0);
    str++;
    int i;
    i = 0;
    while(str[i]){
        destroy_node(str[i]);
        i++;
    }
    return (0);
}