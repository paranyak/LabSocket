#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <zconf.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <chrono>
#include <functional>

using namespace std;


struct sockaddr_in server;
char buf[160000];


int main() {
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd == -1) {
        cout << "error creating socket :( " << endl;
        return -1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = htons(2239);

    int res = bind(sd, (struct sockaddr *) &server, sizeof(server));


    if (res == -1) {
        cout << "error binding :( " << endl;
        return -1;
    }

    listen(sd, 10);
    //Аргумент backlog дозволяє задати максимальну кiлькiсть
    //запитiв, що очiкуватимуть, поки код викличе accept()
    cout << "Connected :) " << endl;


    for (;;) {

        bzero(buf, 160000);
        buf[0] = 'Q';
        int psd = accept(sd, (struct sockaddr *) NULL, NULL);
        if(psd == -1){cout << "incorrect " << endl; return -1;}


        long cc = read(psd, buf, 160000);
        if (buf[0] != 'Q')printf("message:  %s\n", buf);
        buf[cc] = '0';
        buf[cc+1] = 0;

        char response[100];
        bzero(response, 100);
        if (buf[0] == 'h' && buf[1] == '0') {
            strncpy(response, "hello", 100);

        } else if (buf[0] == 'd' && buf[1] == '0') {
            auto end = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(end);
            strncpy(response, ctime(&now_c), 100);

        } else if (buf[0] == 't' && buf[1] == '0') {
            time_t current_time = time(&current_time);
            struct tm *lcltm = localtime(&current_time);
            int hour = lcltm->tm_hour;
            int min = lcltm->tm_min;
            int sec = lcltm->tm_sec;
            string tt = "Time " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec); //
            strncpy(response, tt.c_str(), 100);
        }else if (buf[0] == 'm' && buf[1] == '-'){
            string s(buf+2, buf+4);
            int size_s = atoi(s.c_str());
            if(size_s != 0){
            string resp(buf+5);
            strncpy(response, resp.c_str(), size_s+1);}
            else{
                strncpy(response, "You forget to enter size", 25);
            }
        }
        else{
            strncpy(response, "sorry, please type m (arguments : size of str and string)/ t / d / h", 100);
        }


        write(psd, response, strlen(response) + 1); //sizeof(buf)


    }

}