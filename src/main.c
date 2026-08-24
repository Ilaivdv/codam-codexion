/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   main.c                                            :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:10:02 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/24 14:10:57 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_ctx		ctx;
	t_params	params;

	if (get_args(argc, argv, &params) || params.n_coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'\n");
		return (1);
	}
	ctx.params = &params;
	get_elapsed_time();
	pthread_mutex_init(&ctx.coder_action_mutex, NULL);
	pthread_create(&ctx.monitor_thread, NULL, &monitor_process, &ctx);
	init_coders(&ctx);
	pthread_join(ctx.monitor_thread, NULL);
	cleanup(&ctx);
	return (0);
}
