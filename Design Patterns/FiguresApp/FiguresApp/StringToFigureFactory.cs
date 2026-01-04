namespace FiguresApp;

public class StringToFigureFactory
{
    private static readonly Dictionary<string, Func<string[], Figure>> _registry
        = new()
    {
        { "triangle",  p => new Triangle(p) },
        { "circle",    p => new Circle(p) },
        { "rectangle", p => new Rectangle(p) }
    };

    public static void Register(string type, Func<string[], Figure> creator)
        => _registry[type.ToLowerInvariant()] = creator;

    public static Figure CreateFrom(string input)
    {
        if (string.IsNullOrWhiteSpace(input))
            throw new ArgumentException("Input cannot be empty.");

        string[] tokens = input
            .Split(' ', StringSplitOptions.RemoveEmptyEntries);

        string figureType = tokens[0].ToLowerInvariant();
        string[] parameters = tokens[1..];

        if (!_registry.TryGetValue(figureType, out Func<string[], Figure>? creator))
            throw new ArgumentException($"Unknown figure type: {figureType}");

        return creator(parameters);
    }
}
