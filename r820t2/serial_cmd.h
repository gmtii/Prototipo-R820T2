void R820T2_read(uint8_t addr, uint8_t *data, uint8_t num);
void R820T2_write(uint8_t addr, uint8_t *data, uint8_t num);
uint8_t R820T2_read_reg(uint8_t n);
void R820T2_write_reg(uint8_t n, uint8_t data);
void R820T2_init(void);
int32_t R820T2_calibrate(void);
void R820T2_set_frequency(uint32_t freq);
void R820T2_set_bandwidth(uint8_t bw);
void R820T2_set_lna_gain(uint8_t gain_index);
void R820T2_set_mixer_gain(uint8_t gain_index);
void R820T2_set_vga_gain(uint8_t gain_index);
void R820T2_set_lna_agc(uint8_t value);
void R820T2_set_mixer_agc(uint8_t value);
int r82xx_set_gain(int set_manual_gain, int gain);
int r820t_standby(void);


unsigned int uint1, uint2;
uint32_t uintf;
char cmd[128];
int charsRead;
#include "cat.h"
#include "FT857_cat.h"
void cmd_help() {
  Serial.println(F("help              - show this message"));
  Serial.println(F("scan              - perform I2C scan"));
  Serial.println(F("dump              - read all registers"));
  Serial.println(F("read <reg>        - read given register value)"));
  Serial.println(F("                    (e.g `read 0A`)"));
  Serial.println(F("write <reg> <val> - write <val> to register <reg>)"));
  Serial.println(F("                    (e.g. `write 0A E1`)"));
  Serial.println(F("init              - initialize R820T2"));
  Serial.println(F("calibrate         - calibrate R820T2"));
  Serial.println(F("frequency <val>   - set frequency to <val>"));
  Serial.println(F("                    (e.g. `frequency 144000000`)"));
  Serial.println(F("bandwidth <val>   - Set IF bandwidth [0-15]"));
  Serial.println(F("lna_gain <val>    - Set gain of LNA [0-15]"));
  Serial.println(F("vga_gain <val>    - Set gain of VGA [0-15]"));
  Serial.println(F("mixer_gain <val>  - Set gain Mixer [0-15]"));
  Serial.println(F("lna_agc <val>     - Enable/disable LNA AGC [0-1]"));
  Serial.println(F("mixer_agc <val>   - Enable/disable Mixer AGC [0-1]"));
  Serial.println(F("gain <val>        - Set global gain"));
  Serial.println(F("standby           - Set global gain"));
}

void cmd_dump() {
  uint8_t regs[0x20];
  R820T2_read(0x00, regs, sizeof(regs));
  for (uint8_t i = 0; i < 0x20; i++) {
    Serial.println(regs[i], HEX);
    if ((i & 0x7) == 0x7) {
      Serial.print(F("  "));
    }
    if ((i & 0xF) == 0xF) {
      Serial.println();
    }
  }
}

void cmd_frequency(uint32_t val) {
  if ((val < 24000000) || (val > 1766000000)) {
    Serial.println(F("Out of bound: 24000000-1766000000\r\n"));
    return;
  }
  R820T2_set_frequency(val);
}

void cmd_bandwidth(unsigned int val) {
  if (val > 15) {
    Serial.println(F("Out of bound: 0-15"));
    return;
  }

  R820T2_set_bandwidth(val);
}

void cmd_lna_gain(unsigned int val) {
  if (val > 15) {
    Serial.println(F("Out of bound: 0-15"));
    return;
  }

  R820T2_set_lna_gain(val);
}

void cmd_vga_gain(unsigned int val) {
  if (val > 15) {
    Serial.println(F("Out of bound: 0-15"));
    return;
  }

  R820T2_set_vga_gain(val);
}

void cmd_mixer_gain(unsigned int val) {
  if (val > 15) {
    Serial.println(F("Out of bound: 0-15"));
    return;
  }

  R820T2_set_mixer_gain(val);
}

void cmd_lna_agc(unsigned int val) {
  if (val > 1) {
    Serial.println(F("Out of bound: 0-15"));
    return;
  }

  R820T2_set_lna_agc(val);
}

void cmd_mixer_agc(unsigned int val) {
  if (val > 1) {
    Serial.println(F("Out of bound: 0-1"));
    return;
  }

  R820T2_set_mixer_agc(val);
}

void cmd_init() {
  R820T2_init();
}

void cmd_gain(unsigned int val) {
  r82xx_set_gain(0, val);
}
void cmd_standby() {
  r820t_standby();
}

void Serial_CMD() {


  if (Serial.available() > 0) {
    charsRead = Serial.readBytesUntil('\n', cmd, sizeof(cmd) - 1);
    cmd[charsRead] = '\0';

    if (strcmp(cmd, "") == 0) {
      /* empty command - do nothing */
    } else if (strcmp(cmd, "help\r") == 0) {
      cmd_help();
    } else if (strcmp(cmd, "scan\r") == 0) {
      //cmd_scan();
    } else if (strcmp(cmd, "init\r") == 0) {
      cmd_init();
    } else if (strcmp(cmd, "calibrate\r") == 0) {
      //cmd_calibrate();
    } else if (strcmp(cmd, "dump\r") == 0) {
      cmd_dump();
    } else if (sscanf(cmd, "frequency %" SCNd32, &uintf) == 1) {
      cmd_frequency(uintf);
    } else if (sscanf(cmd, "gain %u", &uintf) == 1) {
      cmd_gain(uintf);
    } else if (strcmp(cmd, "standby\r") == 0) {
      cmd_standby();
    } else if (sscanf(cmd, "bandwidth %u", &uint1) == 1) {
      cmd_bandwidth(uint1);
    } else if (sscanf(cmd, "lna_gain %u", &uint1) == 1) {
      cmd_lna_gain(uint1);
    } else if (sscanf(cmd, "vga_gain %u", &uint1) == 1) {
      cmd_vga_gain(uint1);
    } else if (sscanf(cmd, "mixer_gain %u", &uint1) == 1) {
      cmd_mixer_gain(uint1);
    } else if (sscanf(cmd, "lna_agc %u", &uint1) == 1) {
      cmd_lna_agc(uint1);
    } else if (sscanf(cmd, "mixer_agc %u", &uint1) == 1) {
      cmd_mixer_agc(uint1);
    } else if (sscanf(cmd, "read %02x", &uint1) == 1) {
      //cmd_read((uint8_t)uint1);
    } else if (sscanf(cmd, "write %02x %02x", &uint1, &uint2) == 2) {
      //cmd_write((uint8_t)uint1, (uint8_t)uint2);
    } else {
      Serial.println(F("Unknown command, try `help`"));
    }
  }
}
