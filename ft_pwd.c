#include "minishell.h"

int ft_pwd(char *str){
    if(str){
        ft_putstr_fd("To Many Argument\n",2);
        return 1;
    }
    char *cwd;
    cwd = NULL;
    s_env *PWD;
    PWD = NULL;
    cwd = getcwd(NULL,0);
    if(cwd != NULL){
        ft_putstr_fd(cwd,1);
        free(cwd);
        write(1,"\n",1);
        return(0);
    }
    else{
    PWD = get_env_str("PWD",shell_data.env_list);
    if(PWD){
        ft_putstr_fd(PWD->value,1);
        write(1,"\n",1);
        return 0;
    }
    ft_putstr_fd(strerror(errno),2);
    write(2,"\n",1);
}
    return(1);
}