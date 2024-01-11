#include <DMXSimple.h>

#define HEADLIGHT1TOTAL 1
#define HEADLIGHT1R 2
#define HEADLIGHT1G 3
#define HEADLIGHT1B 4
#define HEADLIGHT1W 5
#define HEADLIGHT1STROBE 6
#define HEADLIGHT1FUNC 7
#define HEADLIGHT1FUNCSP 8

#define HEADLIGHT2TOTAL 37
#define HEADLIGHT2R 38
#define HEADLIGHT2G 39
#define HEADLIGHT2B 40
#define HEADLIGHT2W 41
#define HEADLIGHT2STROBE 42
#define HEADLIGHT2FUNC 43
#define HEADLIGHT2FUNCSP 44

#define MOVINGHEAD1PAN 9 // schwenken (rechts-links)
#define MOVINGHEAD1PANFINE 10
#define MOVINGHEAD1TILT 11 // kippen (hoch-runter)
#define MOVINGHEAD1TILTFINE 12
#define MOVINGHEAD1SPEED 13
#define MOVINGHEAD1EFFECT 14
#define MOVINGHEAD1REDDIM 15
#define MOVINGHEAD1GREENDIM 16
#define MOVINGHEAD1BLUEDIM 17
#define MOVINGHEAD1WHITEDIM 18
#define MOVINGHEAD1COLORCHOOSE 19
#define MOVINGHEAD1COLORSPEED 20
#define MOVINGHEAD1AUTO 21

#define MOVINGHEAD2PAN 23
#define MOVINGHEAD2PANFINE 24
#define MOVINGHEAD2TILT 25
#define MOVINGHEAD2TILTFINE 26
#define MOVINGHEAD2SPEED 27
#define MOVINGHEAD2EFFECT 28
#define MOVINGHEAD2REDDIM 29
#define MOVINGHEAD2GREENDIM 30
#define MOVINGHEAD2BLUEDIM 31
#define MOVINGHEAD2WHITEDIM 32
#define MOVINGHEAD2COLORCHOOSE 33
#define MOVINGHEAD2COLORSPEED 34
#define MOVINGHEAD2AUTO 35

unsigned long startMillis;
unsigned long currentMillis;
int tiltValue;
int panValue;

void setup()
{
    DMXSimple.usePin(3);      // Use digital pin 3 for DMX output
    DmxSimple.maxChannel(44); // Set max channel used to 44
    DMXSimple.write(MOVINGHEAD1PAN, 0);
    DMXSimple.write(MOVINGHEAD2PAN, 255);

    startMillis = millis(); // Save the start time
    tiltValue = 0;
    panValue = 0;


//Color Test for Orange without total dimming
    DMXSimple.write(HEADLIGHT1R, 255); // Orange color (R: 100%, G: 50%, B: 0%)
    DMXSimple.write(HEADLIGHT1G, 127);
    DMXSimple.write(HEADLIGHT1B, 0);
    DMXSimple.write(HEADLIGHT1W, 255)

     DMXSimple.write(HEADLIGHT2R, 255); // Orange color (R: 100%, G: 50%, B: 0%)
    DMXSimple.write(HEADLIGHT2G, 127);
    DMXSimple.write(HEADLIGHT2B, 0);
    DMXSimple.write(HEADLIGHT2W, 255)
}

void loop() {
    currentMillis = millis(); // Get the current time

    // Calculate the tilt value based on the current time
    if (currentMillis - startMillis < 9000) {
        tiltValue = map(currentMillis - startMillis, 0, 9000, 0, 255);
    } else if (currentMillis - startMillis < 17000) {
        tiltValue = map(currentMillis - startMillis, 9000, 17000, 255, 0);
    } else {
        startMillis = currentMillis; // Reset the start time
    }

    void loop() {
    currentMillis = millis(); // Get the current time

    // Calculate the tilt value based on the current time
    if (currentMillis - startMillis < 9000) {
        tiltValue = map(currentMillis - startMillis, 0, 9000, 0, 255);
    } else if (currentMillis - startMillis < 17000) {
        tiltValue = map(currentMillis - startMillis, 9000, 17000, 255, 0);
    } else {
        startMillis = currentMillis; // Reset the start time
    }

    // Calculate the pan value based on a sine wave with a period of 1.5 seconds or 0.8 seconds
    float period = (currentMillis - startMillis < 9000) ? 1500.0 : 800.0; // Period in milliseconds
    float time = (currentMillis % (int)period) / period; // Time in the range 0 to 1
    panValue = 127.5 + 127.5 * sin(2 * PI * time); // Pan value in the range 0 to 255

    // Write the pan and tilt values to the moving heads
    DMXSimple.write(MOVINGHEAD1PAN, panValue);
    DMXSimple.write(MOVINGHEAD1TILT, tiltValue);
    DMXSimple.write(MOVINGHEAD2PAN, 255 - panValue); // Reverse pan direction for second moving head
    DMXSimple.write(MOVINGHEAD2TILT, tiltValue); // Same tilt for second moving head

    // Change color of the headlights to orange and adjust brightness based on tilt value
    int brightness = tiltValue; // Brightness is same as tilt value
    DMXSimple.write(HEADLIGHT1W, brightness); 
    DMXSimple.write(HEADLIGHT2W, brightness); 
}

    // Write the pan and tilt values to the moving heads
    DMXSimple.write(MOVINGHEAD1PAN, panValue);
    DMXSimple.write(MOVINGHEAD1TILT, tiltValue);
    DMXSimple.write(MOVINGHEAD2PAN, 255 - panValue); // Reverse pan direction for second moving head
    DMXSimple.write(MOVINGHEAD2TILT, tiltValue); // Same tilt for second moving head

    // Change color of the headlights to orange and adjust brightness based on tilt value
    int brightness = tiltValue; // Brightness is same as tilt value
    DMXSimple.write(HEADLIGHT1W, brightness); 
    DMXSimple.write(HEADLIGHT2W, brightness); 
}
