/* Nome: Gabriel Santos Araujo
Matrícula: UC21106862
Curso: Engenharia de software */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//Definindo cores de acordo com o código escape ANSI
#define VERDE "\x1b[32m"
#define VERMELHO "\x1b[31m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"


int main(void){
	
	setlocale(LC_ALL, "Portuguese");  //Localizando o programa para adptar-se a linguagem 
    system("CLS");
	
	//Definindo variáveis
	int menu, ID_destino=0, voos_cadastratos=1, aux=0, assentos_voo[100], qtd_passagens, qtd_passagens_5, assentos[20][10], confirmar[20][10], contador[200];
	int assento_escolhido, ID_provisorio, ID_passageiro=0, ID_provisorio_voo, reservados, confirmados, disponiveis, linha[100];
	char destinos[100][50], codigo[20][10];
	float valor_passagem[100], valor_total[100], valor_total_voo[100];

	//Laço (do,while) para repetição do menu 
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
		printf("_/ CÓDIGO _/           OPÇÃO          _/\n");
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
		menu=getch();	//Retorna um caractere digitado, desse modo não existe a necessida de confirmar (enter), deixando o menu mais intuitivo.
		fflush(stdin);
		system("cls");
		
		switch(menu){	//'Switch case' usado para estruturar 'menu'
			case 49:	
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/         REALIZAR RESERVA           _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);

//Verificando se a array "destinos" não está recebendo um valor nulo através da função 'strlen' que retorna o tamanho da string	digitada			
				do{
					printf("Informe o destino desejado: ");
					fflush(stdin);
					fgets(destinos[ID_destino], 50, stdin);
					if(strlen(destinos[ID_destino])<3)
						printf(VERMELHO"\nDESTINO INVÁLIDO!\n\n"RESET);
				}while(strlen(destinos[ID_destino])<3);

//Transformando toda a string digitada para caracteres maiusculos com a função 'toupper', para desse modo possibilitar a verificação a seguir	
				for (int i=0; i<=strlen(destinos[ID_destino]); i++){
                destinos[ID_destino][i] = toupper(destinos[ID_destino][i]);
           		}			

//Verificando se a array 'destinos' já não possui um valor idêntico gravado em uma de suas posições
//A comparação é feita com a função 'strcmp' que retorna '0' se duas strings forem iguais
//Foi adicionada uma condição [if(ID_destino!=i)] para evitar que o 'ID_destino' se compara-se consigo mesmo na array 'destinos'   					
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

//Função para caso não forem encontrados voos que coincidem com o mesmo nome. Um novo cadastro será feito, e uma 'ID_destino' única sera gerada para esse voo				
				system("cls");
				if(aux==0){
					printf(VERMELHO"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
					printf("_/         VOO NÃO CADASTRADO         _/\n");
					printf("_/   DIGITE SUAS INFORMAÇÕES ABAIXO   _/\n");
					printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);

//Array para valor da passagem, atrelado ao ID do destino
//Uma validação é feita para impedir valores abaixo de 0					
					do{
						printf("Informe o valor da passagem: ");
						fflush(stdin);
						scanf("%f", &valor_passagem[ID_destino]);
						if(valor_passagem[ID_destino]<=0)
							printf(VERMELHO"\nVALOR INVÁLIDO!\nA PASSAGEM NÃO PODE CUSTAR MENOS QUE R$ 0!\n\n"RESET);
					}while(valor_passagem[ID_destino]<=0);

//Array para quantidade de assentos no voo, atrelado ao ID do destino
//Uma validação é feita para impedir valores abaixo de 90 e maiores que 200							
					do{
						printf("Informe a quantidade de assentos neste voo: ");
						fflush(stdin);
						scanf("%d", &assentos_voo[ID_destino]);
						if(assentos_voo[ID_destino]<90 || assentos_voo[ID_destino]>200)
							printf(VERMELHO"\nAVIÃO INEXISTENTE!\nOS AVIÕES DA SALUMAR POSSUEM ENTRE 90 E 200 ASSENTOS!\n\n"RESET);
					}while(assentos_voo[ID_destino]<90 || assentos_voo[ID_destino]>200);

//Contando números de assentos totais e salvando seu respectivo caractere (1,2,3...etc) na matriz 'assentos[i][j]'
//A array 'linha' foi definida de forma a evitar que o laço se repita além do necessário de acordo com o número assentos no voo  				
					linha[ID_destino]=(assentos_voo[ID_destino]/10)+1;
					contador[ID_destino]=0;
					for(int i=0; i<linha[ID_destino]; i++){
				        for (int j=0; j<10; j++){
				            contador[ID_destino]++;
				            assentos[i][j]=contador[ID_destino];
				        }  
				    }

//Salvando todos os assentos com o código 'D'(disponível) e salvando na matriz 'codigo[i][j]' que funciona em paralelo com a matriz 'assentos[i][j]'				    
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

//Validando se a quantidade de reservas solicitadas não é menor que 0 ou extrapola o número de assentos	totais do voo com ID único			
				do{
					printf("Informe quantas passagens deseja reservar: ");
					fflush(stdin);
					scanf("%d", &qtd_passagens);
					if(qtd_passagens<=0 || qtd_passagens>assentos_voo[ID_destino])
						printf(VERMELHO"\nQUANTIDADE INVÁLIDA!\nO AVIÃO NÃO POSSUI ESSA QUANTIDADE DE ASSENTOS DISPONÍVEL\n\n"RESET);
				}while(qtd_passagens<=0 || qtd_passagens>assentos_voo[ID_destino]);

//Validando se a quantidade de passageiros com até 5 anos não é menor que 0 ou extrapola o número de reservas solicitadas	
				do{
					printf("Informe quantos passageiros possuem até 5 anos, se não houver nem um, digite 0: ");
					fflush(stdin);
					scanf("%d", &qtd_passagens_5);
					if(qtd_passagens_5<0 || qtd_passagens_5>qtd_passagens)
						printf(VERMELHO"\nQUANTIDADE INVÁLIDA!\nO VALOR INFORMADO ULTRAPASSOU O NÚMERO DE PASSAGENS RESERVADAS TOTAIS\n\n"RESET);
				}while(qtd_passagens_5<0 || qtd_passagens_5>qtd_passagens);

//Imprimindo todos os assentos. 
//Uma comparação é feita para verificar qual o código salvo na matriz 'codigo[i][j]' 
//Se verdadeiro é retornado o respectivo código salvo na matriz 'codigo[i][j]' e o respectivo caractere da matriz paralela 'assentos[i][j]' 				
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
        		printf(VERMELHO"R - RESERVADO"RESET VERDE"\tD - DISPONÍVEL"RESET AZUL"\tC - CONFIRMADO\n"RESET);

//Escolha de assento, uma comparação é feita com o valor digitado e todos os valores salvos na matriz de caracteres 'assentos[i][j]'
//Se os valores coincidirem a matriz paralela 'codigo[i][j]' recebe o código 'R'(Reservado) na respectiva posição
//Uma nova matriz 'confirmar[i][j]' recebe o ID único do passageiro para atrelar aquela posição na matriz ao cliente.           		
        		aux=0;
		        do{
		        	printf("\nInforme o número do %dº assento desejado: ", aux+1);
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

//Uma nova array 'valor_total' é criada para receber o valor gasto em cada reserva com seu ID único.
//O calcúlo é feito de maneira a oferecer 50% de desconto aos passageiros com até 5 anos				
				valor_total[ID_passageiro]=((qtd_passagens-qtd_passagens_5)*valor_passagem[ID_destino])+(qtd_passagens_5*(valor_passagem[ID_destino]/2));
				system("cls");
				
//Imprimindo as informações relevantes ao passageiro
				printf(VERDE"_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
				printf("_/   RESERVA REALIZADA COM SUCESSO    _/\n");
				printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n\n"RESET);
				printf("Destino: %s", destinos[ID_destino]);
				printf("Número total de passagens reservadas: %d\n", qtd_passagens);
				printf("Valor total a ser pago: R$ %.2f\n", valor_total[ID_passageiro]);
				printf(VERMELHO"\nID PESSOAL: %d\n", ID_passageiro);
				printf("ID DO SEU VOO: %d\n", ID_destino);
				printf(VERMELHO"> ATENÇÃO AOS SEUS IDs, ELES SERÃO NECESSÁRIOS PARA CONFIRMAR OU CANCELAR UMA RESERVA <\n\n"RESET);
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

//Através do ID único do passageiro e feita uma comparação até ser encontrada na matriz 'confirmar[i][j]' o valor correspondente
//Na matriz paralela 'codigo[i][j]', na mesma posição da matriz	'confirmar[i][j]', a matriz 'codigo[i][j]' recebe 'C'(Confirmado) 		  
		        for(int i=0; i<linha[ID_provisorio_voo]; i++){ 
		            for(int j=0; j<10; j++){
		                if(confirmar[i][j]==ID_provisorio && codigo[i][j]=='R'){
		                    codigo[i][j]= 'C';
		                    } 
		                }       
		            }

//Com o ID único do voo podemos definir novamente o número de assentos que esse voo possui e imprimir seus assentos atualizados				
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
 
 //Com a reserva confirmada a array 'valor_total_voo', com seu respectivo ID de voo único, já pode receber o valor das passagens compradas.       		
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

//Através do ID único do passageiro e feita uma comparação até ser encontrada na matriz 'confirmar[i][j]' o valor correspondente
//Na matriz paralela 'codigo[i][j]', na mesma posição da matriz	'confirmar[i][j]', a matriz 'codigo[i][j]' recebe 'D'(Disponível) 				
				for(int i=0; i<linha[ID_provisorio_voo]; i++){ 
            		for(int j=0; j<10; j++){
                		if(confirmar[i][j]==ID_provisorio && codigo[i][j]=='R'){
                    		codigo[i][j]='D';
                    	} 
                	}       

//Com o ID único do voo podemos definir novamente o número de assentos que esse voo possui e imprimir seus assentos atualizados            	
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

//Com o ID único do voo podemos definir novamente o número de assentos que esse voo possui e imprimir seus assentos atualizados             
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

//Com o ID único do voo podemos definir novamente o número de assentos que esse voo possui e imprimir seus assentos atualizados 
//Mas desta vez é contado no laço os respectivos valores solicitados				
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

//Imprimindo as informações relevantes do voo				
				printf("Destino: %s\n", destinos[ID_provisorio_voo]);
				printf("Assentos Confirmados: %d\n", confirmados);
				printf("Assentos Reservados: %d\n", reservados);
				printf("Assentos Disponíveis: %d\n\n", disponiveis);
				printf("Valor total, até o momento, de vendas confirmadas: %.2f\n\n", valor_total_voo[ID_provisorio_voo]);
				system("pause");
				system("cls");
				break; 
			
			case 48:

//Encerramento do programa
				printf("_/_/_/_/_/_/"AZUL"A SALUMAR LINHAS AÉREAS AGRADECE PELA PREFERÊNCIA"RESET" _/_/_/_/_/_/");
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
				printf(VERMELHO"\nOPÇÃO INVÁLIDA!\nPOR FAVOR, SELECIONE UMA OPÇÃO DO MENU!\n\n"RESET);
				break;		
		} 	   
	}while(menu!=48); //Menu vai se repetir até que a opção de encerramento seja digitada
	return 0;	
}

