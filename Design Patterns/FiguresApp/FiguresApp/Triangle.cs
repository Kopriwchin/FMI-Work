namespace FiguresApp;

public class Triangle : Figure
{
    private readonly double sideA, sideB, sideC;

    public Triangle(double a, double b, double c)
    {
        Validate(a, b, c);
        sideA = a; sideB = b; sideC = c;
    }

    public Triangle(string[] args)
    {
        if (args is null || args.Length != 3)
            throw new ArgumentException("Triangle requires 3 sides.");

        if (!double.TryParse(args[0], out double a) ||
            !double.TryParse(args[1], out double b) ||
            !double.TryParse(args[2], out double c))
            throw new InvalidCastException("Invalid numeric values.");

        Validate(a, b, c);
        sideA = a; sideB = b; sideC = c;
    }

    private void Validate(double a, double b, double c)
    {
        if (a <= 0 || b <= 0 || c <= 0)
            throw new ArgumentException("Sides must be positive.");

        if (a + b <= c || a + c <= b || b + c <= a)
            throw new ArgumentException("Triangle inequality violated (parsedSideA+parsedSideB>c).");
    }

    public override double CalculatePerimeter() => sideA + sideB + sideC;
    public override string ToString() => $"triangle {sideA:F2} {sideB:F2} {sideC:F2}";
    public override object DeepClone() => new Triangle(sideA, sideB, sideC);
}
