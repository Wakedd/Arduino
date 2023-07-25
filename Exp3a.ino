// Pavlovian Conditioning Protocol
// Exp3a Hennessey et al. (1979) - Classical conditioning in paramecia

static const char spinner[] = "-\\|/";  // Array of ASCII spinning characters
static int spinnerIndex = 0;  // Current index of the spinner character

unsigned long startTime_CS = 0;
unsigned long startTime_US = 0;
unsigned long currentTime = 0;
unsigned long vibrationStart = 0;

int ITI[] = {17,17,38,25,17,31,17,16,26,30,32,17,19,16,21,18,17,20,22,16,19,30,23,20,29,21,24,31,17,16};
int numITIValues = sizeof(ITI) / sizeof(ITI[0]); // Number of ITI values in the array

const int vibrationPin = 9;
const int elektricitetPin = 10;

int interTrialInterval_CS = 16000;  // 16 seconds between trials
int interTrialInterval_US = 16000;  // 16 seconds between trials

const int vibrationDuration = 4000;  // 4 seconds of vibration
const int unconditionedStimulusDuration = 2000;  // 2 seconds of unconditioned stimulus (US)
const int remainingITI = 3000;  // Time from US offset to conditioned stimulus (CS) onset to ensure constant ITI

const int numberOfTrials = 15;
const int numberOfTrials1 = 30;
int currentTrial_CS = 0;
int currentTrial_US = 0;

bool isTrialStarted = false;
bool isUSActivated = false;
bool isVibrationActivated = false;

void printEvent(const char* eventName) {
  Serial.print(currentTime);
  Serial.print("\t");
  Serial.print(eventName);
  Serial.print("\t");
  Serial.println(currentTrial_CS);
}

void activateVibration() {
  if (!isVibrationActivated) {
    printEvent("CS On");
    isVibrationActivated = true;
    digitalWrite(vibrationPin, HIGH);
    vibrationStart = millis();
  }
}

void activateUS() {
  if (!isUSActivated) {
    isUSActivated = true;
    printEvent("US On");
    digitalWrite(elektricitetPin, HIGH);
  }
}

void endVibration() {
  if (isVibrationActivated) {
    isVibrationActivated = false;
    printEvent("CS Off");
    digitalWrite(vibrationPin, LOW);
    int randomIndex = random(numITIValues); // Generate a random index for ITI array
    interTrialInterval_CS = ITI[randomIndex] * 1000; // Convert to milliseconds
    startTime_CS = currentTime;
    currentTrial_CS++;
  }
}

void endUS() {
  if (isUSActivated) {
    isUSActivated = false;
    printEvent("US Off");
    digitalWrite(elektricitetPin, LOW);
    int randomIndex = random(numITIValues); // Generate a random index for ITI array
    interTrialInterval_US = ITI[randomIndex] * 1000; // Convert to milliseconds
    startTime_US = currentTime;
    currentTrial_US++;
  }
  }
  void endUS1() {
  if (isUSActivated) {
    isUSActivated = false;
    printEvent("US Off");
    digitalWrite(elektricitetPin, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Please send a character to start the sketch");

  // Wait for input before starting the sketch
  while (Serial.available() == 0) {
    
  }

  // Empty the read buffer
  while (Serial.available() > 0) {
    Serial.read();
  }

  //set random seed
  randomSeed(analogRead(A0));

  int randomIndex = random(numITIValues); // Generate a random index for ITI array
  interTrialInterval_CS = ITI[randomIndex] * 1000; // Convert to milliseconds
  randomIndex = random(numITIValues); // Generate a random index for ITI array
  interTrialInterval_US = ITI[randomIndex] * 1000; // Convert to milliseconds

  pinMode(vibrationPin, OUTPUT);
  pinMode(elektricitetPin, OUTPUT);
  Serial.println("");
  Serial.print("Time");
  Serial.print("\t");
  Serial.print("Event");
  Serial.print("\t");
  Serial.println("Trial");
  startTime_CS = millis();
  startTime_US = millis();
  currentTime = millis();
  printEvent("Start");
}

void loop() {
  currentTime = millis();

  //Trial triggering event for CS
  if (currentTrial_CS < numberOfTrials) {

    if (currentTime > (startTime_CS + interTrialInterval_CS)) {
      activateVibration();
    }
    if (currentTime > (startTime_CS + interTrialInterval_CS + vibrationDuration)) {
      endVibration();
    }

  }

  //Trial triggering event for US
  if (currentTrial_US < numberOfTrials) {

    if (currentTime > (startTime_US + interTrialInterval_US)) {
      activateUS();
    }
    if (currentTime > (startTime_US + interTrialInterval_US + unconditionedStimulusDuration)) {
      endUS();
    }

  }
  

}
}
