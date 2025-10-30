
#include <stdint.h>

typedef struct {
    uint8_t direction;
    uint8_t peripheral_adr;
    uint8_t type;
    uint8_t payload[];
} p1p2_packet_t;

enum direction {
    DIR_REQUEST = 0x00,
    DIR_RESPONSE = 0x40,
    DIR_INIT = 0x80
};


/* Packet Type 0x10 (OPERATING_STATUS) */
typedef struct {
    uint8_t power; //0
    uint8_t target_operating_mode; //1
    uint8_t actual_operating_mode; //2
    uint8_t target_temperature; //3
    uint8_t unknown4; //4
    uint8_t fan_speed; //5
    uint8_t unknown6; //6
    uint8_t unknown7; //7
    uint8_t unknown8; //8
    uint8_t unknown9; //9
    uint8_t unknown10; //10
    uint8_t unknown11; //11
    uint8_t unknown12; //12
    uint8_t compressor_state; //13
    uint8_t unknown14; //14
    uint8_t unknown15; //15
    uint8_t unknown16; //16
    uint8_t unknown17; //17
    uint8_t unknown18; //18
    uint8_t unknown19; //19
} p1p2_OperatingStatus_t;

enum TargetOperatingMode {
    FAN = 0x60,
    HEAT = 0x61,
    COOL = 0x62,
    AUTO = 0x63,
    DRY = 0x67,
};

// enum ActualOperatingMode {
//     FAN = 0x00,
//     HEAT = 0x01,
//     COOL = 0x02,
// };

// enum FanSpeed {
//     FAN = 0x00,
//     HEAT = 0x01,
//     COOL = 0x02,
// };


/* Packet Type 0x11 (TEMPERATURES) */
typedef struct {
    uint8_t unknown0; //0
    uint8_t unknown1; //1
    uint8_t unknown2; //2
    uint8_t unknown3; //3
    uint8_t unknown4; //4
    int8_t temp_int; //5
    int8_t temp_fraction; //6
    uint8_t unknown7; //7
    uint8_t unknown8; //8
    uint8_t unknown9; //9
} p1p2_Temperatures_t;

/* Packet Type 0x30 (POLL_AUX_CONTROLLER) */
typedef struct {
    uint8_t unknown0; //0
    uint8_t unknown1; //1
    uint8_t unknown2; //2
    uint8_t unknown3; //3
    uint8_t unknown4; //4
    uint8_t unknown5; //5
    uint8_t unknown6; //6
    uint8_t unknown7; //7
    uint8_t unknown8; //8
    uint8_t unknown9; //9
    uint8_t unknown10; //10
    uint8_t unknown11; //11
    uint8_t unknown12; //12
    uint8_t unknown13; //13
    uint8_t unknown14; //14
    uint8_t unknown15; //15
    uint8_t unknown16; //16
    uint8_t unknown17; //17
    uint8_t unknown18; //18
    uint8_t unknown19; //19
} p1p2_PollAuxController_t;


/* Packet Type 0x38 (OPERATION CONTROL) */
typedef struct {
    uint8_t unknown0; //0
    uint8_t unknown1; //1
    uint8_t unknown2; //2
    uint8_t unknown3; //3
    uint8_t unknown4; //4
    uint8_t unknown5; //5
    uint8_t unknown6; //6
    uint8_t unknown7; //7
    uint8_t unknown8; //8
    uint8_t unknown9; //9
    uint8_t unknown10; //10
    uint8_t unknown11; //11
    uint8_t unknown12; //12
    uint8_t unknown13; //13
    uint8_t unknown14; //14
    uint8_t unknown15; //15
} p1p2_OperatingControl_t;

/* Packet Type 0xA1 (PRODUCT IDENTIFIER) */
typedef struct {
    uint8_t product_id[16];  // ASCII product identifier string
} p1p2_ProductIdentifier_t;

/* Packet Type 0xA3 (THERMISTOR DIAGNOSTICS) - 6 temperature sensors */
typedef struct {
    uint8_t th1_msb;      // Th1 high byte (signed)
    uint8_t th1_lsb;      // Th1 low byte (1/256°C resolution)
    uint8_t th2_msb;      // Th2 high byte
    uint8_t th2_lsb;      // Th2 low byte
    uint8_t th3_msb;      // Th3 high byte
    uint8_t th3_lsb;      // Th3 low byte
    uint8_t th4_msb;      // Th4 high byte
    uint8_t th4_lsb;      // Th4 low byte
    uint8_t th5_msb;      // Th5 high byte
    uint8_t th5_lsb;      // Th5 low byte
    uint8_t th6_msb;      // Th6 high byte
    uint8_t th6_lsb;      // Th6 low byte
} p1p2_Thermistors_t;

/* Packet Type 0xB1 (PRODUCT INFO / MAJOR VERSION) */
typedef struct {
    uint8_t major_version;  // F-series major version (A, B, C, L, LA, M, P, PA)
    uint8_t minor_version;
    uint8_t reserved[18];
} p1p2_ProductInfo_t;

/* Packet Type 0xB8 (ENERGY COUNTERS) */
typedef struct {
    uint8_t energy_produced_lsb;      // Energy produced (heating) - byte 0
    uint8_t energy_produced_byte1;    // byte 1
    uint8_t energy_produced_byte2;    // byte 2
    uint8_t energy_produced_msb;      // Energy produced (heating) - byte 3 (u32 little-endian, in 0.1 kWh units)
    uint8_t electricity_consumed_lsb; // Electricity consumed - byte 0
    uint8_t electricity_consumed_byte1; // byte 1
    uint8_t electricity_consumed_byte2; // byte 2
    uint8_t electricity_consumed_msb; // Electricity consumed - byte 3 (u32 little-endian, in 0.1 kWh units)
    uint8_t runtime_hours_lsb;        // System runtime hours - byte 0
    uint8_t runtime_hours_byte1;      // byte 1
    uint8_t runtime_hours_byte2;      // byte 2
    uint8_t runtime_hours_msb;        // System runtime hours - byte 3 (u32 little-endian)
    uint8_t compressor_runtime_lsb;   // Compressor runtime hours - byte 0
    uint8_t compressor_runtime_byte1; // byte 1
    uint8_t compressor_runtime_byte2; // byte 2
    uint8_t compressor_runtime_msb;   // Compressor runtime hours - byte 3 (u32 little-endian)
} p1p2_EnergyCounters_t;

/* Packet Type 0x39/0x3C (FILTER STATUS) */
/* 0x39 used by FDY/L-series, 0x3C used by FDYQ/M-series - same layout */
typedef struct {
    uint8_t unknown0[8];       // Unknown data - bytes 0-7
    uint8_t filter_hours_lsb;  // Filter counter/hours - byte 8 (LSB)
    uint8_t filter_hours_msb;  // Filter counter/hours - byte 9 (MSB) - u16 little-endian
    uint8_t alarm_flags;       // Alarm flags - byte 10 (bit 0: filter alarm)
    // ... rest of packet unknown
} p1p2_FilterStatus_t;

/* Helper function declarations */
static inline int16_t p1p2_f8_8_to_int16(uint8_t msb, uint8_t lsb) {
    return (int16_t)((int8_t)msb << 8) | lsb;
}

static inline float p1p2_f8_8_to_float(uint8_t msb, uint8_t lsb) {
    int16_t raw = p1p2_f8_8_to_int16(msb, lsb);
    return (float)raw / 256.0f;
}

static inline uint32_t p1p2_u32_le(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    return (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
}

void p1p2_parse_packet(const unsigned int *buffer, unsigned int buffer_length);
