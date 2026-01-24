namespace LabelsApp.Labels;

public class SimpleLabel : ILabel
{
    public string Value { get; set; }

    public SimpleLabel(string value) => Value = value;

    public string GetText() => Value;
}
