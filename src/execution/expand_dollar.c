/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:27:50 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/23 18:36:56 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotess(char **str)
{
	int	len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if ((len >= 2 && (*str)[0] == '\'' && (*str)[len - 1] == '\'') || (len >= 2
			&& (*str)[0] == '"' && (*str)[len - 1] == '"'))
	{
		ft_memmove(*str, *str + 1, len - 2);
		(*str)[len - 2] = '\0';
	}
}

char	*remove_quotes(char *s)
{
	char	*result;
	int		wait_for;
	int		i;

	result = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (NULL);
	wait_for = NOT_SET;
	i = 0;
	while (*s)
	{
		if (*s == '\'' && wait_for == NOT_SET)
			wait_for = '\'';
		else if (*s == '\"' && wait_for == NOT_SET)
			wait_for = '\"';
		else if (*s == wait_for)
			wait_for = NOT_SET;
		else
		{
			result[i] = *s;
			i++;
		}
		s++;
	}
	return (result);
}

char	**remove_argv_quotes(char **argv)
{
	int	i;

	if (!argv)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		argv[i] = remove_quotes(argv[i]);
		i++;
	}
	return (argv);
}

void	expand_variable(char **str, t_data *minishell)
{
	char	*value;
	char	*key;
	char	*tmp;
	char	*tmp2;

	if (!str || !*str)
		return ;
	key = ft_strchr(*str, '$');
	if (!key)
		return ;
	tmp = ft_strdup(key + 1);
	if (!tmp)
		return ;
	tmp2 = ft_strchr(tmp, ' ');
	if (tmp2)
		*tmp2 = '\0';
	value = ft_get_envlst_val(tmp, minishell);
	if (value)
	{
		*key = '\0';
		*str = ft_strjoin(*str, value);
	}
	free(tmp);
}

char	**expand_variables(char **argv, t_data *minishell)
{
	int	i;

	if (!argv)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		expand_variable(&argv[i], minishell);
		i++;
	}
	return (argv);
}

void	ft_expand_dollar(char **argv, t_data *minishell)
{
	char	*value;

	if (!argv || !*argv)
		return ;
	if (ft_strncmp(*argv, "$?", 2) == 0)
	{
		value = ft_itoa(minishell->exit_status);
		if (value)
		{
			free(*argv);
			*argv = value;
		}
	}
	else if (*argv[0] == '$')
	{
		value = ft_get_envlst_val(*argv + 1, minishell);
		if (value)
		{
			free(*argv);
			*argv = value;
		}
	}
}

void	handle_quotes_dollar(char **argv, t_data *minishell)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '"' && argv[i][ft_strlen(argv[i]) - 1] == '"')
		{
			remove_quotess(&argv[i]);
			ft_expand_dollar(&argv[i], minishell);
		}
		else if (argv[i][0] == '\'' && argv[i][ft_strlen(argv[i]) - 1] == '\'')
		{
			remove_quotess(&argv[i]);
		}
		else if (ft_strchr(argv[i], '$'))
		{
			ft_expand_dollar(&argv[i], minishell);
		}
		i++;
	}
}

/*

char	*ft_expand_dollarp(char *argv, t_data *minishell)
{
	char	*value;

	if (!argv || !*argv)
		return ;
	if (ft_strncmp(argv, "$?", 2) == 0)
	{
		value = ft_itoa(minishell->exit_status);
		return(value);
	}
	else if (argv[0] == '$')
	{
		value = ft_get_envlst_val(argv + 1, minishell);
		if (value)
			return(value);
	}
}

void	handle_quotes_dollar(char *argv, t_data *minishell)
{
	int	i;
	int	j;

	if (!argv)
		return ;
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i] == '"')
			while(argv[j + i] != '"')
	}
}
/
/
/
/
/
/
/


void	remove_doube_quotes(cahr **str, char *ps)
{
  int len;

  if (!str || !*str)
	return ;
  len = ft_strlen(*str);
  if ((len >= 2 && (*str)[0] == '"' && (*str)[len - 1] == '"'))
  {
	ft_memmove(*str, *str + 1, len - 2);
	(*str)[len - 2] = '\0';
  }
}


void	handle_quotes_dollar(char **argv, t_data *minishell)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '"' && argv[i][ft_strlen(argv[i]) - 1] == '"')
		{
			remove_quotess(&argv[i]);
			ft_expand_dollar(&argv[i], minishell);
		}
		else if (argv[i][0] == '\'' && argv[i][ft_strlen(argv[i]) - 1] == '\'')
		{
			remove_quotess(&argv[i]);
		}
		else if (ft_strchr(argv[i], '$'))
		{
			ft_expand_dollar(&argv[i], minishell);
		}
		i++;
	}
}

int	is_in_quotes(char *str, char *c)
{
  int i;
  int open;
  int close;

  i = 0;
  open = 0;
  close = 0;
  while (str[i])
  {
	if ((str[i] == '"' || str[i] == '\'') && str < c)
		open++;
	if ((str[i] == '"' || str[i] == '\'') && str > c)
		close++;
	i++;
  }
  if (open % 2 == 0 && close % 2 == 0)
	return (0);
  return (1);
}

int	is_in_quotes(char *str, char *c)
{
	char	*current;
	char	*token_ahead;
	char	*token_behind;

	current = c;
}



  */