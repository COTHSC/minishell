# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../libs/libft/libft.h"

int     is_redirect(char c)
{
    if (c == '>')
        return (1);
    else if (c == '<')
        return (3);
    return (0);
}

int is_in_quotes(char *str)
{
    if (str[0] == '\'' || str[ft_strlen(str) - 2] == '\'')
        return (1);
    if (str[0] == '"' || str[ft_strlen(str) - 2] == '"')
        return (2);
    return (0);
}

int check_redirect_type(int redirect_type)
{
    if (redirect_type != 1 && redirect_type != 2 && redirect_type != 3 && redirect_type != 6)
        return (0);
    return (1);
}

int get_redirect_type(char *s)
{
    int i;
    int redirect_type;

    i = 0;
    redirect_type = 0;
    while (s[i] && is_redirect(s[i]))
    {
        redirect_type += is_redirect(s[i]);
        i++;
    }
    return (redirect_type);
}

int isquote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	else 
		return (0);
}

int go_through_quote(char const *s, int lead, int *quote)
{
	while (s[lead] && *quote)
	{
		lead++;
		if (isquote(s[lead]) == *quote)
			*quote = 0;
	}
	return (lead);
}

int check_quotes(char *s)
{
    int quote;
    int i;

    i = 0;
    quote = isquote(s[0]);
    i++;
    while (s[i] && quote)
    {
        if (isquote(s[i]) == quote)
        {
            quote = 0;
            return (0);
        }
        i++;
    }
    return 1;
}

int     check_between_the_pipes(char *s)
{
    int i;

    i = 1;
    while (s[i])
    {
        //replace with iswhitespace
        if (s[i] != ' ')
        {
            if (s[i] == '|')
                return (0);
            else 
                return (1);
        }
        i++;
    }
    return (0);
}

char    *check_syntax(char *s)
{
    int i;
    int quote;

    i = 0;
    while (s[i])
    {
        
        if (s[i] == ';')
        {
            printf("thats an error chief '%c' token\n", s[i]);
            s[i] = 0;
            return (s);
        }
        if (is_redirect(s[i]))
        {
            if (!check_redirect_type(get_redirect_type(&s[i])))
            {
                printf("thats an error chief '%c' token\n", s[i]);
                s[i] = 0;
                return (s);
            }
        }
        if ((quote = isquote(s[i])))
        {
            if(check_quotes(&s[i]))
            {
                printf("thats an error chief '%c' token\n", s[i]);
                s[i] = 0;
                return (s);
            }
            i = go_through_quote(s, i, &quote);
        }
        if (s[i] == '|')
        {
            if (!check_between_the_pipes(&s[i]))
            {
                printf("thats an error chief '%c' token\n", s[i]);
                s[i] = 0;
                return (s);
            }
        }
        i++;
    }
    return (s);
} 
/*    
int main(int argc, char **argv)
{
    char *line_to_check;

    line_to_check = argv[1];
    check_syntax(line_to_check);
    printf("%s\n", line_to_check);
    return (0);
}
*/
