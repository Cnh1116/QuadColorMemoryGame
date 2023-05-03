// Arduino QUAD-COLOR MEMORY GAME
//
// Carson Holland
// Started: May 2023
//
// In memory of William Stapleton

// Global Variables~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int BLUE_LED_READ = 2; int START_LED_READ = 2; //Marking the start and end of the LEDs
int GREEN_LED_READ = 3;                   //wiring them sequentially makes operating on all of them simpler
int YELLOW_LED_READ = 4;
int RED_LED_READ = 5; int END_LED_READ = 5;

int BLUE_LED_OUT = 6; int START_LED_OUT = 6; //Marking the start and end of the LEDs
int GREEN_LED_OUT = 7;                   //wiring them sequentially makes operating on all of them simpler
int YELLOW_LED_OUT = 8;
int RED_LED_OUT = 9; int END_LED_OUT = 9;

int answer_array[100];
int round_number = 0;

void setup() 
{
  Serial.begin(9600);
 
  //Variables
  int current_answer;
  bool round_won;
  
  for(int CURRENT_LED = START_LED_READ; CURRENT_LED <= END_LED_READ; CURRENT_LED++) //Set All READ LED Pins
  {
    digitalWrite(CURRENT_LED, LOW);
    pinMode(CURRENT_LED, INPUT);
  }
  for(int CURRENT_LED = START_LED_OUT; CURRENT_LED <= END_LED_OUT; CURRENT_LED++) //Set All OUTPUT LED Pins
  {
    digitalWrite(CURRENT_LED, LOW);
    pinMode(CURRENT_LED, OUTPUT);
  }
  for(int i = 30; i <= 37; i++) //Set All OUTPUT Pins Digit 0 7SD
  {
    digitalWrite(i, LOW);
    pinMode(i, OUTPUT);
  }
  for(int i = 40; i <= 47; i++) //Set All OUTPUT Pins Digit 1 7SD
  {
    digitalWrite(i, LOW);
    pinMode(i, OUTPUT);
  }
  setDigit0(0);
  setDigit1(0);

  funLightAnimation(); //Light Animation
  do                  //Gameplay loop
  {
    generateRoundAnswer();
    displayAllAnswers();
    round_won = playRound();
    if (round_won) round_number++;
    setDigit0(round_number%10);
    setDigit1(round_number/10);
  }while(round_won);
  
}//VOID SETUP END

void loop() 
{
  
} //VOID LOOP END

void displayAllLED()
{
  for(int CURRENT_LED = START_LED_OUT; CURRENT_LED <= END_LED_OUT; CURRENT_LED++)
  {
    digitalWrite(CURRENT_LED, HIGH);
    delay(500);
    digitalWrite(CURRENT_LED, LOW);
  }
};
void displayAllAnswers()
{
  delay(500);
  for(int i = 0; i <= round_number; i++)
  {
    delay(60);
    digitalWrite(answer_array[i], HIGH);
    delay(500);
    Serial.print("Answer Array at round "); Serial.println(round_number);
    Serial.print("Answer:"); Serial.println(answer_array[i]);
    digitalWrite(answer_array[i], LOW);
  }
}
int readButtonPress()
{
  do //Waiting for a button to be pushed...
  {
    delay(50);
  }while((digitalRead(BLUE_LED_READ)==LOW && // Wait until a button is pressed
          (digitalRead(GREEN_LED_READ)==LOW))&&
          (digitalRead(YELLOW_LED_READ)==LOW)&&
          (digitalRead(RED_LED_READ)==LOW));
  
  if(digitalRead(BLUE_LED_READ)==HIGH) //IF BLUE was input read
  {
      digitalWrite(BLUE_LED_OUT, HIGH); 
      delay(500); 
      digitalWrite(BLUE_LED_OUT,LOW);
      return (BLUE_LED_OUT);
  } 
  else if(digitalRead(GREEN_LED_READ)==HIGH) //IF GREEN was input read
    {
      digitalWrite(GREEN_LED_OUT, HIGH); 
      delay(500); 
      digitalWrite(GREEN_LED_OUT,LOW); 
      return (GREEN_LED_OUT);
  } 
  else if(digitalRead(YELLOW_LED_READ)==HIGH) //IF YELLOW was input read
  {
    digitalWrite(YELLOW_LED_OUT, HIGH); 
    delay(500); 
    digitalWrite(YELLOW_LED_OUT,LOW);
    return (YELLOW_LED_OUT);
  } 
  else if(digitalRead(RED_LED_READ)==HIGH) //IF RED was input read
  {
    digitalWrite(RED_LED_OUT, HIGH); 
    delay(500); 
    digitalWrite(RED_LED_OUT,LOW);
    return (RED_LED_OUT);
  }
  delay(150);
}
void generateRoundAnswer()
{
  srandom(analogRead(0));
  answer_array[round_number] = random(START_LED_OUT, END_LED_OUT);
}
void funLightAnimation()
{
   for(int repeats = 0; repeats < 4; repeats++)
   {
    for(int CURRENT_LED = START_LED_OUT; CURRENT_LED <= END_LED_OUT; CURRENT_LED++)
    {
      digitalWrite(CURRENT_LED, HIGH);
      delay(145);
      digitalWrite(CURRENT_LED, LOW);
    }
   }
   delay(1000);
}
void fastAnimation()
{
  for(int repeats = 0; repeats < 10; repeats++)
   {
    for(int CURRENT_LED = START_LED_OUT; CURRENT_LED <= END_LED_OUT; CURRENT_LED++)
    {
      digitalWrite(CURRENT_LED, HIGH);
      delay(20);
      digitalWrite(CURRENT_LED, LOW);
    }
   }
   delay(1000);
}
bool playRound()
{
  int current_answer_array[round_number];
  for(int i = 0; i <= round_number; i++)
  {
    current_answer_array[i] = readButtonPress();
    Serial.print("The player's choice: "); Serial.println(current_answer_array[i]);
    Serial.print("The answer for this round "); Serial.println(answer_array[i]);
  
 
    if(current_answer_array[i] != answer_array[i])
    {
      Serial.print("i = "); Serial.println(i);
      Serial.print("Current Answer [i] == Answer Array[i]");Serial.println(current_answer_array[i] == answer_array[i]) ;
      digitalWrite(RED_LED_OUT, HIGH);
      return false;
    }
  }
  return true;
}
void setDigit0(int number) //Function to manually set A-G pins on Seven Segment Display
{
  if(number < 0 || number > 10) //IF number is not 0-9, display error
  {
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
    digitalWrite(34, LOW);
    digitalWrite(35, LOW);
    digitalWrite(36, HIGH);
    digitalWrite(37, LOW);
  }
  switch(number)
  {
    case 0:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, HIGH);
      digitalWrite(36, LOW);
      digitalWrite(37, LOW);
      break;
    case 1:
      digitalWrite(30, LOW);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, LOW);
      digitalWrite(34, LOW);
      digitalWrite(35, LOW);
      digitalWrite(36, LOW);
      digitalWrite(37, LOW);
      break;
    case 2:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, LOW);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, LOW);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
    case 3:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, LOW);
      digitalWrite(35, LOW);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
    case 4:
      digitalWrite(30, LOW);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, LOW);
      digitalWrite(34, LOW);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
     case 5:
      digitalWrite(30, HIGH);
      digitalWrite(31, LOW);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, LOW);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
     case 6:
      digitalWrite(30, HIGH);
      digitalWrite(31, LOW);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
     case 7:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, LOW);
      digitalWrite(34, LOW);
      digitalWrite(35, LOW);
      digitalWrite(36, LOW);
      digitalWrite(37, LOW);
      break;
     case 8:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
     case 9:
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, LOW);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      break;
  }
}
void setDigit1(int number) //Function to manually set A-G pins on Seven Segment Display
{
  if(number < 0 || number > 10) //IF number is not 0-9, display error
  {
    digitalWrite(40, LOW);
    digitalWrite(41, LOW);
    digitalWrite(42, LOW);
    digitalWrite(43, LOW);
    digitalWrite(44, LOW);
    digitalWrite(45, LOW);
    digitalWrite(46, HIGH);
    digitalWrite(47, LOW);
  }
  switch(number)
  {
    case 0:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, HIGH);
      digitalWrite(45, HIGH);
      digitalWrite(46, LOW);
      digitalWrite(47, LOW);
      break;
    case 1:
      digitalWrite(40, LOW);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, LOW);
      digitalWrite(44, LOW);
      digitalWrite(45, LOW);
      digitalWrite(46, LOW);
      digitalWrite(47, LOW);
      break;
    case 2:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, LOW);
      digitalWrite(43, HIGH);
      digitalWrite(44, HIGH);
      digitalWrite(45, LOW);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
    case 3:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, LOW);
      digitalWrite(45, LOW);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
    case 4:
      digitalWrite(40, LOW);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, LOW);
      digitalWrite(44, LOW);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
     case 5:
      digitalWrite(40, HIGH);
      digitalWrite(41, LOW);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, LOW);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
     case 6:
      digitalWrite(40, HIGH);
      digitalWrite(41, LOW);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, HIGH);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
     case 7:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, LOW);
      digitalWrite(44, LOW);
      digitalWrite(45, LOW);
      digitalWrite(46, LOW);
      digitalWrite(47, LOW);
      break;
     case 8:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, HIGH);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
     case 9:
      digitalWrite(40, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(42, HIGH);
      digitalWrite(43, HIGH);
      digitalWrite(44, LOW);
      digitalWrite(45, HIGH);
      digitalWrite(46, HIGH);
      digitalWrite(47, LOW);
      break;
  }
}
