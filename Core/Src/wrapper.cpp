#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include "motor_controller.hpp"

void Calibration();

void init(){

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_Delay(500);

	Calibration();

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
	HAL_Delay(5000);
	printf("Init End\n");
}

void loop(){

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1400);
	HAL_Delay(10000);

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

void Calibration(){

	printf("Calibration Start\n");

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
	HAL_Delay(5000);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
	HAL_Delay(5000);

	printf("Calibration End\n");
}
