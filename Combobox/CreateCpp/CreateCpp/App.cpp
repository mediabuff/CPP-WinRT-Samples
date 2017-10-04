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
	ComboBox cbBox;
	TextBlock txtStatus;
	StackPanel sPanel;

	IInspectable MakeString(hstring captionText)
	{
		return PropertyValue::CreateString(captionText);
	}

	Thickness CreateThickness(int top,int bottom,int left,int right)
	{
		Thickness margin;
		margin.Bottom = bottom;
		margin.Left = left;
		margin.Right = right;
		margin.Top = top;
		return margin;
	}

	void CbSelectionChanged(IInspectable const & sender,const RoutedEventArgs &args)
	{
		ComboBox cbbox = sender.as<ComboBox>();
		auto itemSelect = cbbox.SelectedItem().as<IPropertyValue>();
		auto selectItem = itemSelect.GetString();
		txtStatus.Text(selectItem);
	}
	void CbSelectionOpend(IInspectable const & sender, const IInspectable &args)
	{
		sPanel.Background(SolidColorBrush(Colors::Yellow()));
	}

	void CbSelectionClosed(IInspectable const & sender, const IInspectable &args)
	{
		sPanel.Background(SolidColorBrush(Colors::White()));
	}
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		
		cbBox.Items().Append(MakeString(L"Windows 7"));
		cbBox.Items().Append(MakeString(L"Windows 8"));
		cbBox.Items().Append(MakeString(L"Windows 10"));
		cbBox.Items().Append(MakeString(L"Windows Mobile 10"));
		cbBox.Items().Append(MakeString(L"Linux"));
		cbBox.Items().Append(MakeString(L"MacOS"));
		cbBox.Margin(CreateThickness(10, 10, 10, 10));
		
		
		cbBox.SelectionChanged({ this,&App::CbSelectionChanged});
		cbBox.SelectedIndex(0);
		cbBox.DropDownOpened({ this,&App::CbSelectionOpend });
		cbBox.DropDownClosed({ this,&App::CbSelectionClosed });
		

		TextBlock txtBlock;
		txtBlock.Text(L"Select the OS :");
		txtBlock.Margin(CreateThickness(10, 10, 10, 0));
		txtStatus.Margin(CreateThickness(10, 10, 10, 10));

		
		sPanel.Margin(CreateThickness(10,10,10,10));
		sPanel.Orientation(Orientation::Horizontal);
		sPanel.Children().Append(txtBlock);
		sPanel.Children().Append(cbBox);
		sPanel.Children().Append(txtStatus);

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