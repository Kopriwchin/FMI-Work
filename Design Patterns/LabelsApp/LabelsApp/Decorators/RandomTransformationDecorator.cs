using LabelsApp.Labels;
using LabelsApp.Transformations;

namespace LabelsApp.Decorators;

public class RandomTransformationDecorator : LabelDecoratorBase
{
    private readonly List<ITextTransformation> _transformations;
    private readonly Random _random;

    public RandomTransformationDecorator(ILabel label, List<ITextTransformation> transformations)
        : base(label)
    {
        _transformations = transformations;
        _random = new Random(); 
    }

    public override string GetText()
    {
        string text = base.GetText();

        if (_transformations.Count == 0)
            return text;

        int randomIndex = _random.Next(_transformations.Count);
        return _transformations[randomIndex].Transform(text);
    }
}