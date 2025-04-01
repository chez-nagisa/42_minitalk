/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:27:38 by marvin            #+#    #+#             */
/*   Updated: 2025/04/01 17:36:43 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_receive_buffer g_recv_buffer; //受信データを保存するグローバル変数

static void	signal_handler(int signum, siginfo_t *info,
		void *ucontext __attribute__((unused)))
{
	if (g_recv_buffer.bit_count == 0)
		g_recv_buffer.current_byte = 0;
	g_recv_buffer.client_pid = info->si_pid;
	if (signum == SIGUSR1)
		g_recv_buffer.current_byte = (g_recv_buffer.current_byte << 1) + BIT_0;
	if (signum == SIGUSR2)
		g_recv_buffer.current_byte = (g_recv_buffer.current_byte << 1) + BIT_1;
	if (++g_recv_buffer.bit_count == 8)
		ft_putchar_fd(g_recv_buffer.current_byte, STDOUT_FILENO);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_recv_buffer.bit_count = 0;
	while (g_recv_buffer.bit_count || pause())
	{
		if (0 < g_recv_buffer.bit_count && usleep(BIT_RECEIVE_DELAY)
			&& g_recv_buffer.bit_count < 8)
			g_recv_buffer.bit_count = 9;
		if (g_recv_buffer.bit_count == 8 || usleep(SIG_RECEIVE_TIMEOUT) == 0)
		{
			if (g_recv_buffer.bit_count == 8)
				kill(g_recv_buffer.client_pid, SIG_ACK);
			else
				kill(g_recv_buffer.client_pid, SIG_NACK);
			g_recv_buffer.bit_count = 0;
		}
	}
	return (0);
}
