# Test LoRaWAN

## Matériel utilisé

#### Carte STM32 & carte finale

- STM32WL
- STM32 IDE
- TTN

## Les résultats attendus

#### Carte STM32, carte finale

Nous devons nous connecter au TTN, pour pouvoir envoyer des paquets d'informations sur le serveur MQTT pour décoder en partie les trames envoyées

## Les résultats obtenus

#### Premier test d'envoi :

La carte est bien détectée par TTN mais la connexion ne se fait pas.

![Screen recuperationok](/Tests/Lora_WAN/recuperation_LoRaWAN.png)

#### Connexion réussie :

La problème venait de la saisie des appKey et Nwk Key.

![Screen CONNEXION](/Tests/Lora_WAN/LORAWAN_CONNEXION.png)

#### Modification des paquets :

Envoi d'une trame avec date et heure dans un JSON. L'app Cayenne n'existant plus, le JSON était la solution la plus efficace.

![Screen ENVOI_PACKET](/Tests/Lora_WAN/ENVOI_PACKET.png)

#### Décodeur TTN :

Afin de décoder la trame correctement, il faut configurer le décodeur sur TTN.
Voici le code utilisé avec le résultat décodé.

![Screen TEST_DECODER](/Tests/Lora_WAN/TEST_DECODER.png)

#### Réception de la trame :

On retrouve dans le JSON envoyé la partie "payload" qui nous intéresse.
Il y a bien "date" et "time" :

![Screen PAYLOAD_JSON](/Tests/Lora_WAN/PAYLOAD_JSON.png)

Sinon sans même ouvrir nous pouvons directement voir le décodage dans la réception en live :

![Screen DECODER_RESULTAT](/Tests/Lora_WAN/DECODER_RESULTAT.png)

#### Test Uplink et DownLink manuel :

Afin de s'assurer du bon fonctionnement dans les deux sens. Nous avons fait un test de downlink et uplink en manuel.
Nous avons saisi le port 10, et nous pouvons vérifier le résultat sur TTN :

![Screen DOWNLINK_UPLINK_PORT10](/Tests/Lora_WAN/UPLINK_AND_DOWNLINK.png)

La résultat est vérifiable directement sur le port série directement sur l'IDE. Ici il y a bien la réception sur le port 10 :

![Screen RECEIVED_PACKET_ON_PORT_10](/Tests/Lora_WAN/RECEIVED_PACKET_ON_PORT_10.png)

Ainsi nous sommes assurés du bon fonctionnement du système, nous allons pouvoir utiliser de réelles données de capteurs et ajouter quelques fonctionnalités.

#### Envoi de données des capteurs :

Avec les différents codes déjà testés indépendamment, nous avons pu directement ajouter la prise de mesure et envoyer les données de la même manière.
Ici nous pouvons trouver les résultat de température de l'air, l'humidité, et le ph.

![Screen RECEPTION_TRAME_COMPLETE](/Tests/Lora_WAN/RECEPTION_TRAME_COMPLETE.png)

#### Envoi instantané à l'appui :

Maintenant que la plupart des capteurs fonctionnent, nous pouvons ajouter la fonctionnalité d'envoi instantané. Comme prévu au cahier des charges, il doit être possible d'envoyer instantanément les données lors de l'appui d'un bouton.

En effet le résultat du PH n'est pas cohérent, cela est dû au calcul interne dans le code qui doit être ajusté. Le résultat est bien reçu sur TTN (ici la capture a été faite avant l'ajout du PH) :

![Screen PRESS_BOUTON](/Tests/Lora_WAN/ENVOI_TRAME_COMPLETE.png)

Dès l'appui, la broche prend le 5V, l'appui est alors détecté. Ensuite les données sont envoyées et l'envoi instantané est confirmé. Une fois cela fait, le cycle habituel reprend.

Gestion d'erreur : si on reste appuyé longtemps cela ne change rien il n'y aura bien qu'une seule trame d'envoyée et non un envoi constant.

#### Gestion led :

Un petit ajout a été effectué afin que la led bleu s'allume à chaque envoi de données, voici le montage final utilisé pour les tests :

![Screen MONTAGE](/Tests/Lora_WAN/MONTAGE.jpg)

Résultat avec le couvercle 3D :

![Screen MONTAGE](/Tests/Lora_WAN/IHM.jpg)
