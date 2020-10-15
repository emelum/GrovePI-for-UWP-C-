#include "pch.h"
#include "GrovePiCpp.h"

using namespace Concurrency;
using namespace Windows::Devices::I2c;
using namespace Platform;
using namespace Windows::Devices::Enumeration;

namespace N_GrovePiCpp
{

    GrovePICpp::GrovePICpp(int address)  //Inititate the object
    {
        DirectAccess = nullptr;
        Init_I2C_Device(N_GrovePiCpp::GrovePiAddress);
    }

    void GrovePICpp::Init_I2C_Device(int address)
    {

        if (DirectAccess != nullptr) //Check if correctly inititalized
            return;

        /* Initialize the I2C bus */
        I2cConnectionSettings^ settings = ref new I2cConnectionSettings(address);

        if (settings)
            settings->BusSpeed = I2cBusSpeed::StandardMode;
        else {
            DirectAccess = nullptr;
            return;
        }

        ///Get Device Info.......

        //Find the selector string for the I2C bus controller
        String^ aqs = I2cDevice::GetDeviceSelector(N_GrovePiCpp::I2CName);

        //Find the I2C bus controller device with our selector string
        auto my_tarea = create_task(DeviceInformation::FindAllAsync(aqs));

        my_tarea.then([this, settings](DeviceInformationCollection^ dis) {

            // Create an I2cDevice with our selected bus controller and I2C settings   

            GrovePICpp^ my_object = this;

            auto my_tarea2 = create_task(Windows::Devices::I2c::I2cDevice::FromIdAsync(dis->GetAt(0)->Id, settings));

            my_tarea2.then([my_object](Windows::Devices::I2c::I2cDevice^ device) {
                my_object->SetDirectAccess(device);
                return;
                });
            });
    }



    String^ GrovePICpp::GetFirmwareVersion()   //Returns the firmaware verssion of the GrovePi
    {

        if (DirectAccess == nullptr) //Check if correctly inititalized
            return "";

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::Version, Unused, Unused, Unused };
        auto i2cTransferResult = DirectAccess->WritePartial(wbuffer);

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return "0.0.0";
        }

        Platform::Array <unsigned char>^ rbuffer = { 0,0,0,0 };
        i2cTransferResult = DirectAccess->ReadPartial(rbuffer);

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return "0.0.0";
        }
        return rbuffer[1] + "." + rbuffer[2] + "." + rbuffer[3];
    }

    byte GrovePICpp::DigitalRead(Pin pin)
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return 0;

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::DigitalRead, (byte)pin, Unused, Unused };

        auto i2cTransferResult = DirectAccess->WritePartial(wbuffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return 0;
        }

        Platform::Array <unsigned char>^ rbuffer = { 0 };

        i2cTransferResult = DirectAccess->ReadPartial(rbuffer);

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return 0;
        }

        return rbuffer[0];
    }

    void GrovePICpp::DigitalWrite(Pin pin, byte value)
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return;

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::DigitalWrite, (byte)pin, value, Unused };
        DirectAccess->WritePartial(wbuffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    int GrovePICpp::AnalogRead(Pin pin)
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return 0;

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::AnalogRead, (byte)pin, Unused, Unused };
        Platform::Array <unsigned char>^ rbuffer = { 0,0,0 };

        auto i2cTransferResult = DirectAccess->WritePartial(wbuffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return 0;
        }

        i2cTransferResult = DirectAccess->ReadPartial(rbuffer);

        if (i2cTransferResult.Status != I2cTransferStatus::FullTransfer)
        {
            return 0;
        }

        return rbuffer[1] * 256 + rbuffer[2];
    }

    void GrovePICpp::AnalogWrite(Pin pin, byte value)
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return;

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::AnalogWrite, (byte)pin, value, Unused };
        DirectAccess->WritePartial(wbuffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    void GrovePICpp::PinMode(Pin pin, E_PinMode mode)
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return;

        Platform::Array <unsigned char>^ wbuffer = { (byte)Command::PinMode, (byte)pin, (byte)mode, Unused };
        DirectAccess->WritePartial(wbuffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    void GrovePICpp::Flush()
    {
        if (DirectAccess == nullptr) //Check if correctly inititalized
            return;

        Platform::Array <unsigned char>^ wbuffer = { Unused, Unused, Unused, Unused };
        DirectAccess->WritePartial(wbuffer);
    }


}
