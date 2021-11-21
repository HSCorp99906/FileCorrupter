#include "../include/aes.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return -1;
    }

    if (access(argv[1], F_OK) != 0) {  // If file access != F_OK.
        printf("ERROR: Cannot Access %s\n", argv[1]);
        return -1;
    }

    char key[100] = "39792442264528482B4D6251655468576D5A7134743777217A25432A462D4A40";  // 256-bit key.
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key); 

    FILE* fp = fopen(argv[1], "r");

    size_t bufsize = 5;
    size_t writeBufSize = 30;

    char* lineBuf = (char*)malloc(sizeof(char) * bufsize);  
    char writeBuf[10000];

    fseek(fp, 0, SEEK_END);
    size_t lines = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int x = 0;

    for (int i = 0; i < lines; ++i) {
        AES_ECB_encrypt(&ctx, lineBuf);
        writeBuf[i] = lineBuf[i];
    }

    char command[256];

    sprintf(command, "> %s", argv[1]);

    system(command);

    fp = fopen(argv[1], "w");

    for (int i = 0; i < lines; ++i) {
        fputs(writeBuf, fp);
    }

    printf("Your file is now corrupted! :D\n");

    fclose(fp);
    free(lineBuf);
} 
