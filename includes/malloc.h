/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:27:40 by clanier           #+#    #+#             */
/*   Updated: 2017/10/01 00:14:46 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 2048
# define SMALL 4096
# define MMAP_PROT MMAP_READ MMAP_WRITE
# define MMAP_FLAGS MMAP_ANON MMAP_PRIVATE

# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>

void	*malloc(size_t size);

typedef			s_line
{
	void		*tiny;
	void		*small;
	t_malloc	*large;
	rlim_t		limit;
}				t_line;

typedef			s_malloc
{
	t_malloc	*next;
	t_malloc	*prev;
	bool		isFree;
	size_t		size;
}

typedef			s_page
{
	void		*next;
	void		*prev;
	void		*end;
	size_t		size;
	t_malloc	*first;
}				t_page;

#endif
