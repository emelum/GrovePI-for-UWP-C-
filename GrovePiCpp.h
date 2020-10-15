#pragma once

namespace N_GrovePiCpp
{
    /// <summary>
    /// Some definitions to help the coding, please, see GrovePI official if you want to explre other posibilities.
    /// </summary>
    const byte Unused = 0;
    const byte GroveVcc = 5;
    const byte AdcVoltage = 5;
    const int GroveRgpLcdMaxLength = 16;
    const int GroveRgpLcdRows = 2;

    typedef int Pin;  //Pin to access the different ports, just use those definitions in you program....
    const int AnalogPin0 = 0;
    const int AnalogPin1 = 1;
    const int AnalogPin2 = 2;
    const int DigitalPin2 = 2;
    const int DigitalPin3 = 3;
    const int DigitalPin4 = 4;
    const int DigitalPin5 = 5;
    const int DigitalPin6 = 6;
    const int DigitalPin7 = 7;
    const int DigitalPin8 = 8;

    typedef int E_PinMode;
    const int Input = 0;   //Pin Mode as Input
    const int Output = 1;  //Pin Mode as OutPut
    
    const byte GrovePiAddress = 0x04;
    static Platform::String^ I2CName = "I2C1"; /* For Raspberry Pi 2, use I2C1 */

    enum Command
    {
        DigitalRead = 1,
        DigitalWrite = 2,
        AnalogRead = 3,
        AnalogWrite = 4,
        PinMode = 5,
        Version = 8,
        //DhtProSensorTemp = 40,
    };
    

    public ref class GrovePICpp sealed  //GrovePI class to interface the board.
    {
    public:
        GrovePICpp(int address);
    
        Platform::String ^ GetFirmwareVersion();
        byte DigitalRead(Pin pin);
        void DigitalWrite(Pin pin, byte value);
        int  AnalogRead(Pin pin);
        void AnalogWrite(Pin pin, byte value);
        void PinMode(Pin pin, E_PinMode mode);
        void Flush();
        void SetDirectAccess(Windows::Devices::I2c::I2cDevice^ device) { DirectAccess = device; };
    internal:
        void Init_I2C_Device(int address);
        Windows::Devices::I2c::I2cDevice ^DirectAccess; // { get; }
    };
}
