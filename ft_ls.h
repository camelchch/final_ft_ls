#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include <dirent.h>
#include "libft/libft.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BGYELLOW "\033[7;33m"
#define BGBLUE "\033[7;34m"
#define BLUE "\033[1;36m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"

typedef	struct	s_lformat
{
	char	*owner;
	char	*group;
	char	permi[10];
	char	*change_tm;
	int		major;
	int		minor;
}				t_lformat;

typedef	struct	s_max
{
	int		m_link;
	int		m_owner;
	int		m_group;
	int		m_size;
	int		m_maj;
	int		m_min;
	int		total;
}				t_max;

typedef	struct	s_dir
{
	struct stat buf;
	char		name[256];
	int			na_len;
	int			file;
	char		type;
	char		*path;
	t_lformat	long_f;
	struct s_dir *next;
}				t_dir;

typedef	struct	s_win
{
	int		max;
	int		line;
	int		col;
	int		ct_lt;
}				t_win;

typedef	struct	s_index
{
	char	flags[10];
	int		i;
	int		j;
	int		k;
}				t_index;

typedef	struct	s_ct
{
	int		i;
	int		j;
	int		ct;
}				t_ct;

void	color_reset(void);
void	blue(void);
void	put_dirname(t_dir *list, int max);
void	del_onelt(t_dir **list, t_dir *onelt);
void	get_dirlt(t_dir **list, DIR *sub_dp, char *sub_dic, char *flags);
t_dir	*add_lst(t_dir *list, t_dir *add);
void	sort_rev_list(t_dir **list, char *flags, char c);
void	init_lformat(t_dir *list, t_max *max, char *flags);
int		inclu_cbfile(t_dir *list);
int		inclu_dir(t_dir *list);
int		inclu_norfile(t_dir *list);
void	init_cbfile(t_dir *list, t_max *max);
void	init_dictype(t_dir *add);
void	reini_dir(t_dir **dic, t_dir **only_dir, t_index *dex);
void	creat_dic(char **av, t_dir **dic);
void	eachdic(t_dir *only_dir, int winsize, t_index *dex);
void	put_bigr(char *dic, int winsize, t_dir *only_dir, t_index *index);
int		is_flagls(char c);
void	put_list(t_dir *list, t_index *index, int winsize);
#endif
