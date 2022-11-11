#define def_BufferSize 128    // "#define" replaces the term (here "def_BufferSize") by a value (here: "128") while compiling

// global variables definition:
char Buffer[def_BufferSize];  // Buffer
char helpBuffer[def_BufferSize];  // help buffer for arguments
short positionOfEndSign;      // help sign for parsing
char Sign;                    // Current read sign
byte nIndex = 0;              // current position in Buffer
char EndSign = '#';           // Final sign of an incoming string
char ReturnEndSign = '*';     // Final return sign
char emptyBufferSign = '%';   // Sign tellng to clean current buffer immediately



void setup() {      // runs once at arduino start
  Serial.begin(9600);   // begin to listen for possible connections
}

void loop() {                       // runs constantly
while (Serial.available() > 0)      // Searching for incoming chars over and over again
  {
    Sign = Serial.read();           // read incoming char and store it in "Sign"
    if (Sign == EndSign)            // if Sign == EndSign (defined in line 8), the command will end
    {
      Buffer[nIndex++] = EndSign;     // add EndSign to the buffer (why not!)
      positionOfEndSign = nIndex;     // store position of the Endsign in "positionEndSign" to know the length of this char
      Distributor();                  // call distributer function
      nIndex = 0;                     // reset nIndex
      Serial.print(ReturnEndSign);   // return ReturnEndSign to computer so the computer knows the Arduino is ready for the next command

    }
    else if (Sign == emptyBufferSign) // if incoming char is an escape sign (in case something went wrong), just clear the buffer and reset nIndex. System resettet.
    {
      ClearBuffer();
      nIndex = 0;
    }
    else                            // if the incoming char is something else, just add it to the buffer and increase nIndex.
    {
      Buffer[nIndex] = Sign;
      nIndex++;
      
      if (nIndex > def_BufferSize)  // if buffer is overfilled, return error and set nIndex to 0.
      {
        Serial.print("E0001");
        nIndex = 0;
        ClearBuffer();
        Serial.print(ReturnEndSign);
      }
    }
  }
}


void ClearBuffer()  // Clears Buffer
{
  nIndex = 0;
  for(int i = 0; i < def_BufferSize; i++) Buffer[i] = ' ';
}

void Distributor()  // The first char of an incoming command string defines the function to be called. The remaining chars are parameters that
{                   // must be analysed and evaluated by the called function itself
  switch(Buffer[0])   // cases for first char
  {
    case '?':         // in case first char is '?' identify the arduino.
    Identify();
    break;

    /*
     *  ----------------
     *  insert code here
     *  ----------------
     *  
     */
    
    default:          // in case it is anything else that has not been mentioned so far just do nothing
    break;
  }
}

void Identify()   // Identification of Arduino (e.g. "nodeMCURR")
{
    Serial.print("nodeMCURR");
}

void Wait()   // wait for a certain timespan (in ms)
{
  for(int x = 1; x < positionOfEndSign; x++) helpBuffer[x-1] = Buffer[x];   // "helpbuffer" is a small buffer that contains the parameter
                                                                            // (timespan in ms to wait)
  helpBuffer[positionOfEndSign] = '\0';
  delay(atof(helpBuffer));                                                  // "atof" turns a char array into a number. End char must be '\0'
}

// by Dr René Riedel, 2022.
