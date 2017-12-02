/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:27:40 by clanier           #+#    #+#             */
/*   Updated: 2017/12/01 20:39:49 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

# define TINY 2048
# define SMALL 4096
# define MMAP_PROT PROT_READ | PROT_WRITE
# define MMAP_FLAGS MAP_ANON | MAP_PRIVATE

typedef				struct s_malloc
{
	struct s_malloc	*next;
	struct s_malloc	*prev;
	bool			isFree;
	size_t			size;
}					t_malloc;

typedef				struct s_line
{
	void			*tiny;
	void			*small;
	t_malloc		*large;
	rlim_t			limit;
}					t_line;

typedef				struct s_page
{
	struct s_page	*next;
	struct s_page	*prev;
	void			*end;
	size_t			size;
	t_malloc		*first;
}					t_page;

t_line				line;

void				show_alloc_mem();
void				*set_malloc(size_t size, t_malloc **mem);
void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*find_pointer(void *ptr, void **page);

#endif
