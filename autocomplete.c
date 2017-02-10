/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aridolfi <aridolfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:01:14 by aridolfi          #+#    #+#             */
/*   Updated: 2017/02/10 15:36:02 by aridolfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42sh.h"

int        strstr_no_case(char *find, char *search_in_lc)
{
    int        i;
    int        j;
    size_t    f_len;

    f_len = ft_strlen(find);
    i = 0;
    while (search_in_lc[i])
    {
        if (search_in_lc[i] == find[0])
        {
            j = -1;
            while (search_in_lc[i] && search_in_lc[i] == find[++j])
                ++i;
            if (j == f_len)
            {
                free(search_in_lc);
                return (1);
            }
        }
        else
            ++i;
    }
    free(search_in_lc);
    return (0);
}

char    *to_lowercase(char *str)
{
    int        i;
    char    *str_lc;

    str_lc = ft_strdup(str);
    i = -1;
    while (str_lc[++i])
        if (str_lc[i] >= 'A' && str_lc[i] <= 'Z')
            str_lc[i] = str_lc[i] - 'A' + 'a';
    return (str_lc);
}

char    **ac_cmd(char *find, t_env *env)
{
    char ** = buildins && commandes path
    return (char ** =    "echo"
                        "ecarlate")
}

char    **ac_pwd(char *find, t_env *env)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		**sug;
	int			count;
    char		pwd[INPUT_SIZE];

	count = 0;
	sug = (char**)palloc(sizeof(char*));
	sug[0] = NULL;
    getcwd(pwd, INPUT_SIZE);
	dir = opendir(pwd);
	while ((dirent = readdir(dir)))
		if (strstr_no_case(find, to_lowercase(dirent->d_name)))
		{
			++count;
			new = palloc(sizeof(char *) * count + 1);
			i = 1;
			while (i <= count)
				new[i] = sug[i - 1];
			new[0] = ft_strdup(dirent->d_name);
			free(sug);
			sug = new;
		}
	closedir(dir);
	return (sug);
}

char    **auto_possibilities(char *find, char pwd, t_env *env)
{
    char **ac;
    char *find_lwc;

    find_lwc = to_lowercase(find);
    if (pwd == 0)
        ac = ac_cmd(find_lwc, env);
    else
        ac = ac_pwd(find_lwc, env);
    return (ac);
}
