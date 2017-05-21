# Mind Rewind
Cutie Hackathon Project

This project was created by Justin Mac, Spyridon Catechis, and Ryan Wilson.

Hardware Needed:
- Arduino
- HM10 Bluetooth Module
- LCD screen
- EEG NeuroSky headset (Mindflex)

Soldering the EEG headset:
Solder the wire to the TPin on the bottom left corner of the NeuroSky chip. Solder ground to the battery. Put the TPin to the RX pin of the Arduino.

*Install the Arduino library for reading NeuroSky EEG Brain data: https://github.com/kitschpatrol/Brain and place it in the Documents/Arduino/Library folder*

PIN-OUT:
PIN0 = EEG (RX)
PIN1
PIN2 = Button
PIN3
PIN4 = LCD (RS)
PIN5 = LCD (Enable)
PIN6 = LCD
PIN7 = Bluetooth (RX - Arduino, TX - Bluetooth)
PIN8 = Bluetooth (TX - Arduino, RX - Bluetooth)
PIN9 = LCD
PIN10
PIN11 = EEG (Power)
PIN12 = LCD
PIN13 = LCD

How to use the program:

1) User enters page # (in hex) on phone.

2) Phone transmits page # to arduino via bluetooth

3) Once page # recieved, the program begins collecting brain information via EEG headset.

4) As user reads the textbook, average the score until user hits button for next page. Save the average in array. Increment currentPage.

5) Until user stops reading, collect data for each page

6) Once finished reading, sort the array by score. Program suggests pages to reread based on low score first.
