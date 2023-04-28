#include "minishell.h"
#define PRAMPT "minishell$>"

int init_prompt()
{
    while (42) {

		char	*input;
        input = readline(PRAMPT);
        if (!input) {
            break;
        }
        add_history(input);
        rl_on_new_line();
		if (strcmp(input, "pwd") == 0)
			ft_pwd();
        free(input);
    }

    return (0);
}
int main() {
    
	init_prompt();
    return 0;
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