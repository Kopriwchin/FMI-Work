using NUnit.Framework;

namespace FiguresApp.Tests;

[TestFixture]
public class TriangleTests
{
    [Test]
    public void Constructor_ValidSides_CreatesTriangle()
    {
        var t = new Triangle(3, 4, 5);
        Assert.That(t, Is.Not.Null);
    }

    [TestCase(0, 4, 5)]
    [TestCase(3, 0, 5)]
    [TestCase(3, 4, 0)]
    [TestCase(-3, 4, 5)]
    public void Constructor_NonPositiveSides_ThrowsArgumentException(double a, double b, double c)
    {
        Assert.That(() => new Triangle(a, b, c), Throws.ArgumentException.With.Message.Contains("positive"));
    }

    [TestCase(1, 2, 3, Description = "1+2 == 3 (Degenerate)")]
    [TestCase(1, 2, 10, Description = "1+2 < 10")]
    [TestCase(10, 2, 2, Description = "2+2 < 10")]
    public void Constructor_InvalidGeometry_ThrowsArgumentException(double a, double b, double c)
    {
        Assert.That(() => new Triangle(a, b, c), Throws.ArgumentException.With.Message.Contains("inequality"));
    }

    [Test]
    public void Perimeter_ValidSides_ReturnsSum()
    {
        var t = new Triangle(10, 20, 25); // 10+20 > 25 OK
        Assert.That(t.CalculatePerimeter(), Is.EqualTo(55));
    }

    [Test]
    public void ToString_ReturnsCorrectFormat()
    {
        var t = new Triangle(10.5, 20.1, 25.0);
        var str = t.ToString();

        Assert.That(str, Does.StartWith("triangle"));
        Assert.That(str, Does.Contain("10.5").Or.Contain("10,5"));
        Assert.That(str, Does.Contain("20.1").Or.Contain("20,1"));
    }

    [Test]
    public void DeepClone_ReturnsIndependentCopy()
    {
        var original = new Triangle(3, 4, 5);
        var clone = (Triangle)original.DeepClone();

        Assert.That(clone, Is.Not.SameAs(original));
        Assert.That(clone.CalculatePerimeter(), Is.EqualTo(original.CalculatePerimeter()));
    }
}