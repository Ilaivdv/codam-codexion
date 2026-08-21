/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongles.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:42:06 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/21 15:09:02 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/types.h>
#include <stdint.h>

#include <stdio.h>

static void	heap_push(t_coder *coder, t_dongle *dongle);

// TODO queues and mutexes can probably go here
int	init_dongles(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
	{
		if (pthread_mutex_init(&(ctx->dongles + i)->mutex, NULL))
			return (1);
		ctx->dongles[i].queue_size = 0;
	}
	return (0);
}

int	request_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	pthread_mutex_lock(&coder->dongles[1]->mutex);
	heap_push(coder, coder->dongles[0]);
	heap_push(coder, coder->dongles[1]);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	pthread_mutex_unlock(&coder->dongles[1]->mutex);
	return (0);
}

static void	heap_push(t_coder *coder, t_dongle *dongle)
{
	dongle->queue_size += 1;
	if (dongle->queue_size == 1)
		dongle->queue[0] = (t_queue){.cmp = get_cmp(coder),
			.coder = coder};
	else
	{
		if (dongle->queue[0].cmp < get_cmp(coder))
			dongle->queue[1] = (t_queue){.cmp = get_cmp(coder),
				.coder = coder};
		else
		{
			dongle->queue[1] = dongle->queue[0];
			dongle->queue[0] = (t_queue){.cmp = get_cmp(coder),
				.coder = coder};
		}
	}
}
