/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:03:00 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/01 19:09:50 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

/**
 * @brief Trims the string that contains $ARG
 * in order to search it in the ENV list. 
 * @param i 
 * @param j 
 * @param lenvar 
 * @return char* 
 */
static char	*ft_getenv(int i, int j, int lenvar)
{
	char	*var;
	char	*aux; //leak?
	int		n;

	aux = NULL;
	var = ft_substr(g_data.token1[i], j + 1, lenvar - 1);
	n = 0;
	if (g_data.token1[i][j + 1] == '?')
		return (ft_itoa(g_data.child_status));
	while (g_data.env[n])
	{
		// if (ft_strncmp(g_data.env[n], var, ft_str_index_chr(g_data.env[n], '=') - 1) == 0)
		if (ft_strncmp(g_data.env[n], var, ft_strlen(var)) == 0 && g_data.env[n][ft_strlen(var)] == '=')
			break ;
		n++;
	}
	if (g_data.env[n])///HERE MAY to make $?
		//str_error(var,  "not found");
	//else
		aux = &g_data.env[n][ft_strlen(var) + 1];
	if (!aux)
	{
		aux = ft_calloc(1, 1);
	}
	free (var);
	var = NULL;
	return (aux);
}

/**
 * @brief Calculates the len of the $VAR 
 * Is used for the expantion.
 * if there is a $ in the string, it wont count it
 *
 * @param i 
 * @param j 
 * @return int 
 */
static int	aux(int i, int j)
{
	int	k;

	k = 0;
	//printf("TOKEN ENTRA %s\n", g_data.token1[i]);
	//while (g_data.token1[i][j] != ' ' && g_data.token1[i][j] \
	//&& g_data.token1[i][j] != '\"' && g_data.token1[i][j] != '\'') //HARDCODED NEED TO BE FIXED
	if (g_data.token1[i][j + 1] == '?')
		return (2);///POSIBLE 1<->2
	while (ft_isalnum((char)g_data.token1[i][j]) == 1 || g_data.token1[i][j] == '$')
	{
		//printf("\n char -> %c \n", g_data.token1[i][j]);
		//getchar();
		j++;
		k++;
		if (g_data.token1[i][j] == '$')
			break ;
	}
	//printf("-- LEN_VAR %d\n", k);
	return (k);
}

/**
 * @brief This function finds the call of $ 
 * and expands it into the proper string. 
 * @param i 
 * @param j 
 * @return int 
 *///CHECK POINT
int	ft_expand(int i, int j)
{
	int		lenvar;
	char	*str1;
	char	*str2;
	char	*expand;

	str1 = ft_substr(g_data.token1[i], 0, j);
	lenvar = aux(i, j);
	expand = ft_getenv(i, j, lenvar);
	str2 = ft_strjoin(str1, expand);
	expand = NULL;
	free(expand);
	str1 = NULL;
	free(str1);
	str1 = ft_substr(g_data.token1[i], j + lenvar, ft_strlen(g_data.token1[i]));
	g_data.token1[i] = NULL;
	free (g_data.token1[i]);
	g_data.token1[i] = ft_strjoin(str2, str1);
	str1 = NULL;
	free(str1);
	str2 = NULL;
	free(str2);
	return (0);
}
void ft_checkquotes(int i, int *j, int *flag_quote, int *flag_expand)
{
	if (g_data.token1[i][*j] == '\"' && *flag_quote == 0)
	{
		//(*j)++;
		*flag_quote = 1;
	}
	else if (g_data.token1[i][*j] == '\"' && *flag_quote == 1)
	{
		//(*j)++;
		*flag_quote = 0;
	}
	
	else if ( g_data.token1[i][*j] == '\'' && *flag_quote == 0)
	{
		//(*j)++;
		*flag_expand = 0;
	}
	if (*flag_quote == 1)
		*flag_expand = 1;
}

int ft_de_oca_a_oca(int i, int j, int *flag_quote, int *flag_expand)
{
	j++;
	while (g_data.token1[i][j] != '\'')
		j++;
	//j++;
	*flag_quote = 0;
	*flag_expand = 1;
	return (j);
}
/**
 * @brief This function checks if there is $  //flag_quote = 1
 * in each token. Then expand it if it is	  //flag_expand = 1
 * not enclosed by single quotes.
 * 
 * @return int 
 */
int	ft_check_expand(void)
{
	int	i;
	int	j;
	int flag_expand;
	int flag_quote;

	i = 0;
	//write(1, "EXPAND\n", 7);
	//ft_printf_arr(g_data.token1);
	while (g_data.token1[i] != NULL)
	{
		j = 0;
		flag_quote = 0;
		flag_expand = 1;
		while (g_data.token1[i][j] != '\0')
		{	
			//printf("	INICIO INDEX -> %d\n", j);
			ft_checkquotes(i, &j, &flag_quote, &flag_expand);
			//printf("-AFTER CHECH QUOTES -> %s\n", g_data.token1[i]);
			//printf("-AFTER CHECH QUOTES indice-> %d\n", j);
			//printf("-AFTER CHECH QUOTES COMILLAS -> %d, EXPAND -> %d\n", flag_quote, flag_expand);
			if(flag_expand == 0)
			{
				j = ft_de_oca_a_oca(i, j, &flag_quote, &flag_expand);
			//	printf(">FIN OCA -> %s\n", g_data.token1[i]);
		//		printf(">FIN OCA indice-> %d\n", j);
		//		printf(">FIN OCA COMILLAS -> %d, EXPAND -> %d\n", flag_quote, flag_expand);
			}
			if (g_data.token1[i][j] == '$')//&& g_data.token1[i][0] != '\'')
			{
				ft_expand(i, j);
			//	printf("*AFTER EXPAND -> %s\n", g_data.token1[i]);
		//		printf("*AFTER EXPAND indice-> %d\n", j);
		//		printf("*AFTER EXPAND COMILLAS -> %d, EXPAND -> %d\n", flag_quote, flag_expand);
				flag_quote = 0;
				flag_expand = 1;
				j = 0;//try yes/no
			}
		//	printf("=FIN BUCLE -> %s\n", g_data.token1[i]);
		//	printf("=FIN BUCLE indice-> %d\n", j);
		//	printf("=FIN BUCLE COMILLAS -> %d, EXPAND -> %d\n\n", flag_quote, flag_expand);
		//	getchar();
			j++;
		}		
		i++;
	}
	
	return (0);
}
