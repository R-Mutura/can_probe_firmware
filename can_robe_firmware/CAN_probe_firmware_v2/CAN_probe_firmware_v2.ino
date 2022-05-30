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
   memcpy(&converted_data, data, 4);   //Convert data to float
    Serial.println(converted_data);
  //now to compare the IDs so that we know where to store the data
  switch(msg.id){
      case engine_speed:{
         basicdata.engine_speed_data = converted_data;
         break;
        }
       case fuel_flow_rate:{
         basicdata.fuel_flow_rate_data = converted_data;
         break;
        }
       case manifold_air_pressure:{
         basicdata.manifold_air_pressure_data = converted_data;
         break;
        }
        case oil_pressure:{
         basicdata.oil_pressure_data = converted_data;
         break;
        }
        case oil_temperature:{
         basicdata.oil_temperature_data = converted_data;
         break;
        }
         case coolant_temperature:{
         basicdata.coolant_temperature_data = converted_data;
         break;
        }
        case engine_speed_B:{
         basicdata.engine_speed_B_data = converted_data;
         break;
        }
        case fuel_flow_rate_B:{
         basicdata.fuel_flow_rate_B_data = converted_data;
         break;
        }
        case manifold_air_pressure_B:{
         basicdata.manifold_air_pressure_B_data = converted_data;
         break;
        }
        case oil_pressure_B:{
         basicdata.oil_pressure_B_data = converted_data;
         break;
        }
        case oil_temperature_B:{
         basicdata.oil_temperature_B_data = converted_data;
         break;
        }
        case coolant_temperature_B:{
         basicdata.coolant_temperature_B_data = converted_data;
         break;
        }

        //engine daata varables
        case EGT_cylinder_1:{
         enginedata.EGT_cylinder_1_data = converted_data;
         break;
        }
        case EGT_cylinder_2:{
         enginedata.EGT_cylinder_2_data = converted_data;
         break;
        }
        case EGT_cylinder_3:{
         enginedata.EGT_cylinder_3_data = converted_data;
         break;
        }
        case EGT_cylinder_4:{
         enginedata.EGT_cylinder_4_data = converted_data;
         break;
        }
        case EGT_cylinder_1_B:{
         enginedata.EGT_cylinder_1_B_data = converted_data;
         break;
        }
        case EGT_cylinder_2_B:{
         enginedata.EGT_cylinder_2_B_data = converted_data;
         break;
        }
        case EGT_cylinder_3_B:{
         enginedata.EGT_cylinder_3_B_data = converted_data;
         break;
        }
        case EGT_cylinder_4_B:{
         enginedata.EGT_cylinder_4_B_data = converted_data;
         break;
        }
        case throttle_position:{
         enginedata.throttle_position_data = converted_data;
         break;
        }
        case manifold_air_temp:{
         enginedata.manifold_air_temp_data = converted_data;
         break;
        }
        case engine_ambient_temp:{
         enginedata.engine_ambient_temp_data = converted_data;
         break;
        }
        case manifold_air_temp_B:{
         enginedata.manifold_air_temp_B_data = converted_data;
         break;
        }
        case engine_ambient_temp_B:{
         enginedata.engine_ambient_temp_B_data = converted_data;
         break;
        }
        case engine_ambient_press:{
         enginedata.engine_ambient_press_data = converted_data;
         break;
        }
        case engine_ambient_press_B:{
         enginedata.engine_ambient_press_B_data = converted_data;
         break;
        }
        //ECU DATA AND OTHER SMALL DATA
        case ecu_bus_volt:{
         ecudata.ecu_bus_volt_data = converted_data;
         break;
        }
        case ecu_bus_volt_B:{
         ecudata.ecu_bus_volt_B_data = converted_data;
         break;
        }
        case oil_pressure_compensated:{
         ecudata.oil_pressure_compensated_data = converted_data;
         break;
        }
        case boost_pressure:{
         ecudata.boost_pressure_data = converted_data;
         break;
        }
        case boost_pressure_B:{
         ecudata.boost_pressure_B_data = converted_data;
         break;
        }
        case oil_pressure_compensated_B:{
         ecudata.oil_pressure_compensated_B_data = converted_data;
         break;
        }
        case air_flow:{
         ecudata.air_flow_data = converted_data;
         break;
        }
        case air_flow_B:{
         ecudata.air_flow_B_data = converted_data;
         break;
        }
        case boost_pressure_error:{
         ecudata.boost_pressure_error_data = converted_data;
         break;
        }
        case boost_pressure_error_B:{
         ecudata.boost_pressure_error_B_data = converted_data;
         break;
        }
        case target_wastage_position:{
         ecudata.target_wastage_position_data = converted_data;
         break;
        }
        case target_wastage_position_B:{
         ecudata.target_wastage_position_B_data = converted_data;
         break;
        }

        //status data 
        case timestamp_A:{
         statusdata.timestamp_A_data = converted_data;
         break;
        }
        case engine_hours:{
         statusdata.engine_hours_data = converted_data;
         break;
        }
        case engine_hours_B:{
         statusdata.engine_hours_B_data = converted_data;
         break;
        }
        case ecu_hours:{
         statusdata.ecu_hours_data = converted_data;
         break;
        }
        case ecu_hours_B:{
         statusdata.ecu_hours_B_data = converted_data;
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
