
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

struct App :ApplicationT<App>
{
public:
	App()
	{

	}
	virtual ~App() = default;

	TextBlock txtStatus;
	SplitView sView;
	AppBarButton btnHome;


	TextBlock CreateTextBlock(hstring text)
	{
		TextBlock txtBlock;
		txtBlock.Text(text);
		txtBlock.FontSize(15);
		return txtBlock;
	}

	AppBarButton CreateAppBarButton(Symbol icon, hstring text, int Idx)
	{
		AppBarButton appBtn;
		appBtn.Label(text);
		appBtn.Click({ this,&App::OnBtnClick });
		appBtn.Tag(PropertyValue::CreateInt32(Idx));
		appBtn.VerticalAlignment(VerticalAlignment::Top);
		auto sIcon = CreateSymbolIcon(icon);
		appBtn.Icon(sIcon);
		return appBtn;

	}

	void OnBtnClick(IInspectable const &sender, RoutedEventArgs const args)
	{
		if (sView.IsPaneOpen())
		{
			sView.IsPaneOpen(false);
			btnHome.Icon(CreateSymbolIcon(Symbol::Pin));
		}
		else
		{
			sView.IsPaneOpen(true);
			btnHome.Icon(CreateSymbolIcon(Symbol::UnPin));
		}
	}

	SymbolIcon CreateSymbolIcon(Symbol icon)
	{
		SymbolIcon sIcon;
		sIcon.Symbol(icon);
		return sIcon;
	}

	Thickness CreateThickness(int left, int top, int right, int bottom)
	{
		Thickness thick;
		thick.Left = left;
		thick.Top = top;
		thick.Right = right;
		thick.Bottom = bottom;
		return thick;
	}

	StackPanel CreateStackPanel(hstring caption, hstring hamStytle, int Tag)
	{
		StackPanel sPanel;
		sPanel.Orientation(Orientation::Horizontal);
		//sPanel.Margin(CreateThickness(0, 0, 10, 0));  

		auto HamButton = CreateBtnHamburger(caption, hamStytle, Tag);
		sPanel.Children().Append(HamButton);

		Button txtBox;
		IInspectable captionText = PropertyValue::CreateString(caption);
		txtBox.Content(captionText);
		txtBox.Tag(PropertyValue::CreateInt32(Tag));
		txtBox.Click({ this,&App::OnBtnClick });
		txtBox.VerticalAlignment(VerticalAlignment::Center);
		txtBox.Margin(CreateThickness(0, 1, 0, 0));
		txtBox.Width(100);
		txtBox.Height(50);
		sPanel.Children().Append(txtBox);

		return sPanel;
	}

	Button CreateBtnHamburger(hstring caption, hstring hamburgerStytle, int tag)
	{
		Button BtnHamburger;
		IInspectable captionText = PropertyValue::CreateString(hamburgerStytle);
		BtnHamburger.Content(captionText);
		BtnHamburger.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
		BtnHamburger.Click({ this,&App::OnBtnClick });
		BtnHamburger.Width(50);
		BtnHamburger.Height(50);
		BtnHamburger.Margin(CreateThickness(0, 1, 0, 0));
		BtnHamburger.Tag(PropertyValue::CreateInt32(tag));
		return BtnHamburger;
	}

	void OnLaunched(LaunchActivatedEventArgs const&)
	{

		auto txtHeader = CreateTextBlock(L"SplitView Sample");
		txtHeader.HorizontalAlignment(HorizontalAlignment::Center);
		txtHeader.VerticalAlignment(VerticalAlignment::Center);
		txtHeader.FontSize(75);

		auto txtPane = CreateTextBlock(L"Pane area");
		txtPane.HorizontalAlignment(HorizontalAlignment::Center);
		txtPane.VerticalAlignment(VerticalAlignment::Center);
		txtPane.Margin(CreateThickness(20, 0, 0, 0));
		txtPane.FontSize(25);

		txtStatus = CreateTextBlock(L"Modern C++ (SplitView) Content area");
		txtStatus.HorizontalAlignment(HorizontalAlignment::Center);
		txtStatus.VerticalAlignment(VerticalAlignment::Center);
		txtStatus.TextWrapping(TextWrapping::WrapWholeWords);
		txtStatus.FontSize(75);
		txtStatus.Foreground(SolidColorBrush(Colors::Red()));

		auto BtnHamburger = CreateStackPanel(L"Home", L"\uE700", 1);
		auto btnBrigthness = CreateStackPanel(L"Brightness", L"\uE706", 2);
		auto btnWifi = CreateStackPanel(L"Wifi", L"\uE701", 3);
		auto btnbluetooth = CreateStackPanel(L"Bluetooth", L"\uE702", 4);
		auto btnHotSpot = CreateStackPanel(L"Hotspot", L"\uE704", 5);
		auto btnMap = CreateStackPanel(L"Map", L"\uE707", 6);


		StackPanel sPanel;
		sPanel.Children().Append(BtnHamburger);
		sPanel.Children().Append(txtPane);
		sPanel.Children().Append(btnBrigthness);
		sPanel.Children().Append(btnWifi);
		sPanel.Children().Append(btnbluetooth);
		sPanel.Children().Append(btnHotSpot);
		sPanel.Children().Append(btnMap);
		sPanel.Background(SolidColorBrush(Colors::SeaGreen()));


		sView.Pane(sPanel);
		sView.DisplayMode(SplitViewDisplayMode::CompactInline);
		sView.IsPaneOpen(true);
		sView.OpenPaneLength(200);
		sView.CompactPaneLength(50);

		sView.Content(txtStatus);

		Window window = Window::Current();
		window.Content(sView);
		window.Activate();


	}
};



int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}