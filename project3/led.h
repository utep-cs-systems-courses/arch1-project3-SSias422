#ifndef led_included
#define led_included

//LEDS
#define LED_GREEN BIT0		// P1.0 Green Light
#define LED_RED BIT6		// P1.6 Red Light
#define LEDS (BIT0 | BIT6)	// Both Lights

//SWITCHES
#define SW1 BIT0
#define SW2 BIT3
#define SWITCHES (SW1 | SW2)

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

void wdt_init(){
  configureClocks();
  enableWDTInterrupts();
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
}

void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

#endif
