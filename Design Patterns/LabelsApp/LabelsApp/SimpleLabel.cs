namespace LabelsApp;

public class SimpleLabel : ILabel
{
    public string value;
    
    public SimpleLabel(string value)
        => this.value = value;
    
    public string GetText()
        => value;
}
