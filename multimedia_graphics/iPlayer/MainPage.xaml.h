//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace iPlayer
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnRightTapped(Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e) override;

	private:
		Windows::Storage::AccessCache::StorageItemAccessList^ storageItemAccessList;
		Windows::Storage::StorageFile^ pickedFile;
	};
}
