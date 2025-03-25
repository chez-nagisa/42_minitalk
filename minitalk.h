/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:30:25 by marvin            #+#    #+#             */
/*   Updated: 2025/03/25 18:12:25 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h> //sig_atomic_t
# include <stdint.h> //uint8_t

typedef struct s_receive_buffer
{
	pid_t	client_pid;
	uint8_t bit_count;                  //受信したビット数
	volatile sig_atomic_t current_byte; //受診中の1バイトデータ
}			t_receive_buffer;

typedef enum e_bit_value
{
	BIT_0 = 0,
	BIT_1 = 1
}			t_bit_value;

typedef enum e_signal_state
{
	SIG_ACK = SIGUSR1, //"Acknowledgment（受信確認）" の略
	SIG_NACK = SIGUSR2 //"Negative Acknowledgment（受信失敗）" の略
}			t_signal_state;

typedef enum e_signal_timing
{
	BIT_RECEIVE_DELAY = 15,                            // 1ビットを処理する時間（マイクロ秒）
	SIG_RECEIVE_TIMEOUT = 50,                          // シグナルの最大待機時間（マイクロ秒）
	BIT_SEND_INTERVAL = 50,                            // 各ビットの送信間隔（マイクロ秒）
	SERVER_RESPONSE_TIMEOUT = SIG_RECEIVE_TIMEOUT * 20
		// クライアントのPID応答を待つ時間（マイクロ秒）
}			t_signal_timing;
