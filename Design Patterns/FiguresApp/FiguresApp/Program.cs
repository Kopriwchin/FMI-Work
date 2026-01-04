namespace FiguresApp;

public class Program
{
    public static void Main()
        => RunFigureCreation();

    enum ConsoleInputChoice
    {
        Random = 1,
        STDIN = 2,
        File = 3
    }

    private readonly static string NEW_LINE = Environment.NewLine;

    private static void RunFigureCreation()
    {
        Console.WriteLine($"Choose input:{NEW_LINE}" +
            $"{(int)ConsoleInputChoice.Random}={ConsoleInputChoice.Random}{NEW_LINE}" +
            $"{(int)ConsoleInputChoice.STDIN}={ConsoleInputChoice.STDIN}{NEW_LINE}" +
            $"{(int)ConsoleInputChoice.File}={ConsoleInputChoice.File}{NEW_LINE}");

        string? inputChoice = Console.ReadLine();
        if (!int.TryParse(inputChoice, out int inputChoiceInteger))
        {
            Console.WriteLine("Invalid choice.");
            return;
        }

        IFigureFactory? factory = ChooseFigureFactory(inputChoiceInteger);
        if (factory is null)
            return;

        Console.WriteLine("Loading figures... (Type 'exit' to stop if using STDIN)");

        List<Figure> figures = [];

        if (factory is RandomFigureFactory)
        {
            const int RANDOM_MAX_VALUE = 10;
            for (int i = 0; i < RANDOM_MAX_VALUE; i++)
            {
                Figure? fig = factory.Create();
                if (fig == null)
                    break;

                figures.Add(fig);
            }
        }
        else if (factory is StreamFigureFactory)
        {
            bool hasStdinBeenChosen = inputChoiceInteger == (int)ConsoleInputChoice.STDIN;

            Figure? figure;
            while ( (figure = factory.Create()) is not null)
            {
                figures.Add(figure);
                if (hasStdinBeenChosen)
                    Console.WriteLine("Successfully added figure!");
            }
        }

        Console.WriteLine($"{figures.Count} figures loaded.");

        RunUserFiguresCLI(figures);
    }

    private static IFigureFactory? ChooseFigureFactory(int inputChoice)
    {
        switch (inputChoice)
        {
            case (int)ConsoleInputChoice.Random:
                return new RandomFigureFactory();
            case (int)ConsoleInputChoice.STDIN:
                return new StreamFigureFactory(Console.In);
            case (int)ConsoleInputChoice.File:
                Console.Write("Enter filename: ");
                string path = Console.ReadLine() ?? "figures.txt";
                if (File.Exists(path))
                {
                    return new StreamFigureFactory(new StreamReader(path));
                }
                else
                {
                    Console.WriteLine("File not found.");
                    return null;
                }
            default:
                Console.WriteLine("Invalid choice.");
                return null;
        }
    }

    private static void RunUserFiguresCLI(List<Figure> figures)
    {
        bool running = true;
        while (running)
        {
            Console.WriteLine($"{NEW_LINE}Menu: [L]ist, [D]elete, [C]lone, [S]ave, [E]xit");
            string? cmd = Console.ReadLine()?.ToUpper();

            switch (cmd)
            {
                case "L": // List to STDOUT
                    for (int i = 0; i < figures.Count; i++)
                        Console.WriteLine($"{i}: {figures[i]} (Perimeter: {figures[i].CalculatePerimeter():F2})");
                    break;

                case "D": // Delete
                    Console.Write("Index to delete: ");
                    if (int.TryParse(Console.ReadLine(), out int delIdx) && delIdx >= 0 && delIdx < figures.Count)
                    {
                        figures.RemoveAt(delIdx);
                        Console.WriteLine("Deleted.");
                    }
                    break;

                case "C": // Duplicate (Prototype Pattern)
                    Console.Write("Index to clone: ");
                    if (int.TryParse(Console.ReadLine(), out int cloneIdx) && cloneIdx >= 0 && cloneIdx < figures.Count)
                    {
                        // Requirement: Copy should be added to the end of the list
                        Figure clone = (Figure)figures[cloneIdx].DeepClone();
                        figures.Add(clone);
                        Console.WriteLine("Cloned.");
                    }
                    break;

                case "S": // Store to file
                    Console.Write("Save filename (will be saved as .txt): ");
                    string? savePath = Console.ReadLine();
                    if (!string.IsNullOrWhiteSpace(savePath))
                    {
                        using StreamWriter writer = new($"{savePath}.txt");
                        foreach (Figure figure in figures)
                            writer.WriteLine(figure.ToString());
                        Console.WriteLine("Saved.");
                    }
                    break;

                case "E":
                    running = false;
                    break;

                default:
                    Console.WriteLine("Invalid command!");
                    break;
            }
        }
    }
}
