using LabelsApp.Utils;

namespace LabelsApp.Labels;

public class RichLabel : SimpleLabel
{
    public PresetColor Color { get; set; }
    public double FontSize { get; set; }
    public string FontName { get; set; }

    public RichLabel(string value,
        PresetColor color,
        double fontSize,
        string fontName) : base(value)
    {
        Color = color;
        FontSize = fontSize;
        FontName = fontName;
    }
}
