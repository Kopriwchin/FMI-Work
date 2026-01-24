using System.Text;

namespace LabelsApp.Transformations;

public class NormalizeSpaceTransformation : ITextTransformation
{
    public string Transform(string text)
    {
        StringBuilder newString = new();

        bool previousCharacterSpace = false;
        foreach (char character in text)
        {
            if (previousCharacterSpace && Char.IsWhiteSpace(character))
                continue;

            if (Char.IsWhiteSpace(character))
            {
                newString.Append(character);
                previousCharacterSpace = true;
                continue;
            }
            else
            {
                newString.Append(character);
                previousCharacterSpace = false;
            }
            
        }

        return newString.ToString();
    }
}
