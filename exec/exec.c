#include "../minishell.h"

void execute_command(t_shell *shell)
{
    char *command = g_shell.builtin_path[0];

    if (ft_strcmp(command, "cd") == 0)
    {
        bl_cd();
    }
    else if (ft_strcmp(command, "echo") == 0)
    {
        bl_echo();
    }
    else if (ft_strcmp(command, "pwd") == 0)
    {
        bl_pwd();
    }
    else if (ft_strcmp(command, "exit") == 0)
    {
        bl_exit();
    }
    else if (ft_strcmp(command, "unset") == 0)
    {
        ft_unset(g_shell.builtin_path, &g_shell);
    }
    else if (ft_strcmp(command, "env") == 0)
    {
        bl_env();
    }
    else
    {
        // Code pour exécuter les commandes non intégrées
    }
} 