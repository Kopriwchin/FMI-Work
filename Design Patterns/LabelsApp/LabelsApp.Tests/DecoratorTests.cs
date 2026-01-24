using LabelsApp.Decorators;
using LabelsApp.Labels;
using LabelsApp.Transformations;

namespace LabelsApp.Tests;

[TestFixture]
public class DecoratorTests
{
    [Test]
    public void TextTransformationDecorator_ShouldApplyTransformation()
    {
        ILabel label = new SimpleLabel("test");
        label = new TextTransformationDecorator(label, new CapitalizeTransformation());

        Assert.That(label.GetText(), Is.EqualTo("Test"));
    }

    [Test]
    public void ChainedDecorators_ShouldApplyOrderCorrectly()
    {
        ILabel label = new SimpleLabel("abc");

        // Chain: Capitalize -> Decorate
        // 1. Capitalize("abc") -> "Abc"
        // 2. Decorate("Abc") -> "-={ Abc }=-"
        label = new TextTransformationDecorator(label, new CapitalizeTransformation());
        label = new TextTransformationDecorator(label, new DecorateTransformation());

        Assert.That(label.GetText(), Is.EqualTo("-={ Abc }=-"));
    }

    [Test]
    public void RemoveDecorator_ShouldRemoveSpecificInstance()
    {
        ILabel label = new SimpleLabel("test");

        var censorA = new CensorTransformation("a");
        var censorB = new CensorTransformation("b");

        label = new TextTransformationDecorator(label, censorA);
        label = new TextTransformationDecorator(label, censorB);

        var toRemove = new TextTransformationDecorator(null, censorA);
        label = LabelDecoratorBase.RemoveDecoratorFrom(label, toRemove);

        // Simpler check: Remove outer decorator
        Assert.That(label, Is.InstanceOf<TextTransformationDecorator>());

        // Verify the remaining transformation is censorB
        var remainingDecorator = (TextTransformationDecorator)label;
        Assert.That(remainingDecorator.Transformation, Is.EqualTo(censorB));
    }

    [Test]
    public void CyclingDecorator_ShouldCycleThroughTransformations()
    {
        ILabel label = new SimpleLabel("abc");
        var transforms = new List<ITextTransformation>
        {
            new CapitalizeTransformation(), // Returns "Abc"
            new DecorateTransformation()    // Returns "-={ abc }=-"
        };

        var cyclicLabel = new CyclingTransformationsDecorator(label, transforms);

        Assert.That(cyclicLabel.GetText(), Is.EqualTo("Abc"));           // 1st Call
        Assert.That(cyclicLabel.GetText(), Is.EqualTo("-={ abc }=-"));   // 2nd Call
        Assert.That(cyclicLabel.GetText(), Is.EqualTo("Abc"));           // 3rd Call (Wrap around)
    }

    [Test]
    public void RandomDecorator_ShouldReturnResultFromList()
    {
        // To test random strictly is hard, but we can verify it doesn't crash 
        // and returns a valid transformation result.
        ILabel label = new SimpleLabel("abc");
        var transforms = new List<ITextTransformation>
        {
            new DecorateTransformation()
        };

        var randomLabel = new RandomTransformationDecorator(label, transforms);

        Assert.That(randomLabel.GetText(), Is.EqualTo("-={ abc }=-"));
    }
}