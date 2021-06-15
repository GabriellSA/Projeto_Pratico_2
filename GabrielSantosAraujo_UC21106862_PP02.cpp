/* Nome: Gabriel Santos Araujo
Matr�cula: UC21106862
Curso: Engenharia de software */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//Definindo cores de acordo com o c�digo escape ANSI
#define VERDE "\x1b[32m"
#define VERMELHO "\x1b[31m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"


int main(void){
	
	setlocale(LC_ALL, "Portuguese");  //Localizando o programa para adptar-se a linguagem 
    system("CLS");
	
	//Definindo vari�veis
	int menu, ID_destino=0, voos_cadastratos=1, aux=0, assentos_voo[100], qtd_passagens, qtd_passagens_5, assentos[20][10], confirmar[20][10], contador[200];
	int assento_escolhido, ID_provisorio, ID_passageiro=0, ID_provisorio_voo, reservados, confirmados, disponiveis, linha[100];
	char destinos[100][50], codigo[20][10];
	float valor_passagem[100], valor_total[100], valor_total_voo[100];

	//La�o (do,while) para repeti��o do menu 
	do{
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf(AZUL"\n       _/_/_/    _/_/    _/        _/    _/  _/      _/    _/_/    _/_/_/   \n");
		printf("    _/        _/    _/  _/        _/    _/  _/_/  _/_/  _/    _/  _/    _/   \n");
		printf("     _/_/    _/_/_/_/  _/        _/    _/  _/  _/  _/  _/_/_/_/  _/_/_/     \n");
		printf("        _/  _/    _/  _/        _/    _/  _/      _/  _/    _/  _/    _/    \n");
		printf(" _/_/_/    _/    _/  _/_/_/_/    _/_/    _/      _/  _/    _/  _/    _/    \n\n"RESET);
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/              MENU                  _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/ C�DIGO _/           OP��O          _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   1    _/     REALIZAR RESERVA     _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   2    _/     CONFIRMAR RESERVA    _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   3    _/     CANCELAR RESERVA     _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   4    _/     VERIFICAR ASSENTOS   _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   5    _/       CONSULTAR VOO      _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		printf("_/   0    _/     ENCERRAR PROGRAMA    _/\n");
		printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_\n");
		menu=getch();	//Retorna um caractere digitado, desse modo n�o existe a necessida de confirmar (enter), deixando o menu mais intuitivo.
		fflush(stdin);
		system("cls");
		
		switch(menu){	//'Switch case' usado para estruturar 'menu'
			case 49:	
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         REALIZAR RESERVA           _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);

//Verificando se a array "destinos" n�o est� recebendo um valor nulo atrav�s da fun��o 'strlen' que retorna o tamanho da string	digitada			
				do{
					printf("Informe o destino desejado: ");
					fflush(stdin);
					fgets(destinos[ID_destino], 50, stdin);
					if(strlen(destinos[ID_destino])<3)
						printf(VERMELHO"\nDESTINO INV�LIDO!\n\n"RESET);
				}while(strlen(destinos[ID_destino])<3);

//Transformando toda a string digitada para caracteres maiusculos com a fun��o 'toupper', para desse modo possibilitar a verifica��o a seguir	
				for (int i=0; i<=strlen(destinos[ID_destino]); i++){
                destinos[ID_destino][i] = toupper(destinos[ID_destino][i]);
           		}			

//Verificando se a array 'destinos' j� n�o possui um valor id�ntico gravado em uma de suas posi��es
//A compara��o � feita com a fun��o 'strcmp' que retorna '0' se duas strings forem iguais
//Foi adicionada uma condi��o [if(ID_destino!=i)] para evitar que o 'ID_destino' se compara-se consigo mesmo na array 'destinos'   					
				aux=0;
				for(int i=0; i<=voos_cadastratos; i++){
					if(strcmp(destinos[ID_destino], destinos[i])==0){
						if(ID_destino!=i){
							ID_destino=i; 
							aux=1;
							break;
						}
					}
				}

//Fun��o para caso n�o forem encontrados voos que coincidem com o mesmo nome. Um novo cadastro ser� feito, e uma 'ID_destino' �nica sera gerada para esse voo				
				system("cls");
				if(aux==0){
					printf(VERMELHO"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
					printf("_/         VOO N�O CADASTRADO         _/\n");
					printf("_/   DIGITE SUAS INFORMA��ES ABAIXO   _/\n");
					printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);

//Array para valor da passagem, atrelado ao ID do destino
//Uma valida��o � feita para impedir valores abaixo de 0					
					do{
						printf("Informe o valor da passagem: ");
						fflush(stdin);
						scanf("%f", &valor_passagem[ID_destino]);
						if(valor_passagem[ID_destino]<=0)
							printf(VERMELHO"\nVALOR INV�LIDO!\nA PASSAGEM N�O PODE CUSTAR MENOS QUE R$ 0!\n\n"RESET);
					}while(valor_passagem[ID_destino]<=0);

//Array para quantidade de assentos no voo, atrelado ao ID do destino
//Uma valida��o � feita para impedir valores abaixo de 90 e maiores que 200							
					do{
						printf("Informe a quantidade de assentos neste voo: ");
						fflush(stdin);
						scanf("%d", &assentos_voo[ID_destino]);
						if(assentos_voo[ID_destino]<90 || assentos_voo[ID_destino]>200)
							printf(VERMELHO"\nAVI�O INEXISTENTE!\nOS AVI�ES DA SALUMAR POSSUEM ENTRE 90 E 200 ASSENTOS!\n\n"RESET);
					}while(assentos_voo[ID_destino]<90 || assentos_voo[ID_destino]>200);

//Contando n�meros de assentos totais e salvando seu respectivo caractere (1,2,3...etc) na matriz 'assentos[i][j]'
//A array 'linha' foi definida de forma a evitar que o la�o se repita al�m do necess�rio de acordo com o n�mero assentos no voo  				
					linha[ID_destino]=(assentos_voo[ID_destino]/10)+1;
					contador[ID_destino]=0;
					for(int i=0; i<linha[ID_destino]; i++){
				        for (int j=0; j<10; j++){
				            contador[ID_destino]++;
				            assentos[i][j]=contador[ID_destino];
				        }  
				    }

//Salvando todos os assentos com o c�digo 'D'(dispon�vel) e salvando na matriz 'codigo[i][j]' que funciona em paralelo com a matriz 'assentos[i][j]'				    
					for(int i=0; i<linha[ID_destino]; i++){
				        for(int j=0; j<10; j++){
				            if(assentos[i][j]<=assentos_voo[ID_destino]){
				                   codigo[i][j]='D';
				            }
				        }  
				    }
					
					voos_cadastratos++;					
					printf(VERDE"\n_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
					printf("_/     VOO CADASTRADO COM SUCESSO     _/\n");
					printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
					system("pause");
					system("cls");
				}
				
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         REALIZAR RESERVA           _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);

//Validando se a quantidade de reservas solicitadas n�o � menor que 0 ou extrapola o n�mero de assentos	totais do voo com ID �nico			
				do{
					printf("Informe quantas passagens deseja reservar: ");
					fflush(stdin);
					scanf("%d", &qtd_passagens);
					if(qtd_passagens<=0 || qtd_passagens>assentos_voo[ID_destino])
						printf(VERMELHO"\nQUANTIDADE INV�LIDA!\nO AVI�O N�O POSSUI ESSA QUANTIDADE DE ASSENTOS DISPON�VEL\n\n"RESET);
				}while(qtd_passagens<=0 || qtd_passagens>assentos_voo[ID_destino]);

//Validando se a quantidade de passageiros com at� 5 anos n�o � menor que 0 ou extrapola o n�mero de reservas solicitadas	
				do{
					printf("Informe quantos passageiros possuem at� 5 anos, se n�o houver nem um, digite 0: ");
					fflush(stdin);
					scanf("%d", &qtd_passagens_5);
					if(qtd_passagens_5<0 || qtd_passagens_5>qtd_passagens)
						printf(VERMELHO"\nQUANTIDADE INV�LIDA!\nO VALOR INFORMADO ULTRAPASSOU O N�MERO DE PASSAGENS RESERVADAS TOTAIS\n\n"RESET);
				}while(qtd_passagens_5<0 || qtd_passagens_5>qtd_passagens);

//Imprimindo todos os assentos. 
//Uma compara��o � feita para verificar qual o c�digo salvo na matriz 'codigo[i][j]' 
//Se verdadeiro � retornado o respectivo c�digo salvo na matriz 'codigo[i][j]' e o respectivo caractere da matriz paralela 'assentos[i][j]' 				
				printf("\nEscolha os assentos:\n"); 
				for(int i=0; i<linha[ID_destino]; i++){
        			for(int j=0; j<10; j++){
            
						if(assentos[i][j]<=contador[ID_destino]){
			                if (codigo[i][j]=='R'){
			                    printf(VERMELHO"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='D'){
			                    printf(VERDE"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='C'){
			                    printf(AZUL"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                }  
			            } 
			        }
					printf("\n");       
        		} 
        		printf("LEGENDA:\n");
        		printf(VERMELHO"R - RESERVADO"RESET VERDE"\tD - DISPON�VEL"RESET AZUL"\tC - CONFIRMADO\n"RESET);

//Escolha de assento, uma compara��o � feita com o valor digitado e todos os valores salvos na matriz de caracteres 'assentos[i][j]'
//Se os valores coincidirem a matriz paralela 'codigo[i][j]' recebe o c�digo 'R'(Reservado) na respectiva posi��o
//Uma nova matriz 'confirmar[i][j]' recebe o ID �nico do passageiro para atrelar aquela posi��o na matriz ao cliente.           		
        		aux=0;
		        do{
		        	printf("\nInforme o n�mero do %d� assento desejado: ", aux+1);
		        	fflush(stdin);
			        scanf("%d", &assento_escolhido);
			        for(int i=0; i<linha[ID_destino]; i++){  
			        	for(int j=0; j<10; j++){
			            	if(assentos[i][j]==assento_escolhido){
			                	codigo[i][j] = 'R';
			                	confirmar[i][j] = ID_passageiro;
			              	aux++;
		                	} 
		            	}       
		        	}
				}while(aux<qtd_passagens);

//Uma nova array 'valor_total' � criada para receber o valor gasto em cada reserva com seu ID �nico.
//O calc�lo � feito de maneira a oferecer 50% de desconto aos passageiros com at� 5 anos				
				valor_total[ID_passageiro]=((qtd_passagens-qtd_passagens_5)*valor_passagem[ID_destino])+(qtd_passagens_5*(valor_passagem[ID_destino]/2));
				system("cls");
				
//Imprimindo as informa��es relevantes ao passageiro
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/   RESERVA REALIZADA COM SUCESSO    _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				printf("Destino: %s", destinos[ID_destino]);
				printf("N�mero total de passagens reservadas: %d\n", qtd_passagens);
				printf("Valor total a ser pago: R$ %.2f\n", valor_total[ID_passageiro]);
				printf(VERMELHO"\nID PESSOAL: %d\n", ID_passageiro);
				printf("ID DO SEU VOO: %d\n", ID_destino);
				printf(VERMELHO"> ATEN��O AOS SEUS IDs, ELES SER�O NECESS�RIOS PARA CONFIRMAR OU CANCELAR UMA RESERVA <\n\n"RESET);
				ID_destino++;
				ID_passageiro++;	
				system("pause");
				system("cls");
				break;
			
			case 50:
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         CONFIRMAR RESERVA          _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				
				printf("Informe seu ID pessoal: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio);
		        printf("Informe o ID do seu voo: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio_voo);

//Atrav�s do ID �nico do passageiro e feita uma compara��o at� ser encontrada na matriz 'confirmar[i][j]' o valor correspondente
//Na matriz paralela 'codigo[i][j]', na mesma posi��o da matriz	'confirmar[i][j]', a matriz 'codigo[i][j]' recebe 'C'(Confirmado) 		  
		        for(int i=0; i<linha[ID_provisorio_voo]; i++){ 
		            for(int j=0; j<10; j++){
		                if(confirmar[i][j]==ID_provisorio && codigo[i][j]=='R'){
		                    codigo[i][j]= 'C';
		                    } 
		                }       
		            }

//Com o ID �nico do voo podemos definir novamente o n�mero de assentos que esse voo possui e imprimir seus assentos atualizados				
				for(int i=0; i<linha[ID_provisorio_voo]; i++){
        			for(int j=0; j<10; j++){
            
						if(assentos[i][j]<=contador[ID_provisorio_voo]){
			                if (codigo[i][j]=='R'){
			                    printf(VERMELHO"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='D'){
			                    printf(VERDE"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='C'){
			                    printf(AZUL"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                }  
			            } 
			        }
					printf("\n");       
        		}
 
 //Com a reserva confirmada a array 'valor_total_voo', com seu respectivo ID de voo �nico, j� pode receber o valor das passagens compradas.       		
        		valor_total_voo[ID_provisorio_voo]=valor_total_voo[ID_provisorio_voo]+valor_total[ID_provisorio];
        		printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/   RESERVA CONFIRMADA COM SUCESSO   _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				system("pause");
				system("cls"); 
				break;
			
			case 51:
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         CANCELAR RESERVA           _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				
				printf("Informe seu ID pessoal: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio);
		        printf("Informe o ID do seu voo: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio_voo);

//Atrav�s do ID �nico do passageiro e feita uma compara��o at� ser encontrada na matriz 'confirmar[i][j]' o valor correspondente
//Na matriz paralela 'codigo[i][j]', na mesma posi��o da matriz	'confirmar[i][j]', a matriz 'codigo[i][j]' recebe 'D'(Dispon�vel) 				
				for(int i=0; i<linha[ID_provisorio_voo]; i++){ 
            		for(int j=0; j<10; j++){
                		if(confirmar[i][j]==ID_provisorio && codigo[i][j]=='R'){
                    		codigo[i][j]='D';
                    	} 
                	}       

//Com o ID �nico do voo podemos definir novamente o n�mero de assentos que esse voo possui e imprimir seus assentos atualizados            	
				}
				for(int i=0; i<linha[ID_provisorio_voo]; i++){
        			for(int j=0; j<10; j++){
            
						if(assentos[i][j]<=contador[ID_provisorio_voo]){
			                if (codigo[i][j]=='R'){
			                    printf(VERMELHO"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='D'){
			                    printf(VERDE"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='C'){
			                    printf(AZUL"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                }  
			            } 
			        }
					printf("\n");       
        		}
					
				printf(VERDE"\n\n_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/   RESERVA CANCELADA COM SUCESSO    _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				system("pause");
				system("cls");
				break;
				
			case 52:
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         VERIFICAR ASSENTOS         _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				
				printf("Informe o ID do seu voo: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio_voo);
				
				for(int i=0; i<linha[ID_provisorio_voo]; i++){
        			for(int j=0; j<10; j++){

//Com o ID �nico do voo podemos definir novamente o n�mero de assentos que esse voo possui e imprimir seus assentos atualizados             
						if(assentos[i][j]<=contador[ID_provisorio_voo]){
			                if (codigo[i][j]=='R'){
			                    printf(VERMELHO"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='D'){
			                    printf(VERDE"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                } 
							else if (codigo[i][j]=='C'){
			                    printf(AZUL"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                }  
			            } 
			        }
					printf("\n");       
        		}
        		
        		system("pause");
				system("cls");
				break;
				
			case 53:
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/           CONSULTAR VOO            _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				
				printf("Informe o ID do seu voo: ");
				fflush(stdin);
		        scanf("%d", &ID_provisorio_voo);

//Com o ID �nico do voo podemos definir novamente o n�mero de assentos que esse voo possui e imprimir seus assentos atualizados 
//Mas desta vez � contado no la�o os respectivos valores solicitados				
				reservados=0;
				confirmados=0;
				disponiveis=0;
				for(int i=0; i<linha[ID_provisorio_voo]; i++){
        			for(int j=0; j<10; j++){
            
						if(assentos[i][j]<=contador[ID_provisorio_voo]){
			                if (codigo[i][j]=='R'){
			                    printf(VERMELHO"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                    reservados++;
			                } 
							else if (codigo[i][j]=='D'){
			                    printf(VERDE"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                    disponiveis++;
			                } 
							else if (codigo[i][j]=='C'){
			                    printf(AZUL"%d", assentos[i][j]);
			                    printf(" %c\t"RESET, codigo[i][j]);
			                    confirmados++;
			                }  
			            } 
			        }
					printf("\n");       
        		}

//Imprimindo as informa��es relevantes do voo				
				printf("Destino: %s\n", destinos[ID_provisorio_voo]);
				printf("Assentos Confirmados: %d\n", confirmados);
				printf("Assentos Reservados: %d\n", reservados);
				printf("Assentos Dispon�veis: %d\n\n", disponiveis);
				printf("Valor total, at� o momento, de vendas confirmadas: %.2f\n\n", valor_total_voo[ID_provisorio_voo]);
				system("pause");
				system("cls");
				break; 
			
			case 48:

//Encerramento do programa
				printf("_/_/_/_/_/_/"AZUL"A SALUMAR LINHAS A�REAS AGRADECE PELA PREFER�NCIA"RESET" _/_/_/_/_/_/");
				printf("\n\n_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf(AZUL"\n       _/_/_/    _/_/    _/        _/    _/  _/      _/    _/_/    _/_/_/   \n");
				printf("    _/        _/    _/  _/        _/    _/  _/_/  _/_/  _/    _/  _/    _/   \n");
				printf("     _/_/    _/_/_/_/  _/        _/    _/  _/  _/  _/  _/_/_/_/  _/_/_/     \n");
				printf("        _/  _/    _/  _/        _/    _/  _/      _/  _/    _/  _/    _/    \n");
				printf(" _/_/_/    _/    _/  _/_/_/_/    _/_/    _/      _/  _/    _/  _/    _/    \n\n"RESET);
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n\n"); 
				system("pause");
				system("cls");
				break;
				
			default:
				system("cls");
				printf(VERMELHO"\nOP��O INV�LIDA!\nPOR FAVOR, SELECIONE UMA OP��O DO MENU!\n\n"RESET);
				break;		
		} 	   
	}while(menu!=48); //Menu vai se repetir at� que a op��o de encerramento seja digitada
	return 0;	
}

