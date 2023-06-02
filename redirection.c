/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:25 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/02 12:15:29 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(t_data *data, int i)
{
	if (!ft_strncmp(data->tokens[i], "<", ft_strlen(data->tokens[i])))
	{
		data->fdin = open(data->tokens[i + 1], O_RDONLY);
		if (data->fdin == -1)
		{
			perror("Minishell");
			return (1);
		}
		dup2(data->fdin, STDIN_FILENO);
	}
	return (0);
}
