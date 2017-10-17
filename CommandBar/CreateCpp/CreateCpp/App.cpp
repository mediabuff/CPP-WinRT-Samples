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

	TextBlock CreateTextBlock(hstring text)
	{
		TextBlock txtBlock;
		txtBlock.Text(text);
		txtBlock.TextAlignment(TextAlignment::Left);
		txtBlock.FontSize(15);
		return txtBlock;
	}

	AppBarButton CreateAppBarButton(Symbol icon, hstring text, int Idx)
	{
		AppBarButton appBtn;
		appBtn.Label(text);
		appBtn.Click({ this,&App::OnBtnClick });
		appBtn.Tag(PropertyValue::CreateInt32(Idx));
		auto sIcon = CreateSymbolIcon(icon);
		appBtn.Icon(sIcon);
		return appBtn;

	}

	void OnBtnClick(IInspectable const &sender, RoutedEventArgs const args)
	{
		Button btn = sender.as<Button>();
		IPropertyValue tagId = btn.Tag().as<IPropertyValue>();
		if (tagId.GetInt32() == 1)
		{
			txtStatus.Text(L"Primary Button has clicked");
		}
		else if (tagId.GetInt32() == 2)
		{
			txtStatus.Text(L"Secondary Button has clicked");
		}
	}

	SymbolIcon CreateSymbolIcon(Symbol icon)
	{
		SymbolIcon sIcon;
		sIcon.Symbol(icon);
		return sIcon;
	}

	void OnLaunched(LaunchActivatedEventArgs const&)
	{

		auto appBtnPlay = CreateAppBarButton(Symbol::Play, L"Play", 1);
		auto appBtnAccept = CreateAppBarButton(Symbol::Accept, L"Accept", 2);

		CommandBar cmdBar;
		cmdBar.PrimaryCommands().Append(appBtnPlay);
		cmdBar.SecondaryCommands().Append(appBtnAccept);

		auto txtHeader = CreateTextBlock(L"CommandBar content Area , Add custom controls here");
		txtHeader.FontSize(25);

		StackPanel sPanel;
		sPanel.Children().Append(txtHeader);
		sPanel.Children().Append(txtStatus);

		cmdBar.Content(sPanel);

		cmdBar.Background(SolidColorBrush(Colors::BurlyWood()));

		cmdBar.IsSticky(true);
		cmdBar.IsOpen(true);

		//cmdBar.ClosedDisplayMode(AppBarClosedDisplayMode::Minimal);  

		Window window = Window::Current();
		window.Content(cmdBar);
		window.Activate();


	}
};



int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}