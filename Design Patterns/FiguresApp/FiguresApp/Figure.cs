namespace FiguresApp;

public abstract class Figure : IDeepCloneable
{
    public abstract double CalculatePerimeter();
    public override abstract string ToString();
    public abstract object DeepClone();
}
