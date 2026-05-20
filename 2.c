#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (fork() == 0) { 
        message.msg_type = 1;
        printf("[Producer] Enter a message to send: ");
        scanf(" %s", message.msg_text);
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("[Producer] Message passed to queue.\n");
    } else { 
        wait(NULL);
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("[Consumer] Visually fetched from queue: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}