# 🍭Automated Candy Dispenser🍬 (ECE 4180 Fall 2021)
Made by: Ikenna Nwokedi, Harneet Sethi, Felicia E, Anna Yue

## 🍫Project Description🍫
This device dispenses candy in a hands-free manner, similar to how hands-free soap dispensers work. The dispenser will use a lidar to detect motion and a DC motor to spin some blades that release candy. Inside the dispenser, there is a sonar to detect how much candy is left, and this information is displayed as a status bar using colored LEDs. The dispenser itself will sit on a robot chassis such that someone can drive it around using Bluetooth.

## ⚡Parts List⚡
### Robot Chassis
Dual H-bridge (https://www.sparkfun.com/products/14450)  
2 DC motors (https://www.sparkfun.com/products/13302)  
Chassis parts from kit (Sparkfun Shadow Chassis https://www.sparkfun.com/products/13301)  
Bluetooth module (https://www.adafruit.com/product/2479)  
Adafruit app on Andriod/iOS (Bluefruit Connect)  
Battery pack (comes with Shadow Chassis)  
Mbed (https://www.sparkfun.com/products/9564)  
### Candy Dispenser
Lidar (https://www.adafruit.com/product/3317)  
Sonar (https://www.sparkfun.com/products/15569)  
LEDs (1 red, 1 green, 1 yellow) (https://www.sparkfun.com/products/12062)  
Transistor (https://www.sparkfun.com/products/12959)  
1 DC motor (same as above)  
Plywood/MDF (https://www.homedepot.com/p/1-4-in-x-2-ft-x-4-ft-Medium-Density-Fiberboard-1508104/202089069#overlay)  
Battery pack (same as above, or https://www.sparkfun.com/products/9835)  
Mbed (same as above)  
Speaker (https://www.sparkfun.com/products/11089)  
Class D amplifier (https://www.sparkfun.com/products/11044)  
RGB LED (https://www.sparkfun.com/products/10820)  
uLCD (https://www.sparkfun.com/products/11377)  

### Miscellaneous
Wires  
Candy (about the size of Hershey Kisses)  
Wood glue  
Super glue  
Electrical tape  
Masking tape  

## 🛠️Tools Needed🛠️
Laser cutter  
3D Printer  
Drill  

# How It Works
## Sonar and Capacity Indicator LEDs
One component of the project is a sonar and led system that continuously measures the depth of candies in the dispenser and alerts the user to how full the box currently is by turning on separate LEDs.

There are three LEDs: green to indicate a full box or a high level of candies, yellow to indicate a medium level of candies, and red to indicate a low level of candies that will need to be quickly replenished.

The sonar used is a HC-SR04 sonar module. It is mounted to the inside of the top of the box. The detection range is around3-400 cm with around a 15 degree beam width. Its transducers for transmitting and receiving signals are connected to the mbed microcontroller at pins 6 and 7. It uses its transducers to send out a signal and receive an echo back. The speed of sound and the time as returned by a timer interrupt for the delay transmission and reception are used to calculate the distance between the sonar and the candies closest to it.

Depending on the distance that the sonar measures, either one of the LEDs will be switched on while the others are turned off or all LEDs will be turned off and an error message will output through the COM port.  

## Lidar and DC Motor
Another component of the project is a lidar and DC motor system that performs the hand-motion detection and actual dispensing of the candy. By reaching into the box with your hand open, the lidar is activated and the DC Motor will spin half a revolution, pushing out some candy with the attached 3D-printed blades.  

The lidar used is the VL53L0X module. It is able to detect distances from 30-1000 mm and works similarily to a sonar, except with light instead of ultrasonic waves and a smaller "cone" of detection.  

We specifically chose a lidar for this task due to the precision and reliability of the lidar measurements as well as its small size. Additionally, the lidar is situated pointing downwards so that it is always reading ~80 mm, so as soon as that reading drops to 65 mm it knows that some motion is being detected.  

The DC Motor is a standard motor that can be exchanged for a servo if desired. We primarily chose the DC Motor because the axle was easy to design a part to fit onto.  

## uLCD, Speaker, and RGB led
Lorem ipsum delorum  

## Robot Chassis
Lorem ipsum delorum  

# Instructions
## Cutting the Box
We started off by creating box using the website https://en.makercase.com/#/. The settings we used are as follows: Basic Box, Width 5 in., Height 8 in., Length 8 in., Outside dimensions, Material Thickness 1/4 in., Closed box, Finger joints sized 1.0915. These settings can be customized based on how big you want the dispenser to be and thickness of your wood. The box plans can be downloaded with labels disabled and separate panel layout, and these files can be used to laser cut the box at either the Hive or Invention Studio. The files we used are provided in the resources folder.  

![Laser Cut Box](../main/diagrams/just_box.JPG?raw=true "Laser Cut Box")

Furthermore, the box must be modified so that the bottom panel becomes like a shelf (see picture). We cut rectangular holes into the sides of the box so that the shelf could "slide" in, but there are other ways to do it if preferable. An additional rectangular hole was cut on the back panel to facillitate wiring, but again this can be changed as you see fit. The files we used to cut the holes are provided in the resources folder.  

For the LED holes, we used a 7/32" drill bit and approximated the locations. The red, yellow, and green LEDs are on the front panel, and the RGB LED is on the top panel. For the uLCD hole, we cut a xx by xx rectangle on the front panel. For the windmill blade hole, we cut a xx by xx rectangle on the shelf panel.  

> **Note:** We originally proposed using an LED array to display the status for the amount of candy left, but we changed this to individual LEDs to avoid having to replace the parts at the end of the semester.

![Modified Box](../main/diagrams/modified_box.JPG?raw=true "Modified Box")

## The Blades
For the part that releases the candy (referred to as windmill blades), we created a CAD model to 3D print. We used Autodesk Inventor to draw the model before exporting it as an stl file and transferring it to the 3D printer software. These files can be found in the resources folder. Our windmill blades are made from PLA.  

![Windmill Blades](../main/diagrams/windmill_blades.JPG?raw=true "Windmill Blades")

## Assembling the Box
Once the box is cut with all the correct holes and the windmill blades are printed, we can start mounting components in the box. For the purposes of our prototype, components were either taped or glued down, but screws/standoffs are needed if a more permanent solution is desired.  

The uLCD can be first installed by pushing it into the rectangular hole in the front panel. There is a base on the uLCD that prevents it from going all the way through the hole. The windmill blades should snap onto the DC motor axle, and the motor should be positioned on the shelf panel so that the blades can spin freely through the rectangular hole in the shelf panel. The sonar is attached to the underside of the top panel, such that it has a clear vision of the shelf panel without interference from the motor or blades. The LEDs can be pushed through their respective holes and also have a base that prevent them from going all the way through the hole. The lidar is situated on a small breadboard that is attached to the underside of the shelf panel closest to the side where someone would stick their hand through.  

![Mounted Components](../main/diagrams/mount_lcd.JPG?raw=true "Mounted Components")

Once the components are in place, they can be wired following the schematic below. The photos below also show how our wiring looks.

<table>
<tr><th> Sonar </th><th>LED </th></tr>
<tr><td>

| mbed       | HC-SR04 |
| :----: |:----:|
| GND  | GND |
| VU (5V) | VCC |
| P6 | TRIG     |
| P7 | ECHO      |

</td><td>

| mbed       | LEDs |
| :---: |:---:|
| GND  | RED(-), YELLOW (-), GREEN (-) |
| P12  | Red (+) |
| P13 | YELLOW (+) |
| P14 | GREEN (+)|
  
</td></tr> </table>


<table>
<tr><th> MOSFET and Motor connections</th><th> DC Motor </th><th>
<tr><td>

| mbed       | MOSFET (Transistor) |
| :---: |:---:|
| VU (5V) | GND (JP2-2 GND) |
| GND  | POWER (JP2-1 RAW) |
| P8  | CONTROL |

</td><td>

| MOSFET (Transistor) | DC Motor |
| :---: |:---:|
| GND (JP1-2) | GND (-) |
| POWER (JP1-1) | POWER (+) |

</td></tr> </table>

<table>
<tr><th> Lidar </th><th> uLCD </th></tr>
<tr><td>

| mbed  | LIDAR (VL53L0X) |
| :---: |:---:|
| VOUT (3.3V) | VIN |
| VU (5V) | VCC |
| GND  | GND |
| P25  | SHDN |
| P27  | SCL |
| P28  | SDA |

</td><td>

| mbed  | uLCD HEADER | uLCD CABLE |
| :---: |:---:|:---:|
| GND  | GND | GND |
| VU (5V)  | 5V | 5V |
| P9 | RX | TX |
| P10 | RX | TX |
| P10 | TX | RX |
| P11 | RESET | RESET |

</td></tr> </table>

<table>
<tr><th> RGB LED connections </th><th>Speaker connections</th></tr>
<tr><td>

| mbed  | RGB LED |
| :---: |:---:|
| GND  | GND |
| P21  | RED |
| P22  | GREEN |
| P23  | BLUE |

</td><td>

| mbed  | Amp (TPA2005D1) | Speaker |
| :---: |:---:|:---:|
| GND  | PWR- (GND), IN- |
| VU (5V)  | PWR+ |
| P26  | IN+ |
|   | OUT+ | + |
|   | OUT- | - |

</td></tr> </table>

## The Chassis
The robot chassis can be assembled following the Sparkfun guide: https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis. Bluetooth control is added using the Adafruit Bluefruit LE UART Friend board. The Adafruit board mini slide must be set to "UART" (not "CMD"). The "Adafruit Bluefruit BLE" app is used for the user interface and can be found on iOS and Andriod. Select "UART" mode on the phone window and connect to the board. A blue LED should turn on once connected.

![Chassis](../main/diagrams/Chassis.JPG?raw=true "Chassis")

A 6 V battery pack is used to power the two motors attached to the wheels. A dual H-bridge will regulate the speed and direction of the motor wheels. Using the Adafruit Bluefruit BLE app, buttons 1, 2, 3, and 4 set the speed level of the wheels (on a scale from 0 to 1). While the up and down buttons move the motors forward and backward respectfully, the left and right buttons inverse the direction of both motors, resulting in a rotational movement around the chassis center. The motors must gradually increase to their set speed for a minimum of a second to keep the mbed from undervolting. This is done with a separate thread that terminates at the release of the control button. 

![UI Controls](../main/diagrams/BLE_UI_controls.JPG?raw=true "UI Controls")

<table>
<tr><th> Bluetooth </th><th> H-Bridge </th><th> Motor </tr>
<tr><td>

| mbed       | Adafruit BLE          |
| ------------- |:-------------:|
| VU (5V)     | Vin (3.3-16V)     |
| P27 (RX) | TXO     |
| P28 (RX) | RXI      |
| GND      | GND |
| NC | RTS      |

</td><td>

| mbed       | H-Bridge   |
| ------------- |:-------------:|
| P21 | PWMA     |
| P22 | AIN1     |
| P23 | AIN2     |
| P24 | PWMB     |
| P25 | BIN1     |
| P26 | BIN2     |
| VOUT | STBY     |
| GND      | GND |

</td><td>

| H-Bridge   | Battery Pack | Left Motor | Right Motor |
|:-------------:|:-------------:|:-------------:|:-------------:|
|GND|GND  ||
|VM, VCC|5V|||
|A01||GND (BLACK)|
|A02||POWER (RED)|
|B01|||POWER(RED)|
|B02|||GND(BLACK)|

</td></tr> </table>

## Combining Everything
The box can sit exactly on top of the chassis...
