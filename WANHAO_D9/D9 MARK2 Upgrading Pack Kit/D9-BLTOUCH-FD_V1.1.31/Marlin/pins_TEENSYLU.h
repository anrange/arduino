#if !defined(__AVR_AT90USB1286__) && !defined(__AVR_AT90USB1286P__)
  #error "Oops!  Make sure you have 'Teensy++ 2.0' or 'Printrboard' selected from the 'Tools -> Boards' menu."
#endif
#define BOARD_NAME         "Teensylu"
#define USBCON 1286  
#define LARGE_FLASH        true
#define X_STOP_PIN              26   
#define Y_STOP_PIN              27   
#define Z_STOP_PIN              36   
#define X_STEP_PIN              28   
#define X_DIR_PIN               29   
#define X_ENABLE_PIN            19   
#define Y_STEP_PIN              30   
#define Y_DIR_PIN               31   
#define Y_ENABLE_PIN            18   
#define Z_STEP_PIN              32   
#define Z_DIR_PIN               33   
#define Z_ENABLE_PIN            17   
#define E0_STEP_PIN             34   
#define E0_DIR_PIN              35   
#define E0_ENABLE_PIN           13   
#define TEMP_0_PIN               7   
#define TEMP_BED_PIN             6   
#define HEATER_0_PIN            15   
#define HEATER_BED_PIN          14   
#define FAN_PIN                 16   
#define SDSS                    20   
#define CASE_LIGHT_PIN           0   
#if ENABLED(ULTRA_LCD) && ENABLED(NEWPANEL)
  #define BEEPER_PIN            -1
  #if ENABLED(LCD_I2C_PANELOLU2)
    #define BTN_EN1              3   
    #define BTN_EN2              2   
    #define BTN_ENC             41   
    #define SDSS                38   
  #endif
  #define SD_DETECT_PIN         -1
#endif 
#define SPINDLE_LASER_PWM_PIN    24   
#define SPINDLE_LASER_ENABLE_PIN 39   
#define SPINDLE_DIR_PIN          40   
