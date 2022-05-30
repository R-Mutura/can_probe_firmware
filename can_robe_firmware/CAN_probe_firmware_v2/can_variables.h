#ifndef CAN_VARIABLE_H
#define CAN_VARIABLE_H

static CAN_message_t msg,rxmsg;
volatile uint32_t count = 0;
IntervalTimer data_timer;
String CANStr(""); 
volatile uint32_t can_msg_count = 0;
float converted_data;

unsigned char data[4]; //char is a byte wide
//we will be receiving float data which are four bytes wide.
// we ll store them in data variable which is also 4bytes wide

uint8_t no_data1 = 0;   // No data counter for channel 1

 // all the id definitions in the CAN_A and CAB_B lines
#define engine_speed 500
#define fuel_flow_rate 524
#define manifold_air_pressure 528
#define oil_pressure 532
#define oil_temperature 536
#define coolant_temperature 548
#define engine_speed_B 564
#define fuel_flow_rate_B 588
#define manifold_air_pressure_B 592
#define oil_pressure_B 596
#define oil_temperature_B 600
#define coolant_temperature_B 612

#define EGT_cylinder_1 628
#define EGT_cylinder_2 630
#define EGT_cylinder_3 632
#define EGT_cylinder_4 634

#define EGT_cylinder_1_B 644
#define EGT_cylinder_2_B 646
#define EGT_cylinder_3_B 648
#define EGT_cylinder_4_B 650
#define throttle_position 692
#define throttle_position_B 696

#define manifold_air_temp 640
#define engine_ambient_temp 642



#define manifold_air_temp_B 656
#define engine_ambient_temp_B  658

#define engine_ambient_press 694
#define engine_ambient_press_B 698

#define ecu_bus_volt 950
#define ecu_bus_volt_B 954
#define oil_pressure_compensated 1300
#define boost_pressure 1302
#define boost_pressure_B 1306
#define oil_pressure_compensated_B 1304
#define air_flow 1308
#define air_flow_B 1320

#define boost_pressure_error 1312
#define boost_pressure_error_B 1324

#define target_wastage_position 1316
#define target_wastage_position_B 1328

//other status of the system
#define engine_hours 1208
#define engine_hours_B 1212
#define ecu_hours 1216
#define ecu_hours_B 1220
#define timestamp_A 1224
#define timestamp_B 1224


//defining a struct to hold all the data

struct {
float engine_speed_data;
float fuel_flow_rate_data;
float manifold_air_pressure_data;
float oil_pressure_data;
float oil_temperature_data;
float coolant_temperature_data;
float engine_speed_B_data;
float fuel_flow_rate_B_data;
float manifold_air_pressure_B_data;
float oil_pressure_B_data;
float oil_temperature_B_data;
float coolant_temperature_B_data;
  } basicdata;

struct {
float EGT_cylinder_1_data;
float EGT_cylinder_2_data;
float EGT_cylinder_3_data;
float EGT_cylinder_4_data;
float EGT_cylinder_1_B_data;
float EGT_cylinder_2_B_data;
float EGT_cylinder_3_B_data;
float EGT_cylinder_4_B_data;
float throttle_position_data;
float throttle_position_B_data;
float manifold_air_temp_data;
float engine_ambient_temp_data;
float manifold_air_temp_B_data;
float engine_ambient_temp_B_data;
float engine_ambient_press_data;
float engine_ambient_press_B_data;
  } enginedata;

struct {
float ecu_bus_volt_data;
float  ecu_bus_volt_B_data;
float  oil_pressure_compensated_data;
float  boost_pressure_data;
float  boost_pressure_B_data;
float  oil_pressure_compensated_B_data;
float  air_flow_data;
float  air_flow_B_data;

float  boost_pressure_error_data;
float  boost_pressure_error_B_data;

float target_wastage_position_data;
float  target_wastage_position_B_data;
} ecudata;

struct {
float engine_hours_data;
float engine_hours_B_data;
float ecu_hours_data;
float ecu_hours_B_data;
float timestamp_A_data;
  } statusdata;
  
#endif
