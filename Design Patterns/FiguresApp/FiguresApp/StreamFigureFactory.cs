using FiguresApp;

public class StreamFigureFactory : IFigureFactory
{
    private readonly TextReader _reader;

    public StreamFigureFactory(TextReader reader)
        => _reader = reader;

    public Figure? Create()
    {
        while (true)
        {
            string? line = _reader.ReadLine();

            if (line is null) // Handle standard EOF (Ctrl+Z / Ctrl+D)
                return null;

            if (string.IsNullOrWhiteSpace(line))
                continue;

            if (line.Trim().Equals("exit", StringComparison.OrdinalIgnoreCase))
                return null;

            try
            {
                return StringToFigureFactory.CreateFrom(line);
            }
            catch (InvalidCastException castEx)
            {
                Console.WriteLine(castEx.Message);
                continue;
            }
            catch (ArgumentException argEx)
            {
                Console.WriteLine(argEx.Message);
                continue;
            }
            catch
            {
                continue;
            }
        }
    }
}