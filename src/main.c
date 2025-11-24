
#include "stm32f1xx.h"

void delay(void) {
    for(volatile int i = 0; i < 1000000; i++);
}

int main(void) {
    // Включаем тактирование GPIOA и USART2
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    // Настраиваем PA2 (TX) для USART2
    GPIOA->CRL |= GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1;
    GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
    
    // Настройка USART2
    USART2->BRR = 8000000 / 115200;
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;
    
    while(1) {
        const char *msg = "hello artem\r\n";
        while(*msg) {
            while(!(USART2->SR & USART_SR_TXE));
            USART2->DR = *msg++;
        }
        delay();
    }
}