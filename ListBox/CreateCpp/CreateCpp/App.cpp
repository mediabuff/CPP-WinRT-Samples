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
	ListBox lstBox;
	TextBlock txtStatus;

	static IInspectable MakeString(hstring captionText)
	{
		return PropertyValue::CreateString(captionText);
	}

	static Thickness CreateThickness(int top, int bottom, int left, int right)
	{
		Thickness margin;
		margin.Bottom = bottom;
		margin.Left = left;
		margin.Right = right;
		margin.Top = top;
		return margin;
	}

	static TextBlock CreateTextBlock(hstring textCaption)
	{
		TextBlock text;
		text.Text(textCaption);
		text.TextAlignment(TextAlignment::Left);
		text.Margin(CreateThickness(10, 10, 0, 10));
		text.FontSize(30.0);
		return text;
	}

	void App::lstBoxSelectionChange(IInspectable const& sender, const SelectionChangedEventArgs& args) const
	{
		ListBox lstSelect = sender.as<ListBox>();
		auto temp = lstSelect.SelectedItems();
		auto count = temp.Size();

		std::wstring tempString;

		if(count > 0)
			tempString = L" User has Clicked : ";

		for (IInspectable& item : temp)
		{
			IPropertyValue eachItem = item.as<IPropertyValue>();
			tempString = tempString + L"   "  + eachItem.GetString().c_str();
		}

		auto item = PropertyValue::CreateString(tempString);
		IPropertyValue eachItem = item.as<IPropertyValue>();
		hstring selectItem = eachItem.GetString();
		txtStatus.Text(selectItem);
		
	}


	void OnLaunched(LaunchActivatedEventArgs const&)
	{
	
		lstBox.Items().Append(MakeString(L"C++/WinRT"));
		lstBox.Items().Append(MakeString(L"C#"));
		lstBox.Items().Append(MakeString(L"VB.NET"));
		lstBox.SelectionMode(SelectionMode::Multiple);
				
		lstBox.SelectionChanged({ this, &App::lstBoxSelectionChange });

		
		StackPanel panelList;
		panelList.Children().Append(lstBox);
		
		auto txtHeader = CreateTextBlock(L"Select the Language");
		txtStatus = CreateTextBlock(L"");
	
		StackPanel sPanel;
		sPanel.Children().Append(txtHeader);
		sPanel.Children().Append(panelList);
		sPanel.Children().Append(txtStatus);


		Window window = Window::Current();
		window.Content(sPanel);

		window.Activate();
	}
};



int __stdcall wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	Application::Start([](auto &&) {make<App>(); });
	return 0;
}

