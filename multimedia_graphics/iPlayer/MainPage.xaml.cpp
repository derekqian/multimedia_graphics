//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace iPlayer;

using namespace concurrency;
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
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::AccessCache;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	// Make sure we don't run out of entries in StoreItemAccessList.
	// As we don't need to persist this across app sessions/pages, clearing
	// every time is sufficient for this sample
	storageItemAccessList = StorageApplicationPermissions::FutureAccessList;
	storageItemAccessList->Clear();
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	mediaElement->Source = nullptr;
}

void MainPage::OnRightTapped(RightTappedRoutedEventArgs^ e)
{
	// Get file
	auto picker = ref new FileOpenPicker();
	picker->SuggestedStartLocation = PickerLocationId::VideosLibrary;
	picker->FileTypeFilter->Append(".mp4");

	create_task(picker->PickSingleFileAsync()).then([this](StorageFile^ videoFile)
	{
		if (videoFile == nullptr)
		{
			return;
		}

		this->pickedFile = videoFile;

		// These files could be picked from a location that we won't have access to later
		// (especially if persisting the MediaComposition to disk and loading it later). 
		// Use the StorageItemAccessList in order to keep access permissions to that
		// file for later use. Be aware that this access list needs to be cleared
		// periodically or the app will run out of entries.
		storageItemAccessList->Add(this->pickedFile);

		create_task(this->pickedFile->OpenReadAsync()).then([this](IRandomAccessStreamWithContentType^ videoSource)
		{
			mediaElement->SetSource(videoSource, this->pickedFile->ContentType);
			mediaElement->TransportControls->Opacity = 0.5;
		});
	});
}
