/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   codexion.h                                        :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/15 17:04:47 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/26 11:32:56 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdbool.h>
# include <pthread.h>
# include <stdint.h>

# define MAX_THREADS 512
# define UPDATE_TICKS 500

# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define GREY "\e[0;90m"
# define COLOR_RESET "\e[0m"

typedef struct s_params	t_params;
typedef struct s_ctx	t_ctx;
typedef struct s_coder	t_coder;
typedef struct s_queue	t_queue;
typedef struct s_dongle	t_dongle;

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_params
{
	unsigned int	n_coders;
	unsigned int	burnout_time;
	unsigned int	compile_time;
	unsigned int	debug_time;
	unsigned int	refactor_time;
	unsigned int	max_compiles;
	unsigned int	dongle_cooldown;
	t_scheduler		scheduler;
}	t_params;

typedef struct s_ctx
{
	pthread_t		monitor_thread;
	pthread_mutex_t	process_mutex;
	pthread_mutex_t	coder_action_mutex;
	pthread_mutex_t	time_mutex;
	t_params		*params;
	bool			process;

	t_dongle		*dongles;
	t_coder			*coders;
}	t_ctx;

typedef struct s_coder
{
	t_ctx			*ctx;
	pthread_t		thread;
	int				id;
	unsigned int	compiles;
	t_dongle		*dongles[2];
	int64_t			deadline;
	pthread_mutex_t	deadline_mutex;
}	t_coder;

typedef struct s_queue
{
	int64_t	cmp;
	int		id;
	t_coder	*coder;
}	t_queue;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	int64_t			cooldown_time;
	bool			is_available;
	t_queue			queue[2];
	int				queue_size;
	pthread_mutex_t	queue_mutex;
}	t_dongle;

void	*monitor_process(void *ctx);
void	*action_process(void *c);
bool	get_process(t_ctx *ctx);
void	set_process(t_ctx *ctx, bool process);

int		init_coders(t_ctx *ctx);
void	print_action(t_coder *coder, char *msg, char *color);
int64_t	get_coder_deadline(t_coder *coder);
void	set_coder_deadline(t_coder *coder, int64_t deadline);

int		init_dongles(t_ctx *ctx);
int		request_dongles(t_coder *coder);
void	take_dongles(t_coder *coder);
void	release_dongles(t_coder *coder);
void	dongle_heapify(t_dongle *dongle);
void	dongle_heap_push(t_coder *coder, t_dongle *dongle, int64_t cmp);
void	dongle_heap_remove(t_dongle *dongle, int id);
bool	check_queue_front(t_dongle *dongle, int id);

void	cleanup(t_ctx *ctx);
int64_t	get_elapsed_time(t_ctx *ctx);
int		get_args(int argc, char **argv, t_params *params);
int64_t	get_cmp(t_coder *coder);

#endif
