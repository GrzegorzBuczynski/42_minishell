/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/24 18:12:58 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void print_error(char *message)
{
    write(2, message, strlen(message));
}

int is_numeric(char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int get_exit_code(int code)
{
    if (code < 0)
        return (256 + (code % 256));
    return (code % 256);
}

int ft_exit(char **args)
{
    int exit_code = 0;

    // Check for too many arguments
    if (args[1] && args[2])
    {
        print_error("bash error: too many arguments\n");
        exit(1); // Return 1 for too many arguments
    }

    // Check for valid exit code
    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            print_error("bash error: numeric argument required\n");
            exit(2); // Return 2 for non-numeric argument
        }
        exit_code = atoi(args[1]);
        exit_code = get_exit_code(exit_code);
    }
    exit(exit_code);
}