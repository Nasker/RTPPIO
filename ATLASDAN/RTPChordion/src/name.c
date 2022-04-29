#include "usb_names.h"

// Edit these lines to create your own name.  The length must
// match the number of characters in your custom name.
#define MANUFACTURER_NAME   {'R','o','c','k','i ','n','T','e','c','h'}
#define MANUFACTURER_NAME_LEN  10
#define MIDI_NAME   {'C','H','O','R','D','I','O','N','_','M','I','D','I'}
#define MIDI_NAME_LEN 13
#define SERIAL_NUM {'C','H','O','R','D','I','O','N','_','M','I','D','I'}
#define SERIAL_NUM_LEN 13

// Do not change this part.  This exact format is required by USB.


struct usb_string_descriptor_struct usb_string_manufacturer_name = {
        2 + MANUFACTURER_NAME_LEN * 2,
        3,
        MANUFACTURER_NAME
};
struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};

struct usb_string_descriptor_struct usb_string_serial_number = {
        2 + SERIAL_NUM_LEN * 2,
        3,
        SERIAL_NUM
};