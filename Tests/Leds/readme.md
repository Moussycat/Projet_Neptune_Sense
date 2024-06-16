# Test Leds

## Matériel utilisé

#### Carte ESP32

- ESP32 WROOM WIFI
- Arduino IDE
- LED

#### Carte STM32WL55

- STM32WL55
- STM32 IDE
- LED + Résistance

#### Carte finale

##### station extérieure

- STM32WL55
- STM32 IDE
- LED + Résistance

##### station intérieure

- ESP32 WROOM WIFI
- Arduino IDE
- LED + Résistance

## Pins

#### Carte ESP32 WROOM

| ESP32 WROOM Pin | LED |
| :-------------: | :-: |
|       GND       |  -  |
|     GPIO 26     |  +  |

## Les résultats attendus

#### Carte ESP32, STM32WL55, carte finale (station de base et station extérieure)

on arrive à allumer la deuxième led de la carte nucléo.

## Les résultats obtenus

#### Carte ESP32

On a bien le changement d'état de la led jaune avec la trame.
![OK led](/Tests/Leds/ESP32_led.jpg)
![OK oscillo](/Tests/Leds/ESP32_oscillo.jpg)

#### Carte STM32WL55

On a bien le changement d'état de la led verte (en bas de la carte).
![Screen ON](/Tests/Leds/STM_ON.jpg)
On arrive à allumer la led avec la commande initialisation(BSP_LED_Init(LED3)) puis la commande (BSP_LED_Toggle(LED3))

cela utilise c'est ligne de comande :

```
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.Pin = GPIO_PIN_3;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
```

#### Carte finale

##### station extérieure

![testledbleue](/Tests/Leds/test%20led.jpg)
