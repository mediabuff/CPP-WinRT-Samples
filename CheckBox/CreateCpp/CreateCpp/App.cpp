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
	static IInspectable MakeString(hstring);
	static CheckBox CreateCheckBox(hstring,bool,bool);
	static bool CheckBoxStatus(IInspectable const& sender);
	static void OnLaunched(LaunchActivatedEventArgs const&);
	static void ChkBoxCheckedClick(IInspectable const & sender, const RoutedEventArgs &args);
	static void ChkBoxUnCheckedClick(IInspectable const & sender, const RoutedEventArgs &args);
	static void ChkBoxIndeterminateClick(IInspectable const & sender, const RoutedEventArgs &args);
	static hstring GetChkBoxName(IInspectable const& sender);
};

IInspectable App::MakeString(hstring captionText)
{
	return PropertyValue::CreateString(captionText);
}

CheckBox App::CreateCheckBox(hstring captionText,bool threeState,bool isChecked)
{
	CheckBox chkBox;
	chkBox.Content(MakeString(captionText));
	chkBox.IsThreeState(threeState);
	chkBox.IsChecked(isChecked);
	chkBox.Checked(&ChkBoxCheckedClick);
	chkBox.Unchecked(&ChkBoxUnCheckedClick);
	chkBox.Indeterminate(&ChkBoxIndeterminateClick);
	return chkBox;
}

bool App::CheckBoxStatus(IInspectable const& sender)
{
	CheckBox chkBox = sender.as<CheckBox>();
	IReference<bool> value = chkBox.IsChecked();
	auto isSeleted = value.Value();
	return isSeleted;
}

void App::ChkBoxUnCheckedClick(IInspectable const & sender, const RoutedEventArgs &args)
{
	auto ChkStatus = CheckBoxStatus(sender);
	auto chkName = GetChkBoxName(sender);
	MessageDialog msgDlg(L"UnChecked State (false)", chkName);
	msgDlg.ShowAsync();
}

void App::ChkBoxIndeterminateClick(IInspectable const & sender, const RoutedEventArgs &args)
{
	CheckBox chkBox = sender.as<CheckBox>();
	auto value = chkBox.IsThreeState();
	if(value)
	{
		auto chkName = GetChkBoxName(sender);
		MessageDialog msgDlg(L"Indeterminate State", chkName);
		msgDlg.ShowAsync();
	}	
}

hstring App::GetChkBoxName(IInspectable const& sender)
{
	CheckBox chkBox = sender.as<CheckBox>();
	IPropertyValue IValue = chkBox.Content().as<IPropertyValue>();
	return IValue.GetString();
}

void App::ChkBoxCheckedClick(IInspectable const & sender, const RoutedEventArgs &args)
{
	auto ChkStatus = CheckBoxStatus(sender);
	auto chkName = GetChkBoxName(sender);
	MessageDialog msgDlg(L"Checked State (True)", chkName);
	msgDlg.ShowAsync();
}


void App::OnLaunched(LaunchActivatedEventArgs const&)
{

	auto chkBox1 = CreateCheckBox(L"C++",false,false);
	auto chkBox2 = CreateCheckBox(L"C#", true,false);
	auto chkBox3 = CreateCheckBox(L"VB", true, true);
	
	Thickness margin;
	margin.Bottom = 0;
	margin.Left = 20;
	margin.Right = 0;
	margin.Top = 5;

	StackPanel sPanel;
	sPanel.Margin(margin);
	sPanel.Children().Append(chkBox1);
	sPanel.Children().Append(chkBox2);
	sPanel.Children().Append(chkBox3);

	Window window = Window::Current();
	window.Content(sPanel);

	window.Activate();
}


int __stdcall wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}

