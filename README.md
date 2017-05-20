# Study Band
Cutie Hackathon Project

This project was created by Justin Mac, Spyridon Catechis, and Ryan Wilson.

Hardware Needed:
- Arduino
- HM10 Bluetooth Module
- LCD screen
- EEG headset (Mindflex)

1) User enters page # (in hex) on phone.

2) Phone transmits page # to arduino via bluetooth

3) Once page # recieved, begin collecting brain info via EEG nodes

4) As user reads the textbook, average the score until user hits button for next page. Save the average in array. Increment currentPage.

5) Until user stops reading, collect data for each page

6) Once finished reading, sort the array by score. Program suggests pages to reread based on low score first.
