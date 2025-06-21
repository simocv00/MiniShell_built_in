#include "minishell.h"
#include<errno.h>
#include "minishell.h"
int error_messages(int type,char *message,char *file){
     ft_putstr_fd(shell_data.shellname,2);
     ft_putstr_fd(": cd: ",2);
    if(type == 1)
        ft_putstr_fd(message,2);
    else if(type == 2){
        ft_putstr_fd(file,2);
        write(2,": ",2);
        ft_putstr_fd(message,2);
    }
    write(2,"\n",1);
    return(1);
}
int helper(s_env *new,char *name){
    if(!name || !new)
        return 1;
    int len = ft_strlen(name) + 1;
    int i = 0;
    char *name_allocted = malloc(len);
        if(!name_allocted)
        return 1;
    while(name[i]){
        name_allocted[i] = name[i];
        i++;
    }
    name_allocted[i] = '\0';
    new->name = name_allocted;
return (0);
}
int update_pwd(void){
	char *new_pwd = getcwd(NULL,0);
        if(!new_pwd)
            return(error_messages(1,strerror(errno),NULL));
    s_env *env_pwd = get_env_str("PWD",shell_data.env_list);
        if(env_pwd){
                free(env_pwd->value);
                env_pwd->value = new_pwd;
                return(0);
            }
         else{
            s_env *new = malloc(sizeof(s_env));
                if(!new){
                    free(new_pwd);
                    return 1;}
            new->name = NULL;
            new->value = NULL;
            new->next = NULL;
            if(helper(new,"PWD") == 0)
                new->value = new_pwd;  
            else{
                free(new_pwd);
                free(new);
                return 1;
            }
            add_list_back(&(shell_data.env_list),new);
            return(0);
        }
    return (1);
}
void update_oldpwd(char *new_old){
    if(!new_old)
        return;
    s_env *env_opwd = get_env_str("OLDPWD",shell_data.env_list);
        if(env_opwd){
            free(env_opwd->value);
            env_opwd->value = new_old;
            return;
        }
        else{
            s_env *new = malloc(sizeof(s_env));
                if(!new)
                    return;
            new->name = NULL;
            new->value = NULL;
            new->next = NULL;
            if(helper(new,"OLDPWD") == 0){
                new->value = new_old;
            }
            else{
                free(new);
                return;
            }
            add_list_back(&(shell_data.env_list),new);
            return;
        }
        
}

int only_cd(char **cmd,int *ex){
    if(cmd[1] != NULL){
        *ex = -1;
        return(2);
    }
    s_env *home = get_env_str("HOME",shell_data.env_list);
    int status = 0;
    if(!home){
        *ex = 1;
        return (error_messages(1,"HOME not set",NULL));
    }
    status = chdir(home->value);
    if(status == -1){
        *ex = 1;
        return(error_messages(2,strerror(errno),home->value));
    }
    *ex = 0;
return 0;
}
int minus_option(char **cmd, int *ex){
    if(ft_strcmp("-",cmd[1]) || cmd[2] != NULL){
        *ex = -1;
        return (2);
    }
    s_env *oldpwd = get_env_str("OLDPWD",shell_data.env_list);
    int status = 0;
    if(!oldpwd){
        *ex = 1;
        return (error_messages(1,"OLDPWD not set",NULL));
    }
    status = chdir(oldpwd->value);
    if(status == -1){
        *ex = 1;
        return(error_messages(2,strerror(errno),oldpwd->value));
    }
*ex = 0;
return 0;
}

int dots_option(char ** cmd,int *ex){
    if (cmd[1] && ft_strcmp(cmd[1], ".") != 0 )
    return 2;
    char *pwd_check = getcwd(NULL,0);
    if(!pwd_check ){
        ft_putstr_fd("cd: error retrieving current directory:"
            "getcwd: cannot access parent directories: No such file or directory\n",2);
        *ex = 1;
        return 1;
    }
    else{
       int err = chdir(cmd[1]);
       free(pwd_check);
        if(err == -1){
            *ex = 1;
            return (error_messages(2,strerror(errno),cmd[1]));
        }
    }
    *ex = 0;
    return 0;
}

int special_cases(char **str,char *cwd){
    int done = -1;
    if(only_cd(str,&done) == 1 && done != -1)
        return (1);
    else if(done == -1 && (minus_option(str,&done) == 1))
         return (1);
    else if (done == -1 && dots_option(str,&done) == 1)
         return (1);
    if(done == 0){
    if(!update_pwd())
            update_oldpwd(cwd);
    else
    {
        free(cwd);
    }
        return (0);}
    else if(done == 1)
        return 1;
    
    return (2);
}
int tow_dots(char *str){
    char *pwd_check;
    if(ft_strcmp(str, "..") == 0)
    {
        pwd_check = getcwd(NULL,0);
        if(!pwd_check ){
        ft_putstr_fd("cd: error retrieving current directory:"
            "getcwd: cannot access parent directories: No such file or directory\n",2);
        return 1; 
    }
        free(pwd_check);
    }
return 0;
}
int change_dir(char **str,char *cwd){
     int er = 0;
     er = chdir(str[1]);       
        if(er == -1)
        {
            free(cwd);
            return (error_messages(2,strerror(errno),str[1]));
        }
        if(tow_dots(str[1]))
            return 1;
        if(!update_pwd())
         update_oldpwd(cwd);
        else
            free(cwd);
    return 0;
}
int ft_cd(char **str){
    int status  = -1;
    int arg = count_args(str);
    char *cwd = getcwd(NULL,0);
    if(arg  == 0 )
        return 1;
    if(arg > 2){
        free(cwd);
        return (error_messages(1," too many arguments",NULL));
    }
        status = special_cases(str,cwd);
       if(status == 1){
        free(cwd);
            return 1;
        }
        else if(status == 0)
            return 0;
       if(change_dir(str,cwd))
            return 1;
    return 0;
}
