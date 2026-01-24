using LabelsApp.Labels;
using LabelsApp.Transformations;

namespace LabelsApp.Decorators;

public class TextTransformationDecorator : LabelDecoratorBase
{
    private readonly ITextTransformation _transformation;

    public ITextTransformation Transformation => _transformation;


    public TextTransformationDecorator(ILabel label, ITextTransformation transformation)
        : base(label) => _transformation = transformation;

    public override string GetText() => _transformation.Transform(base.GetText());

    public override bool Equals(object? obj)
    {
        if (obj is TextTransformationDecorator other)
            return this._transformation.Equals(other._transformation);

        return false;
    }

    public override int GetHashCode() => _transformation.GetHashCode();
}
