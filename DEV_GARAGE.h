struct DEV_GARAGE : Service::GarageDoorOpener { // A Garage Door Opener

  int closedSensorPin; // The status pin connected to the garage
  int openSensorPin;   // The status pin connected to the garage
  int relayPin;       // The relay pin that actually controls the garage

  int lastOpenPinState = LOW;    // Last known pin state
  int currentOpenPinState = LOW; // Current pin state

  int lastClosedPinState = LOW;  // Last known pin state
  int currentClosedPinState = LOW; // Current pin state

  int garageState = -1;        // Current garage state
  
  // Timer variables for movement timeout
  unsigned long movementStartTime = 0;  // When the door started moving
  const unsigned long MOVEMENT_TIMEOUT = 20000;  // 20 seconds timeout

  // Create a new enum for the garage states
  enum GarageState {
    OPEN,       // 0
    CLOSED,     // 1
    OPENING,    // 2
    CLOSING,    // 3
    STOPPED     // 4
  };

  ////////////////////////////////////////////////

  SpanCharacteristic *current;     // reference to the Current Door State Characteristic (specific to Garage Door Openers)
  SpanCharacteristic *target;      // reference to the Target Door State Characteristic (specific to Garage Door Openers)
  SpanCharacteristic *obstruction; // reference to the Obstruction Detected Characteristic (specific to Garage Door Openers)

  DEV_GARAGE(int closedSensorPin, int openSensorPin, int relayPin) : Service::GarageDoorOpener()
  { // constructor() method

    // Initialize the characteristics

    Serial.println("Configuring Garage Door Controller");

    this->relayPin = relayPin;
    this->closedSensorPin = closedSensorPin;
    this->openSensorPin = openSensorPin;

    pinMode(relayPin, OUTPUT);
    pinMode(closedSensorPin, INPUT_PULLUP);
    pinMode(openSensorPin, INPUT_PULLUP);

    current = new Characteristic::CurrentDoorState(Characteristic::CurrentDoorState::CLOSED);                 // Default state: Closed
    target = new Characteristic::TargetDoorState(Characteristic::TargetDoorState::CLOSED);                    // Default target state: Closed
    obstruction = new Characteristic::ObstructionDetected(Characteristic::ObstructionDetected::NOT_DETECTED); // Default: No obstruction
    obstruction->setVal(false);
  }

  bool update()
  {
    Serial.println("Update method called"); // Debug print to trace execution

    int targetState = target->getVal(); // Get the target state from HomeKit
    WEBLOG(("Target state requested: " + String(targetState)).c_str());
    Serial.println("Target state requested: " + String(targetState)); // Debug print to trace execution

    if (targetState == Characteristic::TargetDoorState::OPEN)
    {
      if (garageState == OPENING)
      {
        // Garage is already opening, do nothing
        WEBLOG("Garage is already opening");
        return true;
      }
      else if (garageState == CLOSING)
      {
        WEBLOG("Garage was closing; now opening");
        // Garage is closing, pulse the relay twice to reverse direction
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
        delay(500);
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
      }
      else
      {
        WEBLOG("Opening the garage");
        // Open the garage
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
      }
      if (current->getVal() != Characteristic::CurrentDoorState::OPEN) {
        current->setVal(Characteristic::CurrentDoorState::OPEN); // Update the current state
      }
      if (target->getVal() != Characteristic::TargetDoorState::OPEN) {
        target->setVal(Characteristic::TargetDoorState::OPEN);   // Confirm the target state
      }
      WEBLOG("Garage state updated to OPEN");
    }
    else if (targetState == Characteristic::TargetDoorState::CLOSED)
    {
      if (garageState == CLOSING)
      {
        // Garage is already closing, do nothing
        WEBLOG("Garage is already closing");
        return true;
      }
      else if (garageState == OPENING)
      {
        WEBLOG("Garage was opening; now closing");
        // Garage is opening, pulse the relay twice to reverse direction
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
        delay(500);
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
      }
      else
      {
        WEBLOG("Closing the garage");
        // Close the garage
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
      }
      if (current->getVal() != Characteristic::CurrentDoorState::CLOSED) {
        current->setVal(Characteristic::CurrentDoorState::CLOSED); // Update the current state
      }
      if (target->getVal() != Characteristic::TargetDoorState::CLOSED) {
        target->setVal(Characteristic::TargetDoorState::CLOSED);   // Confirm the target state
      }
      WEBLOG("Garage state updated to CLOSED");
    }

    return true; // return true
  }

  void loop()
  {
    // this is how we know the state of the garage
    
    // logic:
    // if the closed sensor is LOW, the garage is FULLY closed
    // if the open sensor is LOW, the garage is FULLY open
    // if both sensors are floating (not LOW), the garage must be in motion

    // Read the current sensor states
    int closedSensorState = digitalRead(closedSensorPin);
    int openSensorState = digitalRead(openSensorPin);

    // Update the pin state tracking
    lastClosedPinState = currentClosedPinState;
    lastOpenPinState = currentOpenPinState;
    currentClosedPinState = closedSensorState;
    currentOpenPinState = openSensorState;

    // Definite end states - These take precedence
    if (closedSensorState == LOW && openSensorState == HIGH) // Garage is closed
    {
      garageState = CLOSED;
      current->setVal(Characteristic::CurrentDoorState::CLOSED);
      target->setVal(Characteristic::TargetDoorState::CLOSED); // Confirm the target state
      WEBLOG("Garage is closed");
    }
    else if (closedSensorState == HIGH && openSensorState == LOW) // Garage is open
    {
      garageState = OPEN;
      current->setVal(Characteristic::CurrentDoorState::OPEN);
      target->setVal(Characteristic::TargetDoorState::OPEN); // Confirm the target state
      WEBLOG("Garage is open");
    }
    else if (closedSensorState == HIGH && openSensorState == HIGH) // Garage is in motion
    {
      // Detect transition from closed to in-motion (Opening)
      if (lastClosedPinState == LOW && currentClosedPinState == HIGH) {
        garageState = OPENING;
        current->setVal(Characteristic::CurrentDoorState::OPENING);
        target->setVal(Characteristic::TargetDoorState::OPEN); // Confirm the target state
        movementStartTime = millis();  // Start the timer
        WEBLOG("Garage just started opening");
      }
      // Detect transition from open to in-motion (Closing)
      else if (lastOpenPinState == LOW && currentOpenPinState == HIGH) {
        garageState = CLOSING;
        current->setVal(Characteristic::CurrentDoorState::CLOSING);
        target->setVal(Characteristic::TargetDoorState::CLOSED); // Confirm the target state
        movementStartTime = millis();  // Start the timer
        WEBLOG("Garage just started closing");
      }
    }
    else if (closedSensorState == LOW && openSensorState == LOW) // Both sensors are LOW, indicating an error state
    {
      WEBLOG("Garage is stopped due to error state");
    }
    
    // Check if the door has been in movement state for too long
    if ((garageState == OPENING || garageState == CLOSING) && 
        (millis() - movementStartTime > MOVEMENT_TIMEOUT)) {
      // If we've been opening/closing for more than the timeout, assume it's partially open
      garageState = OPEN;
      current->setVal(Characteristic::CurrentDoorState::OPEN);
      target->setVal(Characteristic::TargetDoorState::OPEN);
      WEBLOG("Movement timeout reached - setting garage to OPEN state");
    }
  }

};