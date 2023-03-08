/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imendonc <imendonc@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:09:48 by imendonc          #+#    #+#             */
/*   Updated: 2023/03/08 15:09:48 by imendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void    embriao(int *fd, char **argv, char **envp)
{
    int infile_fd;

    close(fd[0]);
    infile_fd = open(argv[1], O_RDONLY, 0777);
    if (infile_fd < 0)
        perros();
    dup2(infile_fd, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    command_executer(argv[2], envp);
    close(fd[1]);
}

void    progenitor(int *fd, char **argv, char **envp)
{
    int outfile_fd;

    close(fd[1]);
    outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (outfile_fd < 0)
        perros();
    dup2 (outfile_fd, STDOUT_FILENO);
    dup2 (fd[0], STDIN_FILENO);
    command_executer (argv[3], envp);
    close(fd[0]);
}