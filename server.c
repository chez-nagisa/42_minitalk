/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:27:38 by marvin            #+#    #+#             */
/*   Updated: 2025/03/25 18:34:04 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_receive_buffer g_recv_buffer; //受信データを保存するグローバル変数

static void	signal_handler(int signum, siginfo_t *info,
		void *ucontext __attribute__((unused)))
{
	if (g_recv_buffer.bit_count == 0)
		// bit_count == 0 の場合、新しい文字の受信を開始するため current_byte をリセット
		g_recv_buffer.current_byte = 0;
	g_recv_buffer.client_pid = info->si_pid;
	//クライアントの PID を取得し、g_recv_buffer.client_pid に保存
	if (signum == SIGUSR1)
		g_recv_buffer.current_byte = (g_recv_buffer.current_byte << 1) + BIT_0;
	if (signum == SIGUSR2)
		g_recv_buffer.current_byte = (g_recv_buffer.current_byte << 1) + BIT_1;
	if (++g_recv_buffer.bit_count == 8) // 8bit溜まったら
	{
		//標準出力のファイル番号 = STDOUT_FILENO(standard output file no(number))
		ft_putchar_fd(g_recv_buffer.current_byte, STDOUT_FILENO);
	}
}

int	main(void)
{
	struct sigaction sa;
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);

	sa.sa_flags = SA_SIGINFO;
	//簡単なsa_handlerと詳細なsa_sigactionのどちらかを選択。今回は詳細情報付きのsigaction
	sa.sa_sigaction = signal_handler; // signal_handler関数をシグナルハンドラーに設定。

	sigemptyset(&sa.sa_mask); // sa_maskを空のシグナルセットにする。つまり、何もブロックしない。
	sigaction(SIG_ACK, &sa, NULL);
	// SIGUSR1のシグナルを受け取ったときに、指定したシグナルハンドラー (sa) を実行する設定
	sigaction(SIG_NACK, &sa, NULL);
	//前のシグナル設定を保存しないなら NULL、保存して後で戻したいなら oldact を使う

	g_recv_buffer.bit_count = 0; //初期化

	while (g_recv_buffer.bit_count || pause())
	//ビットが 0 の場合のみ pause() でシグナルを待ち、すでに受信したビットがある場合はpause()を実行せず処理を続行する
	{
		if (0 < g_recv_buffer.bit_count && usleep(BIT_RECEIVE_DELAY)
			&& g_recv_buffer.bit_count < 8) // 受信が途中で止まった場合、エラーとする
			g_recv_buffer.bit_count = 9;

		if (g_recv_buffer.bit_count == 8 || usleep(SIG_RECEIVE_TIMEOUT) == 0)
		// 8ビット揃ったor一定時間待っても次が来なかったら処理を進める
		{
			if (g_recv_buffer.bit_count == 8)
				kill(g_recv_buffer.client_pid, SIG_ACK);
			else
				kill(g_recv_buffer.client_pid, SIG_NACK);
		}
	}
}