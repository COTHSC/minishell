#include <stdio.h>
#include "../../includes/minishell.h"

int ft_isanywordchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

int	find_equal_index(char *s)
{
	char *equal_pos_ptr;

	equal_pos_ptr = ft_strchr(s, '=');
	if (equal_pos_ptr)
		return (equal_pos_ptr - s);
	else
		return (-1);
}

int	is_valid_declaration_name(char *arg)
{
	int i;
	char **name_value_pair;
	int	return_value;

	name_value_pair = split_to_name_value_pair(arg);
	i = 0;
	if (!name_value_pair[0][0])
		return (0);
	while (name_value_pair[0][i])
	{
		if (!ft_isanywordchar(name_value_pair[0][i]))
		{
			free_str_list(name_value_pair, strlen_list(name_value_pair));	
			return (0);
		}
		i++;
	}
	free_str_list(name_value_pair, strlen_list(name_value_pair));	
	return (1);
}

int	parse_var_declaration(char **args)
{
	int i;
	int switch_off_declaration;

	i = 0;
	switch_off_declaration = 0;
	while (args[i])
	{
		printf("Arg[%d]: %s\n", i, args[i]);
		i++;
	}
	i = 0;
	while (args[i] && !switch_off_declaration)
	{
		if (find_equal_index(args[i]) < 1)
			switch_off_declaration = 1;
		i++;
	}
	printf("1st switch: %d\n", switch_off_declaration);
	i = 0;
	while (args[i] && !switch_off_declaration) 
	{
		if (!is_valid_declaration_name(args[i]))
			switch_off_declaration = 1;
		i++;
	}
	printf("2nd switch: %d\n", switch_off_declaration);
	return (switch_off_declaration);
}

//As soon as there are invalid declarations or args without "=" sign
//Declaration is not taken into account
//Other valid command may not be executed as declaration will be interpreted
//As a command not found or file not found

int main (int argc, char **argv)
{
	if (argc > 1)
		printf("Parsing result: %d\n", parse_var_declaration(argv + 1));
}
