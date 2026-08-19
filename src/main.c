/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   main.c                                            :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:10:02 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 22:31:45 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdbool.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_monitor	monitor;
	t_ctx		ctx;

	if (argc != 9 || get_args(argv, &ctx) || ctx.n_coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'\n");
		return (1);
	}
	init_coders(&monitor);
	// TODO cleanup function here, free and destroy mutexes
	return (0);
}
