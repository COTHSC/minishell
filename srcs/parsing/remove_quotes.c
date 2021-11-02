#include "../../libs/libft/libft.h"
#include "../../libs/libft+/libftp.h"
#include <stdio.h>

int isquote(char c);

char *remove_quote(char *str, int i)
{
    char *ret;

    ret = ft_calloc(ft_strlen(str), sizeof(char));
    if (!ret)
        return (NULL);
    ft_strlcpy(ret, str, i + 1);
    ft_strlcpy(&ret[i], &str[i + 1], ft_strlen(&str[i]) + 1);
    //free(str);
    return (ret);
}
char *remove_quotes(char *s)
{
    int i;
    int quotes;

    i = 0;
    quotes = 0;
    while (s[i])
    {
        if (isquote(s[i]))
        {
            quotes = isquote(s[i]);
            s = remove_quote(s, i);
            while (isquote(s[i]) != quotes)
                i++;
            s = remove_quote(s, i);
            i--;
        }
        i++;
    }
    return (s);
}
/*
int main(int argc, char **argv)
{
    char *str;

    str = "\'this is a se\"\"ntence with a quote in i\'t";
    printf("%s\n", str);
    str = remove_quotes(str);
    printf("%s\n", str);
    return 0;
}*/
