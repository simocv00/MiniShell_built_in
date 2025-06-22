#ifndef MINISHELL_H  
# define MINISHELL_H

typedef struct t_env{
    char *name;
    char *value;
    struct t_env *next;
}s_env;
typedef struct s_shell{
    s_env *env_list;
    char **env;
    char **args;
    char *cmd;
    char *shellname;
    int exit_status;
}s_shell;

extern s_shell shell_data;

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
int ft_echo(char **str,int fd);
int ft_env(s_env *list,char **cmd);
int ft_cd(char **str);
int ft_pwd(char *str);
int ft_unset(char **str);
int ft_export(char **cmd);
int ft_exit(char **cmd,char *str);
s_env *create_new_node(char **env);
s_env *get_env_str(char *str,s_env *env);
s_env *create_env_node(char **str);
size_t	ft_strlen(const char *s);
void add_list_back(s_env **head,s_env *last);
void free_cmd(char **cmd);
int ft_putstr_fd(char *str,int fd);
int ft_strcmp(char *s1, char *s2);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int count_args(char **arg);

void	ft_putnbr_fd(int n, int fd);
//char **mini_split(char *str,char c);
#endif 
//char *prompt = "\033[01;32mfang_yuan@Host\033[00m:\033[01;34m~/Desktop/minishell/built-in\033[00m$ ";