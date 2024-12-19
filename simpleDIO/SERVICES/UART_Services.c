/*
* UART_Services.c
*
* Created: 4/15/2024 10:34:44 AM
*  Author: Mohammed
*/
#include "..\std_types.h"
#include "..\memory_map.h"
#include "..\utils.h"
#include "..\MCAL\UART_Interface.h"
#include "UART_Services.h"

extern const uart_task_t uart_taskArray[NUMBEROFTASK];

static u8 sendData[8], sendTop=0, sendHead=0;
static u8 *sendStr, sendFlag=1;
static u8 recievedata[8], recieveTop=0, head=0;
static u8 recieveStr[8][20], recieveStrTop=0, headStr=0;



static void sendFunc(void);
static void recieveFunc(void);
static void sendStrFunc(void);
static void recieveStrFunc(void);
static void uart_taskRunnable(void);
static void searchFunc(u8 *str);


static void sendFunc(void){
	if (sendHead!=sendTop){
		uart_sendNow(sendData[sendHead]);
		sendHead=(sendHead+1)%8;
	}
}


u8 uart_sendAsync(u8 data){
	uart_setCallback_TX(sendFunc);
	if (ReadBit(UCSRA, UDRE)){
		uart_sendNow(data);
	}
	else{
		sendData[sendTop]= data;
		if ((sendTop+1)%8 == sendHead){
			return 0;
		}
		else{
			sendTop=(sendTop+1)%8;
			return 1;
		}
	}
	return 1;
}


static void recieveFunc(void){
	uart_recieveNow(&recievedata[recieveTop]);
	recieveTop=(recieveTop+1)%8==head ? recieveTop:(recieveTop+1)%8;
}


u8 uart_recieveAsync(u8 *data){
	uart_setCallback_RX(recieveFunc);
	if (head!=recieveTop){
		*data=recievedata[head];
		head=(head+1)%8;
		return 1;
	}
	else{
		return 0;
	}
}


static void sendStrFunc(void){
	static u8 i=1;
	if (sendStr[i]==0){
		i=1;
		sendFlag = 1;
		uart_taskInit();
		return;
	}
	uart_sendNow(sendStr[i++]);
}


u8 uart_sendStringAsync(u8 *str){
	uart_EnableInterrupt_TX();
	if (sendFlag){
		sendFlag =0;
		sendStr=str;
		uart_setCallback_TX(sendStrFunc);
		uart_sendNow(str[0]);
	}
	else{
		return 0;
	}
	return 1;
}


static void recieveStrFunc(void){
	static u8 i=0;
	uart_EnableInterrupt_RX();
	uart_recieveNow(&recieveStr[recieveStrTop][i]);
	if (recieveStr[recieveStrTop][i]==0x0D){
		recieveStr[recieveStrTop][i]=0;
		recieveStrTop=(recieveStrTop+1)%8==headStr ? recieveStrTop:(recieveStrTop+1)%8;
		i=0;
		return;
	}
	i++;
}


u8 uart_recieveStringAsync(u8 **data){
	uart_setCallback_RX(recieveStrFunc);
	if (headStr!=recieveStrTop){
		*data=recieveStr[headStr];
		headStr=(headStr+1)%8;
		return 1;
	}
	else{
		return 0;
	}
}




/*********************************** UART Task **************************************/
u8 data, funcName[20];

static s8 strCompare(u8* str1, u8 *str2){
	u8 i=0;
	while(str1[i]&&str2[i]){
		if (str1[i]!=str2[i]){
			break;
		}
		i++;
	}
	return str1[i]-str2[i];
}

static void searchFunc(u8 *strfunc){ //need to complete
	for (u8 i=0; i<NUMBEROFTASK; i++){
		if (strCompare(strfunc, uart_taskArray[i].name)==0){
			uart_taskArray[i].pfunc(data);
		}
	}
}

static void split_str(u8 *str){
	u8 i=0;
	data=0;
	while (str[i] != ' ' && str[i] != 0x0D && str[i] != 0){
		funcName[i]=str[i];
		i++;
	}
	funcName[i]=0;
	if (str[i] == 0){
		return;
	}
	i++;
	while (str[i]){
		data=data*10+str[i]-'0';
		i++;
	}
}

void uart_taskInit(void){
	uart_EnableInterrupt_RX();
	uart_setCallback_RX(uart_taskRunnable);
}

static void uart_taskRunnable(void){ //need to complete
	static u8 i=0;
	uart_recieveNow(&recieveStr[recieveStrTop][i]);
	if (recieveStr[recieveStrTop][i]==0x0D || recieveStr[recieveStrTop][i]=='\n' || recieveStr[recieveStrTop][i]=='\r' 
		|| recieveStr[recieveStrTop][i]=='#' || recieveStr[recieveStrTop][i]==0 || recieveStr[recieveStrTop][i]==0){
		recieveStr[recieveStrTop][i]=0;
		recieveStrTop=(recieveStrTop+1)%8==headStr ? recieveStrTop:(recieveStrTop+1)%8;
		i=0;
		split_str(recieveStr[headStr]);
		searchFunc(funcName);
		headStr=(headStr+1)%8;
		
	}else{
	i++;
		
	}
}
