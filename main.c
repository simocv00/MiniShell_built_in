#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <signal.h>
s_shell shell_data = {0};
int		ft_count_words(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (j == 0 && *str != c)
		{
			j = 1;
			i++;
		}
		else if (j == 1 && *str == c)
			j = 0;
		str++;
	}
	return (i);
}
char *create_string(char *str,char *orignal,char c){
	int i = 0;
	while(orignal[i] != c && orignal[i]){
		str[i] = orignal[i];
		i++;
	}	
	str[i] = '\0';
	return str;
}
char *cut_string(char **str,char c){
	int i = 0;
	while((*str)[i] != c && (*str)[i])
		i++;
	char *send = malloc(i+1);
	send = create_string(send,*str,c);
	while (**str && **str != c)
        (*str)++;
    if ((**str)== c){
        (*str)++;
    }
	return(send);
	
}
char **mini_split(char *str,char c){
	int i = 0;
	int w = ft_count_words(str,c);
	char **words = malloc((sizeof(char *)) * (w + 1));
	while(i < w){
		words[i] = cut_string(&str,c);
		i++;
	}
	words[i] = NULL;
	return words;
}
char *str_join(char *s1,char *s2){
	int len = ft_strlen(s1)+ ft_strlen(s2) + 1;
	char *joined = malloc(len);
	int i = 0;
	int j = 0;
	while(s1[i]){
		joined[i] = s1[i];
		i++;
	}
	while(s2[j]){
		joined[i] = s2[j];
		i++;
		j++;
	}
	if(joined[i] != '\0')
		joined[i] = '\0';
	return joined;
}
void executin(char *path,char **arg,char **env){
	char *cmd = str_join(path,arg[0]);
	int pid = fork();
	if(pid == 0){
		if(execve(cmd,arg,env)){
			perror("execve: ");
			exit(EXIT_FAILURE);
		}}
		else{
		pid_t waited_pid = waitpid(pid,NULL,0);

        if (waited_pid == -1) {
            perror("waitpid");
			free(cmd);
            exit(EXIT_FAILURE);
        }
		}
}
int built_in(char *str,char **cmd_splited){
	if(ft_strcmp("echo",cmd_splited[0]) == 0)
                return (ft_echo(cmd_splited,1));
            else if(ft_strcmp("env",cmd_splited[0]) == 0)
                return (ft_env((shell_data.env_list),cmd_splited));
            else if(ft_strcmp("cd",cmd_splited[0]) == 0)
                return (ft_cd(cmd_splited));
            else if(ft_strcmp("pwd",cmd_splited[0]) == 0)
               return (ft_pwd(cmd_splited[1]));
			else if (ft_strcmp("export",cmd_splited[0]) == 0)
				return (ft_export(cmd_splited));
			else if(ft_strcmp("exit",cmd_splited[0]) == 0)
				return (ft_exit(cmd_splited,str));
	return (-1);
}
int main(int ac , char **av, char **env){
    char *str = NULL;
     (void)ac;
	shell_data.env = env;
	shell_data.env_list = create_env_node(env);
	shell_data.shellname = av[0];
    while (1)
    {
        str = readline("minishell-> ");
        if(str[0] != '\0' && str){
            
            char **cmd = mini_split(str,' ');
			shell_data.exit_status =built_in(str,cmd);
            if(shell_data.exit_status == -1)
            {
				shell_data.exit_status = 0;
				if(cmd[0][0] == '.')
                executin(cmd[0],cmd,env);
				else
				executin("/usr/bin/",cmd,env);
			}
			free_cmd(cmd);
        }
		if(str)
		free(str);
    }
    
}