#include <stdlib.h>
#include "ft_ls.h"

int		is_flagls(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || \
			c == 'u' || c == 'f' || c == 'g' || c == 'd');
}

static void	for_bigr(t_dir **sub_lt, char **sub_dic, t_dir *only, char *dic)
{
	char	*temp;

	*sub_lt = NULL;
	*sub_dic = ft_strjoin(dic, "/");
	temp = *sub_dic;
	*sub_dic = ft_strjoin(temp, only->name);
	free(temp);
}

void	put_bigr(char *dic, int winsize, t_dir *only_dir, t_index *index)
{
	DIR		*sub_dp;
	char	*sub_dic;
	t_dir	*sub_lt;

	for_bigr(&sub_lt, &sub_dic, only_dir, dic);
	sub_dp = opendir((const char *)sub_dic);
	if (sub_dp)
	{
	get_dirlt(&sub_lt, sub_dp, sub_dic, index->flags);
	sort_rev_list(&sub_lt, index->flags, 'n');
	ft_printf("\n%s:\n", sub_dic);
	put_list(sub_lt, index, winsize);
	if (inclu_dir(sub_lt))
	{
		while (sub_lt)
		{
			if (sub_lt->file)
				put_bigr(sub_dic, winsize, sub_lt, index);
			sub_lt = sub_lt->next;
		}
	}
	closedir(sub_dp);
	}
	else
		perror("open directory failed");
}

static	void	for_eachdic(t_dir *only, int win, t_dir *dir_lt, t_index *dex)
{
		while (dir_lt)
		{
			if (dir_lt->file)
				put_bigr(only->name, win, dir_lt, dex);
			dir_lt = dir_lt->next;
		}
}

void			eachdic(t_dir *only_dir, int winsize, t_index *dex)
{
	DIR		*dp;
	t_dir	*dir_lt;

	dir_lt = NULL;
	if (dex->i)
		ft_printf("\n");
	if (dex->j)
		ft_printf("%s:\n", only_dir->name);
	if ((dp = opendir((const char *)only_dir->name)))
	{
	get_dirlt(&dir_lt, dp, only_dir->name, dex->flags);
	sort_rev_list(&dir_lt, dex->flags, 'k');
	put_list(dir_lt, dex, winsize);
	if (ft_strchr(dex->flags, 'R') && inclu_dir(dir_lt))
		for_eachdic(only_dir, winsize, dir_lt, dex);
	dex->i = 1;
	dex->j = 1;
	closedir(dp);
	}
	else
		perror("open directory failed");
}
