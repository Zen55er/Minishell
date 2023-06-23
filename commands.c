/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/23 10:40:30 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints arguments of echo, if -n flag is present, does not write newline*/
int	cmd_echo(t_data *data, int tok)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 0;
	if (!data->tokens[tok + 1] || delim(data->tokens[tok + 1], 1))
		return (OK_EXIT);
	while (data->tokens[++tok] && ++i)
	{
		if (delim(data->tokens[tok], 1))
			break ;
		if (i == 1 && !ft_strncmp(data->tokens[tok], "-n", 2)
			&& !data->tokens[tok][2])
		{
			n_flag = 1;
			continue ;
		}
		if (data->tokens[tok])
			printf("%s", data->tokens[tok]);
		if (data->tokens[tok + 1] && !delim(data->tokens[tok + 1], 1))
			printf(" ");
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
		printf("%s=", temp->var);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	temp = data->exp;
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
		if (!ft_isdigit(token[i]) || (check > LLONG_MAX && signal)
			|| (check - 1 > LLONG_MAX && !signal))
		{
			printf("minishell: exit: %llu: numeric argument required\n", check);
			return (ERROR_MISUSE);
		}
		i++;
	}
	return ((unsigned char)((long long)check * signal));
}

/*Prints "exit", updates prompt, frees memory and exits program.
Can't have more than 1 argument and that argument needs to be numeric.*/
int	cmd_exit(t_data *data, int token)
{
	int	flag;

	printf("exit\n");
	flag = 0;
	if (data->tokens[token + 1])
		flag = 1;
	if (data->tokens[token + 1] && data->tokens[token + 2])
	{
		printf("minishell: exit: too many arguments\n");
		return (ERROR_EXIT);
	}
	if (data->tokens[token + 1])
		set_exit_code(check_exit_arg(data->tokens[token + 1]));
	rl_clear_history();
	free_all(0, data);
	if (flag)
		exit(update_exit_code(0, 0));
	else
		exit(OK_EXIT);
}
