#include "../../includes/minishell.h"

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
        if (!ft_iswhitespace(s[i]))
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

int check_syntax(char *s)
{
    int i;
    int quote;

    i = 0;
    while (s[i])
    {
        if (s[i] == ';')
        {
            perror_syntax_error(s[i]);
            s[i] = 0;
            return (1);
        }
        if (is_redirect(s[i]))
        {
            if (!check_redirect_type(get_redirect_type(&s[i])))
            {
                perror_syntax_error(s[i]);
                s[i] = 0;
                return (1);
            }
        }
        if ((quote = isquote(s[i])))
        {
            if(check_quotes(&s[i]))
            {
                perror_syntax_error(s[i]);
                s[i] = 0;
                return (1);
            }
            i = go_through_quote(s, i, &quote);
        }
        if (s[i] == '|')
        {
            if (!check_between_the_pipes(&s[i]))
            {
                perror_syntax_error(s[i]);
                s[i] = 0;
                return (1);
            }
        }
        i++;
    }
    return (0);
} 
