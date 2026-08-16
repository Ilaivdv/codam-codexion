/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/16 15:20:31 by ivan-der     ###    #### orminette :(    */
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
