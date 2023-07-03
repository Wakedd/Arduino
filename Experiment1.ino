const int vibration = 9;    
const int elektricitet  = 10;       
const int csTid = 4000;   
const int ucsTid = 2000;  
const int intertrialTid = 10000; // 10 sekunder mellan trials 
const int antalTrial = 10;      

void setup() {
  pinMode(vibration, OUTPUT);
  pinMode(elektricitet, OUTPUT);
}

void loop() {
  for (int trial = 0; trial < antalTrial; trial++) {
   
    digitalWrite(vibration, HIGH);
    delay(csTid - ucsTid);  // eller 2000 millisekund 
    digitalWrite(vibration, LOW);
    
   //elstöt
    digitalWrite(elektricitet, HIGH);
    delay(ucsTid);
    digitalWrite(elektricitet, LOW);
    
    
    delay(intertrialTid);
  }
}
