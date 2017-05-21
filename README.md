# Mind Rewind
Cutie Hackathon Project

This project was created by Justin Mac, Spyridon Catechis, and Ryan Wilson. We built this for students who struggle to focus when reading textbooks. The device takes EEG feedback from neural sensors and analyzes the alpha, beta, gamma, and delta waves to construct an "attention" score which is displayed on the LCD screen. Based on this score, the user can determine whether they should re-read the pages with the lowest scores. Every time the user finishes a page, they press the designated button for which the average score is logged along with the page. Then the program starts recording brainwave data for the next page. The user is able to turn on the LCD screen, input the starting page, and turn off the program through the designated iPhone app. The iPhone app is able to submit hex values through the iPhone app, LightBlue.

We first stripped the apart a child's toy that contained EEG sensors and rewired them through our own (smaller) circuitboard. This board was the main hub between the bluetooth module, EEG sensors, and LCD screen.

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

1) User enters page number (in hex) on phone.

2) Phone transmits page number to arduino via bluetooth

3) Once page number recieved, the program begins collecting brain information via EEG headset.

4) As user reads the textbook, the program averages the score until the user hits the button for the next page.

5) Until user stops reading, collect data for each page

6) Once finished reading, sort the array by score. Program suggests pages to reread based on low score first.
