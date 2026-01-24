namespace LabelsApp.Transformations;

public class ReplaceTransformation : ITextTransformation
{
    private readonly string _searchText;
    private readonly string _replaceText;

    public ReplaceTransformation(string searchText, string replaceText)
    {
        _searchText = searchText;
        _replaceText = replaceText;
    }

    public string Transform(string text)
    {
        if (string.IsNullOrEmpty(text))
            return text;

        return text.Replace(_searchText, _replaceText);
    }
}
