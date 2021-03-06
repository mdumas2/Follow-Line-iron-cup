/*
 * Drive_TB66.c
 *
 *  Created on: 31 de mai de 2019
 *      Author: luis_
 */
#include "main.h"
#include "tim.h"
#include "drive_TB66.h"
#include "gpio.h"

uint32_t valor_PWMA;
uint32_t valor_PWMB;

void config_motor(void){
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET); //Iniciar pino AIN1 em 1 para o freio motor 1
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET); //Iniciar pino AIN2 em 1 para o freio motor 1
	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET); //Iniciar pino BIN1 em 1 para o freio motor 2
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET); //Iniciar pino BIN2 em 1 para o freio motor 2
}

int velocidade_motor1(volatile int velocidade1){
	if(velocidade1 > 100){
		velocidade1 = 100;
	}
	else if(velocidade1 < 0){
		if(velocidade1 < -100){
			velocidade1 = -100;
		}
		valor_PWMA= - 10*velocidade1;
		HAL_TIM_PWM_Start(&htim17,TIM_CHANNEL_1);
		TIM17->CCR1 = valor_PWMA;
		motor1_tras();
		return velocidade1;
	}
	valor_PWMA= 10*velocidade1;
	HAL_TIM_PWM_Start(&htim17,TIM_CHANNEL_1);
	TIM17->CCR1 = valor_PWMA;
	motor1_frente();
	return velocidade1;
}
int velocidade_motor2(volatile int velocidade2){
	if(velocidade2 > 100){
		velocidade2 = 100;
	}
	else if(velocidade2 < 0){
		if(velocidade2 < -100){
			velocidade2 = -100;
		}
		valor_PWMB= - 10*velocidade2;
		HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
		TIM16->CCR1 = valor_PWMB;
		motor2_tras();
		return velocidade2;
	}
	valor_PWMB=10*velocidade2;
	HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
	TIM16->CCR1 = valor_PWMB;
	motor2_frente();
	return velocidade2;
}

void motor1_frente(void){
	//Configuração para motor1 frente AIN1 (0) e AIN2 (1)
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET); //AIN1 em 0
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET); //AIN2 em 1

}
void motor1_tras(void){
	//Configuração para motor1 tras AIN1 (1) e AIN2 (0)
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET); //AIN1 em 1
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET); //AIN2 em 0
}
void motor1_freio(void){
	//freiar motor1 AIN1(1) e AIN2(1)
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET); //AIN1 em 1
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET); //AIN2 em 1
//	HAL_TIM_PWM_Start(&htim17,TIM_CHANNEL_1);
//	TIM17->CCR1 = 0;

}
void motor2_frente(void){
	//Configuração para motor2 frente BIN1(0) e BIN2(1)
	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET); //BIN1 em 0
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET); //BIN2 em 1
}
void motor2_tras(void){
	//Configuração para motor2 tras BIN1(1) e BIN2(0)
	HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET); //BIN1 em 1
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET); //BIN2 em 0
}
void motor2_freio(void){
	//freiar motor2 BIN1(1) e BIN2(1)
	HAL_GPIO_WritePin(AIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET); //BIN1 em 1
	HAL_GPIO_WritePin(AIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET); //BIN2 em 1
//	HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
//	TIM16->CCR1 = 0;
}

