using NUnit.Framework;
using FiguresApp;

namespace FiguresApp.Tests;

[TestFixture]
public class RectangleTests
{
    [Test]
    public void Constructor_ValidSides_CreatesRectangle()
    {
        var r = new Rectangle(5, 10);
        Assert.That(r, Is.Not.Null);
    }

    [TestCase(0, 10)]
    [TestCase(5, 0)]
    [TestCase(-5, 10)]
    public void Constructor_NonPositiveSides_ThrowsArgumentException(double width, double height)
    {
        Assert.That(() => new Rectangle(width, height), Throws.ArgumentException);
    }

    [Test]
    public void Perimeter_CalculatesCorrectly()
    {
        var r = new Rectangle(5, 10);
        Assert.That(r.CalculatePerimeter(), Is.EqualTo(30));
    }

    [Test]
    public void ToString_ReturnsCorrectFormat()
    {
        var r = new Rectangle(5, 10);
        var str = r.ToString();
        Assert.That(str, Does.StartWith("rectangle"));
        Assert.That(str, Does.Contain("5"));
        Assert.That(str, Does.Contain("10"));
    }

    [Test]
    public void DeepClone_ReturnsIndependentCopy()
    {
        var original = new Rectangle(10, 20);
        var clone = (Rectangle)original.DeepClone();

        Assert.That(clone, Is.Not.SameAs(original));
        Assert.That(clone.CalculatePerimeter(), Is.EqualTo(original.CalculatePerimeter()));
    }
}