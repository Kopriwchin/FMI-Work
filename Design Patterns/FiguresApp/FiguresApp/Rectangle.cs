namespace FiguresApp;

public class Rectangle : Figure
{
    private readonly double sideA, sideB;

    public Rectangle(double sideA, double sideB)
    {
        Validate(sideA, sideB);
        this.sideA = sideA;
        this.sideB = sideB;
    }

    public Rectangle(string[] args)
    {
        if (args is null)
            throw new ArgumentException("Invalid input arguments!");

        if (args.Length != 2)
            throw new ArgumentException("Rectangle requires 2 sides.");

        if (!double.TryParse(args[0], out double parsedSideA)
            || !double.TryParse(args[1], out double parsedSideB))
            throw new ArgumentException("Invalid numeric values.");

        Validate(parsedSideA, parsedSideB);
        this.sideA = parsedSideA;
        this.sideB = parsedSideB;
    }

    private void Validate(double a, double b)
    {
        if (a <= 0 || b <= 0)
            throw new ArgumentException("Sides must be positive.");
    }

    public override double CalculatePerimeter() => (sideA + sideB) * 2;

    public override string ToString() => $"rectangle {sideA:F2} {sideB:F2}";

    public override object DeepClone() => new Rectangle(sideA, sideB);
}
