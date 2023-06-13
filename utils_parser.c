/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:13:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/13 10:26:45 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns last exit code.*/
char	*get_exit_code(t_data *data, char *str1, char **str2)
{
	free(str1);
	free(*str2);
	return (ft_itoa(data->last_exit));
}

char	*get_section(t_data *data, char *str, int i, int j)
{
	char	*section;

	if (str[i] == '\'' || str[i] == '\"' )
		section = quotes(data, ft_substr(str, i, j + 1));
	else
		section = ft_substr(str, i, j);
	return (section);
}

void	fix_tokens_wc(t_data *data, int *i)
{
	t_ll	*matches;

	matches = expand_wildcards(data->tokens[*i]);
	if (matches && list_size(matches) == 1)
	{
		free(data->tokens[*i]);
		data->tokens[*i] = ft_strdup(matches->var);
	}
	else if ((matches && list_size(matches) > 1))
		*i += add_tokens(data, matches, *i);
	free_list(&matches);
}
