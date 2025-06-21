#include "minishell.h"
void add_list_back(s_env **head,s_env *last){
	if(*head == NULL)
		*head = last;
	else{
	s_env *temp = *head;
	while(temp->next)
		temp = temp->next;
	temp->next = last;
	}
}
void free_list(s_env *list){
    s_env *temp;
    temp = list;
    while(temp){
        free(list->value);
        free(list->name);
        list = list->next;
        free(temp);
        temp = list;
    }
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}

int	ft_strlen_c(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	return (i);
}

char	**ft_arr_str(char *name, char *val)
{
	char	**arr;
	int		count;

	if (!name)
		return (NULL);
	if (val)
		count = 3;
	else
		count = 2;
	arr = (char **)malloc(sizeof(char *) * count);
	if (!arr)
		return (NULL);
	arr[0] = name;
	if (val)
	{
		arr[1] = val;
		arr[2] = NULL;
	}
	else
	{
		arr[1] = NULL;
	}
	return (arr);
}

char	**ft_split_lite(const char *s, char d)
{
	char	*n_str;
	char	*v_str;
	char	**res;
	int		n_len;
	const char	*v_start;

	if (!s)
		return (NULL);
	n_str = NULL;
	v_str = NULL;
	n_len = ft_strlen_c(s, d);
	n_str = (char *)malloc(n_len + 1);
	if (!n_str)
		return (NULL);
	ft_memcpy(n_str, s, n_len);
	n_str[n_len] = '\0';
	if (s[n_len] == d)
	{
		v_start = s + n_len + 1;
		int v_len = ft_strlen_c(v_start, '\0');
		v_str = (char *)malloc(v_len + 1);
		if (!v_str)
		{
			free(n_str);
			return (NULL);
		}
		ft_memcpy(v_str, v_start, v_len);
		v_str[v_len] = '\0';
	}
	res = ft_arr_str(n_str, v_str);
	if (!res)
	{
		free(n_str);
		if (v_str)
			free(v_str);
		return (NULL);
	}
	return (res);
}
s_env *create_new_node(char **env){
    s_env *node = malloc(sizeof(s_env));
        if(!node)
            return NULL;
    node->name = env[0];
    node->value = env[1];
    node->next = NULL;
	free(env);
    return node;
}

s_env *create_env_node(char **str){
    int i = 0;
    char **tmp;
    if(!str)
        return NULL;
    tmp = ft_split_lite(str[i++],'=');
	if(!tmp)
		return NULL;
    s_env *head = create_new_node(tmp);
	if(!head){
		free(tmp);
		return (NULL);
	}
    s_env *next_node = head;
    while(str[i]){
    tmp = ft_split_lite(str[i],'=');
        if (!tmp) {
            free_list(head);
            return NULL;
        }
    next_node->next = create_new_node(tmp);
    next_node = next_node->next;
    i++;
    }
    return head;
}