//test program

static const char spinner[] = "-\\|/";  // Array of ASCII spinning characters
static int spinnerIndex = 0;  // Current index of the spinner character

unsigned long startTime = 0;
unsigned long currentTime = 0;

const int vibration = 9;
const int elektricitet = 10;

const int ITIValues[] = {8, 12, 16, 20, 24, 28, 32}; // Array of ITI durations (in seconds)
const int numITIValues = sizeof(ITIValues) / sizeof(ITIValues[0]); // Number of ITI values in the array

const int duration = 4000; // 4 seconds vibration
const int US = 2000; // 2 seconds US
const int ISI = 2000; // 2 seconds inter-stimuli interval

const int antalTrial = 10;
int currentTrial = 0;

bool isTrialStarted = false;
bool isElektricitetActivated = false;

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
    printEvent("CS off");
    printEvent("US off");
    digitalWrite(vibration, LOW);
    digitalWrite(elektricitet, LOW);
    currentTrial++;
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

  currentTime = millis(); // Set initial current time
  randomSeed(analogRead(0)); // Seed the random number generator with an analog pin reading
}

void loop() {
  currentTime = millis();

  if (currentTrial < antalTrial) {
    if (!isTrialStarted) {
      int randomIndex = random(numITIValues); // Generate a random index for ITI array
      int randomITI = ITIValues[randomIndex] * 1000; // Convert to milliseconds
      startTime = currentTime + randomITI;
      isTrialStarted = true; // Set the trial flag to true
    }

    if (isTrialStarted && currentTime > startTime) {
      startTrial();
    }

    if (isTrialStarted && currentTime > (startTime + ISI)) {
      activateElektricitet();
    }

    if (isTrialStarted && currentTime > (startTime + ISI + US)) {
      endTrial();
      isTrialStarted = false; // Reset the trial flag to false
    }
  }
}
