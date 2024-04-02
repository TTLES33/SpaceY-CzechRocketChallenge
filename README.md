# SpaceY  - Czech Rocket Challenge 
Program pro avioniku raket Falcon 747 - Ludwiq (2023) a Falcon Light - Amadeus (2022) 

  ## Falcon 747 - Ludwiq (2023)
Avionika skládající se ze tří částí - trup a špička rakety + přijímač na zemi.

 **Avionika rakety:**

 - 2x Arduino Nano V3 - tělo + špička
 - 2x Bezdrátový modul (2,4GHz) - tělo + špička
 - GPS modul, barometr - tělo

Avionika těla je zodpovědná za zaznamenávání výšky a následné rozdělení rakety. Elektronika špičky i těla posílá neustále svou gps pozici na frekvenci 2,4Ghz.

**Ground:**

 - Arduino UNO + Bezdrátový modul (2,4GHz)
<br><br>
 
`spacey_2023_spicka_arduino/spacey_2023_spicka.ino` - Program pro vysílaní aktualní GPS souřadnice

`spacey_2023_telo_arduino/spacey_2023_telo.ino` - Program pro vysílaní aktualní GPS souřadnice a rozdělení rakety při vyhodnocení klesání výšky.

`spacey_2023_reciever_nodejs/` - nodejs webserver na portu 8081 pro příjem a vizualizaci dat z rakety přes frekvenci 2,4GHz

`spacey_2023_reciever_arduino/spacey_2023_reciever.ino` - Program pro neustálý příjem dat na frekvenci 2,4GHz

[Final Report](https://github.com/TTLES33/SpaceY-CzechRocketChallenge/assets/73744077/deb2c6aa-9e65-4fe0-9275-cdb2f8e0874a)

[Foto avioniky rakety](https://github.com/TTLES33/SpaceY-CzechRocketChallenge/assets/73744077/a2a5b49b-f613-4c08-b89d-f536124e29a2)

[Foto rakety](https://github.com/TTLES33/SpaceY-CzechRocketChallenge/assets/73744077/e996b476-73c6-43c3-af95-1b7709c1c0fe)


  ## Falcon Light - Amadeus (2022)
Jednoduchá avionika v těle rakety.

 **Avionika rakety:**

 - Raspberry Pi Pico
 - barometr BMP280

Avionika těla je zodpovědná za zaznamenávání výšky a následné rozdělení rakety pomocí elektromotoru. 


`main.py` - Python program pro vyhodnocení změny výšky rakety a spuštění elektromotoru.

[Foto rakety](https://github.com/TTLES33/SpaceY-CzechRocketChallenge/assets/73744077/5d81b139-d639-4baa-8f42-583ea2ef453d)


