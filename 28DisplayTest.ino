/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include "Display_ST7789.h"
#include "Audio_PCM5101.h"
// #include "RTC_PCF85063.h"
// #include "Gyro_QMI8658.h"
#include "LVGL_Driver.h"
#include "PWR_Key.h"
// #include "SD_Card.h"
// #include "LVGL_Example.h"
#include "BAT_Driver.h"
// #include "Wireless.h"
#include "ui.h"
#include "ui_events.h"

#include <Arduino.h>
#include "BLEDevice.h"
#include "BLEHIDDevice.h"
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#include "stratagems_table.h"

#define US_KEYBOARD 1

// Change the below values if desired
#define BUTTON_PIN 15
#define MESSAGE "Hello from ESP32\n"
#define DEVICE_NAME "ESP32 Keyboard"


// Forward declarations
void bluetoothTask(void*);
void typeText(const char* text);


bool isBleConnected = false;


#define KEY_RIGHT 0x4F
#define KEY_LEFT 0x50
#define KEY_DOWN 0x51
#define KEY_UP 0x52
#define KEY_MOD_LCTRL 0x01

BLEHIDDevice* hidDevice;
BLEServer* bleServer;
bool deviceConnected = false;
char sequence[11]; // Buffer for the sequence



void DriverTask(void *parameter) {
  // Wireless_Test2();
  while(1){
    PWR_Loop();
    BAT_Get_Volts();
    // PCF85063_Loop();
    // QMI8658_Loop(); 
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void Driver_Loop() {
  xTaskCreatePinnedToCore(
    DriverTask,           
    "DriverTask",         
    4096,                 
    NULL,                 
    3,                    
    NULL,                 
    0                     
  );  
}
void setup()
{
  // Flash_test();
  PWR_Init();
  BAT_Init();
  // I2C_Init();
  // PCF85063_Init();
  // QMI8658_Init();
  Backlight_Init();

  // configure pin for button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // start Bluetooth task
  xTaskCreate(bluetoothTask, "bluetooth", 20000, NULL, 5, NULL);
  
  // SD_Init();
  // Folder_retrieval(stratagems,);
  Audio_Init();
  LCD_Init();
//   LCD_SetRotation(1);
  Lvgl_Init();
  ui_init();

  // Lvgl_Example1();
  // lv_demo_widgets();               
  // lv_demo_benchmark();          
  // lv_demo_keypad_encoder();     
  // lv_demo_music();              
  // lv_demo_printer();
  // lv_demo_stress();   
  Driver_Loop();
}

void loop()
{
  Lvgl_Loop();
  //vTaskDelay(pdMS_TO_TICKS(5));
    // if (bGUISend_Data == true) 
    // {
    //   if ((Status & S5_RC00_BTN) == S5_RC00_BTN)
    //   {

    //     Status &= ~(S5_RC00_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 00 Pressed");
    //     sendKeySequence("URDR");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC01_BTN) == S5_RC01_BTN)
    //   {

    //     Status &= ~(S5_RC01_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 01 Pressed");
    //     sendKeySequence("DLUDR");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC02_BTN) == S5_RC02_BTN)
    //   {

    //     Status &= ~(S5_RC02_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 02 Pressed");
    //     sendKeySequence("RDURD");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC03_BTN) == S5_RC03_BTN)
    //   {

    //     Status &= ~(S5_RC03_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 03 Pressed");
    //     sendKeySequence("DULRLR");
    //     delay(5);
    //   }


    //   if ((Status & S5_RC10_BTN) == S5_RC10_BTN)
    //   {

    //     Status &= ~(S5_RC10_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 10 Pressed");
    //     typeText("Button 10 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC11_BTN) == S5_RC11_BTN)
    //   {

    //     Status &= ~(S5_RC11_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 11 Pressed");
    //     typeText("Button 11 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC12_BTN) == S5_RC12_BTN)
    //   {

    //     Status &= ~(S5_RC12_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 12 Pressed");
    //     typeText("Button 12 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC13_BTN) == S5_RC13_BTN)
    //   {

    //     Status &= ~(S5_RC13_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 13 Pressed");
    //     typeText("Button 13 Pressed \n");
    //     delay(5);
    //   }

    //   if ((Status & S5_RC20_BTN) == S5_RC20_BTN)
    //   {

    //     Status &= ~(S5_RC20_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 20 Pressed");
    //     typeText("Button 20 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC21_BTN) == S5_RC21_BTN)
    //   {

    //     Status &= ~(S5_RC21_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 21 Pressed");
    //     typeText("Button 21 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC22_BTN) == S5_RC22_BTN)
    //   {

    //     Status &= ~(S5_RC22_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 22 Pressed");
    //     typeText("Button 22 Pressed \n");
    //     delay(5);
    //   }
    //   if ((Status & S5_RC23_BTN) == S5_RC23_BTN)
    //   {

    //     Status &= ~(S5_RC23_BTN);
    //     bGUISend_Data = false;
    //     Serial.println("Button 23 Pressed");
    //     typeText("Button 23 Pressed \n");
    //     delay(5);
    //   }
    //}

    // delay(100);
  //delay(5);
}

// void send_message()
// {
//     bSend_Data = true;
// }
// Message (report) sent when a key is pressed or released
struct InputReport {
    uint8_t modifiers;	     // bitmask: CTRL = 1, SHIFT = 2, ALT = 4
    uint8_t reserved;        // must be 0
    uint8_t pressedKeys[6];  // up to six concurrenlty pressed keys
};

// Message (report) received when an LED's state changed
struct OutputReport {
    uint8_t leds;            // bitmask: num lock = 1, caps lock = 2, scroll lock = 4, compose = 8, kana = 16
};


// The report map describes the HID device (a keyboard in this case) and
// the messages (reports in HID terms) sent and received.
static const uint8_t REPORT_MAP[] = {
    USAGE_PAGE(1),      0x01,       // Generic Desktop Controls
    USAGE(1),           0x06,       // Keyboard
    COLLECTION(1),      0x01,       // Application
    REPORT_ID(1),       0x01,       //   Report ID (1)
    USAGE_PAGE(1),      0x07,       //   Keyboard/Keypad
    USAGE_MINIMUM(1),   0xE0,       //   Keyboard Left Control
    USAGE_MAXIMUM(1),   0xE7,       //   Keyboard Right Control
    LOGICAL_MINIMUM(1), 0x00,       //   Each bit is either 0 or 1
    LOGICAL_MAXIMUM(1), 0x01,
    REPORT_COUNT(1),    0x08,       //   8 bits for the modifier keys
    REPORT_SIZE(1),     0x01,       
    HIDINPUT(1),        0x02,       //   Data, Var, Abs
    REPORT_COUNT(1),    0x01,       //   1 byte (unused)
    REPORT_SIZE(1),     0x08,
    HIDINPUT(1),        0x01,       //   Const, Array, Abs
    REPORT_COUNT(1),    0x06,       //   6 bytes (for up to 6 concurrently pressed keys)
    REPORT_SIZE(1),     0x08,
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
    USAGE_MINIMUM(1),   0x00,
    USAGE_MAXIMUM(1),   0x65,
    HIDINPUT(1),        0x00,       //   Data, Array, Abs
    REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
    REPORT_SIZE(1),     0x01,
    USAGE_PAGE(1),      0x08,       //   LEDs
    USAGE_MINIMUM(1),   0x01,       //   Num Lock
    USAGE_MAXIMUM(1),   0x05,       //   Kana
    LOGICAL_MINIMUM(1), 0x00,
    LOGICAL_MAXIMUM(1), 0x01,
    HIDOUTPUT(1),       0x02,       //   Data, Var, Abs
    REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
    REPORT_SIZE(1),     0x03,
    HIDOUTPUT(1),       0x01,       //   Const, Array, Abs
    END_COLLECTION(0)               // End application collection
};


BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;

const InputReport NO_KEY_PRESSED = { };


/*
 * Callbacks related to BLE connection
 */
class BleKeyboardCallbacks : public BLEServerCallbacks {

    void onConnect(BLEServer* server) {
        isBleConnected = true;

        // Allow notifications for characteristics
        BLE2902* cccDesc = (BLE2902*)input->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
        cccDesc->setNotifications(true);

        Serial.println("Client has connected");
    }

    void onDisconnect(BLEServer* server) {
        isBleConnected = false;

        // Disallow notifications for characteristics
        BLE2902* cccDesc = (BLE2902*)input->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
        cccDesc->setNotifications(false);

        Serial.println("Client has disconnected");
    }
};


/*
 * Called when the client (computer, smart phone) wants to turn on or off
 * the LEDs in the keyboard.
 * 
 * bit 0 - NUM LOCK
 * bit 1 - CAPS LOCK
 * bit 2 - SCROLL LOCK
 */
 class OutputCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
        OutputReport* report = (OutputReport*) characteristic->getData();
        Serial.print("LED state: ");
        Serial.print((int) report->leds);
        Serial.println();
    }
};


void bluetoothTask(void*) {

    // initialize the device
    BLEDevice::init(DEVICE_NAME);
    BLEServer* server = BLEDevice::createServer();
    server->setCallbacks(new BleKeyboardCallbacks());

    // create an HID device
    hid = new BLEHIDDevice(server);
    input = hid->inputReport(1); // report ID
    output = hid->outputReport(1); // report ID
    output->setCallbacks(new OutputCallbacks());

    // set manufacturer name
    hid->manufacturer()->setValue("Maker Community");
    // set USB vendor and product ID
    hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
    // information about HID device: device is not localized, device can be connected
    hid->hidInfo(0x00, 0x02);

    // Security: device requires bonding
    BLESecurity* security = new BLESecurity();
    security->setAuthenticationMode(ESP_LE_AUTH_BOND);

    // set report map
    hid->reportMap((uint8_t*)REPORT_MAP, sizeof(REPORT_MAP));
    hid->startServices();

    // set battery level to 100%
    hid->setBatteryLevel(100);

    // advertise the services
    BLEAdvertising* advertising = server->getAdvertising();
    advertising->setAppearance(HID_KEYBOARD);
    advertising->addServiceUUID(hid->hidService()->getUUID());
    advertising->addServiceUUID(hid->deviceInfo()->getUUID());
    advertising->addServiceUUID(hid->batteryService()->getUUID());
    advertising->start();

    Serial.println("BLE ready");
    delay(portMAX_DELAY);
};


void typeText(const char* text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {

        // translate character to key combination
        uint8_t val = (uint8_t)text[i];
        if (val > KEYMAP_SIZE)
            continue; // character not available on keyboard - skip
        KEYMAP map = keymap[val];

        // create input report
        InputReport report = {
            .modifiers = map.modifier,
            .reserved = 0,
            .pressedKeys = {
                map.usage,
                0, 0, 0, 0, 0
            }
        };

        // send the input report
        input->setValue((uint8_t*)&report, sizeof(report));
        input->notify();

        delay(5);

        // release all keys between two characters; otherwise two identical
        // consecutive characters are treated as just one key press
        input->setValue((uint8_t*)&NO_KEY_PRESSED, sizeof(NO_KEY_PRESSED));
        input->notify();

        delay(5);
    }
}
void sendKeySequence(const char* sequence) {
    if (!input || !isBleConnected) return;

    // Step 1: Press and hold CTRL
    InputReport ctrlHeld = {
        .modifiers = KEY_MOD_LCTRL,
        .reserved = 0,
        .pressedKeys = {0, 0, 0, 0, 0, 0}
    };
    input->setValue((uint8_t*)&ctrlHeld, sizeof(ctrlHeld));
    input->notify();
    delay(75);  // Small delay after pressing CTRL

    // Step 2: Press and release arrow keys with CTRL held
    for (int i = 0; sequence[i] != '\0'; i++) {
        uint8_t keycode = 0;

        switch (sequence[i]) {
            case 'U': keycode = KEY_UP; break;
            case 'D': keycode = KEY_DOWN; break;
            case 'L': keycode = KEY_LEFT; break;
            case 'R': keycode = KEY_RIGHT; break;
            default: continue;
        }

        // Press CTRL + Arrow
        InputReport press = {
            .modifiers = KEY_MOD_LCTRL,
            .reserved = 0,
            .pressedKeys = {keycode, 0, 0, 0, 0, 0}
        };
        input->setValue((uint8_t*)&press, sizeof(press));
        input->notify();
        delay(20); // Tiny buffer

        // Release Arrow (keep CTRL held)
        input->setValue((uint8_t*)&ctrlHeld, sizeof(ctrlHeld));
        input->notify();
        delay(20); // Tiny buffer
    }

    // Step 3: Release everything
    input->setValue((uint8_t*)&NO_KEY_PRESSED, sizeof(NO_KEY_PRESSED));
    input->notify();
    delay(75);
}
