#include "minishell.h"
// static int ft_strlen(char const *str){
//     int i = 0;
//         while(str[i])
//             i++;
//     return i;
// }
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*head;
// 	char	*joined;
// 	int		len1;
// 	int		len2;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	joined = malloc(len1 + len2 + 1);
// 	if (!joined)
// 		return (NULL);
// 	head = joined;
// 	while (*s1 || *s2)
// 	{
// 		if (*s1)
// 			*joined++ = *s1++;
// 		else
// 			*joined++ = *s2++;
// 	}
// 	*joined = '\0';
// 	return (head);
// }
s_env *get_env_str(char *str,s_env *env){
    if(!env || !str)
        return (NULL);
    while(env){
        if(ft_strcmp(env->name,str) == 0){
                return(env);
        }
        env = env->next;
    }
    return NULL;
}