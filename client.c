/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:33 by marvin            #+#    #+#             */
/*   Updated: 2025/04/02 14:06:19 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_signal_status;

static void	signal_handler(int signum)
{
	g_signal_status = signum;
	if (signum == SIG_NACK)
		ft_putstr_fd("timeout\n", STDERR_FILENO);
}

static void	send_byte(pid_t pid, uint8_t byte)
{
	unsigned int	bit_count;

	bit_count = sizeof(byte) * 8;
	while (bit_count--)
	{
		usleep(BIT_SEND_INTERVAL);
		if ((byte >> bit_count) & BIT_1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc < 3)
	{
		ft_putstr_fd("format error\n", STDERR_FILENO);
		return (-1);
	}
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	server_pid = ft_atoi(argv[1]);
	while (*argv[2])
	{
		send_byte(server_pid, *argv[2]);
		if (usleep(SERVER_RESPONSE_TIMEOUT) == 0)
		{
			ft_putstr_fd("server error\n", STDERR_FILENO);
			return (-1);
		}
		if (g_signal_status == SIG_ACK)
			argv[2]++;
	}
	ft_putstr_fd("success\n", STDOUT_FILENO);
	return (0);
}
