/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:26:18 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/20 09:35:38 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/coder.h"
#include <stdlib.h>

int	init_coders(t_ctx *ctx)
{
	ssize_t	i;

	ctx->coders = malloc(sizeof(t_coder) * ctx->params->n_coders);
	ctx->dongles = malloc(sizeof(t_dongle) * ctx->params->n_coders);
	if (!ctx->coders || !ctx->dongles)
		return (1);
	init_dongles(ctx);
	i = -1;
	while (i++ < (ctx->params->n_coders - 1))
	{
		ctx->coders[i] = (t_coder){.id = i,
			.dongles = {ctx->dongles + i,
			ctx->dongles + ((i + 1) % ctx->params->n_coders)}};
	}
	// TODO init_threads function here
	return (0);
}

