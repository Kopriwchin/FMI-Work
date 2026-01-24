using LabelsApp.Decorators;
using LabelsApp.Labels;
using LabelsApp.Transformations;

namespace LabelsApp;

public class Program
{
    public static void Main(string[] args)
    {
        Console.WriteLine("--- Step 9: Flyweight Pattern Verification ---");

        var factory = new CensorTransformationFactory();

        // TEST 1: Short word (<= 4 chars) -> Should be cached
        Console.WriteLine("\nRequesting 'abc' (1st time):");
        var censor1 = factory.GetCensorTransformation("abc");

        Console.WriteLine("Requesting 'abc' (2nd time):");
        var censor2 = factory.GetCensorTransformation("abc");

        bool areSameInstance = object.ReferenceEquals(censor1, censor2);
        Console.WriteLine($"Are 'abc' instances the same object? {areSameInstance}"); // Expected: True

        // TEST 2: Long word (> 4 chars) -> Should NOT be cached
        Console.WriteLine("\nRequesting 'hello' (1st time):");
        var censor3 = factory.GetCensorTransformation("hello");

        Console.WriteLine("Requesting 'hello' (2nd time):");
        var censor4 = factory.GetCensorTransformation("hello");

        bool areSameInstanceLong = object.ReferenceEquals(censor3, censor4);
        Console.WriteLine($"Are 'hello' instances the same object? {areSameInstanceLong}"); // Expected: False


        // TEST 3: Using them in a real label
        ILabel label = new SimpleLabel("abc_hello_abc");
        label = new TextTransformationDecorator(label, censor1); // Use cached 'abc'
        label = new TextTransformationDecorator(label, censor3); // Use new 'hello'

        LabelPrinter.Print(label); // Output: ***_*****_***
    }
}