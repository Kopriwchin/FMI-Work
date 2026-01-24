using LabelsApp.Transformations;

namespace LabelsApp.Tests;

[TestFixture]
public class FlyweightTests
{
    [Test]
    public void Factory_ShouldReuseObjectsForShortWords()
    {
        var factory = new CensorTransformationFactory();

        var t1 = factory.GetCensorTransformation("abc");
        var t2 = factory.GetCensorTransformation("abc");

        // Verify they are the EXACT same object in memory
        Assert.That(object.ReferenceEquals(t1, t2), Is.True);
    }

    [Test]
    public void Factory_ShouldCreateNewObjectsForLongWords()
    {
        var factory = new CensorTransformationFactory();

        var t1 = factory.GetCensorTransformation("hello");
        var t2 = factory.GetCensorTransformation("hello");

        // Verify they are DIFFERENT objects
        Assert.That(object.ReferenceEquals(t1, t2), Is.False);
    }
}