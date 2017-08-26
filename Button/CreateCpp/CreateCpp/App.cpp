#include "pch.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Popups;
using namespace Windows::Storage;

struct App:ApplicationT<App>
{
public:
	virtual ~App() = default;
	static void OnLaunched(LaunchActivatedEventArgs const&);
	static void BtnClick(IInspectable const & sender, const RoutedEventArgs &args);
};

void App::OnLaunched(LaunchActivatedEventArgs const&)
{

	Button BtnClick;
	IInspectable captionText = PropertyValue::CreateString(L"Click Me");
	BtnClick.Content(captionText);

	//To change background and Foreground of the color
	BtnClick.Background(SolidColorBrush(Colors::Red()));
	BtnClick.Foreground(SolidColorBrush((Colors::Yellow())));
	
	BtnClick.Click(&App::BtnClick);
	

	Window window = Window::Current();
	window.Content(BtnClick);

	window.Activate();
}

void App::BtnClick(IInspectable const & sender,const RoutedEventArgs &args)
{
	
	MessageDialog msgDlg(L"Button Click Event",L"C++/UWP");
	msgDlg.ShowAsync();
}

int __stdcall wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}

