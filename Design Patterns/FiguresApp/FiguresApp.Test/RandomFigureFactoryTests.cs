using NUnit.Framework;

namespace FiguresApp.Tests;

[TestFixture]
public class RandomFigureFactoryTests
{
    [Test]
    public void Create_AlwaysReturnsValidFigure()
    {
        RandomFigureFactory factory = new();

        // Generate 100 figures to ensure stability
        for (int i = 0; i < 100; i++)
        {
            Figure fig = factory.Create();

            Assert.That(fig, Is.Not.Null);
            Assert.That(fig.CalculatePerimeter(), Is.GreaterThan(0));

            // Ensure no exception is thrown when calling ToString
            Assert.That(fig.ToString(), Is.Not.Null.And.Not.Empty);
        }
    }
}