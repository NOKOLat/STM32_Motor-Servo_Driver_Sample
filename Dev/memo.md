## HALを直接使ったモーターテスト

- Clock 90Mhz 
- Pre 89
- Counter 19999

```cpp
#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include "motor_controller.hpp"

void init(){

	printf("Program Start: bulid: 2\n");
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
	HAL_Delay(10000);

	printf("Init End\n");
}

void loop(){

	printf("Motor: 50%%\n");
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500);
	HAL_Delay(5000);

	printf("Motor: Stop\n");
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

	while(1);
}
```
