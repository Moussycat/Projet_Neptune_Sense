# README PCB

## Réalisation des PCB

Dans le cadre de notre projet, nous avons conçu et réalisé deux cartes de circuits imprimés (PCB) distinctes. La première est destinée à la station de base, tandis que la deuxième est dédiée à la station extérieure. Il est important de noter que ces deux PCB ne sont pas équipées du même microcontrôleur.

Pour concevoir et fabriquer nos cartes de circuits imprimés (PCB), nous avons fait appel au logiciel `Altium Designer (23.0.1)`, qui nous a fourni les outils et les fonctionnalités nécessaires à la réalisation de notre projet. Nous nous sommes également inspirés de divers projets disponibles en ligne et des fiches techniques (datasheets) fournies par les fabricants de composants, afin de disposer de toutes les informations et les bonnes pratiques requises. Grâce à ces éléments ainsi qu'à la réalisation de tests rigoureux, nous avons pu aboutir aux rendus présentés ci-dessous.

### Station de base

Pour la station de base, nous avons sélectionné le microcontrôleur `ESP32 WROOM WiFi` par Espressif. Ce choix s'est imposé naturellement, car ce composant intègre directement la connectivité WiFi. Ainsi, il nous est possible de réaliser facilement les requêtes MQTT (Message Queuing Telemetry Transport) indispensables pour récupérer les informations en provenance de la station extérieure. Cette configuration nous permet de centraliser et de traiter efficacement les données collectées.

Dimensions: 76mm x 84mm

![PCB station de base](/PCB/pcb_station_base.png)
![PCB station base top](/PCB/PCBB.png)
![schema elec base](/PCB/elec_base.png)

### Station Extérieure

En ce qui concerne la station extérieure, nous avons opté pour un microcontrôleur différent, le `Woi-E5`. Ce dernier est également utilisé dans la STM32WL55JC1 de chez STMicroelectronics. Le choix du Woi-E5 s'est principalement basé sur le fait qu'il intègre la technologie de communication LoRa (Long Range). Cela nous permet de mettre en œuvre le protocole de communication LoRaWAN (Long Range Wide Area Network), essentiel pour assurer des transmissions de données entre la station extérieure et la station de base, via d'autres intermédiaires.

Dimensions: 66mm x 79mm

![PCB station ext bot](/PCB/pcb_station_ext.png)
![PCB station ext top](/PCB/PCB.png)
![schema elec ext](/PCB/elec_ext.png)

## BOM

#### Station Extérieure

- [x] [WIO E5](https://www.digikey.fr/en/products/detail/seeed-technology-co-ltd/114993120/21526009)
      (Footprint locale)

- [x] [USB C](https://my.rs-online.com/web/p/usb-connectors/8950556) (Footprint locale)

- [x] [Capteur de coulombs](https://www.snapeda.com/parts/DS2782E+T/Analog%20Devices/view-part/)
      [(Footprint)](https://www.snapeda.com/parts/DS2782E+T/Analog%20Devices/view-part/)

- [x] [BOOST 5V](https://www.digikey.fr/en/products/detail/monolithic-power-systems-inc/MP3414AGJ-Z/7361472) [(Footprint)](https://www.snapeda.com/parts/MP3414AGJ-Z/Monolithic%20Power/view-part/?ref=search&t=MP3414AGJ-Z)

- [x] [BUCK 3,3v](https://www.digikey.fr/en/products/detail/evvo/AMS1117-3-3/22482148) [(Footprint)](https://www.snapeda.com/parts/AMS1117-3.3/ams%20AG/view-part/?ref=search&t=AMS1117-3.3)

- [x] [Chargeur batterie](https://fr.rs-online.com/web/p/gestion-de-batterie/1459049?gb=s) [(Footprint)](https://www.snapeda.com/parts/MCP73833-GPI/UN/Microchip%20Technology/view-part/?ref=search&t=MCP73833)

- [x] [Chargeur batterie panneau](https://fr.farnell.com/stmicroelectronics/spv1040t/chargeur-batterie-1-8a-tssop-8/dp/2762710?CMP=KNC-GFR-GEN-KWL-No-Audience-Shared-Budgets-01-Mar-21&mckv=s_dc|pcrid|650744400677|plid||kword||match||slid||product||pgrid|103549817689|ptaid|dsa-915064991216|&gad_source=1&gclid=CjwKCAjw5v2wBhBrEiwAXDDoJeK70DMSvAA7zcqXjeuBuuEcbRkl4ev_gvYKbHYqu8RgpD7hmsAmjRoCjAkQAvD_BwE)

- [x] [Bouton poussoir](https://fr.rs-online.com/web/p/boutons-poussoirs/7346704)

- [x] [Interrupteur alim](https://fr.rs-online.com/web/p/interrupteurs-a-bascule/7932563)

- [x] [Interrupteur mode charge](https://fr.rs-online.com/web/p/interrupteurs-a-levier/0394459)

- [x] [Antenne LORA](https://fr.rs-online.com/web/p/antennes-multi-bandes/1248675?gb=s)

- [x] [Port SMA Femelle](https://fr.rs-online.com/web/p/connecteurs-coaxiaux/5265785)[(Footprint)](https://www.snapeda.com/parts/SMA-J-P-H-ST-EM1/Samtec/view-part/?ref=samtec_in_line&t=connecteur%20SMA&con_ref=None)

- [x] [Batterie 3,7v 2,6A](https://fr.rs-online.com/web/p/piles-rechargeables-taille-speciale/7887261?gb=s)

- [x] [Support batterie](https://www.digikey.fr/en/products/detail/mpd-memory-protection-devices/BH-18650-W/3029217)

- [x] [Capteur de Température externe](https://fr.rs-online.com/web/p/kits-et-cartes-compatibles-arduino/2163753?gb=s)

- [x] [Voyant LED rouge](https://fr.rs-online.com/web/p/indicateurs-pour-montage-panneau/0206845)

- [x] [Voyant LED vert](https://fr.rs-online.com/web/p/indicateurs-pour-montage-panneau/0206867)

- [x] [Voyant LED bleu](https://fr.rs-online.com/web/p/indicateurs-pour-montage-panneau/7239696)

- [x] [Diode Zener](https://fr.rs-online.com/web/p/references-de-tension/0810289?cm_mmc=FR-PPC-DS3A-_-google-_-DSA_FR_FR_Semi-conducteurs_Index-_-R%C3%A9f%C3%A9rences+de+tension%7C+Products-_-DYNAMIC+SEARCH+ADS&matchtype=&dsa-1595848822259&gad_source=1&gclid=CjwKCAjw5v2wBhBrEiwAXDDoJTIkla-UucK4AsCojqCka1yGRhM6eHEzjd6G47ikizKRtx6TrInJvxoCFUIQAvD_BwE&gclsrc=aw.ds)

- [x] [AOP](https://fr.rs-online.com/web/p/amplificateurs-operationnels/3569782?gb=s)

- [x] [Potentiomètre](https://fr.rs-online.com/web/p/potentiometres-trimmer/5219647)

#### Station de base

- [x] Ecran TFT
- [ ] [ESP32](https://fr.rs-online.com/web/p/modules-wlan/1697594?searchId=394d8d28-7d02-4260-93f3-ee557f2650ac&gb=s)

## Liste des composants

### CMS

- [x] Inductance 10uH (x1)
- [x] Inductance 1uH (x2)
- [x] Condensateur 0.1uF (x3)
- [x] Condensateur 1uF (x4)
- [x] Condensateur 4,7uF (x2)
- [x] Condensateur 10uF (x8)
- [x] Condensateur 22uF (x2)
- [x] Condensateur 100nF (x3)
- [x] Résistance 10m (x1)(Flo)
- [x] Résistance 150 (x2)
- [x] Résistance 500 (x2)
- [x] Résistance 1k (x10)
- [x] Résistance 2k (x3)
- [x] Résistance 3,3k (x5)
- [x] Résistance 10k (x2)
- [x] Résistance 20k (x1)
- [x] Résistance 100k (x2)
- [x] Résistance 137k (x2)
- [x] Résistance 330k (x1)
- [x] Résistance 1M (x3)
- [x] Diode Zener (x3)
- [x] Diode TL431 (x1)
- [x] Led (x6)
- [x] Résistance variable (x1)

### STATION EXTERIEURE :

#### Chargeur panneau

- Inductance 10uH (x1)
- Condensateur 10uF (x1)
- Condensateur 100nF (x1)
- Condensateur 1uF (x1)
- Condensateur 4,7uF (x1)
- Résistance 1k (x3)
- Résistance 10m (x1)
- Résistance 1M (x1)
- Résistance 330k (x1)
- Diode Zener (x1)

#### Module PH

- Résistance 20k (x1)
- Résistance 10k (x1)
- Résistance 1k (x1)
- Condensateur 0.1uF (x2)
- Diode TL431 (x1)

#### Boost

- Résistance 100k (x1)
- Résistance 1M (x1)
- Résistance 137k (x1)
- Condensateur 10uF (x2)
- Inductance 1uH (x1)

#### Buck

- Condensateur 10uF
- Condensateur 22uF

#### Chargeur batterie

- Résistance 1k (x1)
- Condensateur 1uF (x1)

#### Jauge batterie

- Résistance 150 (x2)
- Résistance 500 (x1)
- Résistance 1k (x1)
- Condensateur 0.1uF (x1)
- Diode Zener 3,3v(x2)

### STATION DE BASE :

#### ESP32

- Résistance 3,3k (x2)
- Condensateur 100nF (x1)
- Condensateur 10uF (x1)
- Led (x2)

#### Boost

- Résistance 100k (x1)
- Résistance 1M (x1)
- Résistance 137k (x1)
- Condensateur 10uF (x2)
- Inductance 1uH (x1)

#### Buck

- Condensateur 10uF
- Condensateur 22uF

#### Conv data to uart

- Résistance 1k (x1)
- Résistance 10k (x1)
- Condensateur 100nF (x1)
