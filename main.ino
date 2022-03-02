/* pin layout
buttons:
    blue buttons 1-5 = pins 0-4;
    green buttons 1-5 = pins 5-9;

leds:
    blue buttons 1-5 = pins 10-14;
    green buttons 1-5 = pins 15-19;
*/

//button presses necessary to win the game
#define score_WIN = 50;


//keeps track of the currently lit up button
int activeButton_BLUE;
int activeButton_GREEN;

//true when game is in progress (for the loading screen)
bool gameInProgress = false;

//keeps track of button presses
int score_BLUE = 0;
int score_GREEN = 0;

/*
initialize all button pins as inputs and all led pins as outputs
also set all leds to LOW
*/

void setup(){
    

}

void loop(){

    //waits until the game is started
    if(startConditionMet()){
        killAllLEDs();
        gameInProgress = true;

        active_BLUE = selectRandomButton_BLUE();
        active_GREEN = selectRandomButton_GREEN();
    }

    while(gameInProgress){
        //if the active button is pressed, choose a new button, turn off the old one, and increase that player's score.
        if(digitalRead(active_BLUE)){
            killLED(active_BLUE);
            active_BLUE = selectRandomButton_BLUE();
            score_BLUE++;
        }
        else if(digitalRead(active_GREEN)){
            killLED(active_GREEN);
            active_GREEN = selectRandomButton_GREEN();
            score_GREEN++;
        }

        //check for winner
        if(score_GREEN >= score_WIN){
            flashWinner_GREEN();
            gameInProgress = false; //end the game and wait for button press to start it again 
        }

        else if(score_BLUE >= score_WIN){
            flashWinner_BLUE();
            gameInProgress = false;
        }

    }
    
}

//returns true if any button is being pressed
bool startConditionMet();

//accepts a button pin, and returns the corresponding led pin
int correspondingLED(int pin){
    return pin + 10;
};

//returns a random integer from 0 to 4 inclusive and sets that pins corresponding led to high
int selectRandomButton_BLUE();

//returns a random integer from 5 to 9 inclusive and sets that pins corresponding led to high
int selectRandomButton_GREEN();

//accepts a button pin, and sets the corresponding led low
void killLED(int pin);

//turns off all the leds
void killAllLEDs();

//flash all the blue buttons, and turn off all the green ones.
void flashWinner_BLUE();

//flash all the green buttons, and turn off all the blue ones.
void flashWinner_GREEN();