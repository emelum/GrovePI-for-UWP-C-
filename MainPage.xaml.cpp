//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "GrovePiCpp.h"

using namespace App1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace N_GrovePiCpp;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	
	//Inititate the GrovePi class controller....

	My_GrovePi = ref new GrovePICpp(GrovePiAddress);

}



void MainPage::Click_Ask_For_Config(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}
		
	Answer->Text=My_GrovePi->GetFirmwareVersion();  // ask for the verssiona and Write the answer to the answer textbox
}

void MainPage::Click_DigitalRead(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	int Temp_Pin_to_Operate = std::wcstol(Pin_to_Operate->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	int response = My_GrovePi->DigitalRead(Temp_Pin_to_Operate); //Read the Pin from GrovePI

	Answer->Text = response.ToString();  //  Write the answer to the answer textbox
}

void MainPage::Click_DigitalWrite(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	int Temp_Pin_to_Operate = std::wcstol(Pin_to_Operate->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	byte Temp_Second_Parameter = (byte) std::wcstol(Second_Param->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	My_GrovePi->DigitalWrite(Temp_Pin_to_Operate, Temp_Second_Parameter); //Write the Pin from GrovePI

	Answer->Text = "Done!";  //Write the answer to the answer textbox
}

void MainPage::Click_AnalogRead(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	int Temp_Pin_to_Operate = std::wcstol(Pin_to_Operate->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	int response = My_GrovePi->AnalogRead(Temp_Pin_to_Operate); //Read the Pin from GrovePI

	Answer->Text = response.ToString();  //  Write the answer to the answer textbox
}

void MainPage::Click_AnalogWrite(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	int Temp_Pin_to_Operate = std::wcstol(Pin_to_Operate->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	byte Temp_Second_Parameter = (byte)std::wcstol(Second_Param->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	My_GrovePi->AnalogWrite(Temp_Pin_to_Operate, Temp_Second_Parameter); //Write the Pin from GrovePI

	Answer->Text = "AnalogWrite-Done!";  //Write the answer to the answer textbox
}

void MainPage::Click_PinMode(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	int Temp_Pin_to_Operate = std::wcstol(Pin_to_Operate->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	int Temp_Second_Parameter = (int)std::wcstol(Second_Param->Text->Data(), nullptr, 10);  //Read the data from the user input, this is not part of the GrovePI read process

	My_GrovePi->PinMode(Temp_Pin_to_Operate, Temp_Second_Parameter); //Change the Pin mode in GrovePI

	Answer->Text = "PinMode-Done!";  //Write the answer to the answer textbox
}

void MainPage::Click_Flush(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!My_GrovePi->DirectAccess)   // DirectAccess tell us if the GrovePi was allready and properly inititate...
	{
		Answer->Text = "Not Inititate properly, please wait or check";
		return;
	}

	My_GrovePi->Flush(); //Flush the GrovePI

	Answer->Text = "Flushed-Done!";  //Write the answer to the answer textbox
}