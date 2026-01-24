using LabelsApp.Transformations;

namespace LabelsApp;

public class TrimLeftTransformation : ITextTransformation
{
    public string Transform(string text) => text.TrimStart();
}
