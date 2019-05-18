# NO SUPPORT ANYMORE #

Autor: Raique

### ENGLISH: ###
### ABOUT IPFORWARD FILE ####
#### knowing an external LAN attack is going to be necessary to set you IP Forward Settings on, a very basic but efficient script has been made and i've made it available to download. ####
1 -> give it execution's permission: chmod +x ipforward
2 -> execute: sudo ./ipforward (if you are at the same directory of the file) otherwise, sudo /path/to/ipforward_file

## About cliente_rvshell.py ##
1 -> once in test, use it as default, in real attacks scenarios, change the '.py' suffix to '.pyw', enabling the python interpreter
to know this script will not run under console/terminal environment, i.e., will not prompt any kind of I/O...

2 -> a .exe (windows) version of this script is possible making use of the cx_Freeze lib, creating a real executable from the python script. platform dependent

3 -> updates/patches will be provided sporadically (or maybe nevermore, since i am working in more advanced stuffs ), the server.py file must be used along with cliente_rvshell.py, once using both ( cliente node, server node ) interactively,
will enable you to enjoy all of resources available.

## ABOUT server.py ##

1 -> from the succesfully connection established on, writing "h" ( no quotes ), will provide you the help panel.


## ABOUT wintroj.cpp ##

1 -> compile with: g++ -o yourfilename.exe wintroj.cpp -lws2_32 --machine=windows

2 -> the above compilation should only be used with you are already within a windows machine, otherwise, you need to cross compile (i.e., from linux to windows )

NOTES: in linux, you need to install `*-mingw32-gcc(g++)`( * = 1686 or w86_64 ) (respectively, 32 bits and 64 bits machine)

32 bit machine compilation:
username@distro:~$ 1686-w64-mingw32-g++ -o example.exe wintroj.cpp -l ws2_32 --machine=windows

64 bit machine:
username@distro:~$ w86_64-w64-mingw32-g++ -o example.exe wintroj.cpp -l ws232 --machine=windows

OR:

username@distro:~$ make 32 (for 32 bits)
username@distro:~$ make 64 (for 64 bits)


3 -> its a raw version, i am working on other projects, anymore supporting this one.

4 -> when in use of wintroj on the client-side, highly recommended to make the server connection through netcat, once netcat is very simple and high quality.

### trojan.cpp (linux) ###

1 -> compilation: g++ -o exemplo trojan.cpp

2 -> trojan along with netcat will give you full control over the target's terminal.

DISCLAIMER:
NO WARRANTY ABOUT THE FUNCTIONALITIES, I AM NOT RESPONSIBLE FOR ANY OF YOUR ACTS.

THANKS!

## PORTUGUÊS: ##
### SOBRE IPFORWARD FILE ####
# Visto que um ataque fora da LAN sera necesario o ipforward, um script foi disponibilizado, escrito em bash.
1-> de permissão de executavel a ele: chmod +x ipforward
2-> e execute-o: sudo ./ipforward (se voce estiver no mesmo diretorio que ele) ou sudo /diretorio/ipforward (se você não
estiver no mesmo diretorio que o script)

OPCIONAL 1-> crie em seu diretorio '~' um arquivo com o nome: .bash_aliases
         2 > Dentro do arquivo, escreva: alias ipf="sudo ~/ipforward"
         @@@isso vai fazer com que voce o execute-o de qualquer path, ja com privilegios sudo, sem tem que ficar indo ao diretorio do 
          arquivo toda vez que necessitar/desejar executa-lo.


### Sobre o cliente_rvshell.py
1-> quando em teste, usar-lo como padrao, em casos de ataques reais, mudar a extensão '.py' para '.pyw', fazendo com que o binario python reconheça que o prompt não deve ser executado.

2-> uma versão em .exe é possivel utilizando a biblioteca python cx_Freeze, gerando um executavel python a partir do script python. Plataforma dependente.

3-> atualizações serão feitas esporadicamente, o server.py deve ser usado juntamente como o cliente_rvshell.py, uma vez que ambos em combinação é possivel aproveitar todos os recursos do exploit.

5-> para que o target machine (windows) execute o programa sempre que iniciar/reiniciar, mova-o para a pasta: "C:\Users\Username\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup",
caso admin: "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp"

4-> trabalhando em uma versao com privillege escalation.


### SOBRE server.py ####

1-> a partir da conexão realizada com sucesso, escreva "h" sem aspas, ira disponibilizar o help, contendo algumas funções interessantes do exploit, dos comandos possiveis, como screenshot, pops up internet na target machine...

# wintroj.cpp

1-> compilar com: g++ -o seuarquivo.exe wintroj.cpp -l ws2_32 --machine=windows

2-> compilção acima é caso você ja esteja dentro da maquina windows, para cross-compiling(i.e., compilar um programa para windows, estando na maquina linux, por exemplo.) use:

32 bit target machine:
username@distro:~$ 1686-w64-mingw32-g++ -o exemplo.exe wintroj.cpp -l ws2_32 --machine=windows

64 bit target machine:
username@distro:~$ w86_64-w64-mingw32-g++ -o exemplo.exe wintroj.cpp -l ws2_32 --machine=windows

OR:

## username@distro:~$ make 32 (for 32 bits)
## username@distro:~$ make 64 (for 64 bits)


3-> versão bem raw, estou trabalhando em outro, talvez mais para frente adiciono mais coisa para ele

4-> recomendado que o servidor no qual ele faça conexão seja o netcat, uma vez que o netcat é muito simples e de alta qualidade

# trojan.cpp (versão linux)

1-> compilação simples: g++ -o exemplo trojan.cpp

2-> usar juntamente com o netcat vai te dar total controle sobre o terminal do target.


valeu!

AVISO LEGAL:
NENHUMA GARANTIA SOBRE AS FUNCIONALIDADES, NÃO ME RESPONSABILIZO POR NADA.

toda ajuda ou melhora é bem vinda, uma vez que tem muita galera com ideias melhores e mais sofisticadas!
