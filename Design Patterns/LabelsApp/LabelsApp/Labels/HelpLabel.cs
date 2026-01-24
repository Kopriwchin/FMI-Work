namespace LabelsApp.Labels;

public class HelpLabel : ILabel
{
    private readonly ILabel _label;
    private readonly string _helpText;

    public HelpLabel(ILabel label, string helpText)
    {
        _label = label;
        _helpText = helpText;
    }

    public string GetText() => _label.GetText();

    public string GetHelpText() => _helpText;
}