/*
  xsns_78_ezoph.ino - EZO EC I2C EC sensor support for Tasmota

  Copyright (C) 2020  Christopher Tremblay

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef USE_I2C
#ifdef USE_EZOEC

#define EZO_EC_READ_LATENCY   600

struct EZOEC : public EZOStruct {
  EZOEC(uint32_t addr) : EZOStruct(addr), EC(NAN) {}

  virtual void ProcessMeasurement(void)
  {
    char data[D_EZO_MAX_BUF];

    EZOStruct::ProcessMeasurement(data, sizeof(data), EZO_EC_READ_LATENCY);
    EC = CharToFloat(data);
  }

  virtual void Show(bool json, const char *name)
  {
    char str[6];
    dtostrfd(EC, 2, str);

    if (json) {
      ResponseAppend_P(PSTR(",\"%s\":{\"" D_JSON_EC "\":%s}" ), name, str);
    }
#ifdef USE_WEBSERVER  
    else {
      WSContentSend_PD(HTTP_SNS_EC, name, str);
#endif  // USE_WEBSERVER
    }
  }

private:
  float     EC;
};

#endif  // USE_EZOEC
#endif  // USE_I2C
