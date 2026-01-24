namespace LabelsApp.Transformations;

public class DecorateTransformation : ITextTransformation
{
    public string Transform(string text) => $"-={{ {text} }}=-";
}
