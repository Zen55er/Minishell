/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:55:19 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/26 08:53:13 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Copies tokens that are inside parentheses and sends them to executor.*/
void	subshell(t_data *data, int *token)
{
	int		i;
	int		j;
	pid_t	pid;
	int		status;
	char	**sub_tokens;

	i = 0;
	j = *token;
	while (data->tokens[++j] && smart_compare(data->tokens[j], ")"))
		i++;
	sub_tokens = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!sub_tokens)
		return ;
	i = -1;
	while (data->tokens[++(*token)] && smart_compare(data->tokens[*token], ")"))
		sub_tokens[++i] = data->tokens[*token];
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
