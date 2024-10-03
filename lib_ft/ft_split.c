/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:34:49 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of words in a string based on a delimiter.
 *
 * This helper function counts the number of words in the string `s`,
 * using the character `c` as a delimiter.
 *
 * @param s The string in which to count words. It should be null-terminated.
 * @param c The delimiter character used to separate words.
 * 
 * @return The number of words in the string.
 */
static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (in_word == 0 && *s != c)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

/**
 * @brief Frees the memory allocated for an array of strings.
 *
 * This helper function frees each string in the array and then frees 
 * the array itself.
 *
 * @param result The array of strings to be freed.
 *
 * @note If `result` is NULL, this function does nothing.
 */
static void	free_word(char **result)
{
	int	i;

	i = 0;
	if (!result)
		return ;
	while (result[i])
	{
		free (result[i]);
		i++;
	}
	free (result);
}

/**
 * @brief Helper function to populate the result array with words from
 * the string.
 *
 * This helper function iterates through the string `s`, identifies 
 * words separated by the delimiter `c`, and populates the result 
 * array with these words.
 *
 * @param s The string from which to extract words. It should be 
 *          null-terminated.
 * @param c The delimiter character used to separate words.
 * @param start A pointer to the start of the current word in the string.
 * @param result The array of strings where words will be stored.
 * 
 * @return A pointer to the populated array of strings, or NULL if memory 
 *         allocation fails.
 */
static char	**ft_helper(const char *s, char c, char *start, char **result)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			result[i] = ft_substr(start, 0, s - start);
			if (!result[i])
			{
				free_word(result);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	return (result);
}

/**
 * @brief Splits a string into an array of words based on a delimiter.
 *
 * The function takes a null-terminated string `s` and splits it into 
 * words, using the character `c` as the delimiter. The resulting 
 * words are stored in a dynamically allocated array of strings. 
 * The array is null-terminated.
 *
 * @param s The string to be split into words. It should be null-terminated.
 * @param c The delimiter character used to separate words in the string.
 * 
 * @return A pointer to an array of strings (words), or NULL if memory 
 *         allocation fails or if `s` is NULL. The last element of the 
 *         array is NULL to indicate the end of the words.
 *
 * @note This function uses helper functions for counting words and 
 *       managing memory. Memory allocated for the array and its contents 
 *       should be freed by the caller after use.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*start;

	result = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	start = NULL;
	result = ft_helper(s, c, start, result);
	return (result);
}
