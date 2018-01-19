#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

static	void	init_fltype(struct dirent *dir, t_dir *add)
{
	add->file = 0;
	add->type = '-';
	if (dir->d_type == DT_BLK)
		add->type = 'b';
	else if (dir->d_type == DT_CHR)
		add->type = 'c';
	else if (dir->d_type == DT_DIR)
	{
		add->type = 'd';
		add->file = 1;
	}
	else if (dir->d_type == DT_FIFO)
		add->type = 'p';
	else if (dir->d_type == DT_LNK)
		add->type = 'l';
	else if (dir->d_type == DT_REG)
		add->type = '-';
	else if (dir->d_type == DT_SOCK)
		add->type = 's';
}

static	t_dir	*add_dirlt(t_dir *list, struct dirent *dir, char *dic)
{
	t_dir	*add;
	char	*path;
	char	*temp;
	int		i;

	path = ft_strjoin(dic, "/");
	temp = path;
	path = ft_strjoin(path, dir->d_name);
	free(temp);
	add = (t_dir *)malloc(sizeof(t_dir));
	init_fltype(dir, add);
	if (add->type == 'l')
		i = lstat(path, &(add->buf));
	else
		i = stat(path, &(add->buf));
	if (i != -1)
	{
	init_dictype(add);
	ft_strcpy(add->name, dir->d_name);
	add->path = path;
	add->na_len = ft_strlen(add->name);
	add->next = NULL;
	return (add_lst(list, add));
	}
	return (list);
}

void		get_dirlt(t_dir **list, DIR *dp, char *dic, char *flags)
{
	struct	dirent	*dir;

	errno = 0;
	while ((dir = readdir(dp)))
	{
		if (dir->d_name[0] == '.')
		{
			if (ft_strchr(flags, 'a') || ft_strchr(flags, 'f'))
				*list = add_dirlt(*list, dir, dic);
		}
		else
			*list = add_dirlt(*list, dir, dic);
	}
	if (errno)
		perror("read directory failed");
	errno = 0;
}


int			inclu_norfile(t_dir *list)
{
	while (list)
	{
		if (list->type != 'c' || list->type != 'b')
			return (1);
			list = list->next;
	}
	return (0);
}

int			inclu_dir(t_dir *list)
{
	while (list)
	{
		if (list->file == 1)
			return (1);
		list = list->next;
	}
	return (0);
}
