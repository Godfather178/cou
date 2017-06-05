#include <winsock2.h>
#include<stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE_MSG 1024
using namespace std;

const char* first = "*";
const char* twice = "**";
const char* third = "***";


int main()
{
     setlocale(LC_ALL, "rus");
     cout << "*   - Удалить историю сообщений." << endl;
     cout << "**  - Запросить историю сообщений у собеседника." << endl;
     cout << "*** - Открыть файл с историей сообщений." << endl;
     cout << "        Client - 0 Server - 1" << endl;
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

            while(1)
                    {
                        sock = accept (listener, NULL, NULL); // принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
                        if(sock < 0) {
                            perror ("accept");
                            exit (3);
                        }
                        else{
                            closesocket(listener);
                        }

                        while (1){
                            recv (sock, buf, SIZE_MSG, 0);//чтение данных из сокета
                            if (stricmp("start_send_history_$Q@dhasjdhagd^@&$#!@", reinterpret_cast<const char*>(buf)) == 0){
                                file_history.close();
                                ifstream file_read("history_server.txt", ios_base::in);
                                memset(buf, 0, SIZE_MSG);
                                while(!file_read.getline(buf, SIZE_MSG).eof()){
                                    send (sock, buf, SIZE_MSG, 0);
                                    Sleep(20);
                                    memset(buf, 0, SIZE_MSG);
                                }
                                send (sock, "stop_send_history_df32*2h&#@^!#$hjgh2$#", SIZE_MSG, 0);
                                file_read.close();
                                file_history.open("history_server.txt", ios_base::app);
                                send (sock, "History send!", SIZE_MSG, 0);
                                continue;
                            }
                            file_history << "<< " << buf << endl;
                            cout << "<< " << buf << endl;
                            cout << ">> ";
                            file_history << ">> ";
                            memset(buf, 0, SIZE_MSG);
                            cin >> buf;
                            if (stricmp(first, reinterpret_cast<const char*>(buf)) == 0){
                                file_history.close();
                                file_history.open("history_server.txt", ios_base::trunc); // удиление содержимого файла
                                send (sock, "User delete history msg", SIZE_MSG, 0);
                                continue;
                            }
                            if (stricmp(twice, reinterpret_cast<const char*>(buf)) == 0){
                               send (sock, "start_send_history_$Q@dhasjdhagd^@&$#!@", SIZE_MSG, 0);
                               memset(buf, 0, SIZE_MSG);
                               while(1){
                                    recv (sock, buf, SIZE_MSG, 0);
                                    if(stricmp("stop_send_history_df32*2h&#@^!#$hjgh2$#", reinterpret_cast<const char*>(buf)) == 0){
                                        memset(buf, 0, SIZE_MSG);
                                        break;
                                    }
                                    file_history << buf << endl;
                                    memset(buf, 0, SIZE_MSG);
                               }
                               continue;
                            }
                            if (stricmp(third, reinterpret_cast<const char*>(buf)) == 0){
                                system("history_sever.txt");
                            }
                            file_history << buf << endl;
                            send (sock, buf, SIZE_MSG, 0);
                        }

                        cout << "Client disconnect!" << endl;
                        closesocket (sock); // закрываем сокет
                        file_history.close();
                    }
                }//end (if flag = server)
                else{
                    ofstream file_history("history_server.txt", ios_base::trunc);
                    char buf [SIZE_MSG]; 		  // буфур для приема
                    struct sockaddr_in addr; // структура с адресом

                    WSADATA wsa;        // Структура с информацией о WinSock
                    SOCKET sock;        // дескриптор сокета

                    // Инициализация WinSock
                    if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0) {
                        printf("Failed. Error Code : %d", WSAGetLastError ());
                        perror("socket");
                        exit(1);
                    }


                    // создаем сокет для входных подключений
                    if  ((sock = socket (AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
                        printf ("Could not create socket : %d" , WSAGetLastError ());
                        perror ("socket");
                        exit (1);
                    }

}
