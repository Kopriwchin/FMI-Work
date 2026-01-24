using LabelsApp.Transformations;

namespace LabelsApp.Tests;

[TestFixture]
public class CompositeTests
{
    [Test]
    public void Composite_ShouldApplyTransformationsInSequence()
    {
        var composite = new CompositeTransformation();

        // Sequence: Replace(abc, def) -> Capitalize
        // "abc" -> "def" -> "Def"
        composite.AddTransformation(new ReplaceTransformation("abc", "def"));
        composite.AddTransformation(new CapitalizeTransformation());

        string result = composite.Transform("abc");
        Assert.That(result, Is.EqualTo("Def"));
    }

    [Test]
    public void Composite_OrderMatters()
    {
        // Case 1: Replace then Capitalize
        var comp1 = new CompositeTransformation();
        comp1.AddTransformation(new ReplaceTransformation("abc", "def"));
        comp1.AddTransformation(new CapitalizeTransformation());
        Assert.That(comp1.Transform("abc_abc"), Is.EqualTo("Def_def"));

        // Case 2: Capitalize then Replace
        // "abc_abc" -> "Abc_abc" -> "Abc_abc" (Replace "abc" fails on "Abc")
        var comp2 = new CompositeTransformation();
        comp2.AddTransformation(new CapitalizeTransformation());
        comp2.AddTransformation(new ReplaceTransformation("abc", "def"));

        Assert.That(comp2.Transform("abc_abc"), Is.EqualTo("Abc_def"));
    }
}