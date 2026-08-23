/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 18:14:05 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

int	coder_compile(t_coder *coder);

void	*action_process(void *c)
{
	t_coder				*coder;

	coder = (t_coder *)c;
	if (request_dongles(coder) || coder_compile(coder))
		return ((int *)1);
	// TODO debug and refactor action can possibly happen here

	return (0);
}

int	coder_compile(t_coder *coder)
{
	int64_t	end_time;

	print_action(coder, "is compiling");
	end_time = get_elapsed_time(false) + coder->ctx->params->compile_time;
	while (coder->ctx->process + 0 * usleep(UPDATE_TICKS))
		if (get_elapsed_time(false) >= end_time)
			return (0);
	return (1);
}
