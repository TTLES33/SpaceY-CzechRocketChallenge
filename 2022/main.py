# https://github.com/dafvid/micropython-bmp280
from bmp280 import *
from machine import Pin, I2C, PWM
import utime
from time import sleep

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
ERROR = -3
sclPin = Pin(1)
sdaPin = Pin(0)
servoPin = PWM(Pin(2))
servoPin.freq(50)
i2c_object = I2C(0,
                 scl=sclPin,
                 sda=sdaPin,
                 freq=1000000)


result = I2C.scan(i2c_object)
print("I2C scan result : ", result)
if result != []:
    print("I2C connection successfull")
else:
    print("No devices found !")

#Nastavení senzoru
bmp280_object = BMP280(i2c_object, addr=0x76, use_case=BMP280_CASE_HANDHELD_DYN)
bmp280_object.power_mode = BMP280_POWER_NORMAL
bmp280_object.oversample = BMP280_OS_HIGH
bmp280_object.temp_os = BMP280_TEMP_OS_8
bmp280_object.press_os = BMP280_TEMP_OS_4
bmp280_object.standby = BMP280_STANDBY_250
bmp280_object.iir = BMP280_IIR_FILTER_2

print("BMP Object created successfully !")
utime.sleep(0.5)
print("\n")



highestAltitude = 0
timesCrossed = 0

while True:
    #výpočet výšky podle atmosferického tlaku
    pressure = bmp280_object.pressure
    temperature_c = bmp280_object.temperature
    altitude = 44330 * (1 - ((pressure / 100) / 1013.25) ** (1 / 5.255))

    #stoupání
    if altitude > highestAltitude:
        print("+", end="")
        highestAltitude = altitude
        timesCrossed = 0
    #klesání s odchylkou 10m
    elif altitude < (highestAltitude - 10):
        timesCrossed += 1
        if timesCrossed > 3:
            print("rozdeleni rakety")

    #log:
    print("p[Pa]:", end=" ")
    print(pressure, end=" ")
    print("t[°C]:", end=" ")
    print(temperature_c, end=" ")
    print("Altitude[m]:", end=" ")
    print(altitude, end=" ")
    print("highighestAltitude (timesCroseed):", end=" ")
    print(highestAltitude, end=" ")
    print("(", end=" ")
    print(timesCrossed, end=" ")
    print(")")
    sleep(0.2)
