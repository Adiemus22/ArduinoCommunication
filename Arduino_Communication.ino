// DEFINITIONS
#define BUFFER_SIZE 128    // All these variable names will be replaced by these values
#define BIT_RATE 9600

// VARIABLES
char Buffer[BUFFER_SIZE];       // Buffer for storage of received chars
char helpBuffer[BUFFER_SIZE];   // Help buffer for argument handling
short positionOfEndChar;        // Length of incoming command
short bufferIndex;              // current writing position in Buffer
char receivedChar;              // Incoming char
char EndChar = '#';             // Final char of an incoming string
char ReturnChar = '*';          // Final return char
char resetChar = '%';           // Char telling to clean current buffer immediately


// SETUP
void setup()
{
  bufferIndex = 0;   // Set buffer reading position to 0
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(BIT_RATE);  // Start connection
}


// LOOP looking for new signs from computer
void loop()
{
  while (Serial.available() > 0)    // if there are new cigns from computer
  {
    receivedChar = Serial.read();         // read it
    receiveAndStoreChar(receivedChar);
  }
}


// Received character handling
void receiveAndStoreChar(char _receivedChar)
{
  // Skip invalid chars
  if(_receivedChar == '\n') return;
  if(_receivedChar == -1) return;
  

  // Look at received char
  if(_receivedChar == EndChar)
  {
    // If EndChar, the full command has been received. Save Length of command and call Distributor function.
    positionOfEndChar = bufferIndex;
    Distributor();
  }
  else if(_receivedChar == resetChar)
  {
    // If reset char, reset buffer
    ClearBuffer();
  }
  else
  {
    // If any other valid char, add to buffer and increment buffer index variable
    Buffer[bufferIndex] = receivedChar;
    bufferIndex++;

    // If the command length exceeds the buffer size, send an error message and clear buffer.
    if (bufferIndex >= BUFFER_SIZE)    
    {
      Serial.print("Cmd length error!");
      ClearBuffer();
    }
  }
}


// Buffer clearage and buffer index reset
void ClearBuffer()
{
  memset(Buffer, 0, sizeof(Buffer));
  bufferIndex = 0;
}


// Command Function caller
void Distributor()    // Looks at the first char of the incoming command (i.e. the buffer) and calls the corresponding function
{
  bufferIndex = 0;
  switch(Buffer[0])   // Buffer[0] = first sign of the command
  {
    case '?':     // arduino self identification
      Identify();
      break;

    case 'd':     // delay
      Delay();
      break;

    case 'e':     // example function
      Example();
      break;
      
    default:      // error message if unknown command type
      Serial.print("undef: '");
      Serial.print(Buffer[0]);
      Serial.print("'");
    break;
  }

  Serial.print(ReturnChar);   // Return end char to tell that command has been worked off

  ClearBuffer();  // Clears Buffer to be ready for next command
}


/* APPLICATION FUNCTIONS */
/* --------------------- */

// Sends the arduino identification string as reply
void Identify()     
{
    Serial.print("arduino"); 
}


// Executes system delay
void Delay()
{
  for(int x = 1; x < positionOfEndChar; x++) helpBuffer[x-1] = Buffer[x];   // Shift Argument to new buffer
  helpBuffer[positionOfEndChar] = '\0';      // Add end character to new buffer
  delay(atoi(helpBuffer));                   // Transfer new buffer to int and delays (in ms)
}


// turns on built-in LED if second char is '0', else turns it off
void Example()
{
  if(Buffer[1] == '0')
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
