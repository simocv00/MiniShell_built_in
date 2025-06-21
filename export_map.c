#include "minishell.h"
static void free_split(char **s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (i < 4)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
static int export_errors(char *cwd,int type){
    if(type == 0){
        ft_putstr_fd(shell_data.shellname,2);
        ft_putstr_fd(": export: `",2);
        ft_putstr_fd(cwd,2);
        ft_putstr_fd("': not a valid identifier\n",2);
        return 1;
    }
    return 1;
}

char *join_and_free(char *s1,char *s2){
    char *str = malloc((ft_strlen(s1)+ft_strlen(s2)) + 1);
        if(!str)
            return NULL;
    int i = 0,j =0;
    while (s1 && s1[i]){
        str[i] = s1[i];i++;}
    
    while (s2 && s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    free(s1);
    free(s2);
    return str;
}
char *s_cpy(char *str,int start,int end){
    if(!str || start >= end)
        return NULL;
    char *s = malloc((end - start)+1);
        if(!s)
            return (NULL);
    int i = 0;
    while (start < end){
        s[i] =  str[start];
        start++;
        i++;
    }
    if(s[i])
    s[i] = '\0';
return s;
}
char **ex_split(char *str){
    if(!str)
        return NULL;
    char **s = malloc((sizeof(char *) * 4));
    if(!s)
        return NULL;
    int f = 0;
    int i = 0, len =ft_strlen(str);
    while(str[i] && str[i] != '=')
        i++;
    f = i;
    if((i > 0 ) && (str[i] == '=' && str[i-1] == '+'))
        i--;
    s[0] = s_cpy(str,0,i);
    if(s[0] != NULL && s[0][0] != '\0'){
    s[1] = s_cpy(str,i,f+1);
    s[2] = s_cpy(str,f+1,len);
    s[3] = NULL;
    }
    else{
        free_split(s);
        return NULL;
    }
    return s;
}
int valid_input(char *str,int pos){
    int i =0;
    if(!str)
        return 1;
    if(pos == 0 && str && str[0] != '\0'){
        while(str[i]){
        if(i == 0 && str[i] != '_'){
            if(ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) != 1)
                return 1;
        }
        else{
            if(str && str[i] != '_' && ft_isalnum(str[i]) == 0)
                return 1;
        }
        i++;
        }
    }
    else if(pos == 1 && str && str[0] != '\0'){
        if(str[i] == '+' && str[i+1] == '=')
            return 0;
        else if(str[i] != '=')
            return 1;
    }
    return 0;
}

void new_env(char **s, int *err, int type)
{
	s_env *node;

	node = malloc(sizeof(s_env));
	if (!node)
	{
		*err = 1;
		free_split(s);
		return ;
	}
	node->name = s[0];
	node->value = s[2];
	node->next = NULL;
	free(s[1]);
	free(s[3]);
	free(s);
	if (type == 0)
		add_list_back(&shell_data.env_list, node);
	else
		shell_data.env_list = node;
}

void edit_env_node(s_env *node, char **s, int *err)
{
	char *new_value;

	if (s[1][0] == '+')
	{
		new_value = join_and_free(node->value, s[2]);
		if (!new_value)
		{
			*err = 1;
			free_split(s);
			return ;
		}
		node->value = new_value;
	}
	else
	{
		free(node->value);
		node->value = s[2];
	}
	free(s[0]);
	free(s[1]);
	free(s[3]);
	free(s);
}

static void helper_function(char **s, int *err, char *cmd)
{
	s_env *node;

	if (!s || valid_input(s[0], 0) || valid_input(s[1], 1))
	{
		if (cmd)
			export_errors(cmd, 0);
		free_split(s);
		*err = 1;
		return ;
	}
	if (shell_data.env_list)
	{
		node = get_env_str(s[0], shell_data.env_list);
		if (node)
			edit_env_node(node, s, err);
		else
			new_env(s, err, 0);
	}
	else
		new_env(s, err, 1);
}

static void print_env(s_env *list)
{
	while (list)
	{
		ft_putstr_fd("export -x ", 1);
		ft_putstr_fd(list->name, 1);
		if (list->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(list->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		list = list->next;
	}
}

int ft_export(char **cmd)
{
	int i;
	int err;

	if (!cmd || !cmd[1])
	{
		print_env(shell_data.env_list);
		return (0);
	}
	i = 1;
	err = 0;
	while (cmd[i])
	{
		helper_function(ex_split(cmd[i]), &err, cmd[i]);
		i++;
	}
	return (err);
}
