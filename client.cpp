//
// Created by matt on 4/6/17.
//

#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <zconf.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>


struct sockaddr_in server;
struct addrinfo addr;
char host_buf[NI_MAXHOST];

using namespace std;

int main(int argc, char *argv[]) {
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd == -1) {
        return -1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(2239);

    if (inet_aton(argv[1], &server.sin_addr) <= 0) {
        return -1;
    }

    int res = connect(sd, (struct sockaddr *) &server, sizeof(server));

    if (res == -1)cout << "Error" << endl;


//    for (;;) {
    int size_of_str = 1;
    if (*argv[2] == 'm' && argc > 3)
    {
        size_of_str = atoi(argv[3]);
        char b[size_of_str+100];
        bzero(b, size_of_str+100);
        b[0] = *argv[2];
        b[1] = '-';
        b[2] = argv[3][0];
        b[3] = argv[3][1];
        b[4] = '-';
        int a = 0;
        int s = 4;
        for(int i = 0; i < size_of_str; i++ ){
            if(s < argc){
                if(a < strlen(argv[s])){
                    if(a != -1){
                b[i+5] = argv[s][a];}
                }
                else {
                    s +=1; a = -1;
                    b[i+5] = ' ';
                }
            }
            a++;
        }
        send(sd, b, size_of_str+100, 0);}
    else {send(sd, argv[2], strlen(argv[2]), 0);}
    cout << "Sent " << argv[2] << "\n";
    sleep(2);
    char buf[ size_of_str+100];
    bzero(buf,  size_of_str+100);
    int cc = recv(sd, buf,  size_of_str+100, 0);
    cout << "Server: " << buf << "\n";
    close(sd);

//    }
}

//g++ client.cpp
//./a.out 127.0.0.1 m 22 tdfkgjlj mgyifcvkj, jgjhv
