#include <msp430.h>
#include <stdlib.h>
#include "timerLib/libTimer.h"
#include "led.h"
#include "h/lcdutils.h"


void switch_interrupt_handler();
void showPosition();
int testUser();

#define MAXMEMORY 5  
int memory[MAXMEMORY];
int memoryCount = 0;
int userInput = 0;
int count = 0;

int main(void) {	// ALL LIGHTS -> OUTPUTS

  switch_init();
  led_init();
  wdt_init();
  buzzer_init();
  lcd_init();
  
  or_sr(0x18);
}


void showPosition(){
  if(memory[count] == 1){
    P1OUT |= LED_GREEN;
    buzzer_set_period(1000);
  }
  else{
    P1OUT |= LED_RED;
    buzzer_set_period(200);
  }
}

void switch_interrupt_handler(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  if (!(p2val & SW1)){
    buzzer_set_period(1000);
    userInput = 1;}
  else if (!(p2val & SW2)){
    buzzer_set_period(200);
    userInput = 2;}
  else{
    buzzer_set_period(0);
    userInput = 0;}
}

int testUser(){
  static int waitForRest = 0;
  if(count == memoryCount && waitForRest == 0){
    count = 0;
    return 1;
  }
  else if(waitForRest == 0){
    if(userInput == memory[count]){
      waitForRest = 1;
      count++;
    }
    else if(userInput != memory[count] && userInput != 0){
      count = 0;
      P1OUT |= LEDS;
    }
  }
  else if(waitForRest == 1)
    if(userInput == 0)
      waitForRest = 0;
  return 0;
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){
  static int secondCount = 0;
  static int state = 1;
  
  secondCount++;


  //S1 ADD TO MEMORY AND BEGIN READING CURRENT MEMORY (S2).
  if(state == 1 && secondCount >= 300){
    if (memoryCount < MAXMEMORY){
      memory[memoryCount++] = (rand() % 2)+1;
    }
    state = 2;
    secondCount = 0;
  }

  //S2 DISPLAY POSITION AND MOVE TO BLINK (S3)
  else if (state == 2 && secondCount >= 50){
    showPosition(count);
    count++;
    secondCount = 0;
    state = 3;
  }

  //S3 TURN OFF ALL LEDS AND CYCLE THROUGH S2 AND S3 UNTIL MAX MEMORY
  //THEN TEST USER (S4)
  else if (state == 3 && secondCount >= 50){
    P1OUT &= ~LEDS;
    buzzer_set_period(0);
    secondCount = 0;
    if(count != memoryCount)
      state = 2;
    else{
      state = 4;
      count = 0;
    }
  }
  //S4 TEST USER AND RETURN TO ADD TO MEMORY
  else if(state == 4){
    secondCount--;
    if(testUser())
      state = 1;
  }
}
