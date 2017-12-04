/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:27:40 by clanier           #+#    #+#             */
/*   Updated: 2017/12/04 17:22:20 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>

# define ENV_SHOW_FREE	0b001
# define ENV_SCRIBBLE	0b010
# define ENV_VERBOSE	0b100

# define TINY 1024
# define SMALL 4096
# define MMAP_PROT PROT_READ | PROT_WRITE
# define MMAP_FLAGS MAP_ANON | MAP_PRIVATE

typedef struct			s_malloc
{
	struct s_malloc		*next;
	struct s_malloc		*prev;
	bool				is_free;
	size_t				size;
}						t_malloc;

typedef struct			s_line
{
	void				*tiny;
	void				*small;
	unsigned int		env;
	t_malloc			*large;
	rlim_t				limit;
	size_t				old_size;
}						t_line;

typedef struct			s_page
{
	struct s_page		*next;
	struct s_page		*prev;
	void				*end;
	size_t				size;
	t_malloc			*first;
}						t_page;

t_line					g_line;
extern pthread_mutex_t	g_mutex;

double					ft_pow(double n, int exp);
bool					is_empty(t_page *page);
void					*ft_memset(void *s, int c, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					free_malloc(t_malloc *mem);
void					free_page(void **page, char page_type);
void					*find_pointer(void *ptr, void **page);
void					free_memory(t_malloc *mem, void **page, char page_type);
void					ft_free(void *ptr);
void					*init_page(size_t size, void **page, t_page *prev);
int						init(void);
void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);
void					*calloc(size_t count, size_t size);
int						create_page(size_t alloc_max,
						void **page, t_page *prev);
void					*set_malloc(size_t size, t_malloc **mem);
void					*get_free_memory(size_t size,
						void **page, size_t size_max);
void					*large_malloc(size_t size);
void					*ft_malloc(size_t size);
int						ft_strlen(char *s);
int						ft_nbrlen_base(size_t x, int base);
void					ft_putstr(char *s);
void					ft_putchar(char c);
void					ft_putnbr_base(size_t x, int base);
void					*move_data(t_malloc *src, void *dest, size_t size);
void					*realloc_memory(void *ptr, size_t size, char page_type);
void					*ft_realloc(void *ptr, size_t size);
void					print_header(char *page_name, size_t first);
void					print_total(size_t total);
void					print_malloc(size_t from, size_t size);
size_t					show_page(t_page *page, char *page_name);
void					ft_show_alloc_mem(void);

#endif
