#include "minishell.h"

int is_echo_n_option(const char *arg)
{
    int i = 1;
    if (arg[0] != '-' || arg[1] == '\0')
        return (0); 
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0); 
        i++;
    }

    return (1); 
}
int testing_exit_status(char *str){
    if((str )&&(str[0] == '$' && str[1] == '?')){
            ft_putnbr_fd(shell_data.exit_status,1);
            return 0;
    }
    return 1;
}
int ft_echo(char **str,int fd)
{
    int i = 0;
    int print_newline = 1; 
    str++;
    while (str[i] && is_echo_n_option(str[i]))
    {
        print_newline = 0;
        i++;
    }
    int j = i;
    while (str[j])
    {
        if(testing_exit_status(str[j]))
            if(ft_putstr_fd((str[j]), fd))
            return 1;
        if (str[j + 1])
            write(fd, " ", 1);
        j++;
    }

    if (print_newline)
        write(fd, "\n", 1);
     return (0);
}