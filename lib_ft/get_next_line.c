/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:52:41 by ssuchane          #+#    #+#             */
/*   Updated: 2024/10/03 19:44:59 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts the remaining content after the first newline character
 * in a string.
 *
 * This function processes a given line to separate the content before the
 * first newline character from the content after it. It modifies the original
 * line to terminate at the newline character and returns a new string containing
 * the remaining content.
 *
 * @param line A pointer to the input string which is expected to contain
 * a newline character.
 *
 * @return A new string containing the content after the first newline character,
 * or NULL if no newline is found or if the allocated memory fails.
 *
 * @note The input string will be modified to terminate at the newline character.
 *       It is the caller's responsibility to free the memory allocated for the 
 *       returned string.
 */
char	*fix_line(char *line)
{
	char	*holder;
	int		i;

	i = 0;
	holder = NULL;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	holder = ft_substr(line, i + 1, ft_strlen(line) + i);
	if (!holder)
		return (NULL);
	if (holder[0] == '\0')
	{
		free(holder);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (holder);
}

/**
 * @brief Reads data from a file descriptor into a buffer and appends it to
 * a stash string.
 *
 * This function continuously reads from the provided file descriptor until
 * either a newline character is found in the buffer or there are no more bytes
 * to read. It combines the newly read data with any existing data stored in the
 * stash string.
 *
 * @param fd The file descriptor from which to read data.
 * @param buffer A pointer to a character buffer used to temporarily store read
 * data.
 * @param stash A pointer to a string that holds previously read data.
 *
 * @return A pointer to the updated stash string containing the combined data
 * from previous reads and the new buffer, or NULL if an error occurs.
 *
 * @note The caller is responsible for freeing any memory allocated for the
 * returned stash string and for the buffer.
 */
char	*fill_buffer(int fd, char *buffer, char *stash)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		if (stash == NULL)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free (temp);
		temp = NULL;
		if (!stash)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

/**
 * @brief Retrieves the next line from the specified file descriptor.
 *
 * This function reads from a file descriptor and returns a line of text, 
 * which may span multiple reads. It utilizes a static stash to keep track 
 * of remaining data from previous reads and returns a dynamically allocated 
 * string containing the next line, including any newline characters.
 *
 * @param fd The file descriptor from which to read the next line.
 *
 * @return A pointer to a dynamically allocated string containing the next line 
 *         read from the file descriptor, or NULL if an error occurs, if the 
 *         end of file is reached, or if the input parameters are invalid.
 *
 * @note The returned string should be freed by the caller. If there are no more 
 *       lines to read, the function returns NULL.
 */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, buffer, stash);
	free(buffer);
	if (!line)
		return (NULL);
	stash = fix_line(line);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("Error opening file.\n");
// 		return (1);
// 	}
// 	while((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free (line);
// 	}
// 	// while (i < 6)
// 	// {
// 	// 	line = get_next_line(fd);
// 	// 	if (line == NULL)
// 	// 		return (0);
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// 	i++;
// 	// }
// 	close(fd);
// 	return (0);
// }
