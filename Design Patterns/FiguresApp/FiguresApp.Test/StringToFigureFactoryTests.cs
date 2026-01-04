using NUnit.Framework;

namespace FiguresApp.Tests;

[TestFixture]
public class StringToFigureFactoryTests
{
    [Test]
    public void CreateFrom_ValidTriangleString_ReturnsTriangle()
    {
        var fig = StringToFigureFactory.CreateFrom("triangle 3 4 5");
        Assert.That(fig, Is.InstanceOf<Triangle>());
        Assert.That(fig.CalculatePerimeter(), Is.EqualTo(12));
    }

    [Test]
    public void CreateFrom_ValidCircleString_ReturnsCircle()
    {
        var fig = StringToFigureFactory.CreateFrom("circle 5");
        Assert.That(fig, Is.InstanceOf<Circle>());
    }

    [Test]
    public void CreateFrom_ValidRectangleString_ReturnsRectangle()
    {
        var fig = StringToFigureFactory.CreateFrom("rectangle 4 5");
        Assert.That(fig, Is.InstanceOf<Rectangle>());
        Assert.That(fig.CalculatePerimeter(), Is.EqualTo(18));
    }

    [Test]
    public void CreateFrom_UnknownType_ThrowsException()
    {
        Assert.That(() => StringToFigureFactory.CreateFrom("hexagon 5"), Throws.ArgumentException);
    }

    [TestCase("")]
    [TestCase("   ")]
    public void CreateFrom_EmptyString_ThrowsException(string input)
    {
        Assert.That(() => StringToFigureFactory.CreateFrom(input), Throws.ArgumentException);
    }

    [TestCase("triangle 1 2")] // Missing side
    [TestCase("circle")] // Missing radius
    [TestCase("rectangle 1 2 3")] // Too many parameters (if strict) or ignored
    public void CreateFrom_InvalidParameterCount_ThrowsException(string input)
    {
        Assert.That(() => StringToFigureFactory.CreateFrom(input), Throws.ArgumentException);
    }

    [TestCase("circle abc")]
    [TestCase("triangle 1 2 three")]
    public void CreateFrom_NonNumericParameters_ThrowsException(string input)
    {
        Assert.That(() => StringToFigureFactory.CreateFrom(input), Throws.TypeOf<InvalidCastException>().Or.TypeOf<ArgumentException>());
    }
}