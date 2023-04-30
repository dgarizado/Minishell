/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/30 22:26:34 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data g_data;

int	print_token1(char **str)
{
	int i = 0;
	while (str[i] != NULL)
	{
		printf("\n%s\n", str[i]);
		i++;
	}
	return (0);
}

int	init_prompt(void)
{
	while (42)
	{
		g_data.input = readline(PRAMPT);
		if (!(g_data.input))
			break ;
		add_history((g_data.input));
		rl_on_new_line();
		ft_lexic((g_data.input));
		g_data.token1 = pipexsplit((g_data.input));
		if (strcmp((g_data.input), "exit") == 0)
			ft_exit();
		print_token1(g_data.token1);
		free((g_data.input));
		free(g_data.token1);
	}
	return (0);
}

int	main(void)
{	
	init();
	while (1)
	{
		g_data.mainpid = fork();
		if (g_data.mainpid == 0)
			init_prompt();
		wait(&g_data.child_status);
		g_data.child_status = (WEXITSTATUS(g_data.child_status));
		if (g_data.child_status == 255)
			break ;
	}
	return (0);
}
// int main(int argc, char **argv, char **envp) {
//     char *(data.input) = readline("Enter some text: ");
//     char buffer[1024];
//     add_history(input);
//     printf("You entered: %s\n", input);
//     free(input);
//     char *path = getenv("PATH");
//     if (getcwd(buffer, sizeof(buffer)) == NULL) {
//     perror("getcwd");
//     exit(EXIT_FAILURE);
//   }
//     printf("\n%s\n", buffer);
//     // int i = 0;
//     // while (envp[i] != NULL)
//     // {
//     //     printf("\n%s\n", envp[i]);
//     //     i++;
//     // }
//     return 0;
// } 
