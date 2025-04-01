/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:30:25 by marvin            #+#    #+#             */
/*   Updated: 2025/04/01 18:44:55 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdint.h>

typedef struct s_receive_buffer
{
	pid_t					client_pid;
	uint8_t					bit_count;
	volatile sig_atomic_t	current_byte;
}							t_receive_buffer;

typedef enum e_bit_value
{
	BIT_0 = 0,
	BIT_1 = 1
}							t_bit_value;

typedef enum e_signal_state
{
	SIG_ACK = SIGUSR1,
	SIG_NACK = SIGUSR2
}							t_signal_state;

typedef enum e_signal_timing
{
	BIT_RECEIVE_DELAY = 100,   // 1ビットを処理する時間（マイクロ秒）
	SIG_RECEIVE_TIMEOUT = 210, // シグナルの最大待機時間（マイクロ秒）
	BIT_SEND_INTERVAL = 200,   // 各ビットの送信間隔（マイクロ秒）
	SERVER_RESPONSE_TIMEOUT = SIG_RECEIVE_TIMEOUT * 50
	// クライアントのPID応答を待つ時間（マイクロ秒）
}							t_signal_timing;

#endif