using LabelsApp.Transformations;

namespace LabelsApp;

public class TrimRightTransformation : ITextTransformation
{
    public string Transform(string text) => text.TrimEnd();
}
