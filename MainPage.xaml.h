//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "GrovePiCpp.h"

namespace App1
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		N_GrovePiCpp::GrovePICpp ^My_GrovePi;
		void Click_Ask_For_Config(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_DigitalRead(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_DigitalWrite(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_AnalogRead(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_AnalogWrite(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_PinMode(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Flush(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
