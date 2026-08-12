/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coder_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/11 14:44:37 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/12 12:21:58 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coder.h"
#include <stdio.h>

void	*coder_get_dongle(void *c)
{
	t_coder	*coder;

	coder = (t_coder *)c;
	printf("coder_id: %d\n", coder->coder_id);
	return (0);
}
