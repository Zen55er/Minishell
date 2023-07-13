/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:55:19 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/13 12:10:24 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts tokens between outer parentheses*/
int	count_sub_tokens(char **tokens, int token)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tokens[++token])
	{
		if (!ft_strcmp(tokens[token], "("))
			flag++;
		else if (!ft_strcmp(tokens[token], ")"))
		{
			if (flag)
				flag--;
			else
				break ;
		}
		i++;
	}
	return (i);
}

/*Creates new array of tokens to be executed.*/
void	assign_subs(char **tokens, char **sub_tokens, int *token)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (tokens[++(*token)])
	{
		if (!ft_strcmp(tokens[*token], "("))
			flag++;
		else if (!ft_strcmp(tokens[*token], ")"))
		{
			if (flag)
				flag--;
			else
				break ;
		}
		sub_tokens[++i] = tokens[*token];
	}
	return ;
}

/*Copies tokens that are inside parentheses and sends them to executor.*/
void	subshell(t_data *data, char **tokens, int *token)
{
	int		i;
	pid_t	pid;
	int		status;
	char	**sub_tokens;

	i = count_sub_tokens(tokens, *token);
	sub_tokens = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!sub_tokens)
		return ;
	assign_subs(tokens, sub_tokens, token);
	pid = fork();
	if (pid == -1)
		return ;
	else if (!pid)
		executor(data, sub_tokens, 1);
	waitpid(pid, &status, 0);
	set_exit_code(WEXITSTATUS(status));
	free(sub_tokens);
	return ;
}
