#include <stdio.h>
#include "../../includes/minishell.h"

int ft_isanywordchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

int	find_index_of_char(char *s, char c)
{
	char *char_pos_ptr;

	char_pos_ptr = ft_strchr(s, c);
	if (char_pos_ptr)
		return (char_pos_ptr - s);
	else
		return (-1);
}

int	is_valid_declaration_name(char *arg)
{
	int i;
	char **name_value_pair;

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
	int declaration_switch;

	i = 0;
	declaration_switch = 1;
	while (args[i] && declaration_switch)
	{
		if (find_index_of_char(args[i], '=') < 1)
			declaration_switch = 0;
		if (!is_valid_declaration_name(args[i]))
			declaration_switch = 0;
		i++;
	}
	return (declaration_switch);
}

char	**delete_block(char **command_blocks, int index_block_to_del)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_str_list(strlen_list(command_blocks));
	if (!tmp)
		return (NULL);
	while (command_blocks[i])
	{
		if (i == index_block_to_del)
			j--;
		else
		{
			tmp[j] = ft_strdup(command_blocks[i]);
			if (!tmp[j])
				return (free_list_and_return_null(tmp, j));
		}
		j++;
		i++;
	}
	return (tmp);
}

char **remove_valid_declaration(char **command_blocks)
{
	char **cleaned_command_blocks;
	char **tmp;
	int i;
	int j;
	
	i = 0;
	j = 0;
	cleaned_command_blocks = str_list_dup(command_blocks);
	while (command_blocks[i])
	{
		if ((find_index_of_char(command_blocks[i], '=') >= 1)
				&& is_valid_declaration_name(command_blocks[i]))
		{
			tmp = str_list_dup(cleaned_command_blocks);
			free_str_list(cleaned_command_blocks, strlen_list(cleaned_command_blocks));
			cleaned_command_blocks = delete_block(tmp, i - j); 
			free_str_list(tmp, strlen_list(tmp));
			if (!cleaned_command_blocks)
				return (NULL);
			j++;
		}
		else
			return (cleaned_command_blocks);
		i++;
	}
	return (cleaned_command_blocks);
}

int main(int argc, char **argv)
{
	char **command_blocks;
	int declaration_switch;
	
	if (argc <= 1)
		return (1);
	declaration_switch = parse_var_declaration(argv + 1);
	printf("Parsing result: %d\n", declaration_switch);
	command_blocks = NULL;
	if (declaration_switch == 0)
	{
		command_blocks = remove_valid_declaration(argv + 1);
		print_str_list(command_blocks, NULL);
		free_str_list(command_blocks, strlen_list(command_blocks));
	}
	else
		printf("ALTER ENV HERE\n");
	return (0);
}
