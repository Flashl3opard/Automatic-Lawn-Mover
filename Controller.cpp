#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// --- Left Motors (L298N #1)
#define IN1 14 // Front Left
#define IN2 27
#define IN3 26 // Rear Left
#define IN4 25

// --- Right Motors (L298N #2)
#define IN5 5  // Front Right
#define IN6 18
#define IN7 19 // Rear Right
#define IN8 21

// --- Blade motor (BLDC via ESC)
#define BLADE 4

WebServer server(80);
String command;

Servo esc;  // ESC for BLDC motor
bool bladeOn = false;

void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);

  // ESC setup
  esc.attach(BLADE, 1000, 2000);  // Attach ESC with min/max pulse width
  Serial.println("Arming ESC...");
  esc.writeMicroseconds(1000);  // Min throttle to arm
  delay(3000);                  // Wait for ESC to arm
  Serial.println("ESC Armed");

  // Start WiFi Access Point
  WiFi.softAP("LawnMower_AP");
  Serial.println("WiFi AP Started. IP: " + WiFi.softAPIP().toString());

  // Setup web server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command.length() > 0) {
    Serial.println("Command: " + command);

    if (command == "F") goForward();
    else if (command == "B") goBackward();
    else if (command == "L") turnLeft();
    else if (command == "R") turnRight();
    else if (command == "S") stopMotors();
    else if (command == "W") {
      Serial.println("Blade ON");
      esc.writeMicroseconds(1200);  // Adjust this value for blade speed
      bladeOn = true;
    }
    else if (command == "w") {
      Serial.println("Blade OFF");
      esc.writeMicroseconds(1000);  // Stop blade
      bladeOn = false;
    }
    else if (command == "0") {
      Serial.println("Blade OFF");
      esc.writeMicroseconds(1000);  // Stop blade
      bladeOn = false;
    }
    else if (command == "1") {
      Serial.println("Blade 1");
      esc.writeMicroseconds(1100);  // Stop blade
      bladeOn = false;
    }
    else if (command == "2") {
      Serial.println("Blade 2");
      esc.writeMicroseconds(1200);  // Stop blade
      bladeOn = false;
    }
    else if (command == "3") {
      Serial.println("Blade 3");
      esc.writeMicroseconds(1300);  // Stop blade
      bladeOn = false;
    }
    else if (command == "4") {
      Serial.println("Blade 4");
      esc.writeMicroseconds(1400);  // Stop blade
      bladeOn = false;
    }
    else if (command == "5") {
      Serial.println("Blade 5");
      esc.writeMicroseconds(1500);  // Stop blade
      bladeOn = false;
    }
    else if (command == "6") {
      Serial.println("Blade 6");
      esc.writeMicroseconds(1600);  // Stop blade
      bladeOn = false;
    }
    else if (command == "7") {
      Serial.println("Blade 7");
      esc.writeMicroseconds(1700);  // Stop blade
      bladeOn = false;
    }
    else if (command == "8") {
      Serial.println("Blade 8");
      esc.writeMicroseconds(1800);  // Stop blade
      bladeOn = false;
    }
    else if (command == "9") {
      Serial.println("Blade 9");
      esc.writeMicroseconds(1900);  // Stop blade
      bladeOn = false;
    }
    else if (command == "q") {
      Serial.println("Blade q");
      esc.writeMicroseconds(2000);  // Stop blade
      bladeOn = false;
    }
  }
}

// --- Movement functions ---

void goForward() {
  Serial.println("Moving Forward");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // FL
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // RL
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);  // FR
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);  // RR
}

void goBackward() {
  Serial.println("Moving Backward");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // FL
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // RL
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);  // FR
  digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);  // RR
}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // FL
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // RL
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);  // FR
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);  // RR
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // FL
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // RL
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);  // FR
  digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);  // RR
}

void stopMotors() {
  Serial.println("Stopping");
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
}

// --- Web handler ---
void HTTP_handleRoot() {
  server.send(200, "text/html", "Command received");
}
