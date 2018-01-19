#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "ft_ls.h"

static	void	for_setflag(char **av)
{
	ft_printf("ft_ls: illegal option -- %c\n", **av);
	ft_printf("usage: ft_ls [-lRartufgd] [file ...]\n");
	exit(1);
}

int		set_flags_ls(char *flags, char **av)
{
	int		ct;
	int		i;

	ct = 1;
	i = 0;
	av++;
	ft_bzero(flags, 10);
	while (*av && (*av)[0] == '-' && (*av)[1])
	{
		(*av)++;
		while (**av)
		{
			if (is_flagls(**av))
			{
				if(!strchr(flags, **av))
					flags[i++] = *((*av)++);
			}
			else
				for_setflag(av);
		}
		(av)++;
		ct++;
	}
	return (ct);
}

static	void	init_main(t_index *dex, t_dir **only, t_dir **dic, char **av)
{
	errno = 0;
	dex->j = 0;
	dex->k = 0;
	*only = NULL;
	*dic = NULL;
	dex->i = set_flags_ls(dex->flags, av);
	av = av + dex->i;
	creat_dic(av, dic);
	dex->i = 0;
}

int		main(int ac, char **av)
{
	t_index	dex;
	t_dir	*dic;
	t_dir	*only_dir;
	struct	winsize w;

	(void)ac;
	ioctl(0,TIOCGWINSZ, &w);
	init_main(&dex, &only_dir, &dic, av);
	if (dic)
	{
		sort_rev_list(&dic, dex.flags, 'd');
		if (ft_strchr(dex.flags, 'd'))
			put_list(dic, &dex, w.ws_col);
		else
		{
			reini_dir(&dic, &only_dir, &dex);
			put_list(dic, &dex, w.ws_col);
			dex.k = 1;
			while (only_dir)
			{
				eachdic(only_dir, w.ws_col, &dex);
				only_dir = only_dir->next;
			}
		}
	}
	return (0);
}
