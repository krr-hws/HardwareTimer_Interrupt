#include "mbed.h"
DigitalOut led(LED1);

void timer_isr(void){
    TIM3->SR = 0;
    led = !led;
}

void timerInit(void){
    RCC->APB1ENR |= 0b10;   //Timer3 mit f=100MHz -> T=10ns
    TIM3->PSC=9999;         //Timer-Takt mit T=100us
    TIM3->ARR=10000;        //10.000 * 100us = 1s
    TIM3->CNT=0;            //bei 0 beginnen
    TIM3->SR=0;             //UIF = 0 - Update Interrupt Flag zurücksetzen
    TIM3->DIER=1;           //UIE = 1 - Update Interrupt Enable setzen

    //Im NVIC an Adr. TIM3_IRQn die Adresse der ISR eintragen
    NVIC_SetVector(TIM3_IRQn, (uint32_t)&timer_isr);  
    //Aktivierung des Interrupts im NVIC  
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    TIM3->CR1=1; //CEN=1 start
}


int main()
{
    timerInit();
    __enable_irq(); //Gloabale Interruptfreigabe

    while (true) {
    }
}
