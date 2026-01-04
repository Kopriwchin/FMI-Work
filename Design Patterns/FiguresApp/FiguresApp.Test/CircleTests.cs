using NUnit.Framework;

namespace FiguresApp.Tests;

[TestFixture]
public class CircleTests
{
    [Test]
    public void Constructor_ValidRadius_CreatesCircle()
    {
        var c = new Circle(5);
        Assert.That(c, Is.Not.Null);
    }

    [TestCase(0)]
    [TestCase(-5)]
    public void Constructor_NonPositiveRadius_ThrowsArgumentException(double radius)
    {
        Assert.That(() => new Circle(radius), Throws.ArgumentException);
    }

    [Test]
    public void Perimeter_CalculatesCorrectly()
    {
        var c = new Circle(10);
        double expected = 2 * Math.PI * 10;
        Assert.That(c.CalculatePerimeter(), Is.EqualTo(expected).Within(0.0001));
    }

    [Test]
    public void ToString_ReturnsCorrectFormat()
    {
        var c = new Circle(1.23);
        Assert.That(c.ToString(), Does.StartWith("circle"));
        Assert.That(c.ToString(), Does.Contain("1.23").Or.Contain("1,23"));
    }

    [Test]
    public void DeepClone_ReturnsIndependentCopy()
    {
        var original = new Circle(5);
        var clone = (Circle)original.DeepClone();

        Assert.That(clone, Is.Not.SameAs(original));
        Assert.That(clone.CalculatePerimeter(), Is.EqualTo(original.CalculatePerimeter()).Within(0.0001));
    }
}