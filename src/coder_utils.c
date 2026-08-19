/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:26:18 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 22:26:54 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/coder.h"
#include <stdlib.h>

int	init_coders(t_monitor *mntr)
{
	ssize_t		i;

	mntr->coders = malloc(sizeof(t_coder) * mntr->ctx->n_coders);
	mntr->dongles = malloc(sizeof(t_dongle) * mntr->ctx->n_coders);
	if (!mntr->coders || !mntr->dongles)
		return (1);
	i = -1;
	while (i++ < (mntr->ctx->n_coders - 1))
	{
		pthread_mutex_init(&(mntr->dongles + i)->mutex, NULL);
		(mntr->dongles + i)->is_available = true;
	}
	i = -1;
	while (i++ < (mntr->ctx->n_coders - 1))
	{
		mntr->coders[i] = (t_coder){.id = i,
			.dongles = {mntr->dongles + i,
			mntr->dongles + ((i + 1) % mntr->ctx->n_coders)}};
	}
	// TODO init_threads function here
	return (0);
}
