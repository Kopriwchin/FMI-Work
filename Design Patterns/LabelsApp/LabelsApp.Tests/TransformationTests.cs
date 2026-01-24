using NUnit.Framework;
using LabelsApp.Transformations;

namespace LabelsApp.Tests;

[TestFixture]
public class TransformationTests
{
    [Test]
    public void Capitalize_ShouldCapitalizeFirstLetter()
    {
        var transformation = new CapitalizeTransformation();
        Assert.That(transformation.Transform("some_text"), Is.EqualTo("Some_text"));
    }

    [Test]
    public void Capitalize_ShouldIgnoreNonLetters()
    {
        var transformation = new CapitalizeTransformation();
        Assert.That(transformation.Transform("_text"), Is.EqualTo("_text"));
    }

    [Test]
    public void TrimLeft_ShouldRemoveLeadingWhitespace()
    {
        var transformation = new TrimLeftTransformation();
        Assert.That(transformation.Transform("   abc"), Is.EqualTo("abc"));
        Assert.That(transformation.Transform("_some_text"), Is.EqualTo("_some_text"));
    }

    [Test]
    public void TrimRight_ShouldRemoveTrailingWhitespace()
    {
        var transformation = new TrimRightTransformation();
        Assert.That(transformation.Transform("abc   "), Is.EqualTo("abc"));
        Assert.That(transformation.Transform("some text"), Is.EqualTo("some text"));
    }

    [Test]
    public void NormalizeSpace_ShouldCollapseMultipleSpaces()
    {
        var transformation = new NormalizeSpaceTransformation();
        Assert.That(transformation.Transform("some   text"), Is.EqualTo("some text"));
        Assert.That(transformation.Transform("a  b c"), Is.EqualTo("a b c"));
    }

    [Test]
    public void Decorate_ShouldAddBrackets()
    {
        var transformation = new DecorateTransformation();
        Assert.That(transformation.Transform("abc"), Is.EqualTo("-={ abc }=-"));
    }

    [Test]
    public void Censor_ShouldReplaceSpecificWordWithAsterisks()
    {
        var transformation = new CensorTransformation("abc");
        string input = "abc_def_abcdef";
        string expected = "***_def_***def";

        Assert.That(transformation.Transform(input), Is.EqualTo(expected));
    }

    [Test]
    public void Replace_ShouldReplaceText()
    {
        var transformation = new ReplaceTransformation("abc", "d");
        Assert.That(transformation.Transform("abc_abcdef"), Is.EqualTo("d_ddef"));
    }
}