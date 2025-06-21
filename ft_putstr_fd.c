#include "minishell.h"

int ft_putstr_fd(char *str,int fd){
    int i ;
    i = 0;
    if(!str)
        return 1;
    while (str[i])
    {
        if(write(fd,&str[i],1) < 0)
            return (1);
        i++;
    }
     return (0);
}