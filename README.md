# can_probe_firmware


## Requirements
1) Set up the IDE, for this application you will need to download the Arduino ide [here](https://www.arduino.cc/en/software) if you don't have it already installed for your distributions
2) Instal the board support package for Teensy by goint to [Download Teensyduino, Version 1.56](https://www.pjrc.com/teensy/td_download.html). Navigate to your desired installation files according to the OS installed on your computer and click to download 
3) Now Close your Arduino IDE if open and click the downloaded file to start the installation process. 
For reference on how to install teensy support to arduino you can follow this [tutorial](https://www.youtube.com/watch?v=eoGyoEx9Iog)
</br> Once installation is done open your IDE and then proceed to the next instructions


## Download the files 
4)  Download all the files on the `Code`:arrow_down_small: on this platform, In your downloads you will get the a folder :file_folder:  `can_robe_firmware`this will have:
     - can_probe_firmware_v2.ino
     - can_variables.h
</br> and `Libraries` zip file -this contains all the related libraries used in the project

## Library Installation
5)  On library installation unzip the folder :file_folder: `libraries` in the downloaded folder :file_folder:, copy and paste all the folders to your directory `documents/arduino/library` folder :file_folder:

# Uploading the codes  :arrow_up:
1) Open Arduino IDE software. ...
2) Next, call out the source code. ...
3) Select the appropriate board by going to ` Tools > Board:xx > Teensyduino` and select your board.
4) Select the USB type ` Tools > USB type: xx> serial`
5) Select CPU speed if needed ` Tools > CPU speed:xx >`
6) Select port if need be ` Tools > port`
7) Press the arrow key and let the IDE compile and the code uploads directly
8) Open the serial monitor for debugging purposes if connected to a computer.

# Features
The `can_variable` folder holds all the variables used in the CAN communication such as sensors data`ID` and structures that hold these data
<br> THe data are stored in 4 major divisions of structures
1) basicdata - holds the basic data information such as `Engine Speed` stored in `engine_speed_data` to `Coolant Temperature` from line B stored in `coolant_temperature_B_data`
2) enginedata - holds engine based data such as `EGT cylinder 1` stored in `EGT_cylinder_1_data` to `engine ambient pressure`on CAN line B stored in `engine_ambient_press_B_data`
3) ecudata - holding the rest of the information such as `ecu_bus_volt_data` to `target_wastage_position_B_data`
4) statusdata - holding status data (NOTE: not all the data is stored in this structure such as those with BLONG type)
5) statusword - this store data of type BLONG which hold the status of various parst such as `Engine Status ` , `Device Status` and `Sensor status`
   <br> Timestamp for line A is stored in the variable timestamp_A_data and since the timestamp is shared it will be the same for both CANs A and B
   
   <br> Therefore, to access data of interest to use on the display or for storage, you can access the structure members of interest. For example to get `Engine Speed` call `basicdata.engine_speed_data`
   . To access `EGT cylinder 4` call ` enginedata.EGT_cylinder_4_data` and to access `Engine hours` availed on CAN line A call `engine_hours` while `Engine hours` availed on CAN lane B call `statusdata.engine_hours_B_data`
 <br>
 <br> 
 To get the engine status of interest just call the function located in the `can_variables.h` file
 eg if you want to get `warning light status` call the function like `int warning_light_lane_A = get_warning_lamp_State(engine_status_data);` You will get values either 0, 1 or 2. this stand for off, on or blinking repectively as described in the ROTARAX Technical document
 the same for other add `get_` prefix then the status you want to get and assign it to a variable. Then you can use the received data to do some other operations.
 You will find comments in the file `variabl.h` for guidance
   ## THANK YOU
