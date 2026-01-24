namespace LabelsApp.Transformations;

public class CompositeTransformation : ITextTransformation
{
    private readonly List<ITextTransformation> _transformations;

    public CompositeTransformation()
        => _transformations = [];

    public void AddTransformation(ITextTransformation transformation)
        => _transformations.Add(transformation);

    public string Transform(string text)
    {
        string result = text;
        
        foreach (ITextTransformation transformation in _transformations)
            result = transformation.Transform(result);
        
        return result;
    }
}