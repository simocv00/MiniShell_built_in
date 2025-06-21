#include "minishell.h"
void env_print(s_env *env){
    if(!env)
        return;
    while (env)
    {
        ft_putstr_fd(env->name,1);
        write(1,"=",1);
        ft_putstr_fd(env->value,1);
        write(1,"\n",1);
        env = env->next;
    }
    
}
int check_args(char **args){
    if (!args){
    ft_putstr_fd("env: ",2);
    ft_putstr_fd(args[1],2);
    ft_putstr_fd(": No such file or directory\n",2);
    return (1);}
    return 0;
}
int ft_env(s_env *list,char **cmd){
    if(check_args(cmd) || !list)
        return (1);
    env_print(shell_data.env_list);
     return (0);
}