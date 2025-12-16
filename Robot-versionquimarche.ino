#include <AFMotor.h>

const int trigPin = 9;
const int echoPin = 10;


AF_DCMotor moteurGauche(3);
AF_DCMotor moteurDroit(4);

const int VITESSE = 180;
const int SEUIL_CM = 4;

enum EtatRobot {
  AVANCE,
  EVITER_OBSTACLE};

EtatRobot etat = AVANCE;

unsigned long tempsDebut = 0;
bool tournerDroite = true;

long distancePrecedente = 0;

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duree = pulseIn(echoPin, HIGH, 30000);
  if (duree == 0) return 400;
  return (duree * 0.034 / 2);} // vitesse du son 


void avancer() {
  moteurGauche.run(FORWARD);
  moteurDroit.run(FORWARD);}

void reculer() {
  moteurGauche.run(BACKWARD);
  moteurDroit.run(BACKWARD);}

void tourner(bool droite) {
  if (droite) {
    moteurGauche.run(FORWARD);
    moteurDroit.run(BACKWARD);} 
    else {
    moteurGauche.run(BACKWARD);
    moteurDroit.run(FORWARD);}}

void arret() {
  moteurGauche.run(RELEASE);
  moteurDroit.run(RELEASE);}


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  moteurGauche.setSpeed(VITESSE);
  moteurDroit.setSpeed(VITESSE);
  arret();
  delay(1000); 
  Serial.println("prêt");}

void loop() {

  // prend 3 distances et fait une moyenne car l'ultrason peut dire de la merde
  long d1 = getDistance();
  long d2 = getDistance();
  long d3 = getDistance();
  long distance = (d1 + d2 + d3) / 3;

  long variation = distance - distancePrecedente;

  Serial.print("Distance:");
  Serial.print(distance);
  Serial.print(" cm");

  if (distancePrecedente > 0) {
    Serial.print(" (variation: ");
    if (variation > 0) Serial.print("+");
    Serial.print(variation);
    Serial.print(" cm)");
  }

  distancePrecedente = distance;

  if (etat == AVANCE && distance < SEUIL_CM && distance > 1) {
    Serial.println("obstacle");
    etat = EVITER_OBSTACLE;
    tempsDebut = millis();
  }

  if (etat == EVITER_OBSTACLE) {

    unsigned long tempsEcoule = millis() - tempsDebut;

    if (tempsEcoule < 300) {
      reculer();
    }
    else if (tempsEcoule < 900) {
      tourner(tournerDroite);
      Serial.print("Tourne ");
      Serial.println(tournerDroite ? "DROITE" : "GAUCHE");
    }
    else {
      arret();
      tournerDroite = !tournerDroite;
      etat = AVANCE;
    }
  }
  else if (etat == AVANCE) {

    if (distance <= 2) { // mesure louche et trop proche
      reculer();
    }
    else {
      Serial.println("avance");
      avancer();
    }
  }
}
