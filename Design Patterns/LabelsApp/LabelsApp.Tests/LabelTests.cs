using LabelsApp.Labels;
using LabelsApp.Utils;

namespace LabelsApp.Tests;

[TestFixture]
public class LabelTests
{
    [Test]
    public void SimpleLabel_ShouldReturnText()
    {
        var label = new SimpleLabel("Hello");
        Assert.That(label.GetText(), Is.EqualTo("Hello"));
    }

    [Test]
    public void RichLabel_ShouldStoreAndReturnText()
    {
        var label = new RichLabel("Hello", PresetColor.Red, 12, "Arial");

        Assert.That(label.GetText(), Is.EqualTo("Hello"));
        Assert.That(label.Color, Is.EqualTo(PresetColor.Red));
        Assert.That(label.FontName, Is.EqualTo("Arial"));
        Assert.That(label.FontSize, Is.EqualTo(12));
    }

    [Test]
    public void HelpLabel_ShouldReturnHelpText()
    {
        ILabel simple = new SimpleLabel("Content");
        var helpLabel = new HelpLabel(simple, "Help Info");

        Assert.That(helpLabel.GetText(), Is.EqualTo("Content"));
        Assert.That(helpLabel.GetHelpText(), Is.EqualTo("Help Info"));
    }

    [Test]
    public void CustomLabelProxy_ShouldReadFromConsoleOnce()
    {
        // Simulate user typing "User Input" then pressing Enter
        var input = new StringReader("User Input\n");
        Console.SetIn(input);

        var proxy = new CustomLabel(timeoutLimit: 5);

        // First call triggers ReadLine
        string result1 = proxy.GetText();

        // Second call should reuse value (would fail if it tried to read again, as Reader is empty)
        string result2 = proxy.GetText();

        Assert.That(result1, Is.EqualTo("User Input"));
        Assert.That(result2, Is.EqualTo("User Input"));
    }

    [Test]
    public void CustomLabelProxy_ShouldTimeoutAndAskForUpdate()
    {
        // Input sequence:
        // 1. "Initial" (First load)
        // ... (Calls 2 to timeout) ...
        // 3. "y" (Yes, update)
        // 4. "Updated" (New value)
        var input = new StringReader("Initial\ny\nUpdated\n");
        Console.SetIn(input);

        var proxy = new CustomLabel(timeoutLimit: 1); // Timeout after 1 request

        // Request 1: Reads "Initial"
        Assert.That(proxy.GetText(), Is.EqualTo("Initial"));

        // Request 2: Triggers Timeout -> User types 'y' -> User types "Updated"
        string result2 = proxy.GetText();
        Assert.That(result2, Is.EqualTo("Updated"));
    }
}