#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644__) && !defined(__AVR_ATmega1284P__)
  #error "Oops!  Make sure you have 'Sanguino' selected from the 'Tools -> Boards' menu."
#endif
#define BOARD_NAME "Gen7 v1.4"
#define GEN7_VERSION 14 
#define X_STOP_PIN          0
#define Y_STOP_PIN          1
#define Z_STOP_PIN          2
#define X_STEP_PIN         29
#define X_DIR_PIN          28
#define X_ENABLE_PIN       25
#define Y_STEP_PIN         27
#define Y_DIR_PIN          26
#define Y_ENABLE_PIN       25
#define Z_STEP_PIN         23
#define Z_DIR_PIN          22
#define Z_ENABLE_PIN       25
#define E0_STEP_PIN        19
#define E0_DIR_PIN         18
#define E0_ENABLE_PIN      25
#define TEMP_0_PIN          1   
#define TEMP_BED_PIN        0   
#define HEATER_0_PIN        4
#define HEATER_BED_PIN      3
#define PS_ON_PIN          15
#define CASE_LIGHT_PIN     15    
#define DEBUG_PIN           0
#define TX_ENABLE_PIN      12
#define RX_ENABLE_PIN      13
#define SPINDLE_LASER_ENABLE_PIN 20  
#define SPINDLE_LASER_PWM_PIN    16  
#define SPINDLE_DIR_PIN          21
