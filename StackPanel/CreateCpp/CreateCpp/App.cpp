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
using namespace Windows::Media::Ocr;
using namespace Windows::Storage;

struct App:ApplicationT<App>
{
public:
	virtual ~App() = default;
	static TextBlock CreateTextBlock(hstring);
	static StackPanel CreateStackPanel(hstring, Orientation);
	static void OnLaunched(LaunchActivatedEventArgs const&);	
	static Thickness CreateThickness(int bottom, int left, int right, int top);
};

Thickness App::CreateThickness(int bottom, int left, int right, int top)
{
	Thickness think;
	think.Bottom = bottom;
	think.Left = left;
	think.Right = right;
	think.Top = top;
	return think;
}

TextBlock App::CreateTextBlock(hstring textCaption)
{
	TextBlock text;
	text.Text(textCaption);
	text.TextAlignment(TextAlignment::Center);		
	text.Margin(CreateThickness(10,10,0,10));
	return text;
}

StackPanel App::CreateStackPanel(hstring panelName, Orientation oriPosition)
{
	StackPanel stPanel;
	stPanel.Children().Append(CreateTextBlock(panelName));
	stPanel.Children().Append(CreateTextBlock(L"Panel 1"));
	stPanel.Children().Append(CreateTextBlock(L"Panel 2"));
	stPanel.Children().Append(CreateTextBlock(L"Panel 3"));
	stPanel.Children().Append(CreateTextBlock(L"Panel 4"));
	stPanel.Children().InsertAt(4,CreateTextBlock(L"Panel 5"));
	stPanel.Children().InsertAt(5,CreateTextBlock(L"Panel 6"));
	stPanel.Orientation(oriPosition);
	if(oriPosition==Orientation::Horizontal)
		stPanel.Background(SolidColorBrush(Colors::Red()));
	else
		stPanel.Background(SolidColorBrush(Colors::Blue()));

	return stPanel;
}

void App::OnLaunched(LaunchActivatedEventArgs const&)
{

	auto panel1 = CreateStackPanel(L"StackPanel 1",Orientation::Horizontal);
	auto panel2 = CreateStackPanel(L"StackPanel 2", Orientation::Vertical);
	
	StackPanel panel;
	panel.Children().Append(panel1);
	panel.Children().Append(panel2);
	panel.BorderThickness(CreateThickness(5, 5, 5, 5));
	panel.Background(SolidColorBrush(Colors::Yellow()));
	Window window = Window::Current();
	window.Content(panel);

	window.Activate();
}

int __stdcall wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	Application::Start([](auto &&) {make<App>(); });
	 return 0;
}