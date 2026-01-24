using LabelsApp.Labels;

namespace LabelsApp;

public class LabelPrinter
{
    public static void Print(ILabel label)
        => Console.WriteLine($"Here is a label: {label.GetText()}");

    public static void PrintWithHelpText(HelpLabel label)
    {
        Print(label);
        Console.WriteLine($"Some help information about this label: {label.GetHelpText()}");
    }
}
