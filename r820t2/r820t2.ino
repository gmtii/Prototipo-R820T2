/* 
	Prototipo R820T2+QSD con Si5351 
	Basado en drivers
    Copyright (C) 2020 EA8DGL

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
	
	*/


#include <Arduino.h>
#include <Wire.h>

#include "si5351.h"
#include "serial_cmd.h"

const int ledPin = 13;


#define SI5351_XTAL_FREQ  25000000

uint64_t target_freq = 2000000000ULL;
int32_t cal_factor = 10000;


Si5351 si5351;

void setup() {

  byte error;
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.flush();

  delay(2000);

  Wire.begin();

  Wire.beginTransmission(0x1A);
  error = Wire.endTransmission();

  if (error == 0)
  {
    Serial.println("I2C device found at address 0x1A");

    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }

  Wire.beginTransmission(0x60);
  error = Wire.endTransmission();

  if (error == 0)
  {
    Serial.println("I2C device found at address 0x60");

    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
  }

  R820T2_init();

  delay(500);

  // Start on target frequency
  si5351.set_correction(cal_factor, SI5351_PLL_INPUT_XO);
  si5351.set_pll(SI5351_PLL_FIXED, SI5351_PLLA);


  si5351.init(SI5351_CRYSTAL_LOAD_0PF, SI5351_XTAL_FREQ, 0);
  si5351.set_freq(target_freq, SI5351_CLK2);
  si5351.output_enable(SI5351_CLK2, 1);

  si5351.update_status();

  delay(500);

  // I had near 0.7 Vpp CLKIN -> LOS=1 so it need to repeat init sequence.

  si5351.init(SI5351_CRYSTAL_LOAD_0PF, SI5351_XTAL_FREQ, 0);
  si5351.set_freq(target_freq, SI5351_CLK2);
  si5351.output_enable(SI5351_CLK2, 1);
  
  si5351.output_enable(SI5351_CLK0, 0);
  si5351.output_enable(SI5351_CLK1, 0);

  si5351.update_status();

  //tft.fillScreen(TFT_BLACK);
  //tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //tft.setTextFont(3);

}

static void flush_input(void)
{
  while (Serial.available() > 0)
    Serial.read();
}

// ;Loop to check for FT 575 Yaesu compatible CAT commands.

void loop()
{
  // Serial_CMD();  // Uncomment to enable R820T2 console.
  checkCAT(); 

}
