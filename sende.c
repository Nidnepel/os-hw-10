#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void transBit(int receiver_pid, int bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    } else {
        kill(receiver_pid, SIGUSR2);
    }
    sleep(1);
}

int main() {
    printf("Трансмиттер PID: %d\n", getpid());

    printf("Введите PID получателя: ");
    int recv_pid;
    scanf("%d", &recv_pid);

    printf("Введите число для посылки: ");
    int num_to_send;
    scanf("%d", &num_to_send);

    for (int i = 0; i < (5<<1); ++i) {
        transBit(recv_pid, (num_to_send >> i) & 1);
    }

    return 0;
}
