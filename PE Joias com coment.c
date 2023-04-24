#include <stdio.h>
#include <string.h>
#define TAM 99

typedef struct {
	int teto;//quant max possivel
	float valor, valorBonificar; //valor de 1 bonus e valor para receber bonus
}tBonus;

typedef struct {
	float vsbCompra;
	float vtCompra;
	int bonusNadicionado;
	int compraCanc;//1-sim, 0-nao
	tBonus bonus;
}tCompra;

typedef struct {
	char nome[50], cpf[12], telefone[15], email[30];
	int bonus;
	float tgCompras;//Apenas a parte que nao usou bonus
	tCompra uCompra;
}tCliente;


/*
Objetivo: Imprimir as opções do menu Principal e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuPrincipal(){
	int n;
	printf("1-Cliente\n2-Compra\n3-Bonus\n4-Relatorios\n0-Sair\n");
	scanf("%d", &n);
	return n;
}

/*
Objetivo: Imprimir as opções do menu Cliente e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuCliente(){
	int n;
	printf("1-Cadastrar\n2-Alterar\n3-Consultar\n4-Remover\n0-Sair\n");
	scanf("%d", &n);
	return n;
}

/*
Objetivo: Imprimir as opções do menu Compra e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuCompra(){
	int n;
	printf("1-Efetivar\n2-Cancelar\n0-Sair\n");
	scanf("%d", &n);
	return n;
}

/*
Objetivo: Imprimir as opções do menu Bonus e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuBonus(){
	int n;
	printf("1-Configurar\n2-Exibir\n0-Sair\n");
	scanf("%d", &n);
	return n;
}

/*
Objetivo: Imprimir as opções do menu Configurar e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuConfigurar(){
	int n;
	printf("1-Alterar teto\n2-Alterar valor do bonus\n3-Alterar valor para receber bonus\n0-Sair\n");
	scanf("%d", &n);
	return n;
	
}

/*
Objetivo: Imprimir as opções do menu Relatorios e ler o valor escolhido pelo usuario. Não possui parâmetros. Retorna
o valor escolhido pelo usuario.
*/
int menuRelatorios(){
	int n;
	printf("1-Listar clientes\n2-Listar bonus\n3-Listar cliente por compras\n0-Sair\n");
	scanf("%d", &n);
	return n;
}

/*
Objetivo: Procurar por um CPF. Parâmetros: Recebe um vetor do tipo tCliente(estrutura) para obter acesso
a ela, recebe um numero de cpf tipo char para ser procurado e recebe um valor quant inteiro
para obter a quantidade de clientes ja cadastrados. Retorna -1 se NAO achou esse cpf cadastrado ou 
o índice do cpf caso encontre.
*/
int procura(tCliente vetCliente[TAM], char cpf[12], int quant){
	int i;
	int achou = -1;
	for(i=0;i<quant;i++){
		if(strcmp(cpf, vetCliente[i].cpf)==0){
			achou = i;
			break;
		}
	}
	return achou;
}

/*
Objetivo: Cadastrar as informações de um cliente. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)
para obter acesso a ela e recebe um valor quant inteiro para obter a quantidade de clientes
ja cadastrados. Retorna 0 se ja existe um cpf cadastrado igual ao que foi tentado cadastrar ou retorna 
1 caso consiga realizar o cadastro.
*/
int cadastrar(tCliente vetCliente[TAM], int quant){
	int a;
	char testeCpf[12];
	printf("Qual o CPF?Digite:\n");
	scanf("%s", testeCpf);
	a = (procura(vetCliente, testeCpf, quant));
	if (a!=-1){
		printf("ERRO: CPF ja cadastrado.\n");
		return 0;
	}else{
		strcpy(vetCliente[quant].cpf, testeCpf);
		printf("Qual o nome?Digite:\n");
        scanf(" %[^\n]", vetCliente[quant].nome);
		printf("Qual o telefone?Digite:\n");
		scanf("%s", vetCliente[quant].telefone);
		printf("Qual o email?Digite:\n");
		scanf("%s", vetCliente[quant].email);
		vetCliente[quant].bonus = 0;
		vetCliente[quant].tgCompras = 0;
		printf("CLIENTE CADASTRADO!\n");
		return 1;
	}
	
}

/*
Objetivo: Alterar as informações de um cliente. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)
para obter acesso a ela e recebe um valor quant inteiro para obter a quantidade de clientes
ja cadastrados e poder procurar cpf. Não retorna nenhum valor.
*/
void alterar(tCliente vetCliente[TAM], int quant){
	char cpf[12], cpfA[12];
	int retorno, retornoA;
	int menuAltera;
	char nomeA[50], telefoneA[15], emailA[30];
	printf("Qual o CPF do cliente?\n");
	scanf("%s", cpf);
	retorno = procura(vetCliente,cpf,quant);
	if(retorno==-1){
		printf("Erro: CPF nao cadastrado.\n");
	}else{
		
        // retornoA = -1;
        do{
		printf("1-Alterar CPF\n2-Alterar nome\n3-Alterar telefone\n4-Alterar email\n0-Voltar ao menu Cliente\n");
		scanf("%d", &menuAltera);
		switch(menuAltera){
		case 1: printf("Qual o novo CPF?\n");
		        scanf("%s", cpfA);
		        retornoA = procura(vetCliente,cpfA,quant);
		        if (retornoA!=-1){
                   printf("ERRO: CPF ja cadastrado.\n");
				}else{
					strcpy(vetCliente[retorno].cpf, cpfA);
				}  
			break;
		case 2: printf("Qual o novo nome?\n");
		        scanf(" %[^\n]", nomeA);
		        strcpy(vetCliente[retorno].nome, nomeA);
			break;
		case 3: printf("Qual o novo telefone?\n");
		        scanf("%s", telefoneA);
		        strcpy(vetCliente[retorno].telefone, telefoneA);
			break;
		case 4: printf("Qual o novo email?\n");
		        scanf("%s", emailA);
		        strcpy(vetCliente[retorno].email, emailA);
			break;
		case 0: break;
		}
		}while(menuAltera!=0);
	}
	
}

/*
Objetivo: Consultar as informações de um cliente. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)
para obter acesso a ela e recebe um valor quant inteiro para obter a quantidade de clientes
ja cadastrados e poder procurar cpf. Não retorna nenhum valor.
*/
void consultar(tCliente vetCliente[TAM], int quant){
      char cpf[12];
      int retornoC;
      printf("Qual o CPF do cliente?\n");
	  scanf("%s", cpf);
      retornoC = procura(vetCliente,cpf,quant);
      	  if(retornoC==-1){
			printf("Erro: CPF nao cadastrado.\n");
  		  }else{
  		  	printf("Nome: %s\n", vetCliente[retornoC].nome);
  		  	printf("CPF: %s\n", vetCliente[retornoC].cpf);
  		  	printf("Telefone: %s\n", vetCliente[retornoC].telefone);
  		  	printf("Email: %s\n", vetCliente[retornoC].email);
  		  	printf("Bonus: %d\n", vetCliente[retornoC].bonus);
  		  	printf("Total em compras: %.2f\n", vetCliente[retornoC].tgCompras);
  		  	printf("Dados da sua ultima compra\n");
  		  	printf("Valor total da compra: %.2f\n", vetCliente[retornoC].uCompra.vtCompra);
  		  	printf("Valor da compra sem bonus: %.2f\n", vetCliente[retornoC].uCompra.vsbCompra);
  		  	printf("Compra cancelada: %d\n", vetCliente[retornoC].uCompra.compraCanc);
  		  	printf("Valor de 1 bonus: %.2f\n", vetCliente[retornoC].uCompra.bonus.valor);
  		  	printf("Teto: %d\n", vetCliente[retornoC].uCompra.bonus.teto);
  		  	printf("Valor para receber bonus: %.2f\n", vetCliente[retornoC].uCompra.bonus.valorBonificar);
          }
      
}

/*
Objetivo: Remover as informações de um cliente. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)
para obter acesso a ela e recebe um valor quant inteiro para obter a quantidade de clientes
ja cadastrados e poder procurar cpf. Retorna 0 se NAO existe um cpf cadastrado igual ao que foi tentado
remover ou retorna 0 caso o usuario decida NAO remover ou retorna 1 caso o usuario decida remover.
*/
int remover(tCliente vetCliente[TAM], int quant){
     int a, i;
     int duvida;
	char testeCpf[12];
	printf("Qual o CPF do cliente?Digite:\n");
	scanf("%s", testeCpf);
	a = (procura(vetCliente, testeCpf, quant));
	if (a==-1){
		printf("ERRO: CPF nao cadastrado.\n");
		   return 0;
	}else{
	     	printf("Nome: %s\n", vetCliente[a].nome);
  		  	printf("CPF: %s\n", vetCliente[a].cpf);
  		  	printf("Telefone: %s\n", vetCliente[a].telefone);
  		  	printf("Email: %s\n", vetCliente[a].email);
  		  	printf("Bonus: %d\n", vetCliente[a].bonus);
  		  	printf("Total em compras: %f\n", vetCliente[a].tgCompras);
  		  	printf("Tem certeza que deseja remover esse cliente[1-sim <outro valor>-nao]?\n");
  		  	scanf("%d", &duvida);
  		  	if(duvida!=1){
					printf("CADASTRO DO CLIENTE NAO EXCLUIDO!\n");
					return 0;
			}else{
				for(i=a+1;i<=quant;i++){
					strcpy(vetCliente[i-1].nome,vetCliente[i].nome);
					strcpy(vetCliente[i-1].cpf,vetCliente[i].cpf);
					strcpy(vetCliente[i-1].telefone,vetCliente[i].telefone);
					strcpy(vetCliente[i-1].email,vetCliente[i].email);
					vetCliente[i-1].bonus = vetCliente[i].bonus;
					vetCliente[i-1].tgCompras = vetCliente[i].tgCompras;
					
				}
				printf("CADASTRO DO CLIENTE EXCLUIDO\n");
					return 1;
			}
				
	}
}


/*
Objetivo: Realizar a efetivacao da compra de um cliente. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)
para obter acesso a ela, recebe um valor quant inteiro para obter a quantidade de clientes
ja cadastrados e poder procurar cpf e recebe uma estrutura do tipo tBonus declarada na função main para
obter acesso aos valores ja definidos de seus campos. Não retorna nenhum valor.
*/
void efetivar(tCliente vetCliente[TAM], int quant, tBonus bonusM){
	int e, respostaB, respostaP, calcularPontos, bonusS, aux=0;
	char testeCpf[12];
	float valorCb, vCompra, vPagamento, complemento, vCompraSemBonus;
	printf("Qual o CPF do cliente?\n");
	scanf("%s", testeCpf);
	e = (procura(vetCliente, testeCpf, quant));
	if (e==-1){
		printf("ERRO: CPF nao cadastrado.\n");
	}else{
		valorCb = vetCliente[e].bonus * bonusM.valor;
		printf("BONUS = %d. VALOR CORRESPONDENTE = R$ %.2f\n", vetCliente[e].bonus, valorCb);
		
		printf("Qual o valor da compra?R$\n");
	do{
	scanf("%f", &vCompra);
	  if(vCompra<0){
		  printf("Erro: valor negativo. Digite novamente:\n");
	  }
	}while(vCompra<0);
	
	vCompraSemBonus = vCompra;
	calcularPontos = 0;
	bonusS = 0;
	vetCliente[e].uCompra.bonusNadicionado = vetCliente[e].bonus;
	
	if(vetCliente[e].bonus!=0){
	  printf("Deseja utilizar seu bonus?[1-sim <outro valor>-nao]\n");
	  scanf("%d", &respostaB);
	   if(respostaB==1){

	  	    if(valorCb>=vCompra){
	  	    	//simulacao bonus
				bonusS = (valorCb - vCompra) / (bonusM.valor);
				vCompra = 0;
			}else{
				//simulacao bonus
				vCompra = vCompra - valorCb;
				bonusS = 0;
				calcularPontos = vCompra/(bonusM.valorBonificar);
			}
			 
			bonusS = bonusS + calcularPontos;
			
		  printf("BONUS ATUAL = %d. VALOR DA COMPRA ATUALIZADO = R$ %.2f\n", bonusS, vCompra);
		  aux = bonusS;
			 
	  }else{
	  	  if(vetCliente[e].bonus <= bonusM.teto){
	  	      calcularPontos = vCompra/(bonusM.valorBonificar);
		      aux = vetCliente[e].bonus + calcularPontos;
		      if(aux>bonusM.teto){
				 aux = bonusM.teto;
			  }
		  }else{
			
			if(vetCliente[e].bonus > bonusM.teto){
				aux = vetCliente[e].bonus;
			}
		  }
	  }
	}
     if(vetCliente[e].bonus==0){
		calcularPontos = vCompra/(bonusM.valorBonificar);
		aux = calcularPontos;
		if(aux>bonusM.teto){
				 aux = bonusM.teto;
		}
	 }
	
	
	 printf("Qual o valor do pagamento do cliente?R$\n");
	 do{
	  scanf("%f", &vPagamento);
	  if(vPagamento<0)
	  	printf("Erro: valor negativo. Digite novamente:\n");
	 }while(vPagamento<0);
	 
	 if(vPagamento<vCompra){
	 	do{
		 printf("Erro: Valor do pagamento inferior ao valor da compra. Deseja fornecer mais dinheiro? [1-sim <outro valor>-nao]:\n");
		 scanf("%d", &respostaP);
		 if(respostaP!=1){
			 printf("COMPRA NAO EFETIVADA. Valor devolvido ao cliente: R$ %.2f.\n", vPagamento);
			 break;
		 }else{
			 printf("Digite o valor adicional:\n");
			 scanf("%f", &complemento);
			 vPagamento = vPagamento + complemento;
		 }
        }while(vPagamento<vCompra);
	 }
	 if(vPagamento>=vCompra){
		 printf("TROCO = R$ %.2f\n", vPagamento - vCompra);
		 vetCliente[e].tgCompras = vetCliente[e].tgCompras + vCompra;
		 
		 vetCliente[e].bonus = aux;
		 
		 vetCliente[e].uCompra.vsbCompra = vCompra;
		 vetCliente[e].uCompra.vtCompra = vCompraSemBonus;
		 vetCliente[e].uCompra.compraCanc = 0;
		 vetCliente[e].uCompra.bonus.teto = bonusM.teto;
		 vetCliente[e].uCompra.bonus.valor = bonusM.valor;
		 vetCliente[e].uCompra.bonus.valorBonificar = bonusM.valorBonificar;
		 printf("COMPRA EFETIVADA!\n");
	 }
	
		
	}
}

/*
Objetivo: Realizar o cancelamento de uma compra de um cliente, podendo ser a ultima compra ou não.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor quant
inteiro para obter a quantidadede clientes ja cadastrados e poder procurar cpf e recebe uma 
estrutura do tipo tBonus declarada na função main para obter acesso aos valores ja definidos de seus
campos. Não retorna nenhum valor.
*/
void cancelar(tCliente vetCliente[TAM], int quant, tBonus bonusM){
	int c, respC, bonusU, bonusG, confirmarC, respV, bonusRet, valorBonusRV, temp, temp2;
	char testeCpf[12];
	float valorPagoCan;
	printf("Qual o CPF do cliente?\n");
	scanf("%s", testeCpf);
	c = (procura(vetCliente, testeCpf, quant));
	if (c==-1){
		printf("ERRO: CPF nao cadastrado.\n");
	}else{
		do{
		 printf("Qual compra deseja cancelar[1 - Ultima compra, 2 - Outra compra]?\n");
		 scanf("%d", &respC);
		}while(respC!=1 && respC!=2);
		
		if(respC==1){
			if(vetCliente[c].uCompra.compraCanc == 1){
				printf("ERRO: Ultima compra já cancelada!\n");
			}else{
				printf("Valor da compra: %.2f\n", vetCliente[c].uCompra.vtCompra);
				printf("Valor pago: %.2f\n", vetCliente[c].uCompra.vsbCompra);
				bonusU = (vetCliente[c].uCompra.vtCompra - vetCliente[c].uCompra.vsbCompra)/vetCliente[c].uCompra.bonus.valor;
				bonusG = vetCliente[c].uCompra.vsbCompra/vetCliente[c].uCompra.bonus.valorBonificar;
					
				if(bonusG>vetCliente[c].uCompra.bonus.teto){
					bonusG = vetCliente[c].uCompra.bonus.teto;
				}
				
				if(bonusG==vetCliente[c].uCompra.bonus.teto){
					bonusG = bonusG - vetCliente[c].uCompra.bonusNadicionado;
				}
				
				
                  temp = vetCliente[c].uCompra.bonusNadicionado;
				
				
				if(vetCliente[c].tgCompras<vetCliente[c].uCompra.vsbCompra){
					temp2 = 0;
				}else{
					temp2 = vetCliente[c].tgCompras - vetCliente[c].uCompra.vsbCompra;
				}
				
				
				
				printf("Bonus usados: %d Bonus ganhos: %d\n", bonusU, bonusG);
				printf("Tem certeza que deseja cancelar essa compra [1-sim <outro valor>-nao]?\n");
				scanf("%d", &confirmarC);
				
				 if(confirmarC!=1){
					 printf("COMPRA NAO CANCELADA!\n");
				 }else{
					 vetCliente[c].tgCompras = temp2;
					 vetCliente[c].bonus = temp;
					 vetCliente[c].uCompra.compraCanc = 1;
					 printf("COMPRA CANCELADA!\n");
				 }
				 
				 
			}
		}
		
		if(respC==2){
			printf("Qual o valor pago da compra a ser cancelada?\n");
			scanf("%f", &valorPagoCan);
			printf("Valor da compra: RS %.2f\n", valorPagoCan);
			bonusRet = valorPagoCan/bonusM.valorBonificar;
			printf("Bonus a ser retirado do cliente: %d\n", bonusRet);
			printf("Vendedor, deseja informar um valor menor de bonus? [1-sim <outro valor>-nao]?\n");
			scanf("%d", &respV);
			if(respV==1){
				do{
					printf("Digite o valor do bonus a ser retirado do cliente (menor ou igual a %d):\n", bonusRet);
					scanf("%d", &valorBonusRV);
				}while(valorBonusRV>bonusRet);
				bonusRet = valorBonusRV;
				
			}
			printf("Tem certeza que deseja cancelar essa compra [1-sim <outro valor>-nao]?\n");
			scanf("%d", &confirmarC);
				if(confirmarC!=1){
					printf("COMPRA NAO CANCELADA!\n");
				}else{
					
					if(bonusRet>=vetCliente[c].bonus){
						vetCliente[c].bonus = 0;
					}else{
						vetCliente[c].bonus = vetCliente[c].bonus - bonusRet;
					}
					
					vetCliente[c].tgCompras = vetCliente[c].tgCompras - valorPagoCan;
					printf("COMPRA CANCELADA\n");
				}
		}
		
		
	}
	
	
}


/*
Objetivo: Informar o bonus de um cliente e seu valor em real.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor quant
inteiro para obter a quantidadede clientes ja cadastrados e poder procurar cpf e recebe uma 
estrutura do tipo tBonus declarada na função main para obter acesso aos valores ja definidos de seus
campos. Não retorna nenhum valor.
*/
void exibir(tCliente vetCliente[TAM], int quant, tBonus bonusM){
	int e;
	float vCorresp;
	char testeCpf[12];
	printf("Qual o CPF do cliente?\n");
	scanf("%s", testeCpf);
	e = (procura(vetCliente, testeCpf, quant));
	if (e ==-1){
		printf("ERRO: CPF nao cadastrado.\n");
	}else{
		vCorresp = vetCliente[e].bonus * bonusM.valor;
		printf("BONUS = %.2d. VALOR CORRESPONDENTE = R$ %.2f.\n", vetCliente[e].bonus, vCorresp);
	}
    
	
}

/*
Objetivo: Recebe o valor que o usuario escolher no Menu Cliente, caso 1:chama a função cadastrar e
atualiza a  quantidade de clientes cadastrados, caso precise, caso 2: chama a função alterar, caso 3:
chama a função consultar e caso 4: chama a função remover e atualiza a  quantidade de clientes
cadastrados, caso um cliente seja removido.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um endereço
*quant inteiro que recebe o endereço da variável cont do main para atualizá-la, caso precise. Não
retorna nenhum valor.
*/
void cliente(tCliente vetCliente[TAM], int *quant){
	int ncliente;
	int resposta;
	int quantCliente = *quant;
	do{
		printf("MENU CLIENTE\n");
		ncliente = menuCliente();
	switch(ncliente){
	case 1: resposta = cadastrar(vetCliente, quantCliente);
	       if(resposta == 1){
			   *quant = *quant+1;
			    quantCliente = *quant;
		   }
		break;
	case 2: alterar(vetCliente, quantCliente);
		break;
	case 3: consultar(vetCliente, quantCliente);
		break;
	case 4: resposta = remover(vetCliente, quantCliente);
	        if(resposta == 1){
			   *quant = *quant-1;
			   quantCliente = *quant;
		   }  
		break;
	case 0: printf("Fim do menu\n");
		break;
	default: printf("Erro:Opcao invalida\n");
		break;
	}
	}while(ncliente!=0);
}

/*
Objetivo: Recebe o valor que o usuario escolher no Menu Compra, caso 1:chama a função efetivar e caso 2:
chama a função cancelar.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor
cont inteiro para obter a quantidade de clientes ja cadastrados e recebe uma 
estrutura do tipo tBonus declarada na função main para obter acesso aos valores definidos de seus
campos. Não retorna nenhum valor.
*/
void compra(tCliente vetCliente[TAM], int cont, tBonus bonusM){
	int ncompra;
	do{
		printf("MENU COMPRA\n");
		ncompra = menuCompra();
	switch(ncompra){
	case 1: efetivar(vetCliente, cont, bonusM);
		break;
	case 2: cancelar(vetCliente, cont, bonusM);
		break;
	case 0: printf("Fim do menu\n");
		break;
	default: printf("Erro:Opcao invalida\n");
		break;
	}
	}while(ncompra!=0);
}

/*
Objetivo: Recebe o valor que o usuario escolher no Menu Bonus, caso 1:Caso queira, o cliente pode mudar
o teto, o valor de 1 bonus ou o valor para receber bonus, dependendo do valor escolhido no menu
configurar bonus e caso 2: chama a função exibir.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor
quant inteiro para obter a quantidade de clientes ja cadastrados e recebe uma estrutura *bonusM do tipo
tBonus que recebe o endereço dessa estrutura do main para modificar os valores dos seus campos, caso o 
usuário queira. Não retorna nenhum valor.
*/
void bonus(tCliente vetCliente[TAM], int quant, tBonus *bonusM){
	int nbonus, nconfigurar;
	do{
		printf("MENU BONUS\n");
		nbonus = menuBonus();
	switch(nbonus){
	case 1: //configurar(bonusM);
        do{
	 
	 	 	 printf("MENU CONFIGURAR BONUS\n");
	 	 	 nconfigurar = menuConfigurar();
	 	 	 switch(nconfigurar){
	 	 	 case 1: //novoTeto(bonusM);
	 	 	            printf("Qual o novo valor do teto?\n");
						do{
							scanf("%d", &bonusM->teto);
							if(bonusM->teto<0){
			   	   	   	   	   	printf("Erro valor negativo. Digite novamente: \n");
							}
						}while(bonusM->teto<0);
				 break;
	 	 	 case 2: //novoVBonus(bonusM);
	 	 	         printf("Qual o novo valor de 1 bonus?\n");
				     do{
					 	 scanf("%f", &bonusM->valor);
							if(bonusM->valor<0){
								printf("Erro valor negativo. Digite novamente: \n");
							}
					 }while(bonusM->valor<0);
		 	 	 break;
	 	 	 case 3: //novoVBonificar(bonusM);
	 	 	         printf("Qual o novo valor para receber bonus?\n");
					 do{
						scanf("%f", &bonusM->valorBonificar);
							if(bonusM->valorBonificar<0){
								printf("Erro valor negativo. Digite novamente: \n");
							}
					}while(bonusM->valorBonificar<0);
		 	 	 break;
	 	 	 case 0:
		 	 	 break;
	 	 	 }
	 
	    }while(nconfigurar!=0);
		break;
	case 2: exibir(vetCliente, quant, *bonusM);
		break;
	case 0: printf("Fim do menu\n");
		break;
	default: printf("Erro:Opcao invalida\n");
		break;
	}
	}while(nbonus!=0);
}

/*
Objetivo: Listar dados de todos os cliente, menos a última compra.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela e recebe um valor
cont inteiro para obter a quantidade de clientes ja cadastrados. Não
retorna nenhum valor.
*/
void listarC(tCliente vetCliente[TAM], int cont){
	int i;
	printf("Dados de todos os clientes\n");
	for(i=0;i<cont;i++){
		printf("Dados do cliente %d:\n", i+1);
		printf("Nome: %s\n", vetCliente[i].nome);
		printf("CPF: %s\n", vetCliente[i].cpf);
		printf("Telefone: %s\n", vetCliente[i].telefone);
		printf("Email: %s\n", vetCliente[i].email);
		printf("Bonus: %d\n", vetCliente[i].bonus);
		printf("Total gasto em compras: %.2f\n\n", vetCliente[i].tgCompras);
		
	}
}

/*
Objetivo: Listar para todos os clientes o bônus e o valor correspondente ao bônus.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor
cont inteiro para obter a quantidade de clientes ja cadastrados e recebe uma 
estrutura do tipo tBonus declarada na função main para obter acesso aos valores ja definidos de seus
campos. Não retorna nenhum valor.
*/
void listarB(tCliente vetCliente[TAM], int cont, tBonus bonusM){
	int i;
	float vCorresp;
	printf("Lista de bonus de todos os clientes\n");
	for(i=0;i<cont;i++){
		printf("Bonus do cliente %d:\n", i+1);
		vCorresp = vetCliente[i].bonus * bonusM.valor;
		printf("BONUS = %d. VALOR CORRESPONDENTE = R$ %.2f.\n", vetCliente[i].bonus, vCorresp);
	}
}

/*
Objetivo: Listar os clientes que realizaram um valor total em compras inferior, superior ou igual a um
valor. Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela e recebe um valor
cont inteiro para obter a quantidade de clientes ja cadastrados. Não
retorna nenhum valor.
*/
void listarCpCompras(tCliente vetCliente[TAM], int cont){
	int i, resp=2;
	float valor;
	printf("Digite um valor desejado em compras para ser pesquisado:\n");
	scanf("%f", &valor);
	printf("Deseja as informacoes dos clientes com valor total (1 - maior, 0 - igual, -1 - menor) a esse valor?\n");
	scanf("%d", &resp);
	
	if(resp==1){
		for(i=0;i<cont;i++){
			if(vetCliente[i].tgCompras > valor){
			 printf("Dados do cliente %d:\n", i+1);
		     printf("Nome: %s\n", vetCliente[i].nome);
			 printf("CPF: %s\n", vetCliente[i].cpf);
			 printf("Telefone: %s\n", vetCliente[i].telefone);
			 printf("Email: %s\n", vetCliente[i].email);
			 printf("Bonus: %d\n", vetCliente[i].bonus);
			 printf("Total gasto em compras: %.2f\n\n", vetCliente[i].tgCompras);
			}
		}
	}
	
	if(resp==0){
		for(i=0;i<cont;i++){
			if(vetCliente[i].tgCompras == valor){
			 printf("Dados do cliente %d:\n", i+1);
		     printf("Nome: %s\n", vetCliente[i].nome);
			 printf("CPF: %s\n", vetCliente[i].cpf);
			 printf("Telefone: %s\n", vetCliente[i].telefone);
			 printf("Email: %s\n", vetCliente[i].email);
			 printf("Bonus: %d\n", vetCliente[i].bonus);
			 printf("Total gasto em compras: %.2f\n\n", vetCliente[i].tgCompras);
			}
		}
	}
	
	if(resp==-1){
		for(i=0;i<cont;i++){
			if(vetCliente[i].tgCompras < valor){
			 printf("Dados do cliente %d:\n", i+1);
		     printf("Nome: %s\n", vetCliente[i].nome);
			 printf("CPF: %s\n", vetCliente[i].cpf);
			 printf("Telefone: %s\n", vetCliente[i].telefone);
			 printf("Email: %s\n", vetCliente[i].email);
			 printf("Bonus: %d\n", vetCliente[i].bonus);
			 printf("Total gasto em compras: %.2f\n\n", vetCliente[i].tgCompras);
			}
		}
	}
	
	
}

/*
Objetivo: Recebe o valor que o usuario escolher no Menu Relatorios, caso 1:chama a função listarC, 
caso 2: chama a função listarB e caso 3: chama a função listarCpCompras.
Parâmetros: Recebe um vetor do tipo tCliente(estrutura)para obter acesso a ela, recebe um valor
cont inteiro para obter a quantidade de clientes ja cadastrados e recebe uma 
estrutura do tipo tBonus declarada na função main para obter acesso aos valores definidos de seus
campos. Não retorna nenhum valor.
*/
void relatorios(tCliente vetCliente[TAM], int cont, tBonus bonusM){
	int nrelat;
	do{
		printf("MENU RELATORIOS\n");
		nrelat = menuRelatorios();
	switch(nrelat){
	case 1: listarC(vetCliente, cont);
		break;
	case 2: listarB(vetCliente, cont, bonusM);
		break;
	case 3: listarCpCompras(vetCliente, cont);
		break;
	case 0: printf("Fim do menu\n");
		break;
	default: printf("Erro:Opcao invalida\n");
		break;
	}
	}while(nrelat!=0);
}

int main(){
	int nM, cont=0;
	tCliente vetCliente[TAM];
	tBonus bonusM;
	bonusM.teto = 100;
	bonusM.valor = 0.5;
	bonusM.valorBonificar = 100;
	
	do{
      printf("MENU PRINCIPAL:\n");
	  nM = menuPrincipal();
	switch(nM){
	case 1: cliente(vetCliente, &cont);
		break;
	case 2: compra(vetCliente, cont, bonusM);
		break;
	case 3: bonus(vetCliente, cont, &bonusM);
		break;
	case 4: relatorios(vetCliente, cont, bonusM);
		break;
	case 0: printf("Fim do programa");
		break;
	}
	}while(nM!=0);
	
	
	
	return 0;
}