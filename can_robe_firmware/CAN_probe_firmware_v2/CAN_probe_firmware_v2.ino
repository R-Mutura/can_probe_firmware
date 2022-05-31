#include <FlexCAN_T4.h> //CAN library
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
#include <SPI.h>
//screen libraries // SPI MODE
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "can_variables.h"
//SCREENS DEFINITIONS
#define TFT_RST 35
#define TFT_DC  37
#define TFT_CS  10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup(void) {
  Serial.begin(115200); delay(400);
  //SCREEN SETUP
   SPI.setMOSI(11);
   SPI.setSCK(13);
   tft.begin();
  //CAN SETUP
  Can0.begin(); 
  
  Can0.setBaudRate(125000);//CAN SPEED AT 125KHz
  Serial.print("CAN Bus enabled successfully");
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  Can0.mailboxStatus();

  data_timer.begin(data_count, 1000000);   // Start no data interrupt counter at 1s interval
 //this is used as an error checking variable to check how long we ll go without data when on
 
}

void data_count(void)
{
  no_data1++;
  
}

//CAN message recived interrupt handler
void canSniff(const CAN_message_t &msg) {
//  Serial.print("MB "); Serial.print(msg.mb);
//  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
//  Serial.print("  LEN: "); Serial.print(msg.len);
//  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
//  Serial.print(" TS: "); Serial.print(msg.timestamp);
//  Serial.print(" ID: "); Serial.print(msg.id, HEX);
//  Serial.print(" Buffer: ");
//   //extracting bytes from buffer
      data[0] = msg.buf[0];
      data[1] = msg.buf[1];
      data[2] = msg.buf[2];
      data[3] = msg.buf[3];
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(data[i], HEX); Serial.print(" ");//printin on screen the received bytes
  }
  Serial.println();
  
  //now to compare the IDs so that we know where to store the data
  switch(msg.id){
      case engine_speed:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
          basicdata.engine_speed_data = converted_data;
         break;
        }
       case fuel_flow_rate:{
         basicdata.fuel_flow_rate_data = converted_data;
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         break;
        }
       case manifold_air_pressure:{
        memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.manifold_air_pressure_data = converted_data;
         break;
        }
        case oil_pressure:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.oil_pressure_data = converted_data;
         break;
        }
        case oil_temperature:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.oil_temperature_data = converted_data;
         break;
        }
         case coolant_temperature:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.coolant_temperature_data = converted_data;
         break;
        }
        case engine_speed_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.engine_speed_B_data = converted_data;
         break;
        }
        case fuel_flow_rate_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.fuel_flow_rate_B_data = converted_data;
         break;
        }
        case manifold_air_pressure_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.manifold_air_pressure_B_data = converted_data;
         break;
        }
        case oil_pressure_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.oil_pressure_B_data = converted_data;
         break;
        }
        case oil_temperature_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.oil_temperature_B_data = converted_data;
         break;
        }
        case coolant_temperature_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         basicdata.coolant_temperature_B_data = converted_data;
         break;
        }

        //engine daata varables
        case EGT_cylinder_1:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_1_data = converted_data;
         break;
        }
        case EGT_cylinder_2:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_2_data = converted_data;
         break;
        }
        case EGT_cylinder_3:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_3_data = converted_data;
         break;
        }
        case EGT_cylinder_4:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_4_data = converted_data;
         break;
        }
        case EGT_cylinder_1_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_1_B_data = converted_data;
         break;
        }
        case EGT_cylinder_2_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_2_B_data = converted_data;
         break;
        }
        case EGT_cylinder_3_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_3_B_data = converted_data;
         break;
        }
        case EGT_cylinder_4_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.EGT_cylinder_4_B_data = converted_data;
         break;
        }
        case throttle_position:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.throttle_position_data = converted_data;
         break;
        }
        case manifold_air_temp:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.manifold_air_temp_data = converted_data;
         break;
        }
        case engine_ambient_temp:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.engine_ambient_temp_data = converted_data;
         break;
        }
        case manifold_air_temp_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.manifold_air_temp_B_data = converted_data;
         break;
        }
        case engine_ambient_temp_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.engine_ambient_temp_B_data = converted_data;
         break;
        }
        case engine_ambient_press:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.engine_ambient_press_data = converted_data;
         break;
        }
        case engine_ambient_press_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         enginedata.engine_ambient_press_B_data = converted_data;
         break;
        }
        //ECU DATA AND OTHER SMALL DATA
        case ecu_bus_volt:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.ecu_bus_volt_data = converted_data;
         break;
        }
        case ecu_bus_volt_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.ecu_bus_volt_B_data = converted_data;
         break;
        }
        case oil_pressure_compensated:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.oil_pressure_compensated_data = converted_data;
         break;
        }
        case boost_pressure:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.boost_pressure_data = converted_data;
         break;
        }
        case boost_pressure_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.boost_pressure_B_data = converted_data;
         break;
        }
        case oil_pressure_compensated_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.oil_pressure_compensated_B_data = converted_data;
         break;
        }
        case air_flow:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.air_flow_data = converted_data;
         break;
        }
        case air_flow_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.air_flow_B_data = converted_data;
         break;
        }
        case boost_pressure_error:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.boost_pressure_error_data = converted_data;
         break;
        }
        case boost_pressure_error_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.boost_pressure_error_B_data = converted_data;
         break;
        }
        case target_wastage_position:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.target_wastage_position_data = converted_data;
         break;
        }
        case target_wastage_position_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         ecudata.target_wastage_position_B_data = converted_data;
         break;
        }

        //status data 
        case timestamp_A:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         statusdata.timestamp_A_data = converted_data;
         break;
        }
        case engine_hours:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         statusdata.engine_hours_data = converted_data;
         break;
        }
        case engine_hours_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         statusdata.engine_hours_B_data = converted_data;
         break;
        }
        case ecu_hours:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         statusdata.ecu_hours_data = converted_data;
         break;
        }
        case ecu_hours_B:{
          memcpy(&converted_data, data, 4);   //Convert data to float
          Serial.println(converted_data);
         statusdata.ecu_hours_B_data = converted_data;
         break;
        }
        case engine_status:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.engine_status_data = status_word;
         break;
        }
         case engine_status_B:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.engine_status_B_data = status_word;
         break;
        }
        case lane_A_sensor_status:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_A_sensor_status_data = status_word;
         break;
        }
         case lane_A_sensor_status_B:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_A_sensor_status_B_data = status_word;
         break;
        } 
         case lane_A_device_status:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_A_device_status_data = status_word;
         break;
        } 
        case lane_A_device_status_B:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_A_device_status_B_data = status_word;
         break;
        } 
        case lane_B_sensor_status:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_B_sensor_status_data = status_word;
         break;
        } 
        case lane_B_sensor_status_B:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_B_sensor_status_B_data = status_word;
         break;
        }     
        case lane_B_device_status:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_B_device_status_data = status_word;
         break;
        }  
        case lane_B_device_status_B:{
          memcpy(&status_word, data, 4);   //Convert data to float
          Serial.println(status_word);
         statusword.lane_B_device_status_B_data = status_word;
         break;
        }                     
        default:{
          break;
          }
    }//end of switch case statements
     no_data1 = 0;
}

void loop() {
  Can0.events();

  if( no_data1>60){
    Serial.println("Check connecion, NO data avilable");
    }

}
