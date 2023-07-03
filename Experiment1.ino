static const char spinner[] = "-\\|/";  // Array of ASCII spinning characters
static int spinnerIndex = 0;  // Current index of the spinner character

unsigned long startTime = 0; 
unsigned long currentTime = 0; 

const int vibration = 9;    
const int elektricitet  = 10;       

const int intertrialTid = 10000; // 10 sekunder mellan trials 
const int antalTrial = 10;    
int currentTrial = 0 ;  

void setup() {
   Serial.begin(9600);
   Serial.println();
   Serial.println("Please send a character to start the sketch");
   while (Serial.available() == 0) {
      Serial.print(spinner[spinnerIndex]);  // Print the spinner character
      spinnerIndex = (spinnerIndex + 1) % sizeof(spinner);  // Update the spinner index
      delay(100);  // Delay between each spinner character update
   }
   while (Serial.available() > 0) {
      Serial.read(); // Empty the read buffer
   }

  pinMode(vibration, OUTPUT);
  pinMode(elektricitet, OUTPUT);
  startTime= millis();
}

void loop() {

  if (currentTrial < antalTrial) {
  
    startTime = millis();
    digitalWrite(vibration, HIGH); 
    Serial.println ("****");
    delay (2000);
    currentTime = millis(); 

   if (currentTime-startTime >= 2)
   {
     //elstöt
    digitalWrite(elektricitet, HIGH);
    delay(2000);
    Serial.println ("  **");
     currentTime = millis(); 
    }
    if (currentTime-startTime >=4) {
      digitalWrite(vibration, LOW);
      digitalWrite(elektricitet, LOW);
    }
    Serial.println("");
    delay(intertrialTid);
  }
}
