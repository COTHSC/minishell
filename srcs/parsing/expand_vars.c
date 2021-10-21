 #include "../../libs/libft/libft.h"
 #include "../../libs/libft+/libftp.h"
 #include <stdio.h> 
 

int isquote(char c);

char    *get_var_name(char *s, int *i)
{
    char *var_name;

    while (!ft_iswhitespace(s[*i]) && s[*i] && s[*i] != '$')
        (*i)++;
    var_name = ft_calloc(*i, sizeof(char));
    if (!var_name)
        return (0);
    ft_strlcpy(var_name, s, *i + 1);
    return (var_name);
}

char    *get_var_value(char *var_name, int *i, int *offset)
{
    char *var_value;
    
    if (getenv(var_name) != getenv("notreal"))
    {
        var_value = ft_strdup(getenv(var_name)); 
        *offset = ft_strlen(var_value) - *i;
    }
    else
    {
        var_value = NULL;
        *offset = *i * -1;
    }
    return (var_value);
}

char     *expand_and_replace(char *s, char *var_value, char *var_name, int offset, int i)
{
    unsigned long int d;
    char *newstr;

    d = 0;
    if (offset < 0)
    {
        newstr = ft_strdup(&s[-offset]);
        while (d < ft_strlen(var_name) + offset)
        {
            newstr[d] = var_value[d];
            d++;
        }
    }
    else
    {
        newstr = ft_calloc(ft_strlen(s) + offset, sizeof(char));
        while (d <= offset + ft_strlen(s))
        {
            newstr[d] = var_value[d];
            d++;
        }
        ft_strlcpy(&newstr[ft_strlen(var_value)], &s[i], ft_strlen(s) - i + 1);
    }
    return (newstr);
}

char *expand_vars(char *s)
{
    int i;
    char *var_name;
    char *var_value;
    int offset;
    char *newstr;

    i = 0;
    var_name = get_var_name(s, &i);
    var_value = get_var_value(s, &i, &offset);
    newstr = expand_and_replace(s, var_value, var_name, offset, i); 
    if (var_value)
        free(var_value);
    free(var_name);
    return (newstr);
}

char *find_dollars(char *s)
{
    int i;
    char *newend;
    char *news;

    i = -1;
    while (s[++i])
    {
        if (isquote(s[i]) == 1)
        {
            i++;
            while (isquote(s[i]) != 1)
                i++;
        }
        if (s[i] == '$')
        {
            newend = expand_vars(&s[i + 1]);
            s[i] = 0;
            news = ft_strjoin(s, newend);
            free(newend);
            free(s);
            s = news;
        }
    }
    return (s);
}
/*
int main(int argc, char **argv, char **env)
{
    char *news;
    news = find_dollars(ft_strdup(argv[1]));
    printf("this is the $TEST new s: %s\n", news);
    return (0);
}*/
