/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imendonc <imendonc@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:41 by imendonc          #+#    #+#             */
/*   Updated: 2023/01/26 12:26:41 by imendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char *triple_join(char *s1, char *s2, char *s3)
{
    char *str;
    size_t a;
    size_t b;

    str = malloc(sizeof(*s1) * ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
    a = 0;
    b = 0;
    if (!s1 || !s2 || !s3 || !str)
        return (NULL);
    while (s1[a])
        str[b++] = s1[a++];
    a = 0;
    while (s2[a])
        str[b++] = s2[a++];
    a = 0;
    while (s3[a])
        str[b++] = s3[a++];
    str[b] = '\0';
    return (str);
}

/* funcao que encontra o PATH do comando*/
char *pathfinder(char *command, char **envp)
{
    char    **path_search;
    char    *path;
    char    **without;
    int p;

    without = ft_split(command, 32);
    p = 0;
    while (!(ft_strnstr(envp[p], "PATH", 4)))
        p++;
    path_search = ft_split(envp[p] + 5, ':');
    p = 0;
    while (path_search[p])
    {
        path = triple_join(path_search[p], "/", without[0]);
        if(access(path, 0) == 0)
            return (path);
        free(path);
        p++;
    }
	if (access(path, 0) == -1)
		perros();
    p = -1;
    while (path_search[++p])
    	free (path_search[p]);
    free (path_search);
    free (without);
    return (path);
}

void    command_executer(char *argv, char **envp)
{
    char *path;
    char **way;

    way = ft_split(argv, 32);
    path = pathfinder(way[0], envp);
    if (!path)
    {
        free (way);
        perros();
    }
    else if (execve(path, way, envp) == -1)
        perros();
    else
    	free(path);
}
