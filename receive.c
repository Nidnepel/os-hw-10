#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int bitCount = 0;
volatile int receivedNumber = 0;

void FirstSigHandler(int) {
    bitCount++;
}

void SecondSigHandler(int) {
    receivedNumber |= (1 << (bitCount++));
}

int main() {
    struct sigaction act_sigusr1, act_sigusr2;
    act_sigusr1.sa_handler = FirstSigHandler;
    act_sigusr2.sa_handler = SecondSigHandler;
    sigemptyset(&act_sigusr1.sa_mask);
    sigemptyset(&act_sigusr2.sa_mask);
    act_sigusr1.sa_flags = 0;
    act_sigusr2.sa_flags = 0;
    if (sigaction(SIGUSR1, &act_sigusr1, NULL) < 0 || sigaction(SIGUSR2, &act_sigusr2, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    printf("PID получателя: %d\n", getpid());
    printf("Ожидание...\n");

    while (bitCount < 32) {
        pause();
    }
    printf("Полученное число: %d\n", receivedNumber);
    return 0;
}