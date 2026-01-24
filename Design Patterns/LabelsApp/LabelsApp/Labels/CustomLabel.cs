namespace LabelsApp.Labels;

public class CustomLabel : ILabel
{
    private string? _value;
    private readonly int _timeoutLimit;
    private int _requestCount;

    public CustomLabel(int timeoutLimit)
    {
        _timeoutLimit = timeoutLimit;
        _requestCount = 0;
        _value = null;
    }

    public string GetText()
    {
        if (_value == null)
        {
            Console.Write("Enter label text: ");
            _value = Console.ReadLine() ?? "";
        }

        _requestCount++;

        if (_requestCount > _timeoutLimit)
        {
            Console.WriteLine($"\n[System] Timeout reached ({_timeoutLimit} requests).");
            Console.Write("Do you want to update the label text? (y/n): ");
            string? response = Console.ReadLine();

            if (response?.ToLower() == "y")
            {
                Console.Write("Enter new text: ");
                _value = Console.ReadLine() ?? "";
            }

            _requestCount = 1;
        }

        return _value;
    }
}