/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:09:33 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 13:09:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t g_signal_status; //シグナルを一時的に保管する変数

static void signal_handler(int signum)
{
    g_signal_status = signum; // 受信したシグナルをg_signal_statusに保存

    if(signum == SIG_NACK)  // シグナルがエラー（タイムアウト）の場合
        ft_putstr_fd("timeout\n", STDERR_FILENO); //エラー表示
}

static void send_byte(pid_t pid, uint8_t byte) //1バイト（8ビット）のデータを、ビット単位でサーバー（pid）に送信
{
    unsigned int bit_count = sizeof(byte) * 8; //bit_count は「あと何ビット送信するか」のカウンター。8を掛けてバイトからビットに変換

    while(bit_count--)
    {
        usleep(BIT_SEND_INTERVAL); //シグナルが連続して送信されると受信側が処理できなくなるため、数マイクロ秒待機する
        if((byte >> bit_count) & BIT_1) //最上位のビットから順に、プロセスにシグナルを送る
            kill(pid, SIG_ACK);
        else
            kill(pid, SIG_NACK);
    }
}

int main(int argc, char *argv[])
{
    pid_t server_pid;
    if(argc < 3)
    {
        ft_putstr_fd("format error\n", STDERR_FILENO);
        return(-1); //異常終了
    }

    signal(SIG_ACK, signal_handler);
    signal(SIG_NACK, signal_handler);

    server_pid = ft_atoi(argv[1]); //pid

    while(*argv[2])
    {
        send_byte(server_pid, *argv[2]);
        if(usleep(SERVER_RESPONSE_TIMEOUT) == 0) //0を返した場合タイムアウト
        {
            ft_putstr_fd("pid error\n", STDERR_FILENO);
            return(-1);
        }
        if(g_signal_status == SIG_ACK)
            argv[2]++;
    }
    ft_putstr_fd("success!\n", STDOUT_FILENO);
    return(0);
}