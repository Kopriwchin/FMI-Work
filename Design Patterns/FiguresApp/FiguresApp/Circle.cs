namespace FiguresApp;

public class Circle : Figure
{
    private readonly double radius;

    public Circle(double radius)
    {
        Validate(radius);
        this.radius = radius;
    }

    public Circle(string[] args)
    {
        if (args is null)
            throw new ArgumentException("Invalid input arguments!");

        if (args.Length != 1)
            throw new ArgumentException("Circle requires 1 parameter (radius).");

        if (!double.TryParse(args[0], out double parsedRadius))
            throw new ArgumentException("Invalid numeric value for radius.");

        Validate(parsedRadius);
        this.radius = parsedRadius;
    }

    private void Validate(double r)
    {
        if (r <= 0)
            throw new ArgumentException("Radius must be positive.");
    }

    public override double CalculatePerimeter() => 2 * Math.PI * radius;
    public override string ToString() => $"circle {radius:F2}";
    public override object DeepClone() => new Circle(radius);
}
