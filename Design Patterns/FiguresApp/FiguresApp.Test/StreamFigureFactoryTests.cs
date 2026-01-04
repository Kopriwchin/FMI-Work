using NUnit.Framework;
using FiguresApp;

namespace FiguresApp.Tests;

[TestFixture]
public class StreamFigureFactoryTests
{
    [Test]
    public void Create_ValidStream_ReturnsFiguresSequence()
    {
        // Setup a fake file in memory
        string fileContent = """
            triangle 3 4 5
            circle 10
            rectangle 2 3
            """;

        using var reader = new StringReader(fileContent);
        var factory = new StreamFigureFactory(reader);

        // Act
        var f1 = factory.Create();
        var f2 = factory.Create();
        var f3 = factory.Create();
        var f4 = factory.Create();

        // Assert
        Assert.That(f1, Is.InstanceOf<Triangle>());
        Assert.That(f2, Is.InstanceOf<Circle>());
        Assert.That(f3, Is.InstanceOf<Rectangle>());
        Assert.That(f4, Is.Null, "Should return null when stream ends");
    }

    [Test]
    public void Create_StreamWithEmptyLines_SkipsEmptyLines()
    {
        string fileContent = """
            circle 5
            
               
            circle 10
            """;

        using StringReader reader = new(fileContent);
        StreamFigureFactory factory = new(reader);

        Figure? firstFigure = factory.Create();
        Figure? secondFigure = factory.Create();

        Assert.That(firstFigure, Is.Not.Null);
        Assert.That(firstFigure!.CalculatePerimeter(), Is.EqualTo(10 * Math.PI).Within(0.001));

        Assert.That(secondFigure, Is.Not.Null);
        Assert.That(secondFigure!.CalculatePerimeter(), Is.EqualTo(20 * Math.PI).Within(0.001));
    }

    [Test]
    public void Create_StreamWithInvalidLines_SkipsThemRecursively()
    {
        string fileContent = """
            BAD_DATA
            circle 5
            """;

        using var reader = new StringReader(fileContent);
        var factory = new StreamFigureFactory(reader);

        var f1 = factory.Create();

        Assert.That(f1, Is.Not.Null);
        Assert.That(f1, Is.InstanceOf<Circle>());
    }

    [Test]
    public void Create_StreamWithExitCommand_StopsReading()
    {
        string fileContent = """
        triangle 3 4 5
        EXIT
        circle 10
        """;

        using var reader = new StringReader(fileContent);
        var factory = new StreamFigureFactory(reader);

        var f1 = factory.Create();
        Assert.That(f1, Is.InstanceOf<Triangle>());

        var f2 = factory.Create();
        Assert.That(f2, Is.Null);
    }
}