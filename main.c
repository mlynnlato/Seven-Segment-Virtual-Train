#include <msp430.h>
#include <Four_Digit_Display.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * main.c
 */
typedef enum {
ONE,
TWO,
THREE,
FOUR,
FIVE,
SIX,
SEVEN,
EIGHT,
NINE,
TEN,
ELEVEN,
TWELVE,
MAX_STATES
} state_t;

void init() {
    //initialize GPIOs
    //  P2DIR=0x00;
    P2DIR &=~BIT3; // &=~0x08
    P4DIR &=~BIT1;
    //  P2REN=0x08;
    P2REN |=0x08; // OR |= BIT3
    P4REN |=BIT1;
    //  P2OUT=0x08;
    P2OUT |=0x08; // OR |= BIT3
    P4OUT |=BIT1;
    //
    //  P1DIR=0x01;
    P1DIR |=BIT0;
    P6DIR |=BIT6;
}

void setGreen(bool en) {
    if(en) {
        P6OUT|=BIT6;
    }

    else {
        P6OUT &=~BIT6;
    }
}

void setRed(bool en) {
    if(en==true) {
        P1OUT |=BIT0;
    }

    else {
        P1OUT &=~BIT0;
    }
}

bool buttonPressedGO() {
    if((P4IN & BIT1)==0x00) {
        __delay_cycles(100000); //used for de-bouncing

        if((P4IN & BIT1)==0x00) {
            return true;
        }
    }

    return false;
}

bool buttonPressedSTOP() {
    if((P2IN & BIT3)==0x00) {
        __delay_cycles(100000); //used for de-bouncing

        if((P2IN & BIT3)==0x00) {
            return true;
        }
    }

    return false;
}

state_t runONE(bool direc){
    display_segment(POS_1, SEG_A | SEG_F|SEG_E);
    if(direc){
        return TWO;
    }else{
        return TWELVE;
    }
}
state_t runTWO(bool direc){
    display_segment(POS_2,SEG_A);
    display_segment(POS_1, SEG_A|SEG_F);
    if(direc){
        return THREE;
    }else{
        return ONE;
    }
}
state_t runTHREE(bool direc){
            display_segment(POS_3,SEG_A);
            display_segment(POS_2, SEG_A);
            display_segment(POS_1, SEG_A);

    if(direc){
        return FOUR;
    }else{
        return TWO;
    }
}
state_t runFOUR(bool direc){
            display_segment(POS_4, SEG_A);
            display_segment(POS_2, SEG_A);
            display_segment(POS_3, SEG_A);


    if(direc){
        return FIVE;
    }else{
        return THREE;
    }
}
state_t runFIVE(bool direc){
            display_segment(POS_3, SEG_A);
            display_segment(POS_4, SEG_A| SEG_B);

    if(direc){
        return SIX;
    }else{
        return FOUR;
    }
}
state_t runSIX(bool direc){
    display_segment(POS_4, SEG_A| SEG_B|SEG_C);

    if(direc){
        return SEVEN;
    }else{
        return FIVE;
    }
}
state_t runSEVEN(bool direc){
    display_segment(POS_4, SEG_D| SEG_B|SEG_C);

    if(direc){
        return EIGHT;
    }else{
        return SIX;
    }
}
state_t runEIGHT(bool direc){
            display_segment(POS_4, SEG_D|SEG_C);
            display_segment(POS_3, SEG_D);

    if(direc){
        return NINE;
    }else{
        return SEVEN;
    }
}
state_t runNINE(bool direc){
            display_segment(POS_4, SEG_D);
            display_segment(POS_3, SEG_D);
            display_segment(POS_2, SEG_D);

    if(direc){
        return TEN;
    }else{
        return EIGHT;
    }
}
state_t runTEN(bool direc){
            display_segment(POS_1, SEG_D);
            display_segment(POS_3, SEG_D);
            display_segment(POS_2, SEG_D);

    if(direc){
        return ELEVEN;
    }else{
        return NINE;
    }
}
state_t runELEVEN(bool direc){
            display_segment(POS_1, SEG_D|SEG_E);
            display_segment(POS_2, SEG_D);

    if(direc){
        return TWELVE;
    }else{
        return TEN;
    }
}
state_t runTWELVE(bool direc){
    display_segment(POS_1, SEG_D|SEG_E|SEG_F);

    if(direc){
        return ONE;
    }else{
        return ELEVEN;
    }
}

state_t (*state_table[MAX_STATES])(bool)={runONE, runTWO, runTHREE, runFOUR, runFIVE, runSIX, runSEVEN, runEIGHT, runNINE, runTEN, runELEVEN, runTWELVE};

int train(state_t exp,bool direction){
    state_t currentState= exp;
    state_t nextState=exp;
    four_digit_clear();
    if(buttonPressedSTOP()){ //SWITCHES DIRECTION
        direction=!direction;
    }
    setRed(false);
    setGreen(true);
    switch(currentState){
    case ONE:
//        display_segment(POS_1, SEG_A | SEG_F|SEG_E);
        nextState=runONE(direction);
        break;
    case TWO:
//        display_segment(POS_2,SEG_A);
//        display_segment(POS_1, SEG_A|SEG_F);
        nextState=runTWO(direction);
                break;
    case THREE:
//        display_segment(POS_3,SEG_A);
//        display_segment(POS_2, SEG_A);
//        display_segment(POS_1, SEG_A);
        nextState=runTHREE(direction);
        break;
    case FOUR:
//        display_segment(POS_4, SEG_A);
//        display_segment(POS_2, SEG_A);
//        display_segment(POS_3, SEG_A);
        nextState=runFOUR(direction);
        break;
    case FIVE:
//        display_segment(POS_3, SEG_A);
//        display_segment(POS_4, SEG_A| SEG_B);
        nextState=runFIVE(direction);
        break;
    case SIX:
//        display_segment(POS_4, SEG_A| SEG_B|SEG_C);
        nextState=runSIX(direction);
        break;
    case SEVEN:
//        display_segment(POS_4, SEG_D| SEG_B|SEG_C);
        nextState=runSEVEN(direction);
        break;
    case EIGHT:
//        display_segment(POS_4, SEG_D|SEG_C);
//        display_segment(POS_3, SEG_D);
        nextState=runEIGHT(direction);
        break;
    case NINE:
//        display_segment(POS_4, SEG_D);
//        display_segment(POS_3, SEG_D);
//        display_segment(POS_2, SEG_D);
        nextState=runNINE(direction);
        break;
    case TEN:
//        display_segment(POS_1, SEG_D);
//        display_segment(POS_3, SEG_D);
//        display_segment(POS_2, SEG_D);
        nextState=runTEN(direction);
        break;
    case ELEVEN:
//        display_segment(POS_1, SEG_D|SEG_E);
//        display_segment(POS_2, SEG_D);
        nextState=runELEVEN(direction);
        break;
    case TWELVE:
//        display_segment(POS_1, SEG_D|SEG_E|SEG_F);
        nextState=runTWELVE(direction);
        break;

    }
    currentState=nextState;

    if(buttonPressedGO()){ //STOPS THE TRAIN
        while((P4IN & BIT1) == 0x00){ //conditional while loop to check if button is released
             __delay_cycles(100000);   //delay to avoid any occurrence of bouncing
        }
        setRed(true);
        setGreen(false);

        return currentState;
    }
    __delay_cycles(1000000);
    train(currentState,direction);
}




int main(void) {
    WDTCTL=WDTPW | WDTHOLD; // stop watchdog timer
    PM5CTL0 &=~LOCKLPM5;
    init();
    P6OUT &=~BIT6;
    four_digit_init();
    four_digit_clear();
    state_t pos=ONE;


    while(1){
        pos=train(pos,true);
        while(!buttonPressedGO()){ //IF btn is pressed when while loop with terminate and recall train function

        }
    }

}



