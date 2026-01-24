using LabelsApp.Decorators;
using LabelsApp.Labels;
using LabelsApp.Transformations;
using LabelsApp.Utils;

namespace LabelsApp;

public class LabelProvider
{
    public ILabel CreateLabel()
    {
        Console.WriteLine("\n--- Interactive Label Creator ---");

        ILabel label = CreateBaseLabel();

        while (true)
        {
            Console.Write("Add a transformation? (y/n): ");
            if (Console.ReadLine()?.ToLower() != "y") break;

            ITextTransformation transformation = CreateTransformation();
            label = new TextTransformationDecorator(label, transformation);
        }

        Console.Write("Add Help Text? (y/n): ");
        if (Console.ReadLine()?.ToLower() == "y")
        {
            Console.Write("Enter Help Text: ");
            string help = Console.ReadLine() ?? "";
            label = new HelpLabel(label, help);
        }

        return label;
    }

    private ILabel CreateBaseLabel()
    {
        Console.WriteLine("Choose Base Label Type:");
        Console.WriteLine("1. Simple");
        Console.WriteLine("2. Rich");
        Console.WriteLine("3. Custom (Proxy)");
        Console.Write("Selection: ");
        string choice = Console.ReadLine() ?? "1";

        switch (choice)
        {
            case "2":
                Console.Write("Text: ");
                string t = Console.ReadLine() ?? "";
                return new RichLabel(t, PresetColor.Blue, 12, "Arial");
            case "3":
                return new CustomLabel(3);
            case "1":
            default:
                Console.Write("Text: ");
                return new SimpleLabel(Console.ReadLine() ?? "");
        }
    }

    private ITextTransformation CreateTransformation()
    {
        Console.WriteLine("Choose Transformation:");
        Console.WriteLine("1. Capitalize");
        Console.WriteLine("2. Censor");
        Console.WriteLine("3. Decorate");
        Console.WriteLine("4. Replace");
        Console.Write("Selection: ");
        string choice = Console.ReadLine() ?? "3";

        return choice switch
        {
            "1" => new CapitalizeTransformation(),
            "2" => new CensorTransformation(Prompt("Word to censor: ")),
            "4" => new ReplaceTransformation(Prompt("Replace what: "), Prompt("With what: ")),
            _ => new DecorateTransformation()
        };
    }

    private string Prompt(string text)
    {
        Console.Write(text);
        return Console.ReadLine() ?? "";
    }
}