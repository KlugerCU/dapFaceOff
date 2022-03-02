/* pin layout
buttons:
    blue buttons 1-5 = pins 0-4;
    green buttons 1-5 = pins 5-9;

leds:
    blue buttons 1-5 = pins 10-14;
    green buttons 1-5 = pins 15-19;
*/

//button presses necessary to win the game
const int score_WIN = 50;
const int stage2 = 30;
const int stage3 = 45;


//keeps track of the currently lit up button
int activeButton_BLUE;
int activeButton_GREEN;

// 0 = startScreen, 1 = simple, 2 = hard mode, 3 = impossible
int gameMode = 0;

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

    //waits until the gamemode is selected
    if(gameStarted()){
        killAllLEDs();

        activeButton_BLUE = selectRandomButton_BLUE();
        activeButton_GREEN = selectRandomButton_GREEN();
    }

    while(gameMode == 1){
        gameMode1();
        
        checkWinCondition();
    }

    while(gameMode == 2){
        if(checkStage2Condition())
        {
            gameMode2();
        }
        else
            gameMode1();

        checkWinCondition();
    }
    
    while(gameMode == 3){
        if(checkStage3Condition())
        {
            gameMode3();
        }
        else if(checkStage2Condition())
        {
            gameMode2();
        }
        else
            gameMode1();

        checkWinCondition();
    }
}

//returns true if game select buttons are pressed, and sets gameMode variable to the chosen gamemode
bool gameStarted(){};

//accepts a button pin, and returns the corresponding led pin
int correspondingLED(int pin){
    return pin + 10;
};

//returns a random integer from 0 to 4 inclusive and sets that pins corresponding led to high
int selectRandomButton_BLUE(){};

//returns a random integer from 5 to 9 inclusive and sets that pins corresponding led to high
int selectRandomButton_GREEN(){};

//accepts a button pin, and sets the corresponding led low
void killLED(int pin){};

//turns off all the leds
void killAllLEDs(){};

//accepts a bool, 0 if blue, 1 if green, flash all the winners buttons, and turn off all the opponent buttons.
void flashWinner(bool winner){};

//sets gameMode to 0, kills all leds, and lights up buttons 1-3 for choosing the gamemode
void resetGame(){};

//gameMode 1 operation
void gameMode1(){
    //if the active button is pressed, choose a new button, turn off the old one, and increase that player's score.
    if(digitalRead(activeButton_BLUE)){
        killLED(activeButton_BLUE);
        activeButton_BLUE = selectRandomButton_BLUE();
        score_BLUE++;
    }
    else if(digitalRead(activeButton_GREEN)){
        killLED(activeButton_GREEN);
        activeButton_GREEN = selectRandomButton_GREEN();
        score_GREEN++;
    }
}

//gameMode 2 operation
void gameMode2(){};

//gameMode 3 operation
void gameMode3(){};

//check for transition to stage 2
bool checkStage2Condition(){
    if(score_GREEN >= stage2){
        flashWinner(1);
        resetGame();
    }

    else if(score_BLUE >= stage2){
        flashWinner(0);
        resetGame();
    }
}

//check for transition to stage 3
bool checkStage3Condition(){
    if(score_GREEN >= stage3){
        flashWinner(1);
        resetGame();
    }

    else if(score_BLUE >= stage3){
        flashWinner(0);
        resetGame();
    }
}

//check if any team has one, if so, flash their buttons and reset the game
void checkWinCondition(){
    if(score_GREEN >= score_WIN){
        flashWinner(1);
        resetGame();
    }

    else if(score_BLUE >= score_WIN){
        flashWinner(0);
        resetGame();
    }
}
