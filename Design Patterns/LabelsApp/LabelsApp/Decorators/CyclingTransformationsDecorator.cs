using LabelsApp.Labels;
using LabelsApp.Transformations;

namespace LabelsApp.Decorators;

public class CyclingTransformationsDecorator : LabelDecoratorBase
{
    private int _index;
    private readonly List<ITextTransformation> _transformations;

    public CyclingTransformationsDecorator(ILabel label, List<ITextTransformation> transformations)
        : base(label)
    {
        _index = 0;
        _transformations = transformations;
    }

    public override string GetText()
    {
        string text = base.GetText();

        if (!_transformations.Any())
            return text;

        string result = _transformations[_index].Transform(text);

        _index = (_index + 1) % _transformations.Count;

        return result;
    }
}
