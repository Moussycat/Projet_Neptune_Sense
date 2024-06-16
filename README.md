# Project_Neptune_Sense

### Projet de synthèse objets connectés

#### Semestre 8 - Option Electronique et Objets connectés ESEO

Notre système se compose de deux modules complémentaires. Il est conçu pour simplifier la gestion de votre espace aquatique tout en garantissant une qualité d'eau optimale

Le premier module, autonome en énergie, est spécialement conçu pour résister aux conditions extérieures. Équipé de capteurs de pointe, il collecte en temps réel les informations essentielles à la bonne gestion de votre piscine. Mesurez avec précision le pH de l'eau, sa température ainsi que celle de l'air ambiant, pour une expérience de baignade toujours agréable. De plus, ce module est doté d'un indicateur de niveau de batterie, vous assurant ainsi une utilisation continue et sans souci.

Le second module, alimenté par le secteur, est votre station de base. Il reçoit et traite toutes les données transmises par le module extérieur. Grâce à son interface intuitive, accédez facilement à toutes les informations relatives à votre piscine, et ce, en un seul endroit.

Ce projet, alliant technologie et praticité, vous offre une solution pour une gestion simplifiée de votre piscine ou bassin.

## Description

Pour que vous puissiez mieux appréhender la logique et les choix qui ont guidé notre projet, nous vous fournissons quelques éléments d'information essentiels. Parmi ces documents, se trouve le [cahier des charges](Cahier_des_charges.pdf) qui définit les objectifs, les contraintes et les exigences auxquelles notre projet doit répondre ainsi que le [schéma synoptique](Schema_synoptique_Neptune_Sense.pdf), qui présente de manière graphique l'ensemble des systèmes pour une vue générale du projet.

### [Code](Code/README.md)

#### [Station de base](Code/main_station_base/)

Cette station s'installe dans un bâtiment où elle pourra avoir accès à un réseau internet. La station permet d'afficher sur un écran TFT la température de l'eau et de l'air, le PH de votre bassin, le niveau de l'eau, le niveau de batterie de la station extérieure, l'horloge et la météo.

#### [Station extérieure](Code/CODE%20NeptuneSense/)

Cette station se met à proximité de votre bassin. La sonde de PH, le capteur de température d'eau et le niveau de l'eau doivent être placé dans l'eau. Le dispositif doit être à proximité d'une station de réception Lora public.

### [PCB](PCB/README.md)

Au cours de notre projet, nous avons élaboré et fabriqué deux cartes de circuits imprimés (PCB) bien distinctes. La première d'entre elles est destinée à la station de base, tandis que la seconde est spécifiquement conçue pour la station extérieure. Il convient de souligner que ces deux PCB sont équipées de microcontrôleurs différents, afin de répondre au mieux aux contraintes et aux exigences de chaque station. Pour en savoir plus sur ce sujet, nous vous invitons à cliquer sur le titre de la partie correspondante.

### [Tests](Tests/README.md)

Nous avons procédé à la réalisation de tests unitaires pour chacune des fonctions implémentées dans les deux stations. Ces tests ont pour objectif de vérifier le bon fonctionnement de chaque fonctionnalité de manière isolée. Les détails et les descriptions de ces tests sont disponibles dans les dossiers respectifs de chaque test, afin de faciliter la compréhension et la traçabilité des vérifications effectuées.
