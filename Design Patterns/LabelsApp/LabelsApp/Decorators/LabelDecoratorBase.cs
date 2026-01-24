using LabelsApp.Labels;

namespace LabelsApp.Decorators;

public class LabelDecoratorBase : ILabel
{
    private ILabel _label;

    public LabelDecoratorBase(ILabel label) => _label = label;

    public virtual string GetText() => _label.GetText();

    public static ILabel RemoveDecoratorFrom(ILabel label, LabelDecoratorBase decoratorToRemove)
    {
        if (label is LabelDecoratorBase decorator)
            return decorator.RemoveDecorator(decoratorToRemove);
        
        return label;
    }

    public virtual ILabel RemoveDecorator(LabelDecoratorBase decoratorToRemove)
    {
        if (this.Equals(decoratorToRemove))
            return _label;

        if (_label is LabelDecoratorBase childDecorator)
            _label = childDecorator.RemoveDecorator(decoratorToRemove);

        return this;
    }
}
