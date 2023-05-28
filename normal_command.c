/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:22:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/26 11:45:05 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prepares cmds struct and sends it to execve*/
int	normal_command(t_data *data, int token)
{
	char	**cmds;
	int		temp;
	int		i;

	i = 0;
	temp = token;
	while (data->tokens[temp])
	{
		if (delim(data->tokens[temp]))
			break ;
		i++;
		temp++;
	}
	cmds = (char **)malloc(sizeof(char *) * (i + 1));
	cmds[i] = 0;
	i = 0;
	while (token < temp)
	{
		cmds[i] = ft_strdup(data->tokens[token]);
		token++;
		i++;
	}
	/*DELETE AFTER TESTING*/
	printf("COMMANDS 2D\n");
	for (int j = 0; cmds[j]; j++)
		printf("%s\n", cmds[j]);
	free_double(cmds);
	/**/
	return (0);
}
