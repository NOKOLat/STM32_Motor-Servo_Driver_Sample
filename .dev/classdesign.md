ｗ
## 運用について

- インスタンスはstd::optional （初期化の保証、メモリの動的確保を避ける）
- クラス内で演算子オーバーロードを行い、単一保有を保証する
- instance.emplace(...)で初期化するときにピンを渡す
- instance.begin()のときに、初期化の成功変数の読み出し、ピンのクロックの読み取りを行う（以降クロックは変わらないとする）

- 派生クラスがパルス幅[μs]を計算する（これは角度や速度などから変換する、ハード依存）
- 基底クラスがパルス幅[μs]をタイマーへの入力値に変更する（STMの設定依存）

## PwmController

### public methods
- constructor(HAL_TIMER_HandleTypeDef* htim, uint32_t channel) 
// ここでピン変数の取り込みと、内部で使用するタイマーのクロック取得も行う

- destructor() // ライフタイムはmain()に依存するため、特に何もしない

- uint8_t isInitialized()() // インスタンスの初期化チェック

- uint8_t setPulseWidth(uint32_t pulseWidth) // 成功したら0を返す

- uint8_t stop() // PWM出力を停止する。成功したら0を返す

### private methods

- パルス幅を実際に入力する値に変換するための関数

- bool checkPulseWidthRange(uint32_t pulseWidth) //パルス幅の範囲チェックを行う関数

## ServoController : public PwmController

- パルスは開閉を1000~2000usで制御する
- 中立は1500usとしておく（ここは内部にconstexprで持たせる）
- 角度は-90~90度で制御する

### public methods

- constructor()
- destructor()
- uint8_t isInitialized()　// 基底クラスのメソッドを使用
- uint8_t setAngle(float angle)
- uint8_t neutral()
- uint8_t stop()

pwmの設定系のメソッドは基底クラスのsetPulseWidth()を使用する


## SampleCode

clock = 90Mhz
presclaler 89
period 19999

**wrapper.cpp**

```cpp
#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"

void init(){

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_Delay(500);
}

void loop(){

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
    printf("-90deg\n");
    HAL_Delay(1000);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1450);
    printf("0deg\n");
    HAL_Delay(1000);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2400);
    printf("90deg\n");
    HAL_Delay(1000);
}
```