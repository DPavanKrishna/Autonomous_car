
#include <Servo.h>

// Define pins for ultrasonic sensor
#define trigPin 9
#define echoPin 10

// Motor pins
#define enA 5  // Left motor speed control
#define in1 6  // Left motor direction
#define in2 7  // Left motor direction
#define enB 3  // Right motor speed control
#define in3 4  // Right motor direction
#define in4 2  // Right motor direction

// Servo pin
#define servoPin 11

// Structure to manage car status
struct Car {
    int speed;            // Car's speed
    int motorState;      // 1 for moving, 0 for stopped
};

// Structure to manage sensor data
struct Sensor {
    long distance;       // Measured distance
    char status[10];     // Obstacle status ("CLEAR", "BLOCKED")
};

Servo steering;

// Declare car object globally
struct Car car;
struct Sensor sensor;
bool carRunning = false; // New variable to control car state

// Function to initialize the motor pins
void motorSetup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}

// Function to initialize the ultrasonic sensor
void sensorSetup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Function to read the ultrasonic sensor and update the distance
void readDistance(struct Sensor *sensor) {
    for (int i = 0; i < 2; i++) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        
        long duration = pulseIn(echoPin, HIGH);
        sensor->distance = (duration * 0.034) / 2;

        Serial.print("Reading ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(sensor->distance);
        Serial.println(" cm");

        if (sensor->distance > 20) {
            strcpy(sensor->status, "CLEAR");
        } else {
            strcpy(sensor->status, "BLOCKED");
        }
    }
}

// Function to move the car forward
void moveForward(struct Car *car) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, car->speed);
    
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, car->speed);
    
    car->motorState = 1;
    delay(2000); // Wait before printing
    Serial.println("Moving straight.");
}

// Function to turn left
void turnLeft() {
    for (int i = 0; i < 2; i++) {
        steering.write(45);
        delay(1000);
        steering.write(90);
    }
    Serial.println("Turning left at 45 degrees."); 
}

// Function to turn right
void turnRight() {
    for (int i = 0; i < 2; i++) {
        steering.write(135);
        delay(1000);
        steering.write(90);
    }
    Serial.println("Turning right at 135 degrees.");
}

// Function to stop the car
void stopCar(struct Car *car) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    car->motorState = 0;
}

// Function to check and avoid obstacles
void checkAndAvoidObstacle() {
    if (!carRunning) return; // If car is not running, exit the function
    
    readDistance(&sensor); // Read distance from the sensor

    if (strcmp(sensor.status, "CLEAR") == 0) {
        moveForward(&car);
    } else {
        stopCar(&car);
        Serial.println("Obstacle detected!");

        if (sensor.distance <= 20 && sensor.distance > 10) {
            analogWrite(enB, 100);
            turnRight();
        } else if (sensor.distance <= 10) {
            turnLeft();
        }

        moveForward(&car); // Move forward after turn
    }
}

// This function runs once when the Arduino starts
void setup() {
    Serial.begin(9600);
    motorSetup();
    sensorSetup();
    steering.attach(servoPin);
    steering.write(90);
    car.speed = 255; // Set speed (max)
}

// This is the main function that runs repeatedly
void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.equalsIgnoreCase("exit")) {
            stopCar(&car); // Immediately stop the car
            Serial.println("Car stopped."); // Notify user
            carRunning = false; // Set carRunning to false
        } else if (input.equalsIgnoreCase("start")) {
            carRunning = true; // Set carRunning to true
            Serial.println("Car started."); // Notify user
        }
    }

    checkAndAvoidObstacle(); // Continuously check for obstacles
}

