/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongles.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:42:06 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/20 09:35:01 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/types.h>

// TODO queues and mutexes can probably go here
int	init_dongles(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;	
	while (i++ < (ctx->params->n_coders - 1))
	{
		pthread_mutex_init(&(ctx->dongles + i)->mutex, NULL);
		(ctx->dongles + i)->is_available = true;
	}
	return (0);
}
