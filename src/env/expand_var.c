

#include "../../inc/minishell.h"

char		*get_var_name(char *input, int *i);

static int	add_another_space(int i, int quotes, char *input)
{
	if (input[i] == '|' && input[i + 1] != ' ' && input[i + 1] != '\0'
		&& quotes == NOT_SET)
		return (1);
	else if (((input[i] == '<' && input[i + 1] != '<') || (input[i] == '>'
				&& input[i + 1] != '>')) && input[i + 1] != ' ' && input[i
		+ 1] != '\0' && quotes == NOT_SET)
		return (1);
	return (0);
}

static int	add_space(int i, int quotes, char *input)
{
	if (i > 0 && input[i] == '|' && input[i - 1] != ' ' && quotes == NOT_SET)
		return (1);
	else if (i > 0 && ((input[i] == '>' && input[i - 1] != '>')
			|| (input[i] == '<' && input[i - 1] != '<')) && input[i - 1] != ' '
		&& quotes == NOT_SET)
		return (1);
	return (0);
}

bool	do_copy_var(int quotes, char *input, int i)
{
	return ((input[i] == '$' && quotes != '\'' && input[i + 1] != ' ' && input[i
			+ 1] != '\"' && input[i + 1] != '+' && input[i + 1] != ':'
			&& input[i + 1] != '/' && input[i + 1] != '=' && input[i + 1] != '.'
			&& input[i + 1] != ',' && input[i + 1] != '\0'));
}

static void	set_quotes(char *quotes, char word)
{
	if (*quotes == NOT_SET && (word == '\'' || word == '\"'))
		*quotes = word;
	else if (*quotes != NOT_SET && word == *quotes)
		*quotes = NOT_SET;
}

int	copy_variable(char *name, t_data *minishell, int *j, char *result)
{
	if (!name)
		return (0);
	ft_strlcpy(result + *j, ft_get_var_value(name, minishell),
		ft_strlen(ft_get_var_value(name, minishell)) + 1);
	*j += ft_strlen(ft_get_var_value(name, minishell));
	free(name);
	return (1);
}

int	replace_var_loop(char *input, t_data *minishell, char *result, int i)
{
	int		j;
	char	quotes;

	j = 0;
	quotes = NOT_SET;
	while (input[i])
	{
		set_quotes(&quotes, input[i]);
		if (!do_copy_var(quotes, input, i))
		{
			if (add_space(i, quotes, input))
				result[j++] = ' ';
			result[j] = input[i];
			if (add_another_space(i, quotes, input))
				result[++j] = ' ';
			i++;
			j++;
		}
		else
		{
			i++;
			copy_variable(get_var_name(input, &i), minishell, &j, result);
		}
	}
	return (1);
}

static void	check_for_spaces(char *input, int *length, int *i,
		bool is_in_quotes)
{
	if (*i > 0 && input[*i] == '|' && input[*i - 1] != ' ' && !is_in_quotes)
		(*length)++;
	if (input[*i] == '|' && input[*i + 1] != ' ' && input[*i + 1] != '\0'
		&& !is_in_quotes)
		(*length)++;
	if (input[*i] == '<' || input[*i] == '>')
		(*length) += 2;
	(*length) += 2;
	(*i)++;
}

char	*ft_strchrs_mf(const char *str, const char *c)
{
	char	*ptr;
	char	*chrs;

	ptr = (char *)str;
	while (*ptr)
	{
		chrs = (char *)c;
		while (*chrs)
		{
			if (*ptr == *chrs)
				return (ptr);
			chrs++;
		}
		ptr++;
	}
	if (*ptr == '\0')
		return (ptr);
	return (NULL);
}

char	*get_var_name(char *input, int *i)
{
	char	*name;
	char	*chrptr;

	if (!input || !i)
		return (NULL);
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	chrptr = input + *i;
	name = ft_strndup(chrptr, ft_strchrs_mf(chrptr, " \"\'/:.,=+") - chrptr);
	if (!name)
		return (NULL);
	*i += ft_strlen(name);
	return (name);
}

int	count_length(char *input, t_data *minishell, int *length)
{
	bool	is_in_quotes;
	char	*name;
	int		i;

	i = 0;
	is_in_quotes = false;
	while (input[i])
	{
		if (input[i] == '\'')
			is_in_quotes = !is_in_quotes;
		if (input[i] == '$' && !is_in_quotes && input[i + 1] != ' ' && input[i
			+ 1] != '\"' && input[i + 1] != '\0')
		{
			i++;
			name = get_var_name(input, &i);
			if (!name)
				return (error);
			if (*name == '?')
				*length += ft_strlen(ft_itoa(minishell->exit_status));
			else
				*length += ft_strlen(ft_get_var_value(name, minishell)) + 1;
			free(name);
		}
		else
			check_for_spaces(input, length, &i, is_in_quotes);
	}
	return (*length);
}

char	*replace_var(char *input, t_data *minishell)
{
	int		length;
	char	*result;

	length = 0;
	count_length(input, minishell, &length);
	if (length <= 0)
		return (NULL);
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (!replace_var_loop(input, minishell, result, 0) || !result)
		return (free(result), NULL);
	return (result);
}

void		set_last_exit_code(t_data *minishell)
{
	t_env *envlst;
	char *value;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp("?", envlst->key))
		{
			value = ft_itoa(minishell->exit_status);
			if (value)
			{
				free(envlst->value);
				envlst->value = value;
			}
			return ;
		}
		envlst = envlst->next;
	}
}
