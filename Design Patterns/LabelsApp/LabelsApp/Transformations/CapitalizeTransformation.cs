namespace LabelsApp.Transformations;

public class CapitalizeTransformation : ITextTransformation
{
    public string Transform(string text)
    {
        if (string.IsNullOrWhiteSpace(text)) return text;

        char firstChar = text[0];

        if (!char.IsLetter(firstChar))
            return text;

        return char.ToUpper(firstChar) + text.Substring(1);
    }
}