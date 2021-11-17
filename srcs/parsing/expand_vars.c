 #include "../../includes/minishell.h"
 #include <stdio.h> 
 

int isquote(char c);

char    *get_var_name(char *s, int *i)
{
    char *var_name;

    while (!ft_iswhitespace(s[*i]) && s[*i] && s[*i] != '$' && !isquote(s[*i]))
        (*i)++;
    var_name = ft_calloc(*i + 1, sizeof(char));
    if (!var_name)
        return (0);
    ft_strlcpy(var_name, s, *i + 1);
    return (var_name);
}

char    *get_var_value(char *var_name, int *offset, int status)
{
    char *var_value;
    char *tmp;

    tmp = ft_strjoin("x", var_name);
    if (ft_getenv(tmp) != NULL)
    {
        var_value = ft_strdup(ft_getenv(tmp)); 
        *offset = ft_strlen(var_value) - ft_strlen(var_name);
    }
    else if (!ft_strncmp(var_name, "?", 2))
    {
        var_value = ft_itoa(status);
        *offset = ft_strlen(var_value) - ft_strlen(var_name);
    }
    else
    {
        var_value = NULL;
        *offset = ft_strlen(var_name) * -1;
    }
    free(tmp);
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
        newstr[d] = '\0';
    }
    else
    {
        newstr = ft_calloc(ft_strlen(s) + offset + 1, sizeof(char));
        while (d <= offset + ft_strlen(var_name))
        {
            newstr[d] = var_value[d];
            d++;
        }
        ft_strlcpy(&newstr[ft_strlen(var_value)], &s[i], ft_strlen(s) - i + 1);
    }
    return (newstr);
}

char *expand_vars(char *s, int status)
{
    int i;
    char *var_name;
    char *var_value;
    int offset;
    char *newstr;

    i = 0;
    var_name = get_var_name(s, &i);
    var_value = get_var_value(var_name, &offset, status);
    newstr = expand_and_replace(s, var_value, var_name, offset, i); 
    if (var_value)
        free(var_value);
    free(var_name);
    return (newstr);
}

char *find_dollars(char *s, int status)
{
    int i;
    char *newend;
    char *news;
    int d;

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
            newend = expand_vars(&s[i + 1], status);
            s[i] = 0;
            news = ft_strjoin(s, newend);
            free(newend);
            d = ft_strlen(s);
            free(s);
            s = news;
            if (i >= d)
                return s;
           // find_dollars(s, status);
        }
    }
    return (s);
}
