//---------DECLARACIÓN DE VARIABLES -------------------

//Pines de Entrada y Salida

const int pinH1 = 22; 
const int pinH2 = 23;
const int pinButton = 19;
const int pinLightSensor = 17;
const int pinBuzzer = 18;


//Se utiliza un booleano para invertir la dirección del motor. 

bool directionUp = true; 


//Se utiliza un enum para los casos posibles.

enum State {
  OFF,
  WAITING_FOR_LIGHT,
  WAITING_FOR_SHADOW
};

//Se inicia con el primer estado. 

State currentState = OFF;

int TimeButtonState = LOW;
int lastButtonReading = LOW;

//Se utiliza un intervalo de 50 ms cocmo antirebote. 

unsigned long lastTime = 0;
const unsigned long DelayTime = 50;


//Se van a mostrar 5 lecturas por segundo en el monitor serie. 

unsigned long lastSerialTime = 0;
const unsigned long SerialInterval = 200;

//Por amor a los oídos, se implementa un intervalo para el buzzer. 

unsigned long lastBuzzerTime = 0;
const unsigned long BuzzerInterval = 300;
bool buzzerOn = false;

void setup() {
  Serial.begin(9600);

  pinMode(pinH1, OUTPUT);
  pinMode(pinH2, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLightSensor, INPUT);
  pinMode(pinButton, INPUT);
  
  stopMotor();
}

//--------------BUCLE------------------

void loop() {

  unsigned long currentTime = millis();

  int rawReading = digitalRead(pinButton);
  bool buttonJustPressed = false;

 
  //Lee el pulsador y actualiza su tiempo 

  if (rawReading != lastButtonReading) {
    lastTime = currentTime;
  }

  //Se realiza la lectura definitiva del pulsador al superar los 50 ms. 

  if ((currentTime - lastTime) > DelayTime) {
    if (rawReading != TimeButtonState) {
      TimeButtonState = rawReading;
      if (TimeButtonState == HIGH) {
        buttonJustPressed = true;
      }
    }
  }
  lastButtonReading = rawReading;

  //Muestra las lecturas en el tiempo especificado. 

  if (currentTime - lastSerialTime >= SerialInterval) {
    lastSerialTime = currentTime;
    Serial.print("Button: ");
    Serial.print(TimeButtonState);
    Serial.print(" | State: ");
    Serial.println(currentState);
  }

  //Genera un pitido intermitente mientras el motor está activo.

  if (currentState != OFF) {
    if (currentTime - lastBuzzerTime >= BuzzerInterval) {
      lastBuzzerTime = currentTime;
      buzzerOn = !buzzerOn;
      if (buzzerOn) {
        tone(pinBuzzer, 400);
      } else {
        noTone(pinBuzzer);
      }
    }
  }

  bool isShadow = (digitalRead(pinLightSensor) == HIGH);

  //Se utiliza un switch case para los estados. 

  switch (currentState) {
    
    case OFF:
      stopMotor();
      if (buttonJustPressed) {
        activateMotor(directionUp);
        currentState = WAITING_FOR_LIGHT;
      }
      break;

    //El estado WAITING FOR LIGHT simplemente funciona para que el programa 
    //pueda detectar siempre la sombra como señal. 

    case WAITING_FOR_LIGHT:
      if (!isShadow) { 
        currentState = WAITING_FOR_SHADOW;
      }
      break;

    case WAITING_FOR_SHADOW:
      if (isShadow) {
        stopMotor();
        currentState = OFF;
        directionUp = !directionUp; 
      }
      break;
  }
}

//-----------FUNCIONES-----------------

void activateMotor(bool up) {
  if (up) {
    digitalWrite(pinH1, HIGH);
    digitalWrite(pinH2, LOW);
  } else {
    digitalWrite(pinH1, LOW);
    digitalWrite(pinH2, HIGH);
  }
  // Se inicia el primer pítido del buzzer en su única ejecución 
  //y se utiliza el booleano para que continue. 

  tone(pinBuzzer, 400);
  buzzerOn = true;
  lastBuzzerTime = millis();
}

void stopMotor() {
  digitalWrite(pinH1, LOW);
  digitalWrite(pinH2, LOW);
  noTone(pinBuzzer);
  buzzerOn = false;
}
