/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/07 10:40:59 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Searches env for specific directory*/
char	*get_dir(t_data *data, char *dir)
{
	t_ll	*temp;

	temp = data->env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, dir))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

/*Changes env entry for new directory*/
void	update_env_dir(t_data *data, char *dir, char *new_dir)
{
	t_ll	*temp;

	temp = data->env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, dir))
		{
			free(temp->value);
			temp->value = ft_strdup(new_dir);
			break ;
		}
		temp = temp->next;
	}
	return ;
}

/*Checks if input is a directory.*/
int	check_dir(char *input)
{
	if (!input[0])
		return (OK_EXIT);
	if (!access(input, F_OK))
	{
		if (access(input, X_OK))
			print_error(input, 0, "Permission denied", 0);
		else
			print_error(input, 0, "Is a directory", 0);
		return (ERROR_EXECUTE_PERMISSIONS);
	}
	print_error(input, 0, "No such file or directory", 0);
	return (ERROR_WRONG_COMMAND);
}
