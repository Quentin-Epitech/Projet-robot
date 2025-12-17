# WALLE2

Ce projet consiste à réaliser un **robot qui voit les obstacles devant lui,et qui change de direction s'il détecte un obstacle devant lui automatiquement.** grâce à un **capteur ultrason HC-SR04** et de **moteurs DC contrôlés par un motor shield** utilisant la bibliothèque `AFMotor`.

Le robot avance en ligne droite et, lorsqu’un obstacle est détecté à courte distance, il tourne pour l’éviter.

## Fonctionnement

1. Le capteur ultrason mesure la distance devant le robot.
2. Trois mesures sont effectuées et moyennées pour éviter les erreurs.
3. Si un obstacle est détecté à moins de 4 cm :
   - Le robot recule
   - Puis tourne à droite ou à gauche 
   - Le sens de rotation alterne à chaque obstacle
4. Une fois l’obstacle évité, le robot reprend sa trajectoire.

## Matériel requis
- Arduino Uno
- Motor Shield compatible `AFMotor`
- 2 moteurs DC
- Capteur ultrason **HC-SR04**
- Châssis de robot
- Batterie
- Fils de connexion 


## Bibliothèque nécessaire

- `AFMotor`  
  https://github.com/adafruit/Adafruit-Motor-Shield-library 



