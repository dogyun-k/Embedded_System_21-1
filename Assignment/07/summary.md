### 21/05/13 (목)
---------------------------

# 1. ADC 구동 과정

## 0. ADC란?

- Analog-to-Digital Converter의 약자로 아날로그 신호(온도, 소리, 가속도 등)를 디지털 형식으로 변환하는 것이다. 

- ADC 변환 과정

    임베디드 시스템에서 ADC 과정은 다음과같다.

    1. 입력 채널 선택
    2. ADC 변환 시작
    3. ADC 변환 완료
    4. 디지털 값 읽기

- STM32F board는 최대 19개의 멀티플렉싱 채널을 통해 16개의 외부 소스, 2개의 내부 소스 및 VBAT 채널로부터의 신호를 측정할 수 있다.


## 1. ADC 구조체 및 주소 설정

1. **Reference : 13.13.18 ADC Register map**을 참조하여 ADC 제어에 사용되는 레지스터 구조체 선언

    ```c
    typedef volatile struct{
        unsigned int rSR;
        unsigned int rCR1;
        unsigned int rCR2;
        unsigned int rSMPR1;
        unsigned int rSMPR2;
        unsigned int rJOFR1;
        unsigned int rJOFR2;
        unsigned int rJOFR3;
        unsigned int rJOFR4;
        unsigned int rHTR;
        unsigned int rLTR;
        unsigned int rSQR1;
        unsigned int rSQR2;
        unsigned int rSQR3;
        unsigned int rJSQR;
        unsigned int rJDR1;
        unsigned int rJDR2;
        unsigned int rJDR3;
        unsigned int rJDR4;
        unsigned int rDR;
        unsigned int rCRS;
        unsigned int rCCR;
        unsigned int rCDR;
    }REG_ADC;
    ```

    - STM32FDiscovery.h 파일에 선언.

2. **Reference : 2.3 Memory map**을 참조하여 ADC 주소를 설정해줬다.

   - ADC 1~3은 다음 주소의 메모리를 사용한다.
       
       > 0x4001 2000 ~ 0x4001 23FF

    ```c
    #define ADC1_BASE 0x40012000

    #define ADC1 ((REG_ADC*) ADC1_BASE)
    #define ADC1_SR (ADC1->rSR)
    #define ADC1_CR1 (ADC1->rCR1)
    #define ADC1_CR2 (ADC1->rCR2)
    #define ADC1_SMPR1 (ADC1->rSMPR1)
    #define ADC1_SMPR2 (ADC1->rSMPR2)
    #define ADC1_JOFR1 (ADC1->rJOFR1)
    #define ADC1_JOFR2 (ADC1->rJOFR2)
    #define ADC1_JOFR3 (ADC1->rJOFR3)
    #define ADC1_JOFR4 (ADC1->rJOFR4)
    #define ADC1_HTR (ADC1->rHTR)
    #define ADC1_LTR (ADC1->rLTR)
    #define ADC1_SQR1 (ADC1->rSQR1)
    #define ADC1_SQR2 (ADC1->rSQR2)
    #define ADC1_SQR3 (ADC1->rSQR3)
    #define ADC1_JSQR (ADC1->rJSQR)
    #define ADC1_JDR1 (ADC1->rJDR1)
    #define ADC1_JDR2 (ADC1->rJDR2)
    #define ADC1_JDR3 (ADC1->rJDR3)
    #define ADC1_JDR4 (ADC1->rJDR4)
    #define ADC1_DR (ADC1->rDR)
    #define ADC1_CRS (ADC1->rCRS)
    #define ADC1_CCR (ADC1->rCCR)
    #define ADC1_CDR (ADC1->rCDR)
    ```

    - STM32FDiscovery.h 파일에 선언.

## 2. STM32F board ADC 설정 

0. 전체 코드

    ```c
    void set_adc1() {        // ADC1, channel 1, PA1
        RCC_AHB1ENR |= 0x00000001;      // RCC clock enable
        GPIOA_MODER |= 3<<2;            // PA1 analog mode
        RCC_APB2ENR |= 1<<8;            // ADC1 clock enable
        RCC_CFGR |= 1<<15 | 1<<13;      // set APB2 div4 = 42 MHz

        ADC1_CR2 |= 1<<0;               // ADC1 enable
        
        ADC1_SMPR2 |= 3<<0;             // channel 1 sampling cycle 56 cycle
        ADC1_CR1 |= 2<<24 | 1<<5;       // 8-bit resolution
                                        // end-of-conversion interrupt enable
        
        ADC1_CCR |= 1<<16;              // PCLK2 div 4      haven't to know
        ADC1_SQR1 |= 0<<20;             // channel 1:1 conversion
        ADC1_SQR3 |= 1<<0;              // 1st conversion : channel 1

        NVIC_ISER0 |= 1<<18;            // enable interrupt
    }   
    ```

1. Port / Pin 설정

    A 포트를 통해 아날로그 신호를 받기위한 설정을 진행한다.
    
    - RCC_AHB1ENR |= 0x00000001; : A포트 Clock 활성화
    - GPIOA_MODER |= 3<<2; : 포트 mode를 아날로그 모드로 설정
    - RCC_APB2ENR |= 1<<8; : ADC1 Clock 활성화
    - ADC1_CR2 |= 1<<0; : ADC1 활성화

2. ADC 설정

    ADC 샘플링할 주기 설정

    - ADC1_SMPR2 |= 3<<0; : 56 cycle마다 1번씩 샘플링
    - ADC1_CR1 |= 2<<24 | 1<<5; : 샘플링 값을 8비트안에서 표시한다. 값을 더 올리면 자세하게 표현될 것이다. 
    
3. 인터럽트 설정

    - NVIC_ISER0 |= 1<<18; : 인터럽트 활성화

그 외의 세팅은 자세히 알 필요가 없다.

## 3. 동작 순서

1. 설정한 포트로 아날로그 전압값이 입력된다.

2. 설정한 Clock, Cycle 등 원하는 Resolution에 따른 측정시간동안 소요.

3. 아날로그 신호 변환을 완료하면 인터럽트를 발생시켜 gtkterm으로 값을 출력하게 한다.

이 과정(ADC가 처리)은 속도는 굉장히 빨라서 빠르게 출력된다.



-------------------------

# 2. ADC 변환 값을 UART로 plotting하는 프로그램 구현.

- stdio.h와 같은 standard library를 사용하지 않고 구현
- STM32FDiscovery.h 헤더파일만 참조

```c
void ADC1_IRQHandler() {
    if( ADC1_SR & 1<<1 ) {
        adc_val = ADC1_DR & 0xff;

        if(adc_val > 100) {
            buf[0] = adc_val/100 + '0';
            buf[1] = (adc_val % 100)/10 +'0';
            buf[2] = (adc_val % 100) % 10 +'0';
            buf[3] = '\n';
            len = 4;
        }
        else {
            buf[0] = adc_val/10 + '0';
            buf[1] = adc_val % 10 +'0';
            buf[2] = '\n';
            len = 3;
        }
        sendStr(buf, len);
    }
    ADC1_CR2 |= 1<<30;
}
```

- ADC1_SR & 1<<1 : ADC1의 Statu register가 1이 될 때 변환이 완료된 것이다.

- 입력 값을 직접 파싱하여 각 자리수를 버퍼에 입력하여 출력하게 하였다.