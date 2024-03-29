/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 17:03:11 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if token is a delimiter*/
int	delim_tok(char *token)
{
	if (!ft_strcmp(token, "|") || !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<<") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "(") || !ft_strcmp(token, ")")
		|| !ft_strcmp(token, "&&"))
		return (1);
	return (0);
}

/*Prints arguments of echo, if -n flag is present, does not write newline*/
int	cmd_echo(char **tokens, int tok)
{
	int	n_flag;

	n_flag = 0;
	if ((!tokens[tok + 1] || delim_tok(tokens[tok + 1])) && printf("\n"))
		return (OK_EXIT);
	while (!ft_strcmp(tokens[++tok], "-n") && !tokens[tok][2])
	{
		n_flag = 1;
		continue ;
	}
	while (tokens[tok])
	{
		if (delim_tok(tokens[tok]))
			break ;
		quotes_delimiter_full(tokens, tok, 0);
		if (tokens[tok])
			printf("%s", tokens[tok]);
		quotes_delimiter_full(tokens, tok, 1);
		if (tokens[tok + 1] && !delim_tok(tokens[tok + 1]))
			printf(" ");
		tok++;
	}
	if (!n_flag)
		printf("\n");
	return (OK_EXIT);
}

/*Prints env linked list and any exported variables at the end,
in the same order they were created*/
int	cmd_env(t_data *data)
{
	t_ll	*temp;

	temp = data->env;
	while (temp)
	{
		if (!temp->value)
		{
			temp = temp->next;
			continue ;
		}
		printf("%s=", temp->var);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (OK_EXIT);
}

/*Checks exit argument, it can't be non-numeric
or greater than long long bounds.*/
unsigned char	check_exit_arg(char *token)
{
	int					i;
	long long			signal;
	unsigned long long	check;

	i = 0;
	signal = 1;
	if (token[i] == '+' || token[i] == '-')
	{
		if (token[i] == '-')
			signal *= -1;
		i++;
	}
	check = ft_atoull(&token[i]);
	while (token[i])
	{
		if (!ft_isdigit(token[i]) || (check > LLONG_MAX && signal == 1)
			|| (check - 1 > LLONG_MAX && signal == -1))
		{
			print_error("exit", token, "numeric argument required", 0);
			return (ERROR_MISUSE);
		}
		i++;
	}
	return ((unsigned char)((long long)(check * signal)));
}

/*Prints "exit", updates prompt, frees memory and exits program.
Can't have more than 1 argument and that argument needs to be numeric.*/
int	cmd_exit(t_data *data, char **tokens, int token)
{
	int	flag;

	printf("exit\n");
	flag = 0;
	if (tokens[token + 1])
		flag = 1;
	if (tokens[token + 1] && tokens[token + 2])
	{
		print_error("exit", 0, "too many arguments", 0);
		return (ERROR_EXIT);
	}
	if (tokens[token + 1])
		update_exit_code(check_exit_arg(tokens[token + 1]), 1);
	free_all(0, data);
	if (flag)
		exit(update_exit_code(0, 0));
	else
		exit(OK_EXIT);
}
