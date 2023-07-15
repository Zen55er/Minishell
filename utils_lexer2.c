/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:31:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/14 14:47:51 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Reads missing input from file.*/
int	read_missing(char **input, char *file)
{
	int		input_fd;
	char	*new_input;
	char	*temp;

	input_fd = open(file, O_RDONLY);
	if (input_fd == -1)
		return (1);
	new_input = ft_strdup("");
	while (1)
	{
		temp = get_next_line(input_fd);
		if (!temp)
			break ;
		new_input = ft_strjoin_free(new_input, temp);
	}
	close(input_fd);
	unlink(file);
	update_input(input, new_input);
	return (0);
}

/*Prepares missing input fd to read remaining input.*/
int	missing_input_fork(char **input, char match)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	unlink(".missing_input");
	pid = fork();
	if (pid == -1)
	{
		perror("missing_input fork");
		return (1);
	}
	if (!pid)
		missing_input(input, match);
	waitpid(pid, &status, 0);
	signal_global();
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2 && printf("\n"))
		return (CTRL_C);
	if (read_missing(input, ".missing_input"))
		return (1);
	return (0);
}

/*Requests extra input from user and updates input string*/
int	missing_input(char **input, char match)
{
	int		input_fd;
	char	*temp;

	signal(SIGINT, SIG_DFL);
	input_fd = open(".missing_input", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(input_fd, " ", 1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
			break ;
		if (match == '\n' && temp[0] == '\n' && int_free(temp, 1))
			continue ;
		write(input_fd, temp, ft_strlen(temp));
		if (temp[0] == match || char_finder(temp, match))
			break ;
		free(temp);
	}
	if (temp[0] != match && !char_finder(temp, match) && int_free(temp, 1))
		exit (unexpected_eof(input, match));
	free(temp);
	close(input_fd);
	exit (0);
}

/*If input ends in |, || or &&, calls missing input to complete it.*/
int	check_end(char **input, int i)
{
	if ((*input)[i] == '|' && (*input)[i + 1] != '|')
		i++;
	if ((*input)[i] == '|' && (*input)[i + 1] == '|')
		i += 2;
	if ((*input)[i] == '&' && (*input)[i + 1] == '&')
		i += 2;
	while ((*input)[i] && ft_isspace((*input)[i]))
		i++;
	if (!(*input)[i])
		return (missing_input_fork(input, '\n'));
	return (0);
}

/*Returns index of next matching quote (or end of str).
If there is no matching quote and the string ends, returns the index
of the previous character to avoid a heap overflow in validate_input.*/
int	jump_quotes(char *str, int i, char quote)
{
	while (str[++i] && str[i] != quote)
		continue ;
	if (!str[i])
		return (i - 1);
	return (i);
}

/*Checks whether input is complete
(no missing information after |, ||, && or ${).*/
int	validate_input(char **str)
{
	int		i;
	int		exit;
	char	match;

	exit = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			i = jump_quotes(*str, i, (*str)[i]);
		if (forbidden((*str), i))
			return (1);
		else if ((*str)[i] == '(' || ((*str)[i] == '$' && (*str)[i + 1] == '{'))
		{
			match = get_match((*str)[i]);
			if (!char_finder(*str, match))
				exit = missing_input_fork(str, match);
			i += char_finder(*str + i, (*str)[i]);
		}
		else if (i && ((*str)[i] == '|' || (*str)[i] == '&'))
			exit = check_end(str, i);
		if (exit || !ft_strcmp(*str, "exit 2"))
			return (exit);
	}
	return (0);
}
