#include "minishell.h"

void free_everything(char **cmd,char *str)
{
		free_cmd(cmd);
		free(str);
	while (shell_data.env_list){
		s_env *t = shell_data.env_list;
		shell_data.env_list = (shell_data.env_list)->next;
		free(t->name);
		free(t->value);
		free(t);
		t = NULL;
	}
}
int exit_errors_messages(char *value,int type){
    ft_putstr_fd(shell_data.shellname,2);
    if(type==0){
        ft_putstr_fd(": exit: ",2);
        ft_putstr_fd(value,2);
        ft_putstr_fd(": numeric argument required\n",2);
        return (2);
    }
    else if(type==1){
        ft_putstr_fd(": exit: ",2);
        ft_putstr_fd("too many arguments\n",2);
        return (1);
    }
return 2;
}

long long	ft_atoll_edited(const char *str,int *flag)
{
	int	i;
	unsigned long long	n;
	int	s;
    long long	temp;

	i = 0;
	n = 0;
	s = 1;
	if (!str[i])
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
            if (n > 9223372036854775807)
            {
                (*flag)++;
               return 0;
            }
            
		i++;
	}
    temp = n;
	return (temp * s);
}
int check_char(char *num){
    int i;
    i = 0;
    if(!num)
        return -1;
    while (num[i])
    {
        if(!ft_isdigit(num[i]))
            return 1;
        i++;
    }
    return 0;
}
int check_exit_args(char **cmd,int *track){
    if(!cmd || !cmd[1]){
    (*track)++;
        return (0);
    }
    int len = ft_strlen(cmd[1]);
    long long num = 0;
    int flag = 0;
    if(len > 19 || check_char(cmd[1])){
        (*track)++;
        return(exit_errors_messages(cmd[1],0));
    }
    num = ft_atoll_edited(cmd[1],&flag);
    int count = count_args(cmd);
    if(count > 2 && flag == 0){
        *track = -1;
        return(exit_errors_messages(NULL,1));
    }
    (*track)++;
    if(num < 0)
        return 255;
return (num%256);
}
int ft_exit(char **cmd,char *str){
    ft_putstr_fd("exit\n",1);
    int flag = 0;
    int status = check_exit_args(cmd,&flag);
    if(flag == 1){
        free_everything(cmd,str);
        exit(status);
    }
    else if(flag == -1)
        return status;
    return 0;
}