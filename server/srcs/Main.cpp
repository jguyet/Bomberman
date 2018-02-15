/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 00:09:41 by frmarinh          #+#    #+#             */
/*   Updated: 2018/02/15 00:09:48 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"
#include "Server.hpp"

int		main(int argc, char **argv)
{
	try
	{
		Server server(8964);
		server.start();
	}
	catch (std::exception &e)
	{
		std::cerr << "Bomber server cant start: " << e.what() << std::endl;
	}
	return (0);
}
