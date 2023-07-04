//test program

static const char spinner[] = "-\\|/";  // Array of ASCII spinning characters
static int spinnerIndex = 0;  // Current index of the spinner character

unsigned long startTime = 0; 
unsigned long currentTime = 0; 
unsigned long vibrationStart=0; 

const int vibration = 9;    
const int elektricitet  = 10;       

int ITI[] = {8, 12, 16, 20, 24, 28, 32};
int numITIValues = sizeof(ITI) / sizeof(ITI[0]); // Number of ITI values in the array

const int duration = 4000; // 4 sekunder vibration
const int US = 2000; // 2 sekunders US 
const int CS= 2000; // 2 sekudner CS 
//int remainingITI = ITI - ISI - US ; 

 
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
   // ITI = remainingITI ; 
    startTime = currentTime;
    currentTrial++; 
    int randomIndex = random(numITIValues); // Generate a random index for ITI array
    int randomITI = ITI[randomIndex] * 1000; // Convert to milliseconds
   
  }
}
void shutVib() {
  if (!hasShutVib) {
    hasShutVib = true;
    printEvent("CS off");
    digitalWrite(vibration, LOW);
    int randomIndex = random(numITIValues); // Generate a random index for ITI array
    int randomITI = ITI[randomIndex] * 1000; // Convert to milliseconds

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
    
    if (currentTime > (startTime + ITI + duration ) ) {
       
      shutVib() ;
      
    }
  
  }
  if (currentTrial < antalTrial)
  if (currentTime > (startTime + ITI + duration)){
      activateElektricitet();
    }
    if (currentTime > startTime + ITI + duration + US){
      endTrial();
    }

}
