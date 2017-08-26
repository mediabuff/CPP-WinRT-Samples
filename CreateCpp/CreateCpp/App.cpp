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
	static void OnLaunched(LaunchActivatedEventArgs const&);
};

void App::OnLaunched(LaunchActivatedEventArgs const&)
{

	TextBlock txtBlock;
	txtBlock.Text(L"Hello World ( Welcome to UWP/C++ tutorial)");
	txtBlock.TextAlignment(TextAlignment::Center);
	txtBlock.VerticalAlignment(VerticalAlignment::Center);

	Window window = Window::Current();
	window.Content(txtBlock);

	window.Activate();
}

int __stdcall wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}

