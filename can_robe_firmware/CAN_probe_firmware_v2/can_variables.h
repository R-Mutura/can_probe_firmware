#ifndef CAN_VARIABLE_H
#define CAN_VARIABLE_H

static CAN_message_t msg,rxmsg;
volatile uint32_t count = 0;
IntervalTimer data_timer;
String CANStr(""); 
volatile uint32_t can_msg_count = 0;
float converted_data;
uint32_t status_word;

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

//status ID with data typr blong
#define engine_status 556
#define engine_status_B 620
#define lane_A_sensor_status 1500
#define lane_A_sensor_status_B 1504
#define lane_A_device_status 1508
#define lane_A_device_status_B 1512

#define lane_B_sensor_status 1516
#define lane_B_sensor_status_B 1520
#define lane_B_device_status 1524
#define lane_B_device_status_B 1528

//defining a struct to hold all the data


  //basic data
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


  //status data word formats with BLONG TYPE IN DOCUMENT
struct{
  uint32_t engine_status_data;
 uint32_t engine_status_B_data;
 uint32_t lane_A_sensor_status_data;
 uint32_t lane_A_sensor_status_B_data;
 uint32_t lane_A_device_status_data;
 uint32_t lane_A_device_status_B_data;

 uint32_t lane_B_sensor_status_data;
 uint32_t lane_B_sensor_status_B_data;
 uint32_t lane_B_device_status_data;
 uint32_t lane_B_device_status_B_data;
  }statusword;

//definition of data found in engine status 
#define lane_in_control 0
#define power_economy_mode 1
#define generator_select_switch_state 2
#define overboost_relief_PCV_actuated 3 //returns 1 or zero
#define warning_lamp_state_on 5
#define warning_lamp_state_blinking 4//if both are not 1 then the lamp is off
#define wastegate_PCV_test_2_complete 6
#define wastegate_PCV_test_1_complete 7
// #define knock_state_maximum_normal_operation //all are ero in this state for bits 8 and 9
#define knock_state_maximum_timing_retarded 8
#define knock_state_maximum_unable 9
//#define knock_state_maximum_normal_operation //if both bits 8 and 9 are 1
#define knock_protection_enabled 11
#define engine_speed_status_stall 20
#define engine_speed_status_waiting 21
//#define engine_speed_status_halfsync ((1<<engine_speed_status_waiting)|(1<<engine_speed_status_stall)
#define engine_speed_status_fullsync 22




//funtion to get specific user status data

//getting lane which is in control status
int get_lane_incontrol(uint32_t wordvariable ){
   //call this function and pass the status data you want to check if is in control
   //eg int laneAstatus = get_lane_incontrol(statusword.engine_status_data);
   //you will get 1 (meaning the lane is in control) or 0 (meaning lane is not in control)

     int x = (wordvariable & (1<lane_in_control));
    return x; //returns 1 or zero
  }

int get_power_economy_mode(uint32_t wordvariable ){
      int x = (wordvariable & (1<power_economy_mode));
    return x; //returns 1 or zero
    }

int get_generator_select_switch_state(uint32_t wordvariable ){
      int x = (wordvariable & (1<generator_select_switch_state));
    return x; //returns 1 or zero
    }
int get_overboost_relief_PCV_actuated(uint32_t wordvariable ){
      int x = (wordvariable & (1<overboost_relief_PCV_actuated));
    return x; //returns 1 or zero
    }
int get_warning_lamp_State(uint32_t wordvariable ){
      int x; 
      if(wordvariable & (1<<warning_lamp_state_on)) {
        return(x=1);
      }
      else if(wordvariable &(1<<warning_lamp_state_blinking)){
        return (x=2);
        }
        else{
           return (x=0);
          }
    //returns 1 or 2 or 0
    // 1 == lamp on
    //2 == lamp blinking
    // 0 == lamp off
    }
 int get_wastegate_PCV_test_2_complete(uint32_t wordvariable ){
      
       int x = (wordvariable & (1<wastegate_PCV_test_2_complete));
    return x; //returns 1 or zero  
  }

int get_wastegate_PCV_test_1_complete(uint32_t wordvariable ){
      
       int x = (wordvariable & (1<wastegate_PCV_test_1_complete));
    return x; //returns 1 or zero  
  }

int get_knock_state_maximum(uint32_t wordvariable ){
      
           int x; 
      if(wordvariable &(1<<knock_state_maximum_timing_retarded )) {
        return(x=1);
      }
      else if(wordvariable &(1<<knock_state_maximum_unable)){
        return (x=2);
        }
        else if(wordvariable &((1<<knock_state_maximum_unable)|(1<<knock_state_maximum_timing_retarded ))){
           return (x=3);
          }
          else {
            return(x=0);
            }
    //returns 1 or 2 or 0
    // 0 == Normal operation
    // 1 == timit retarded
    // 2 =Unable to mitigate Knock, Maximum Timing Retard Applied
    // 3 == Failsafe, Maximum Timing Retard Applied (Knock Sensor Failure)
  }
int get_knock_protection_enabled(uint32_t wordvariable ){
    int x = (wordvariable & (1<knock_protection_enabled ));
    return x; //returns 1 or zero  
  }


int get_engine_speed_status(uint32_t wordvariable ){
      
           int x; 
      if(wordvariable &(1<<engine_speed_status_stall )) {
        return(x=1);
      }
      else if(wordvariable &(1<<engine_speed_status_waiting)){
        return (x=2);
        }
        else if(wordvariable &((1<<engine_speed_status_waiting)|(1<<engine_speed_status_stall))){
           return (x=3);
          }
        else if (wordvariable &(1<<engine_speed_status_fullsync)) {
            return(x=4);
            }
        else{
            return 0;
            }
    //returns 1 or 2 or 0
    // 0 == Normal operation
    // 1 == timit retarded
    // 2 =Unable to mitigate Knock, Maximum Timing Retard Applied
    // 3 == Failsafe, Maximum Timing Retard Applied (Knock Sensor Failure)
  }

#endif
