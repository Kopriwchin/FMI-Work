namespace FiguresApp;

public class RandomFigureFactory : IFigureFactory
{
    private readonly Random _rng = new();

    public Figure Create()
    {
        // 0=Triangle, 1=Circle, 2=Rectangle
        int type = _rng.Next(0, 3);

        switch (type)
        {
            case 0: // Triangle
                int a = _rng.Next(10, 50);
                int b = _rng.Next(10, 50);

                int minC = Math.Abs(a - b) + 1;

                int maxC = a + b;

                int c = _rng.Next(minC, maxC);

                return new Triangle(a, b, c);

            case 1: // Circle
                return new Circle(_rng.Next(1, 50));

            case 2: // Rectangle
                return new Rectangle(_rng.Next(1, 50), _rng.Next(1, 50));

            default:
                throw new InvalidOperationException("Random generation failed."); // Normally - not possible
        }
    }
}