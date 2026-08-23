/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongle_utils.c                                    :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/21 16:06:22 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 18:18:16 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/types.h>

// #include <stdio.h>

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

static void	dongle_heapify(t_dongle *dongle)
{
	t_queue	tmp;

	dongle->queue[0].cmp = get_cmp(dongle->queue[0].coder);
	dongle->queue[1].cmp = get_cmp(dongle->queue[1].coder);
	if (dongle->queue[1].cmp < dongle->queue[0].cmp)
	{
		tmp = dongle->queue[0];
		dongle->queue[0] = dongle->queue[1];
		dongle->queue[1] = tmp;
	}
}

void	dongle_heap_push(t_coder *coder, t_dongle *dongle)
{
	dongle->queue_size++;
	if (dongle->queue_size == 1)
		dongle->queue[0] = (t_queue){.cmp = get_cmp(coder),
			.id = coder->id, .coder = coder};
	else
	{
		if (dongle->queue[0].cmp < get_cmp(coder))
			dongle->queue[1] = (t_queue){.cmp = get_cmp(coder),
				.id = coder->id, .coder = coder};
		else
		{
			dongle->queue[1] = dongle->queue[0];
			dongle->queue[0] = (t_queue){.cmp = get_cmp(coder),
				.id = coder->id, .coder = coder};
		}
		if (coder->ctx->params->scheduler == EDF)
			dongle_heapify(dongle);
	}
	// DEBUG
	// printf("coder %d queue: id %d %ld, id %d %ld\n", coder->id, dongle->queue[0].id,
	// 		dongle->queue[0].cmp, dongle->queue[1].id, dongle->queue[1].cmp);
}

void	dongle_heap_pop(t_dongle *dongle)
{
	dongle->queue[0] = dongle->queue[1];
	dongle->queue[1] = (t_queue){.cmp = 0, .id = 0};
	dongle->queue_size--;
}
