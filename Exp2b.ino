//test program

static const char spinner[] = "-\\|/";  // Array of ASCII spinning characters
static int spinnerIndex = 0;  // Current index of the spinner character

unsigned long startTime = 0; 
unsigned long currentTime = 0; 
unsigned long vibrationStart=0; 

const int vibration = 9;    
const int elektricitet  = 10;       

 int ITI = 10000; // 10 sekunder mellan trials 
const int duration = 4000; // 4 sekunder vibration
const int US = 2000; // 2 sekunders US 
const int ISI = 7000; // 2 sekunders inter stimuli interval 
const int remainingITI = ITI - ISI - US ; 

 
const int antalTrial = 10;    
int currentTrial = 0 ;  

bool isTrialStarted = false;
bool isElektricitetActivated = false;
bool hasShutVib = false; 

void printEvent(const char* eventName) {
  Serial.print(currentTime);
  Serial.print("\t");
  Serial.print(eventName);
  Serial.print("\t");
  Serial.println(currentTrial);
}

void startTrial() {
  if (!isTrialStarted) {
    isTrialStarted = true;
    printEvent("CS on");
    digitalWrite(vibration, HIGH);
    vibrationStart =millis(); 
  }
}

void activateElektricitet() {
  if (isTrialStarted && !isElektricitetActivated) {
    isElektricitetActivated = true;
    printEvent("US on");
    digitalWrite(elektricitet, HIGH);
  }
}

void endTrial() {
  if (isTrialStarted) {
    isTrialStarted = false;
    isElektricitetActivated = false;
    printEvent("US off");
    digitalWrite(elektricitet, LOW);
    ITI = remainingITI ; 
    startTime = currentTime;
    currentTrial++;
   
  }
}
void shutVib() {
  if (!hasShutVib) {
    hasShutVib = true;
    printEvent("CS off");
    digitalWrite(vibration, LOW);
  }
}
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
  Serial.println("");
  Serial.print("Time");
  Serial.print("\t");
  Serial.print("Event");
  Serial.print("\t");
  Serial.println("Trial");
  startTime = millis();
  currentTime = millis();
  printEvent("start");

}

void loop() {
  currentTime = millis();

  if(currentTrial < antalTrial){

    if (currentTime > (startTime + ITI)) {
      startTrial();
    }
    if (currentTime > (startTime + ITI + duration) ) {
       
      shutVib() ;
      
    }
  
    if (currentTime > (startTime + ITI + ISI  + duration)) {
      activateElektricitet();
    }

    if (currentTime > (startTime + ITI + ISI + US  +duration )) {
      endTrial();
    }
    
  }

}
