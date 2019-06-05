
//Pin Connections
int DATA = 12;//pin 3
int DATA_OUTPUT_ENABLE = 11;//pin 4
int LATCH = 10;//pin 5
int CLOCK = 5;//pin 6
int RESET = 6;//pin 7

// Led matrix buffer
/*
Color codes:
0 - RGB Led off
1 - Green
2 - Red
3 - Yellow
4 - Blue
5 - Cyan
6 - Magenta
7 - White
*/
byte Screen[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}};

byte SmileyFace[8][8] = {{0, 0, 2, 2, 2, 2, 0, 0},
                         {0, 2, 0, 0, 0, 0, 2, 0},
                         {2, 0, 4, 0, 0, 4, 0, 2},
                         {2, 0, 0, 0, 0, 0, 0, 2},
                         {2, 0, 1, 0, 0, 1, 0, 2},
                         {2, 0, 0, 1, 1, 0, 0, 2},
                         {0, 2, 0, 0, 0, 0, 2, 0},
                         {0, 0, 2, 2, 2, 2, 0, 0}};

void sendBit(uint8_t aData)
{
  digitalWrite(DATA, aData);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, LOW);
}

void sendDataToDisplay()
{
  byte lineIndex;
  byte rowIndex;

  for (lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    //Set Anode Line
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if (lineIndex == rowIndex)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Green Row
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][7 - rowIndex] & 1) == 0) // fix
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Red Row
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 2) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Blue Row
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 4) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Send data to output
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
  }
}

void Clear()
{
  byte lineIndex;
  byte rowIndex;

  for (lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = 0;
    }
  }
}

void DisplaySmileyFace()
{
  byte lineIndex;
  byte rowIndex;

  for (lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for (rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = SmileyFace[lineIndex][rowIndex];
    }
  }
}

void setup()
{
  pinMode(DATA, OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);

  digitalWrite(DATA_OUTPUT_ENABLE, LOW);
  digitalWrite(RESET, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);

  Clear();
  DisplaySmileyFace();
}

void blink()
{
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}

void loop()
{
  sendDataToDisplay();

}