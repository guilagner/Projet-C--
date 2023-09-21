# raspberryAJC

# README

## Description
Ce code C++ est destiné à être utilisé avec une Raspberry Pi 3 modèle B et la bibliothèque WiringPi pour contrôler des broches GPIO en fonction d'une entrée sur la broche 12. Il alterne entre trois états de broche de sortie en réponse à l'entrée.

## Configuration matérielle
Avant d'utiliser ce code, assurez-vous d'avoir correctement câblé ( plug ) votre Raspberry Pi. Voici la configuration recommandée :

- kernel : 64 bytes
- Broche GPIO 12 : Utilisée comme entrée
- Broche GPIO 16, 20, 21 : Utilisées comme sorties
![Config ](https://www.framboise314.fr/wp-content/uploads/2018/02/kit_composants_GPIO_01.png)
- Programme en C++



## Utilisation
- Assurez-vous d'avoir installé la bibliothèque WiringPi sur votre Raspberry Pi.

- Compilez le code en utilisant le compilateur C++.

   ```bash
   g++ -o mon_programme Programme_Capteur.cpp -lwiringPi
   ```

- excuter le fichier issu de l'excution.

- La diode Verte  doit être allumé de base , si vous passer la main rapidement devant le capteur, la diode Verte s'éteind et la diode Jaune s'allume. Si vous laissez la main sur le capter , au bout de quelques seconde la diode devient rouge.

