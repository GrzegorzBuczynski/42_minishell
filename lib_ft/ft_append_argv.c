/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:05:38 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 18:54:31 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends a new string to an existing array of strings (argv).
 *
 * This function takes an existing array of strings (`argv`) and appends
 * a new string (`line`) to it. It allocates memory for a new array that is
 * one element larger than the original `argv` and copies all strings from
 * the original array into the new one. It then adds the new string and
 * terminates the array with a NULL pointer.
 *
 * @param argv The existing array of strings (can be NULL).
 * @param line The new string to append to the array.
 *
 * @return A new array of strings with `line` appended. The new array is
 *         dynamically allocated and should be freed by the caller.
 *
 * @note The function allocates memory for the new array and copies the
 *       strings. The caller is responsible for freeing the memory allocated
 *       for both the new array and the duplicated strings.
 *
 * @warning If `malloc` fails,
 *	the function calls `ft_panic` and exits the program.
 */
char	**ft_append_argv(char **argv, char *line)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (new_argv == NULL)
		ft_panic("malloc", 1);
	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	new_argv[i] = ft_strdup(line);
	new_argv[i + 1] = NULL;
	return (new_argv);
}
