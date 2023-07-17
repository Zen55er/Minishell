/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/17 13:49:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d_error(char *limiter)
{
	char		*tmp;
	int			fd;
	static int	n;
	static int	first;

	fd = open(".here_doc", O_RDONLY);
	tmp = get_next_line(fd);
	n++;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp)
			n++;
	}
	free(tmp);
	close(fd);
	if (!first)
	{
		first = 1;
		print_error2(limiter, first);
		return ;
	}
	print_error2(limiter, n);
}

pid_t	here_doc_fork(char *limiter)
{
	pid_t	p;

	signal(SIGINT, SIG_IGN);
	p = fork();
	if (p == 0)
		here_doc(limiter);
	return (p);
}

int	here_doc(char *limiter)
{
	int		doc;
	char	*buf;

	signal(SIGINT, SIG_DFL);
	doc = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "here_doc> ", 10);
		buf = get_next_line(STDIN_FILENO);
		if (!buf || (!ft_strncmp(buf, limiter, ft_strlen(limiter))
				&& buf[ft_strlen(limiter)] == '\n'))
			break ;
		write(doc, buf, ft_strlen(buf));
		free(buf);
	}
	close (doc);
	if (!buf)
		exit(1);
	free(buf);
	exit(0);
}

int	open_fds(char *redir, char *file)
{
	int		i;
	int		status;
	pid_t	p;

	i = -1;
	if (!ft_strcmp(redir, "<<"))
	{
		p = here_doc_fork(file);
		waitpid(p, &status, 0);
		signal_global();
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			ctrl_d_error(file);
		if (WIFSIGNALED(status) && WTERMSIG(status) == 2 && printf("\n"))
			return (-2);
		i = open(".here_doc", O_RDONLY);
	}
	else if (!ft_strcmp(redir, ">"))
		i = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(redir, ">>"))
		i = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(redir, "<"))
		if (!access(file, R_OK))
			i = open(file, O_RDONLY);
	return (i);
}

int	get_fds(char **tokens, int *fdin, int *fdout, int c)
{
	while (tokens[c] && ft_strcmp(tokens[c], "|"))
	{
		if (!ft_strcmp(tokens[c], ">") || !ft_strcmp(tokens[c], ">>"))
			*fdout = open_fds(tokens[c], tokens[c + 1]);
		else if (!ft_strcmp(tokens[c], "<") || !ft_strcmp(tokens[c], "<<"))
			*fdin = open_fds(tokens[c], tokens[c + 1]);
		if (*fdin == -1 || *fdout == -1)
			break ;
		c++;
	}
	if (*fdout == -1 || *fdin == -1)
		print_error(tokens[c + 1], 0, "No such file or directory", 0);
	if (*fdin == -2)
	{
		update_exit_code(CTRL_C, 1);
		return (1);
	}
	return (0);
}
