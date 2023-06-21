/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/21 14:41:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In cases where input for a command comes in a path (e.g. user/bin/ls),
returns only the end of the string (after the last '/).*/
char	*get_end_cmd(char *str)
{
	char	*cmd;
	int		i;

	i = -1;
	while (str[++i])
		continue ;
	while (str[--i] != '/')
		continue ;
	i++;
	cmd = ft_substr(str, i, ft_strlen(str) - i);
	return (cmd);
}
