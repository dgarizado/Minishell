#include "minishell.h"

static int	ft_shift(char *str, int *index)
{
	int i;

	i = *index;
	while (str[i] != '\0')
	{
		str[i] = str[i  + 1];
		i++;
	}
	return (0);
}
static int	ft_remove(char *str, int *index, char c)
{
	ft_shift(str, index);
	while (str[*index] != '\0')
	{
		if (str[*index] == c)
		{
			ft_shift(str, index);
			break ;
		}
		(*index)++;
	}
	return (0);
}

int ft_unquote(char *input)
{
	int	i;

	i = 0;
	while(input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			ft_remove(input, &i, input[i]);
		}
		i++;
	}
	return (0);
}

static int	ft_is_closed(char *str, int *index, char c)
{
	(*index)++;
	while (str[*index] != '\0')
	{
		if (str[*index] == c)
			return (0);
		(*index)++;
	}
	return (1);
}

int	ft_lexic(char *input)
{
	int	i;

	i = 0;
	while(input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"' )
		{
			if (ft_is_closed(input, &i, input[i]) == 1)
				printf("\nunclosed quotes!\n");
		}
		i++;
	}
	ft_unquote(input);
	printf("\nmodified: %s\n", input);
	return (0);
}