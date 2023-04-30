#include "minishell.h"

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
	return (0);
}