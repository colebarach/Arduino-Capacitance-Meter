// Capacitance Meter
//   Author - Cole Barach
//   Date Created - 22.07.11
//   Date Updated - 22.07.11
//   Usage - Connect a capacitor in series with a resistor to form a RC circuit. The
//     input to this circuit will be the charge and discharge pins, and the voltage
//     will be monitored via the comparator pin. The capacitance will be calculated
//     automatically and averaged over time.

// Pin Assignments
  const int           chargePin             = 12;
  const int           dischargePin          = 11;
  const int           comparatorPin         = A0;

// Control Variables
  const int           chargedVoltage        = 647; // 63.2% of 1024
  const int           dischargedVoltage     = 1;
  const unsigned long resistance            = 10000;

// Internal Variables
  unsigned long       initialTime           = 0;
  float               cumulativeCapacitance = 0;
  int                 cumulativeCount       = 0;
  float               meanCapacitance       = 0;

void setup() {
  Serial.begin(9600);
  pinMode(chargePin,     OUTPUT);
  pinMode(dischargePin,  INPUT);
  pinMode(comparatorPin, INPUT);
}

void loop() {
  Discharge();
  Charge();
}

void Charge() {
  digitalWrite(chargePin,HIGH);
  initialTime = millis();
  int voltage = 0;
  while(voltage < chargedVoltage) {
    voltage = analogRead(comparatorPin);
    Serial.println("");
    Serial.print("Capacitance: ");
    Serial.print(meanCapacitance);
    Serial.print("mF - Charging: ");
    Serial.print(voltage/10.24f);
    Serial.print("%");
  }
  
  cumulativeCapacitance += (float)((millis()-initialTime)/1000)/resistance * 1000;
  cumulativeCount++;
  meanCapacitance = cumulativeCapacitance/cumulativeCount;

  Serial.println("");
  Serial.print("Capacitance: ");
  Serial.print(meanCapacitance);
  Serial.print("mF");
}
void Discharge() {
  pinMode(dischargePin,OUTPUT);
  digitalWrite(chargePin,LOW);
  digitalWrite(dischargePin,LOW);
  int voltage = 1024;
  while(voltage > dischargedVoltage) {
    voltage = analogRead(comparatorPin);
    Serial.println("");
    Serial.print("Capacitance: ");
    Serial.print(meanCapacitance);
    Serial.print("mF - Discharging: ");
    Serial.print(voltage/10.24f);
    Serial.print("%");
  }
  pinMode(dischargePin,INPUT);
}
