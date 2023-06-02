// DEFINITIONS
#define def_BufferSize 128    // All these variable names will be replaced bz these values
#define def_BitRate 9600

// VARIABLES
char Buffer[def_BufferSize];  // Buffer
char helpBuffer[def_BufferSize];
short positionOfEndSign;
char Sign;                    // Current read sign
byte nIndex;               // current position in Buffer
char EndSign = '#';           // Final sign of an incoming string
char ReturnEndSign = '*';     // Final return sign
char emptyBufferSign = '%';   // Sign tellng to clean current buffer immediately


// SETUP
void setup()
{
  nIndex = 0;   // Set buffer reading position to 0
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(def_BitRate);  // Start connection
}


// LOOP looking for new signs from computer
void loop()
{
  while (Serial.available() > 0)    // if there are new cigns from computer
  {
    Sign = Serial.read();         // read it
    if (Sign == EndSign)          // if it is the endsign (signifying the end of the command from the computer)
    {
      Buffer[nIndex++] = EndSign; 
      positionOfEndSign = nIndex; // Save position of endsign in the buffer
      Distributor();              // Call the Distributor
    }
    else if (Sign == emptyBufferSign)   // If it is the empty-buffer-sign, the current buffer will be cleared
    {
      ClearBuffer();
    }
    else
    {
      Buffer[nIndex] = Sign;          // If it is any other sign, save it to the buffer at the current position
      nIndex++;                       // Increase buffer position
      if (nIndex > def_BufferSize)    // If the command is longer than the buffer size, send an error message.
      {
        ClearBuffer();
      }
    }
  }
}


void ClearBuffer()  // Clears Buffer
{
  for(int i = 0; i < def_BufferSize; i++) Buffer[i] = ' ';
  Sign = ' ';
  nIndex = -1;
}

void Distributor()    // Looks at the first sign of the incoming command (i.e. the buffer) and calls the corresponding function
{
  switch(Buffer[0])   // Buffer[0] = first sign of the command
  {
    case '?':
      Identify();
      break;

    case 'd':
      Delay();
      break;

    case 'e':
      Example();
      break;
      
    default:
      Serial.print(Buffer[0]);
      Serial.print(" undef.");   
    break;
  }

  Serial.print(ReturnEndSign);   // Return endsign for 
  ClearBuffer();
}


void Identify()     // Sends the arduino identification string as reply
{
    Serial.print("arduino"); 
}


void Delay()
{
  for(int x = 1; x < positionOfEndSign; x++) helpBuffer[x-1] = Buffer[x];   // Shift Argument to new buffer
  helpBuffer[positionOfEndSign] = '\0';      // Add end character to new buffer
  delay(atoi(helpBuffer));                   // Transfer new buffer to int and delay
}


void Example()  // turns on built-in LED if second char is '1', else turns it off
{
  if(Buffer[1] == '1')
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
