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
	virtual ~App() = default;
	StackPanel sPanel;
	
	IInspectable MakeString(hstring captionText)
	{
		return PropertyValue::CreateString(captionText);
	}

	IInspectable MakeTag(int Idx)
	{
		return PropertyValue::CreateInt32(Idx);
	}

	RadioButton CreateRadioBtn(hstring groupName, hstring contentName,int TagIdx)
	{
		RadioButton RButton;
		RButton.GroupName(groupName);
		RButton.Content(MakeString(contentName));
		RButton.Checked({this,&App::RdButtonClick});
		RButton.Tag(MakeTag(TagIdx));

		return RButton;
	}

	hstring GetRbButtonName(IInspectable const& sender)
	{
		RadioButton chkBox = sender.as<RadioButton>();
		IPropertyValue IValue = chkBox.Content().as<IPropertyValue>();
		return IValue.GetString();
	}

	int GetTagIndex(IInspectable const& sender)
	{
		RadioButton chkBox = sender.as<RadioButton>();
		IPropertyValue IValue = chkBox.Tag().as<IPropertyValue>();
		return IValue.GetInt32();
	}

	void RdButtonClick(IInspectable const & sender, const RoutedEventArgs &args)
	{
		auto Idx = GetTagIndex(sender);
		auto chkName = GetRbButtonName(sender);

		switch(Idx)
		{
		case 1:
			sPanel.Background(SolidColorBrush(Colors::Red()));
			break;
		case 2:
			sPanel.Background(SolidColorBrush(Colors::Green()));
			break;
		case 3:
			sPanel.Background(SolidColorBrush(Colors::Blue()));
			break;
		}			
	}

	void OnLaunched(LaunchActivatedEventArgs const&)
	{

		auto RdBtnRed = CreateRadioBtn(L"Color", L"Red",1);
		auto RdBtnGreen = CreateRadioBtn(L"Color", L"Green",2);
		auto RdBtnBlue = CreateRadioBtn(L"Color", L"Blue",3);

		Thickness margin;
		margin.Bottom = 10;
		margin.Left = 10;
		margin.Right = 10;
		margin.Top = 10;

		/*static StackPanel sPanel;*/
		sPanel.Margin(margin);
		sPanel.Children().Append(RdBtnRed);
		sPanel.Children().Append(RdBtnGreen);
		sPanel.Children().Append(RdBtnBlue);

		auto window = Window::Current();
		window.Content(sPanel);

		window.Activate();
	}
};


int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}