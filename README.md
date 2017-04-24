# PiWebcam
Mini-projet réalisé sur RaspberryPi3 où l'orientation de la PiCamera est commandée à l'aide d'un serveur web, d'une Arduino, et 3 servomoteurs.

## Connection Wifi puis SSH
SSDI : `PiWebcam`
Code : `mdppiwebcam`

```
ssh pi@192.168.3.1
```
code : `raspberry`

## Configuration de l'ensemble du système
1. Installez de RASBIAN (Suivre [ce lien](https://www.raspberrypi.org/downloads/raspbian/)) ;
2. Configurez de la Raspberry en point d’accès Wifi ;
3. Configurez pour streamer la vidéo d'une PiCamera ;
4. Installez le serveur nweb modifié ;
5. Configurez la communication Série entre l'Arduino et Linux TTY
6. Mettre en place un lancement automatique des différents process au démarrage de la Raspberry

### Configuration de la Raspberry en point d’accès Wifi

### Streaming vidéo via la PiCamera

### Installation du serveur nweb
Placer le dossier `www` contenant le site dans un répertoire sensible (et non pas dans un répertoire système comme `/` ou `/temp`). Par exemple dans `/home`. Puis rendre le rendre lisible. [Pour plus d'info...](https://github.com/ankushagarwal/nweb)
```
chmod ugo+r /home/www
```
Décidez ensuite du numéro de port que vous utilisez (ici *8081*). Puis lancez nweb à l'aide de la commande suivante.
```
cc /home/Raspberry/nweb23.c -o /home/Raspberry/nweb
chmod r+x /home/Raspberry/nweb
/home/Raspberry/nweb 8081 /home/Raspberry/www
```

### Configuration de la communication entre Arduino et Linux TTY
Pour configurer la connection Série entre la Raspberry et l'Arduino avec la bonne parité, vitesse... [Pour plus d'info...](http://playground.arduino.cc/Interfacing/LinuxTTY)
```
stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
```

Pour envoyer un String à l'Arduino.
```
#Avec fin de ligne
echo "Hello Arduino" > /dev/ttyUSB0

#Sans fin de ligne
echo -n "Hello" > /dev/ttyUSB0
```

Pour lire un String envoyé de l'Arduino.
```
tail -f /dev/ttyUSB0
```

### Lancement des différents process au démarrage de la Raspberry
