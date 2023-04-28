/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:45:55 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/28 23:44:53 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data data;

int	init_prompt(void)
{
	char	*input;

	while (42)
	{
		input = readline(PRAMPT);
		if (!input)
			break ;
		add_history(input);
		rl_on_new_line();
		if (strcmp(input, "pwd") == 0)
			ft_pwd();
		if (strcmp(input, "cd") == 0)
			ft_cd("..");
		free(input);
	}
	return (0);
}

int	main(void)
{	
	init();
	init_prompt();
	return (0);
}
// int main(int argc, char **argv, char **envp) {
//     char *input = readline("Enter some text: ");
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
