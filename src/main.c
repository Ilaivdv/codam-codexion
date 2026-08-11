/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/07 12:23:34 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/11 20:44:31 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/coder.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	// t_coder		*coders;
	t_ctx		ctx;
	ssize_t		i;

	if (argc != 9 || get_args(argv, &ctx) || ctx.coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'\n");
		return (1);
	}
	threads = malloc(sizeof(pthread_t) * ctx.coders);
	if (!threads)
		return (2);
	i = -1;
	while (i++ < (ctx.coders - 1))
		if (pthread_create(&threads[i], NULL, &init_coder, NULL))
			return (2);
	i = -1;
	while (i++ < (ctx.coders - 1))
		if (pthread_join(threads[i], NULL))
			return (3);
	free(threads);
	return (0);
}
