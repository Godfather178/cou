#include <winsock2.h>
#include<stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE_MSG 1024

using namespace std;
int main()
{
     setlocale(LC_ALL, "rus");

    bool flag = false;
        cin >> flag;
        if(flag == true){
            ofstream file_history("history_server.txt", ios_base::trunc);
            struct sockaddr_in addr; // структура с адресом
            char buf [SIZE_MSG]; 		  // буфур для приема
            WSADATA wsa;            // Структура с информацией о WinSock
            SOCKET sock, listener;  // дескрипторы сокетов
            // Инициализация WinSock
            if (WSAStartup (MAKEWORD(2,2),&wsa) != 0) {
                printf ("Failed. Error Code : %d",WSAGetLastError());
                perror ("socket");
                exit (1);
            }
            // создаем сокет для входных подключений
            if  ((listener = socket (AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
                printf ("Could not create socket : %d" , WSAGetLastError ());
                perror ("socket");
                exit (1);
            }

            // Указываем параметры сервера
            addr.sin_family = AF_INET;
            addr.sin_port = htons (3425);
            addr.sin_addr.s_addr = htonl (INADDR_ANY);

            if (bind (listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror ("bind");
                exit (2);
            }

            listen (listener, 1); // очередь входных подключений

}
