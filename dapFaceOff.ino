/* pin layout
buttons:
    blue buttons 1-5 = pins 2-6; 
    blue temp = 2 and 3
    red buttons 1-5 = pins 7-11;
    red temp = 7 and 8
leds:
    blue buttons 1-5 = analog pins 0-4 = digital pins 54-58;
                        analog pins 0-2 = digital 54-56
    red buttons 1-5 = analog pins 5-9 = digital pins 59-63;
                    analog pins 5-6 = digital pins 59-61
*/

// button presses necessary to win the game
const int score_WIN = 50;
const int stage2 = 30;
const int stage3 = 45;

// keeps track of the currently lit up button
int activeButton_BLUE;
int activeButton_red;

// 0 = startScreen, 1 = simple, 2 = hard mode, 3 = impossible
int gameMode = 0;

// keeps track of button presses
int score_BLUE = 0;
int score_red = 0;


/*
initialize all button pins as inputs and all led pins as outputs
also set all leds to LOW
*/
void setup()
{
    Serial.begin(115200);
    for (int i = 2; i <= 11; ++i)
    {
        pinMode(i, INPUT);
    }

    for (int i = 2; i <= 11; ++i)
    {
        pinMode(correspondingLED(i), OUTPUT);
    }

    killAllLEDs();
    for(int i = 2; i <=4; i++){
        digitalWrite(correspondingLED(i), HIGH);
    }

    randomSeed(analogRead(15));
}

void loop()
{

    delay(50);

    // waits until the gamemode is selected
    if (gameStarted())
    {
        killAllLEDs();

        activeButton_BLUE = selectRandomButton_BLUE();
        activeButton_red = selectRandomButton_red();
    }

    Serial.print("GameMode: ");
    Serial.println(gameMode);
    while (gameMode == 1)
    {
        Serial.print("score_BLUE: ");
        Serial.print(score_BLUE);

        Serial.print("\t score_red: ");
        Serial.println(score_red);
        gameMode1();

        checkWinCondition();
        delay(50);
    }
    
    while (gameMode == 2)
    {
        if (checkStage2Condition())
        {
            gameMode2();
        }
        else
            gameMode1();

        checkWinCondition();
        delay(50);
    }

    while (gameMode == 3)
    {
        if (checkStage3Condition())
        {
            gameMode3();
        }
        else if (checkStage2Condition())
        {
            gameMode2();
        }
        else
            gameMode1();

        checkWinCondition();
        delay(50);
    }
}

// returns true if game select buttons are pressed, and sets gameMode variable to the chosen gamemode
bool gameStarted()
{
    for (int i = 2; i <= 4; ++i)
    {
        if (digitalRead(i))
        {
            gameMode = i - 1;
            return true;
        }
    }
    return false;
};

// returns a random integer from 2 to 6 inclusive and sets that pins corresponding led to high
int selectRandomButton_BLUE()
{
    int rand = random(2, 4);
    digitalWrite(correspondingLED(rand), HIGH);
    return rand;
};

// returns a random integer from 7 to 11 inclusive and sets that pins corresponding led to high
int selectRandomButton_red()
{
    int rand = random(7, 9);
    digitalWrite(correspondingLED(rand), HIGH);
    return rand;
}

//returns the corresponding led pin for a given button pin
int correspondingLED(int pin){
    return pin + 52;
}

// turns off all the leds
void killAllLEDs()
{
    for (int i = 2; i <= 11; ++i)
    {
        digitalWrite(correspondingLED(i), LOW);
    }
};

// accepts a bool, 0 if blue, 1 if red, flash all the winners buttons, and turn off all the opponent buttons.
void flashWinner(bool winner)
{
    // lower number is faster blinking
    int blinkSpeed = 200;
    killAllLEDs();

    switch (winner)
    {
    case 0:
        for (int i = 0; i < 10; ++i)
        {
            for (int i = 2; i <= 6; ++i)
            {
                digitalWrite(correspondingLED(i), HIGH);
            }
            delay(blinkSpeed);

            for (int i = 2; i <= 6; ++i)
            {
                digitalWrite(correspondingLED(i), LOW);
            }
            delay(blinkSpeed);
        }
        break;
    case 1:

        for (int i = 0; i < 10; ++i)
        {
            for (int i = 7; i <= 11; ++i)
            {
                digitalWrite(correspondingLED(i), HIGH);
            }
            delay(blinkSpeed);

            for (int i = 7; i <= 11; ++i)
            {
                digitalWrite(correspondingLED(i), LOW);
            }
            delay(blinkSpeed);
        }

        break;
    }
};

// sets gameMode to 0, kills all leds, and lights up buttons 1-3 for choosing the gamemode
void resetGame(){
    gameMode = 0;

    killAllLEDs();
    for(int i = 2; i <=4; i++){
        digitalWrite(correspondingLED(i), HIGH);
    }

    score_BLUE = 0;
    score_red = 0;

};

// gameMode 1 operation
void gameMode1()
{
    // if the active button is pressed, choose a new button, turn off the old one, and increase that player's score.
    if (digitalRead(activeButton_BLUE))
    {
        digitalWrite(correspondingLED(activeButton_BLUE),LOW);
        activeButton_BLUE = selectRandomButton_BLUE();
        score_BLUE++;
    }
    else if (digitalRead(activeButton_red))
    {
        digitalWrite(correspondingLED(activeButton_red), LOW);
        activeButton_red = selectRandomButton_red();
        score_red++;
    }
}

// gameMode 2 operation
void gameMode2(){};

// gameMode 3 operation
void gameMode3(){};

// check for transition to stage 2
bool checkStage2Condition()
{
    if (score_red >= stage2)
    {
        flashWinner(1);
        resetGame();
    }

    else if (score_BLUE >= stage2)
    {
        flashWinner(0);
        resetGame();
    }
}

// check for transition to stage 3
bool checkStage3Condition()
{
    if (score_red >= stage3)
    {
        flashWinner(1);
        resetGame();
    }

    else if (score_BLUE >= stage3)
    {
        flashWinner(0);
        resetGame();
    }
}

// check if any team has won, if so, flash their buttons and reset the game
void checkWinCondition()
{
    if (score_red >= score_WIN)
    {
        flashWinner(1);
        resetGame();
    }

    else if (score_BLUE >= score_WIN)
    {
        flashWinner(0);
        resetGame();
    }
}
