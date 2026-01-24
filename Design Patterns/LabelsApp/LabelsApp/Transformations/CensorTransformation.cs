namespace LabelsApp.Transformations;

public class CensorTransformation : ITextTransformation
{
    private readonly string _wordToCensor;

    public CensorTransformation(string wordToCensor)
        => _wordToCensor = wordToCensor;

    public string Transform(string text)
    {
        if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(_wordToCensor))
            return text;

        string replacement = new('*', _wordToCensor.Length);

        return text.Replace(_wordToCensor, replacement);
    }

    public override bool Equals(object? obj)
    {
        if (obj is CensorTransformation other)
            return this._wordToCensor == other._wordToCensor;
        
        return false;
    }

    public override int GetHashCode() => _wordToCensor.GetHashCode();
}
