

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void	update_quote_flags(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

bool	is_token_inside_quotes(char *start, char token1, char token2,
		bool in_single_quote, bool in_double_quote)
{
	while (*start)
	{
		if (*start == '\'' && in_single_quote && (*start == token1
			|| *start == token2))
			return (true);
		else if (*start == '"' && in_double_quote && (*start == token1
				|| *start == token2))
			return (true);
		start++;
	}
	return (false);
}

/* 
** check if the needle is inside quotes, specify the quotes with token1 or token2 or both
** put 0 if you don't want to specify a token
** @param stack the string to search in
** @param needle must be a pointer to a character in the stack
** return true if the needle is inside quotes, false otherwise
 */
bool	is_inside_quotes(char *stack, char *needle, char token1, char token2)
{
	bool	in_single_quote;
	bool	in_double_quote;
	char	*p;

	in_single_quote = false;
	in_double_quote = false;
	p = stack;
	while (*p)
	{
		update_quote_flags(*p, &in_single_quote, &in_double_quote);
		if (needle == p && (in_single_quote || in_double_quote))
		{
			if (is_token_inside_quotes(p, token1, token2, in_single_quote,
					in_double_quote))
				return (true);
		}
		p++;
	}
	return (false);
}

int	main(void)
{
	char	*stack;
	char	*needle;

	stack = "To jest 'przykład' testu \"needle\" w cudzysłowie.";
	needle = stack + 27;
	if (is_inside_quotes(stack, needle, '\"', 0))
	{
		printf("'%s' znajduje się w obrębie cudzysłowów.\n", needle);
	}
	else
	{
		printf("'%s' nie znajduje się w obrębie cudzysłowów.\n", needle);
	}
	return (0);
}

/* bool	is_inside_quotes(char *stack, char *needle, char token1, char token2)
{
	bool	in_single_quote;
	bool	in_double_quote;
	char	*p;
	char	*b;

	p = stack;
	b = p;
	in_single_quote = false;
	in_double_quote = false;
	while (*p)
	{
		if (*p == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*p == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (needle == p && (in_single_quote || in_double_quote))
		{
			b = p;
			while (*b)
			{
				if (*b == '\'' && in_single_quote && (*b == token1
					|| *b == token2))
					return (true);
				else if (*b == '"' && in_double_quote && *b == token1
					|| *b == token2)
					return (true);
				b++;
			}
		}
		p++;
	}
	return (false);
} */