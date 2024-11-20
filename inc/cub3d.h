/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:09:30 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:54:47 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <math.h>
# define SPD 0.07
# define SENSI 2
# define SENSI_MOUSE 4
# define NO "NO "
# define SO "SO "
# define WE "WE "
# define EA "EA "
# define RA 0.0174533
# define PI 3.1415926535
# define N -1.57079632679
# define S  1.57079632679
# define W  3.1415926535
# define E  0
# define GRS 0x808080FF
# define GRN 0x00FF00FF
# define BLC 0xFFFFFFFF
# define RG  0xFF0000FF
# define FOV 1.15192
# define X 1080
# define Y 720

typedef struct s_p
{
	float	n_py; // prochain y par rapport au joueur et son angle
	float	n_px; // prochain x par rapport au joueur et son angle
	float	adj; //cote adjacent
	float	opp; //cote oppose
	float	hx; //hypothenuse du prochain x
	float	hy; //hypothenuse du prochain y
	float	px; //position y du joueur
	float	py; //positon y du joueur
	float	pan; //angle du joueur
}			t_p;

typedef struct s_color
{
	long	floor;
	long	ceiling;
	char	*no; //texture nord
	char	*so; //texture sud
	char	*we; //texture ouest
	char	*ea; //texture est
}				t_color;

typedef struct s_png
{
	mlx_texture_t	*text;
	unsigned long	**tabh;
}				t_png;

typedef struct s_dta
{
	void			*img;
	t_p				*p; //structure du joueur
	mlx_t			*mlx;
	t_color			*clr;
	t_png			**png;
	mlx_mousefunc	*mousefunc;
	int32_t			mousex;
	int32_t			mousey;
	int				maplen;
	int				wx; //si le mur toucher par un rayon est un x alors wx = 1
	int				wy; //si le mur toucher par un rayon est un y alors wy = 1
	int				wall_height; // taille du mur
	int				err; //norminette
	char			**map;
	char			**cub;
	char			ply; //player
	float			ran; //angle rayon
	float			len; //taille du rayon
	float			f;
}			t_dta;

//LIBFT//
void			*ft_memset(void *s, int c, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isdigit(char c);
int				ft_strlen(const char *str);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			**ft_split(char const *s, char c);

//UTILS//
void			ft_freetab(char **tab);
void			free_png(t_dta *dta);
void			ft_free_tabh(unsigned long **tabh);
int				err(char *str);
int				ft_tablen(char **tab);
int				dta_init(t_dta *dta, char *argv);
int				ft_strlcpy(char *dst, const char *src, int size);
int				ft_space(char *line);
char			*ft_suppr_space(char *line);

//MAP//

int				parser(t_dta *dta);
int				skip_space_err(char *s, int *j); // test
int				check_cub_parser(t_dta *dta, char **cub);
int				check_charset(char *map, char set);
int				check_texture(t_dta *dta, char *txt, char *line, char *coor);
int				stock_cub(t_dta *dta, char **map);
void			update_cub(int len_tab[2], char **cub);
int				check_cub(t_dta *dta, char **cub);
int				check_cub2(char **cub);
int				check_cub3(t_dta *dta, char **cub, int *i, int *j);
char			**ft_get_map(char *argv);

//MLX//
void			deal_key(void *param);
void			keybind(t_dta *dta, t_p *p, int key);
void			deal_mouse(double x, double y, void *param);
int				exit_window(t_dta *dta, char *msg);
void			open_or_close(mlx_key_data_t keydata, void *param);

//MINIMAP
int				ft_minimap(t_dta *dta, char **cub, float x, float y);
int				ft_wall(t_dta *dta, float x, float y, int c);
int				calcul_minimap(t_dta *dta);
int				find_max_len_x(char **cub);

//CLR AND TEXTURE
int				create_tab_hexa(t_png *png, char *path);
int				which_texture(t_dta *dta);
int				stock_texture(t_dta *dta, t_color *clr, char **map);
int				stock_color(t_color *clr, char **map);
int				hexa_color(char *map);
unsigned long	ft_texture(t_dta *dta, int wall_height, int j, t_png *png);
unsigned long	**alloc_tabh(t_png *png);
unsigned long	creatergba(int r, int g, int b, int a);

//RAYCAST//
void			ft_reload(t_dta *dta, t_p *p);
void			get_adj_and_opp(t_p *p, float ran);
int				ft_floor(t_dta *dta, float x, float y);
void			traceray(t_dta *dta, t_p *p);
int				iftouch_wall(t_dta *dta, t_p *p, int i);
int				touchwally(t_dta *dta, t_p *p);
int				touchwallx(t_dta *dta, t_p *p);
int				displaywall(t_dta *dta, int i, unsigned long clr);
int				displaydoor(t_dta *dta, int i, unsigned long clr);
int				display_ceilling_floor(t_dta *dta, t_color *clr);
float			find_len_ray(t_dta *dta, t_p *p, float ran);

//FREE
void			free_1(t_dta *dta);
void			free_2(t_dta *dta);
void			free_3(t_dta *dta);
void			free_4(t_dta *dta);

#endif
